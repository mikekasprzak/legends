// - ------------------------------------------------------------------------------------------ - //
// ArrayCompression - Compression code for GelArray library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelArray_LZMA_H__
#define __Library_Data_GelArray_LZMA_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_LZMA.h"

#include "GelArray_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// This decompressor is done from scratch because it'll be used very often.  Other compressors //
//   will mainly only be used for intermediary formats. //
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a new GelArray //
template< class Type >
inline GelArray<Type>* unpack_LZMA_GelArray( const DataBlock* _Src ) {
	// Take a copy of the File Header (for some reason) //
	unsigned char header[LZMA_PROPS_SIZE + 8];
	copy_Data( &_Src->Data[0], &header[0], sizeof( header ) );

	// Get the Uncompressed Size from the properties (WARNING! 5 BYTES IN!) //
	UInt64 UncompressedSize = *((UInt64*)&_Src->Data[LZMA_PROPS_SIZE]);	

	// Allocate LZMA Workspace //
	CLzmaDec state;
	LzmaDec_Construct(&state);
	{
		int Result = LzmaDec_Allocate(&state, header, LZMA_PROPS_SIZE, &lzma_alloc_struct);
		if (Result != SZ_OK)
			return 0;
	}

	// Allocate a new Array for our uncompressed Data //
	GelArray<Type>* UBuffer = new_GelArray<Type>( UncompressedSize / sizeof(Type) );

	// TODO: Assert if uncompressed size doesn't divide evenly by Type //

	SizeT destLength = (SizeT)UncompressedSize;
	SizeT srcLength = (SizeT)_Src->Size;
	ELzmaStatus LZMAStatus;

	// Initialize the LZMA Decoder //
	LzmaDec_Init(&state);

	// Decompress File //
    int Result = LzmaDec_DecodeToBuf(
		&state,
		(unsigned char*)UBuffer->Data,
		&destLength, 
        (unsigned char*)&_Src->Data[ LZMA_PROPS_SIZE + 8 ],
		&srcLength,
		LZMA_FINISH_END,
		&LZMAStatus
		);

	// NOTE: This call can do *some bytes* by changing to LZMA_FINISH_ANY, and calling multiple times //
	// TODO: Something about errors //

	// Shutdown the LZMA Decoder
	LzmaDec_Free(&state, &lzma_alloc_struct);

	return UBuffer;

/*
	unsigned char LZMAProperties[LZMA_PROPERTIES_SIZE];
	
	// Copy first byte of LZMA Properties.  Somehow, this is vitally important. //
	*LZMAProperties = _Src->Data[0];
	
	// Get the Uncompressed Size from the properties //
	unsigned long long int UncompressedSize = *((unsigned long long int*)&_Src->Data[LZMA_PROPERTIES_SIZE]);
	
	// Decoder State structure //
	CLzmaDecoderState state;
	
	// Decode the properties //
	if( LzmaDecodeProperties( &state.Properties, LZMAProperties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK ) {
		//Log( LOG_MESH_INFO, "Incorrect stream properties (LZMA.h)" );
 	  	return 0;
    }
	
	CProb Probs[ LzmaGetNumProbs(&state.Properties) ];
	state.Probs = (UInt16*)&Probs;
	
	// Allocate a new GelArray for our uncompressed Data //
	GelArray<Type>* UBuffer = new_GelArray<Type>( UncompressedSize / sizeof(Type) );
	
	// TODO: Assert if uncompressed size doesn't divide evenly by Type //

	// Temporary variables modified by decode function, so to learn about how it went //
	SizeT inProcessed = 0;
	SizeT outProcessed = 0;
	
	// Decode the file //
	int Result = LzmaDecode( 
		&state,
		( unsigned char* )&_Src->Data[ LZMA_PROPERTIES_SIZE + 8 ],
		_Src->Size,
		&inProcessed,
		( unsigned char* )UBuffer->Data,
		UncompressedSize,
		&outProcessed
		);
	
	// Return our new LZMA decompressed data //
	return UBuffer;
*/
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelArray<Type>::UnpackLZMA( const cDataBlock& _Src ) {
	*this = cGelArray<Type>( unpack_LZMA_GelArray<Type>( _Src.Data() ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelArray<Type>::UnpackLZMA( const DataBlock* _Src ) {
	*this = cGelArray<Type>( unpack_LZMA_GelArray<Type>( _Src ) );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelArray_LZMA_H__ //
// - ------------------------------------------------------------------------------------------ - //
