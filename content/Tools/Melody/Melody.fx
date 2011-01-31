/***************************************************************************************
	
    Copyright (C) NVIDIA Corporation 2003

    TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED
    *AS IS* AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS
    OR IMPLIED, INCLUDING, BUT NOT LIMITED fxOffset, IMPLIED WARRANTIES OF MERCHANTABILITY
    AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS
    BE LIABLE FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES
    WHATSOEVER (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
    BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
    ARISING OUT OF THE USE OF OR INABILITY fxOffset USE THIS SOFTWARE, EVEN IF NVIDIA HAS
    BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

*****************************************************************************************/
 

#define NORMAL_MAP_FP 0

float  fxScale = 2; 
float  fxOffset = 1; 

static const float4 vOne = float4(1, 1, 1, 1);

// transformations

float4x4 Projection : PROJECTION;
float4x4 World      : WORLD;
float4x4 View       : VIEW;


// light direction (view space)
float3 ConstantColor = float3(0, 0, 1);

float3 fxLightDir <  string UIDirectional = "Light Direction"; > = {0.577, -0.577, 0.577};
float3 fxLightLight <  string UIDirectional = "Light Direction"; > = {0.577, -0.577, 0.577};
float  fxLightEnable = 1;
float  fxDiffuseEnable = 1; // base color
float  fxSpecEnable = 1; // base color
float  fxTextureEnable = 1; // multiply texture color
float  fxNormalMapForLightingEnable = 0; // for normal map or vertex
float  fxNormalMapIsTangentSpace = 0; // 
texture fxDecalTexture;
texture fxLocalNormalMapTexture;
texture fxObjectNormalMapTexture;



// light intensity
float4 I_a = { 0.3f, 0.3f, 0.3f, 1.0f };    // ambient
float4 I_d = { 1.0f, 1.0f, 1.0f, 1.0f };    // diffuse
float4 I_s = { 0.6f, 0.6f, 0.6f, 1.0f };    // specular

// material reflectivity
//float4 k_a = { 0.2f, 0.2f, 0.2f, 1.0f };    // ambient
//float4 k_d = { 1.0f, 0.7f, 0.2f, 1.0f };    // diffuse
//float4 k_s = { 1.0f, 1.0f, 1.0f, 1.0f };    // specular

float4 k_a = { 0.0f, 0.0f, 0.0f, 0.0f };    // ambient
//float4 k_d = { 0.0f, 0.0f, 0.0f, 0.0f };    // diffuse
float4 k_d = { 0.0f, 0.0f, 0.0f, 0.0f };    // diffuse
float4 k_s = { 0.0f, 0.0f, 0.0f, 0.0f };    // specular

int    k_n   = 64;                            // power


float3x3 invert(float3x3 a)
{
    float fDetInv = 
        a[0][0] * ( a[1][1] * a[2][2] - a[1][2] * a[2][1] ) -
        a[0][1] * ( a[1][0] * a[2][2] - a[1][2] * a[2][0] ) +
        a[0][2] * ( a[1][0] * a[2][1] - a[1][1] * a[2][0] );

    float3x3 b;

    fDetInv = 1.0 /fDetInv;
    b[0][0] =  fDetInv * ( a[1][1] * a[2][2] - a[1][2] * a[2][1] );
    b[0][1] = -fDetInv * ( a[0][1] * a[2][2] - a[0][2] * a[2][1] );
    b[0][2] =  fDetInv * ( a[0][1] * a[1][2] - a[0][2] * a[1][1] );

    b[1][0] = -fDetInv * ( a[1][0] * a[2][2] - a[1][2] * a[2][0] );
    b[1][1] =  fDetInv * ( a[0][0] * a[2][2] - a[0][2] * a[2][0] );
    b[1][2] = -fDetInv * ( a[0][0] * a[1][2] - a[0][2] * a[1][0] );

    b[2][0] =  fDetInv * ( a[1][0] * a[2][1] - a[1][1] * a[2][0] );
    b[2][1] = -fDetInv * ( a[0][0] * a[2][1] - a[0][1] * a[2][0] );
    b[2][2] =  fDetInv * ( a[0][0] * a[1][1] - a[0][1] * a[1][0] );

    return b; 
} 



float3 p0;
float3 p1;
float3 p2;
float3 calc_bary(float3 p)
{
    double denomInv = -(p0.z*p1.y*p2.x) + p0.y*p1.z*p2.x + p0.z*p1.x*p2.y - p0.x*p1.z*p2.y - p0.y*p1.x*p2.z + p0.x*p1.y*p2.z;

    denomInv = 1.0 /  denomInv;

    float3 bary;
    bary[0] = -(p1.z*p2.y*p.x - p1.y*p2.z*p.x - p1.z*p2.x*p.y + p1.x*p2.z*p.y + p1.y*p2.x*p.z - p1.x*p2.y*p.z)* denomInv;
    bary[1] = -(-(p0.z*p2.y*p.x) + p0.y*p2.z*p.x + p0.z*p2.x*p.y - p0.x*p2.z*p.y - p0.y*p2.x*p.z + p0.x*p2.y*p.z) * denomInv;
    bary[2] = -(p0.z*p1.y*p.x - p0.y*p1.z*p.x - p0.z*p1.x*p.y + p0.x*p1.z*p.y + p0.y*p1.x*p.z - p0.x*p1.y*p.z) * denomInv;
    
    return bary;

}   


struct VS_OUTPUT
{
    float4 Pos  : POSITION;
    float3 Diff : COLOR0;
    float3 Spec : COLOR1;
    
    float2 Tex0 : TEXCOORD0;               
    float2 Tex1 : TEXCOORD1;               
    
    float3 Tex2 : TEXCOORD2;               // 
    float3 Tex3 : TEXCOORD3;               // 
    float3 Tex4 : TEXCOORD4;               // 
    float3 Tex5 : TEXCOORD5;               // 
    float3 Tex6 : TEXCOORD6;               // 
    float3 Tex7 : TEXCOORD7;
};


#define VERTEX_INPUT                                 \
    float3 Pos  : POSITION,                          \
    float3 Diffuse : COLOR ,                         \
                                                     \
    float2 DecalTextureCoords : TEXCOORD0,           \
    float2 NormalMapCoords : TEXCOORD1,              \
                                                     \
    float3 Tangent : TEXCOORD2,                     \
    float3 BiNormal   : TEXCOORD3,                  \
    float3 Normal : TEXCOORD4 ,                      \
    float3 p   : TEXCOORD5                           \
   




float invTriArea;

float area2D(float2 a, float2 b, float2 c)
{
    return ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)) * 0.5;
}
 
  

// samplers
sampler DecalTextureSampler = sampler_state 
{
    texture = <fxDecalTexture>;
    AddressU  = WRAP;        
    AddressV  = WRAP;
    AddressW  = WRAP;
    //MIPFILTER = POINT;
    //MINFILTER = POINT;
    //MAGFILTER = POINT;
};

sampler LocalNormalMapSampler = sampler_state 
{
    texture = <fxLocalNormalMapTexture>;
    AddressU  = WRAP;        
    AddressV  = WRAP;
    AddressW  = WRAP;
    //MIPFILTER = POINT;
    //MINFILTER = POINT;
    //MAGFILTER = POINT;
};


sampler ObjectNormalMapSampler = sampler_state 
{
    texture = <fxObjectNormalMapTexture>;
    AddressU  = WRAP;        
    AddressV  = WRAP;
    AddressW  = WRAP;
    //MIPFILTER = POINT;
    //MINFILTER = POINT;
    //MAGFILTER = POINT;
};




/*////////////////////////////////////////////////////

  Diffuse color - DiffuseEnable
  Lighting - LightEnable
  Decal Texture - Texture Enable

*/


VS_OUTPUT DiffuseColorVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)
                         // view direction (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)

    Out.Diff = Diffuse; 
    
    return Out;
}


float4 DiffuseColorPS(VS_OUTPUT In) : COLOR
{   

    float4 Color;

    Color.rgb = In.Diff;

    
    Color.w   = 1;
    return Color;
}  


technique fxDiffuseColor
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 DiffuseColorVS();
        PixelShader  = compile ps_2_0 DiffuseColorPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}

///////////////////////////////////////////






VS_OUTPUT BaseMaterialVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float3 L = -fxLightDir;
    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)
    float3 N = Normal;
    
                             // view direction (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    
    Out.Diff = Diffuse;
    
    Out.Tex0 = DecalTextureCoords;     
    Out.Tex1 = NormalMapCoords;        

     /*float3x3 ObjectSpace2TangentSpace =  
     float3x3(Tangent.x,   Tangent.y,   Tangent.z, 
              BiNormal.x,  BiNormal.y,  BiNormal.z, 
              Normal.x,      Normal.y,      Normal.z); 
             
    
    float3 tangentSpaceLight = mul(ObjectSpace2TangentSpace, -fxLightDir);*/
            
    float3 objectSpaceLight = -fxLightDir;

    Out.Tex2 = objectSpaceLight;
    

    Out.Tex3 = Tangent;  
    Out.Tex4 = BiNormal;  
    Out.Tex5 = Normal;  
    Out.Tex6 = P;  
    
    
        
    
    return Out;
}



float4 BaseMaterialPS(VS_OUTPUT In) : COLOR
{   

    float4 FinalColor;

    
    
    
    float3 Tangent = In.Tex3; 
    
    float3 BiNormal = In.Tex4;
    float3 Normal = In.Tex5;
    
    float3 Diffuse;
    /*if (fxDiffuseEnable)
    {
        if (fxTextureEnable)
            Diffuse.rgb = tex2D(DecalTextureSampler, In.Tex0);
        else
            Diffuse.rgb = k_d;  // material diffuse
    }
    else
        Diffuse.rgb = float3(1,1,1);*/
      

                
                
    Diffuse.rgb = tex2D(DecalTextureSampler, In.Tex0) * fxDiffuseEnable * fxTextureEnable +
    k_d * (1 - fxTextureEnable) * fxDiffuseEnable +
    float3(1,1,1) * (1 - fxTextureEnable) * (1 - fxDiffuseEnable);
     
        
                
  
   ///////////////////////////////////////////////////     
        
        
    float3 objectSpaceLight = In.Tex2;
       
    float3 white = float3(1,1,1);
    float3 fLightEnable = float3(fxLightEnable,fxLightEnable,fxLightEnable);
    

    float3 objectSpaceNormal;
    float Occlusion = 1;
    float brightness = 1;
    
    if (fxNormalMapForLightingEnable)
    {    

        // convert tangent space into object space
        if (fxNormalMapIsTangentSpace)
        {    
#if NORMAL_MAP_FP
            float4 LocalNormalMapNormal = tex2D(LocalNormalMapSampler, In.Tex1);  // fetch from normal map
#else
            float4 LocalNormalMapNormal = tex2D(LocalNormalMapSampler, In.Tex1) * fxScale - fxOffset;  // fetch from normal map
#endif


            /*float3x3 ObjectSpace2TangentSpace =  
            float3x3(Tangent.x,   Tangent.y,   Tangent.z, 
                     BiNormal.x,  BiNormal.y,  BiNormal.z, 
                     Normal.x,    Normal.y,    Normal.z); */

            float3x3 TangentSpace2ObjectSpace =  
            float3x3(
                Tangent.x, BiNormal.x, Normal.x,  
                Tangent.y, BiNormal.y, Normal.y,  
                Tangent.z, BiNormal.z, Normal.z);
                        
            float3 objectSpaceNormalMapNormal = mul(TangentSpace2ObjectSpace, LocalNormalMapNormal.xyz);
            
            objectSpaceNormalMapNormal = normalize(objectSpaceNormalMapNormal);
                
            Occlusion = LocalNormalMapNormal.w;
            brightness = max(0, dot(objectSpaceNormalMapNormal, objectSpaceLight));
            
            
         }
         else
         {
#if NORMAL_MAP_FP
            float4 ObjectNormalMapNormal = tex2D(ObjectNormalMapSampler, In.Tex1);  // fetch from normal map
#else
            float4 ObjectNormalMapNormal = tex2D(ObjectNormalMapSampler, In.Tex1) * fxScale - fxOffset;  // fetch from normal map
#endif
            objectSpaceNormal = ObjectNormalMapNormal.rgb;

            brightness = max(0, dot(objectSpaceNormal, -fxLightDir));

            Occlusion = ObjectNormalMapNormal.w;

         }
            
     }
    else
    {
        objectSpaceNormal = In.Tex5; // iterated normal
        brightness = max(0, dot(objectSpaceNormal, -fxLightDir));
     }
    

    float3 Lighting = fLightEnable * I_d * brightness + (1-fLightEnable) * white;
    FinalColor.rgb = I_a * k_a + Diffuse * Lighting * Occlusion; // diffuse + ambient
   
#if 0 
    float3 fSpecEnable = float3(fxSpecEnable,fxSpecEnable,fxSpecEnable);
    
    float3 N = objectSpaceNormal;
    float3 P = In.Tex6;
    
    float3 R = normalize(2 * dot(N, L) * N - L);            // reflection vector (view space)
    float3 V = -normalize(P);  
        
    FinalColor.rgb = FinalColor.rgb + fSpecEnable * I_s * k_s * pow(max(0, dot(R, V)), k_n);   // specular
#endif

      
    FinalColor.w   = 1;
    return FinalColor;

}  


technique fxBaseMaterial
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 BaseMaterialVS();
        PixelShader  = compile ps_2_a BaseMaterialPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
    
}

/////////////////


VS_OUTPUT IteratedNormalsVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)
    //float3 N = normalize(mul(Normal, (float3x3)WorldView));   // normal (view space)
    float3 N = Normal;   // normal (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    Out.Tex2 = N; 

    return Out;
}



float4 IteratedNormalsPS(VS_OUTPUT In) : COLOR
{   

    float4 Color;
    Color.rgb = In.Tex2 * 0.5 + 0.5;
    Color.w   = 1;
    return Color;
}  




technique fxIteratedNormals
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 IteratedNormalsVS();
        PixelShader  = compile ps_2_0 IteratedNormalsPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}
    



///////////////////////////////////////////////////////////////////
       

VS_OUTPUT NormalMapVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float3 L = -fxLightDir;
    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)
    //float3 N = normalize(mul(Normal, (float3x3)WorldView));   // normal (view space)
    float3 N = Normal;   // normal (view space)
    
    float3 R = normalize(2 * dot(N, L) * N - L);            // reflection vector (view space)
    float3 V = -normalize(P);                               // view direction (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    Out.Diff = I_a * k_a + I_d * Diffuse * max(0, dot(N, L)); // diffuse + ambient
    Out.Spec = I_s * k_s * pow(max(0, dot(R, V)), k_n);   // specular

    Out.Tex1 = NormalMapCoords;        
    
    return Out;
}



float4 NormalMapPS(VS_OUTPUT In) : COLOR
{   

    float4 Color;
     
#if NORMAL_MAP_FP
    Color.rgb = fxNormalMapIsTangentSpace * ((tex2D(LocalNormalMapSampler, In.Tex1) + fxOffset) / fxScale) + 
                    (1-fxNormalMapIsTangentSpace) * ((tex2D(ObjectNormalMapSampler, In.Tex1) + fxOffset) / fxScale);
#else    

    Color.rgb = fxNormalMapIsTangentSpace  * tex2D(LocalNormalMapSampler, In.Tex1) +
             (1-fxNormalMapIsTangentSpace) * tex2D(ObjectNormalMapSampler, In.Tex1);
    

#endif 
    
    Color.w   = 1;
    return Color;
}  

technique fxNormalMap
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 NormalMapVS();
        PixelShader  = compile ps_2_0 NormalMapPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}
    

///////////////////////////////
VS_OUTPUT AmbientVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float3 L = -fxLightDir;
    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)
    //float3 N = normalize(mul(Normal, (float3x3)WorldView));   // normal (view space)
    float3 N = Normal;   // normal (view space)
    
    float3 R = normalize(2 * dot(N, L) * N - L);            // reflection vector (view space)
    float3 V = -normalize(P);                               // view direction (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    Out.Diff = I_a * k_a + I_d * Diffuse * max(0, dot(N, L)); // diffuse + ambient
    Out.Spec = I_s * k_s * pow(max(0, dot(R, V)), k_n);   // specular

    Out.Tex1 = NormalMapCoords;        
    
    return Out;
}



float4 AmbientPS(VS_OUTPUT In) : COLOR
{   

    float4 Color;
     
#if NORMAL_MAP_FP
    Color.rgb = fxNormalMapIsTangentSpace * ((tex2D(LocalNormalMapSampler, In.Tex1) + fxOffset) / fxScale) + 
                    (1-fxNormalMapIsTangentSpace) * ((tex2D(ObjectNormalMapSampler, In.Tex1) + fxOffset) / fxScale);
#else    
 

    Color.rgb = tex2D(LocalNormalMapSampler, In.Tex1).aaaa;
             

#endif 
    
    Color.w   = 1;
    return Color;
}  

technique fxAmbient
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 AmbientVS();
        PixelShader  = compile ps_2_0 AmbientPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}
    




///////////////////////////////////////////////
// rotate tangent space to object space

VS_OUTPUT TangentSpaceToObjectSpaceVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
   
    Out.Tex0 = DecalTextureCoords;  
    Out.Tex1 = NormalMapCoords;  
    
    Out.Tex3 = Tangent;  
    Out.Tex4 = BiNormal;  
    Out.Tex5 = Normal;  
    
    Out.Diff = 0; 


    return Out;
}



float4 TangentSpaceToObjectSpacePS(VS_OUTPUT In) : COLOR
{   

    float4 Color;
    float3 Tangent =  In.Tex3; 
    float3 BiNormal =  In.Tex4;
    float3 Normal = In.Tex5;
        
#if NORMAL_MAP_FP
    float3 bumpedNormal = tex2D(LocalNormalMapSampler, In.Tex1);
#else
    float3 bumpedNormal = tex2D(LocalNormalMapSampler, In.Tex1) * fxScale - fxOffset;
#endif
    
    float3 objectSpaceNormal;


     /*
     dhr - original float3x3 ObjectSpace2TangentSpace =  
     float3x3(Tangent.x,   Tangent.y,   Tangent.z, 
              BiNormal.x,  BiNormal.y,  BiNormal.z, 
              Normal.x,      Normal.y,      Normal.z); 
              
              
     float3x3 TangentSpace2ObjectSpace;
           
    TangentSpace2ObjectSpace = invert(ObjectSpace2TangentSpace);       */
    
    float3x3 TangentSpace2ObjectSpace =  
    float3x3(
         Tangent.x, BiNormal.x, Normal.x,  
         Tangent.y, BiNormal.y, Normal.y,  
         Tangent.z, BiNormal.z, Normal.z);
             
    
    objectSpaceNormal = mul(TangentSpace2ObjectSpace, bumpedNormal);


    // display normal
    Color.rgb = objectSpaceNormal * 0.5 + 0.5;
    
    Color.w   = 1;
    return Color;
}  

  
technique fxTangentSpaceToObjectSpace
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 TangentSpaceToObjectSpaceVS();
        PixelShader  = compile ps_2_0 TangentSpaceToObjectSpacePS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}




///////////////////////////////////////////////
// using normal map lighting

VS_OUTPUT TangentSpaceNormalMapLightingVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    
   
    Out.Tex0 = DecalTextureCoords;  
    Out.Tex1 = NormalMapCoords;  
    
    Out.Tex2 = -fxLightDir; 
        
    float3 N = Normal;
    float3 T = Tangent;
    float3 B = BiNormal;

    
    Out.Tex3 = T;  
    Out.Tex4 = B;  
    Out.Tex5 = N;  
    
    Out.Diff = 0; 




    return Out;
}



float4 TangentSpaceNormalMapLightingPS(VS_OUTPUT In) : COLOR
{   

    float4 Color;
    
#if NORMAL_MAP_FP
    float3 bumpedNormal = tex2D(LocalNormalMapSampler, In.Tex1);
#else
    float3 bumpedNormal = tex2D(LocalNormalMapSampler, In.Tex1) * fxScale - fxOffset;
#endif
    
    float3 objectSpaceNormal;
    
    float3x3 ObjectSpace2TangentSpace =  
        float3x3(In.Tex3.x, In.Tex4.x, In.Tex5.x,
                 In.Tex3.y, In.Tex4.y, In.Tex5.y, 
                 In.Tex3.z, In.Tex4.z, In.Tex5.z);    
                 
    
    objectSpaceNormal = mul(ObjectSpace2TangentSpace, bumpedNormal);
    
    
    float3 L = In.Tex2;
    
    
    /*if (fxTextureEnable)
        Color.rgb = I_a * k_a + I_d * max(0, dot(bumpedNormal, L) ) * tex2D(DecalTextureSampler, In.Tex0);
    else
        Color.rgb = I_a * k_a + I_d * max(0, dot(objectSpaceNormal, L) );
        */

    Color.rgb = (I_a * k_a + I_d * max(0, dot(bumpedNormal, L) ) * tex2D(DecalTextureSampler, In.Tex0) ) * fxTextureEnable +
        (I_a * k_a + I_d * max(0, dot(objectSpaceNormal, L) ) ) * (1 - fxTextureEnable);

        
    Color.w   = 1;
    return Color;
}  



technique fxTangentSpaceNormalMapLighting
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 TangentSpaceNormalMapLightingVS();
        PixelShader  = compile ps_2_0 TangentSpaceNormalMapLightingPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}


// sampler
sampler ClampedLinear = 
sampler_state
{
    Texture   = NULL;
    AddressU  = CLAMP;
    AddressV  = CLAMP;
    MipFilter = POINT;
    MinFilter = POINT;
    MagFilter = POINT;
};

// techniques
technique Init
{
    pass P0
    {
        // render states
        CullMode = NONE;

        AmbientMaterialSource = COLOR1;
        DiffuseMaterialSource = COLOR1;

        //BlendOp   = ADD;
        //SrcBlend  = SRCALPHA;
        //DestBlend = INVSRCALPHA;

        AlphaTestEnable = FALSE;
        AlphaFunc       = GREATER;
        AlphaRef        = 0;

        AlphaBlendEnable = TRUE;

        // texture stage states
        AlphaOp[0]   = DISABLE;
        //AlphaArg1[0] = TEXTURE;
        //AlphaArg2[0] = CURRENT;

        // sampler
        Sampler[0]  = (ClampedLinear);

        // lighting
        /*LightType[0]      = DIRECTIONAL;
        LightDirection[0] = (fxLightDir);
        LightAmbient[0]   = (I_a);
        LightDiffuse[0]   = (I_d);
        LightSpecular[0]  = (I_s);
        LightEnable[0]    = TRUE;*/

        Lighting = FALSE;

        /*// vertex shader constants
        VertexShaderConstantF[CV_ZERO]              = (0.0f * vOne);
        VertexShaderConstantF[CV_ONE]               = (1.0f * vOne);
        VertexShaderConstantF[CV_HALF]              = (0.5f * vOne);
        VertexShaderConstantF[CV_QUARTER]           = (0.25f * vOne);
        
        VertexShaderConstantF[CV_LIGHT_DIRECTION]   = (fxLightDir);
        VertexShaderConstantF[CV_LIGHT_AMBIENT]     = (I_a);
        VertexShaderConstantF[CV_LIGHT_DIFFUSE]     = (I_d);
        VertexShaderConstantF[CV_LIGHT_SPECULAR]    = (I_s);
        VertexShaderConstantF[CV_MATERIAL_SPECULAR] = (k_s);
         */


        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
    }
}









    
    

    
    








      

    

    



float4 BlackPS(VS_OUTPUT In) : COLOR
{   
    float4 Color = float4(0,0,0,0);
    return Color;
}  
technique fxBlack
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 DiffuseColorVS();
        PixelShader  = compile ps_2_0 BlackPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}




/////////////////////////


VS_OUTPUT TangentSpaceLightingVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float3 L = -fxLightDir;
    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)
    float3 N = Normal;
    
                             // view direction (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    
    Out.Diff = Diffuse;
    
    Out.Tex0 = DecalTextureCoords;     
    Out.Tex1 = NormalMapCoords;        


     float3x3 ObjectSpace2TangentSpace =  
     float3x3(Tangent.x,   Tangent.y,   Tangent.z, 
              BiNormal.x,  BiNormal.y,  BiNormal.z, 
              Normal.x,    Normal.y,    Normal.z); 
             
    
    float3 tangentSpaceLight = mul(ObjectSpace2TangentSpace, -fxLightDir);
            

    Out.Tex2 = tangentSpaceLight;

    Out.Tex3 = Tangent;  
    Out.Tex4 = BiNormal;  
    Out.Tex5 = Normal;  
    Out.Tex6 = P;  // object space point
    

    
    return Out;
}



float4  TangentSpaceLightingPS(VS_OUTPUT In) : COLOR
{

    float4 FinalColor;

    float2 NormalMapCoords =  In.Tex1; 
    float3 Tangent =  In.Tex3; 
    float3 Binormal =  In.Tex4;
    float3 Normal = In.Tex5;
    

    
    
    float3 tangentSpaceLightDir = In.Tex2;

    float3 LocalNormalMapNormalColor = tex2D(LocalNormalMapSampler, In.Tex1);  // fetch from normal map    
    float3 LocalNormalMapNormal = LocalNormalMapNormalColor * fxScale - fxOffset;  // fetch from normal map    
    float localLdotN = max(0, dot(LocalNormalMapNormal, tangentSpaceLightDir));
    
        
    FinalColor.rgb = float3(localLdotN, localLdotN, localLdotN);
        
    FinalColor.w   = 1;
    return FinalColor;
    
}  


technique fxTangentSpaceLighting
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 TangentSpaceLightingVS();
        PixelShader  = compile ps_2_0 TangentSpaceLightingPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}

/////////////////////////////////////


VS_OUTPUT ObjectSpaceLightingVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float3 L = -fxLightDir;
    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)
    float3 N = Normal;
    
                             // view direction (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    
    Out.Diff = Diffuse;
    
    Out.Tex0 = DecalTextureCoords;     
    Out.Tex1 = NormalMapCoords;        




    Out.Tex3 = Tangent;  
    Out.Tex4 = BiNormal;  
    Out.Tex5 = Normal;  
    Out.Tex6 = P;  
    
    
        
    
    return Out;
}



float4  ObjectSpaceLightingPS(VS_OUTPUT In) : COLOR
{

    float4 FinalColor;

    float3 Tangent =  In.Tex3; 
    float3 BiNormal =  In.Tex4;
    float3 Normal = In.Tex5;
    
    
    float3 objectSpaceLightDir = -fxLightDir;

    float3 NormalMapNormalColor = tex2D(ObjectNormalMapSampler, In.Tex1);  // fetch from normal map
    float3 NormalMapNormal = NormalMapNormalColor * fxScale - fxOffset;  // 
    
    FinalColor.rgb = max(0, dot(NormalMapNormal, objectSpaceLightDir) );
    

        
    FinalColor.w   = 1;
    return FinalColor;
    
}  


technique fxObjectSpaceLighting
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 ObjectSpaceLightingVS();
        PixelShader  = compile ps_2_0 ObjectSpaceLightingPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}


/////////////////////////////////////////////

///////////////////////////////////////////////
// rotate tangent space to object space

VS_OUTPUT TangentSpaceToObjectSpaceLightingVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
   
    Out.Tex0 = DecalTextureCoords;  
    Out.Tex1 = NormalMapCoords;  
    
    Out.Tex3 = Tangent;  
    Out.Tex4 = BiNormal;  
    Out.Tex5 = Normal;  
    
    Out.Diff = 0; 


    return Out;
}

/////////////////////////////////

float4 TangentSpaceToObjectSpaceLightingPS(VS_OUTPUT In) : COLOR
{   

    float4 Color;
    float3 Tangent =  In.Tex3; 
    float3 BiNormal =  In.Tex4;
    float3 Normal = In.Tex5;
        
#if NORMAL_MAP_FP
    float3 bumpedNormal = tex2D(LocalNormalMapSampler, In.Tex1);
#else
    float3 bumpedNormal = tex2D(LocalNormalMapSampler, In.Tex1) * fxScale - fxOffset;
#endif
    
    float3 objectSpaceNormal;



     /* dhr
     original
     float3x3 ObjectSpace2TangentSpace =  
     float3x3(Tangent.x,   Tangent.y,   Tangent.z, 
              BiNormal.x,  BiNormal.y,  BiNormal.z, 
              Normal.x,    Normal.y,    Normal.z); 
              
              
     float3x3 TangentSpace2ObjectSpace;
           
    TangentSpace2ObjectSpace = invert(ObjectSpace2TangentSpace);    */
    
    float3x3 TangentSpace2ObjectSpace =  
    float3x3(
        Tangent.x, BiNormal.x, Normal.x,  
        Tangent.y, BiNormal.y, Normal.y,  
        Tangent.z, BiNormal.z, Normal.z);
                  
    
       
    objectSpaceNormal = mul(TangentSpace2ObjectSpace, bumpedNormal);


    Color.rgb = max(0, dot(objectSpaceNormal, -fxLightDir ));

    // display normal
    //Color.rgb = objectSpaceNormal * 0.5 + 0.5;
    
    Color.w   = 1;
    return Color;
}  

  
technique fxTangentSpaceToObjectSpaceLighting
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 TangentSpaceToObjectSpaceLightingVS();
        PixelShader  = compile ps_2_0 TangentSpaceToObjectSpaceLightingPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}

///////////////////////////////


VS_OUTPUT NormalAsColorVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float3 L = -fxLightDir;
    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)
    float3 N = Normal;
    
                             // view direction (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    
    Out.Diff = Diffuse;
    
    Out.Tex0 = DecalTextureCoords;     
    Out.Tex1 = NormalMapCoords;        


    float3 objectSpaceLight = -fxLightDir;
            

    Out.Tex2 = objectSpaceLight;

    Out.Tex3 = Tangent;  
    Out.Tex4 = BiNormal;  
    Out.Tex5 = Normal;  
    Out.Tex6 = P;  
    
    
        
    
    return Out;
}



float4  NormalAsColorPS(VS_OUTPUT In) : COLOR
{

    float4 FinalColor;

    float2 tc =  In.Tex1; 
    float3 Tangent =  In.Tex3; 
    float3 BiNormal =  In.Tex4;
    float3 Normal = In.Tex5;
    
    
    //FinalColor.rgb = (Normal + 1) / 2;
    FinalColor.rgb = Normal;
    

        
    FinalColor.w   = tc.x;
    return FinalColor;
    
}  


technique fxNormalAsColor
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 NormalAsColorVS();
        PixelShader  = compile ps_2_0 NormalAsColorPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}



VS_OUTPUT TangentAsColorVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float3 L = -fxLightDir;
    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)
    float3 N = Normal;
    
                             // view direction (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    
    Out.Diff = Diffuse;
    
    Out.Tex0 = DecalTextureCoords;     
    Out.Tex1 = NormalMapCoords;        


    float3 objectSpaceLight = -fxLightDir;
            

    Out.Tex2 = objectSpaceLight;

    Out.Tex3 = Tangent;  
    Out.Tex4 = BiNormal;  
    Out.Tex5 = Normal;  
    Out.Tex6 = P;  
    
    
        
    
    return Out;
}



float4  TangentAsColorPS(VS_OUTPUT In) : COLOR
{

    float4 FinalColor;

    float3 Tangent  = In.Tex3; 
    float3 BiNormal = In.Tex4;
    float3 Normal   = In.Tex5;
    

// interpolated tangent basis    
    //FinalColor.rgb = (Tangent + 1) / 2;
    FinalColor.rgb = Tangent;
    

        
    FinalColor.w   = 1;
    return FinalColor;
    
}  


technique fxTangentAsColor
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 TangentAsColorVS();
        PixelShader  = compile ps_2_0 TangentAsColorPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}

VS_OUTPUT BinormalAsColorVS(    
VERTEX_INPUT
    
    )
{
    VS_OUTPUT Out = (VS_OUTPUT)0;

    float3 L = -fxLightDir;
    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)
    float3 N = Normal;
    
                             // view direction (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)
    
    Out.Diff = Diffuse;
    
    Out.Tex0 = DecalTextureCoords;     
    Out.Tex1 = NormalMapCoords;        


    float3 objectSpaceLight = -fxLightDir;
            

    Out.Tex2 = objectSpaceLight;

    Out.Tex3 = Tangent;  
    Out.Tex4 = BiNormal;  
    Out.Tex5 = Normal;  
    Out.Tex6 = P;  
    
    
        
    
    return Out;
}



float4  BinormalAsColorPS(VS_OUTPUT In) : COLOR
{

    float4 FinalColor;

    float3 Tangent =  In.Tex3; 
    float3 BiNormal =  In.Tex4;
    float3 Normal = In.Tex5;
    

    //FinalColor.rgb = (BiNormal + 1) / 2;
    FinalColor.rgb = BiNormal;
    

        
    FinalColor.w   = 1;
    return FinalColor;
    
}  


technique fxBinormalAsColor
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 BinormalAsColorVS();
        PixelShader  = compile ps_2_0 BinormalAsColorPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}






struct VS_OUTPUT2
{
    float4 Pos  : POSITION;
    float3 Diff : COLOR0;
    float3 Spec : COLOR1;
};

VS_OUTPUT2 VertexLightingVS(    
    float3 Pos  : POSITION,                          
    float3 Normal : Normal                         
    
    )
{
    VS_OUTPUT2 Out = (VS_OUTPUT2)0;

    float4x4 WorldView = mul(World, View);
    float3 P = mul(float4(Pos, 1), (float4x3)WorldView);    // position (view space)
                         // view direction (view space)

    Out.Pos  = mul(float4(P, 1), Projection);             // position (projected)

 
    float3 Light2 = float3(-fxLightLight.x, fxLightLight.z, -fxLightLight.y);
    
    
    Out.Diff = max(0, dot(Normal, -fxLightLight)) + max(0, dot(Normal, -Light2));
    //Out.Diff = (Normal + 1) / 2;
 
    
    return Out;
}


float4 VertexLightingPS(VS_OUTPUT2 In) : COLOR
{   

    float4 Color;

    Color.rgb = In.Diff * k_d + k_a;

    
    Color.w   = 1;
    return Color;
} 

technique fxVertexLighting
{
    pass P0
    {
        // render states
        //CullMode = CCW;

        AlphaBlendEnable = FALSE;

        // lighting
        Lighting = TRUE;

        // fixed function
        VertexShader = compile vs_1_1 VertexLightingVS();
        PixelShader  = compile ps_2_0 VertexLightingPS();       
        
        // transforms
        WorldTransform[0]   = (World);
        ViewTransform       = (View);
        ProjectionTransform = (Projection);
        
    }
}

