// - ------------------------------------------------------------------------------------------ - //
// Quaternion //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Quaternion_H__
#define __Geometry_Quaternion_H__
// - ------------------------------------------------------------------------------------------ - //

// Some noteworthy stuff from the-list //
/*
void Quaternion::setAxisRotation(float axisX, float axisY, float axisZ, float angle)
{
    //axis must be a unit vector
    w = cosf(angle/2.0f);
    x = axisX * sinf(angle/2.0f);
    y = axisY * sinf(angle/2.0f);
    z = axisZ * sinf(angle/2.0f);
}

//-----------------------------------------------------------------------------
// Premultiply the current cumulative rotation by the given axis rotation
// axis must be a unit vector
//-----------------------------------------------------------------------------

void Quaternion::axisRotatePre(float axisX, float axisY, float axisZ, float angle)
{
    Quaternion a;
    a.setAxisRotation(axisX, axisY, axisZ, angle);
    Quaternion b = Quaternion(this);

    w = a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z;
    x = a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y;
    y = a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x;
    z = a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w;
}
*/
// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Quaternion_H__ //
// - ------------------------------------------------------------------------------------------ - //
