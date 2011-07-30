// - ------------------------------------------------------------------------------------------ - //
// DataBlockCompression - Compression code for DataBlock library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_DataBlock_LZMA_H__
#define __Library_Data_DataBlock_LZMA_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4305) // Truncation
#pragma warning (disable : 4244) // Tructation, data loss potential 
#endif // _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef Bool
#undef Bool
#endif // Bool //
#include <External/LzmaAllocators.h>
// - ------------------------------------------------------------------------------------------ - //
extern "C" {
#include <External/LZMA/LzmaDec.h>
};
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a new DataBlock //
inline DataBlock* unpack_LZMA_DataBlock( const DataBlock* _Src ) {
	// Take a copy of the File Header (for some reason) //
	unsigned char header[LZMA_PROPS_SIZE + 8];
	copy_Data( &_Src->Data[0], &header[0], sizeof( header ) );

	// Get the Uncompressed Size from the properties (WARNING! 5 BYTES IN!) //
	//UInt64 UncompressedSize = *((UInt64*)&_Src->Data[LZMA_PROPS_SIZE]);	
	// Hack to avoid alignment issues //
	UInt64 UncompressedSize = (*((UInt64*)&_Src->Data[4])) >> 8;	

	// Allocate LZMA Workspace //
	CLzmaDec state;
	LzmaDec_Construct(&state);
	{
		int Result = LzmaDec_Allocate(&state, header, LZMA_PROPS_SIZE, &lzma_alloc_struct);
		if (Result != SZ_OK)
			return 0;
	}

	// Allocate a new DataBlock for our uncompressed Data //
	DataBlock* UBuffer = new_DataBlock( UncompressedSize );

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
	
#ifdef _MSC_VER
	CProb* Probs = new CProb[ LzmaGetNumProbs(&state.Properties) ];
#else // _MSC_VER //
	CProb Probs[ LzmaGetNumProbs(&state.Properties) ];
#endif // _MSC_VER //
	state.Probs = (UInt16*)&Probs;
	
	// Allocate a new DataBlock for our uncompressed Data //
	DataBlock* UBuffer = new_DataBlock( UncompressedSize );

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

#ifdef _MSC_VER
	delete [] Probs;
#endif // _MSC_VER //

	// Return our new LZMA decompressed data //
	return UBuffer;
*/
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZMA data to a passed DataBlock //
inline const SizeT unpack_LZMA_DataBlock( const DataBlock* _Src, DataBlock* _Dest ) {

	// Take a copy of the File Header (for some reason) //
	unsigned char header[LZMA_PROPS_SIZE + 8];
	copy_Data( &_Src->Data[0], &header[0], sizeof( header ) );

	// Get the Uncompressed Size from the properties (WARNING! 5 BYTES IN!) //
	UInt64 UncompressedSize = *((UInt64*)&_Src->Data[LZMA_PROPS_SIZE]);	

	// If the passed DataBlock is too small for our uncompressed data, fail //
	if ( UncompressedSize > _Dest->Size ) {
		// Not enough memory available in passed block! //
		return 0;
	}

	// Allocate LZMA Workspace //
	CLzmaDec state;
	LzmaDec_Construct(&state);
	{
		int Result = LzmaDec_Allocate(&state, header, LZMA_PROPS_SIZE, &lzma_alloc_struct);
		if (Result != SZ_OK)
			return 0;
	}

	SizeT destLength = (SizeT)UncompressedSize;
	SizeT srcLength = (SizeT)_Src->Size;
	ELzmaStatus LZMAStatus;

	// Initialize the LZMA Decoder //
	LzmaDec_Init(&state);

	// Decompress File //
    int Result = LzmaDec_DecodeToBuf(
		&state,
		(unsigned char*)&_Dest->Data,
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

	return UncompressedSize;

/*
	unsigned char LZMAProperties[LZMA_PROPERTIES_SIZE];
	
	// Copy first byte of LZMA Properties.  Somehow, this is vitally important. //
	*LZMAProperties = _Src->Data[0];
	
	// Get the Uncompressed Size from the properties //
	unsigned long long int UncompressedSize = *((unsigned long long int*)&_Src->Data[LZMA_PROPERTIES_SIZE]);
	
	// If the passed DataBlock is too small for our uncompressed data, fail //
	if ( UncompressedSize > _Dest->Size ) {
		// Not enough memory available in passed block! //
		return 0;
	}
	
	// Decoder State structure //
	CLzmaDecoderState state;
	
	// Decode the properties //
	if( LzmaDecodeProperties( &state.Properties, LZMAProperties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK ) {
		//Log( LOG_MESH_INFO, "Incorrect stream properties (LZMA.h)" );
 	  	return 0;
    }

#ifdef _MSC_VER
	CProb* Probs = new CProb[ LzmaGetNumProbs(&state.Properties) ];
#else // _MSC_VER //
	CProb Probs[ LzmaGetNumProbs(&state.Properties) ];
#endif // _MSC_VER //
	state.Probs = (UInt16*)&Probs;

	// Temporary variables modified by decode function, so to learn about how it went //
	SizeT inProcessed = 0;
	SizeT outProcessed = 0;
	
	// Decode the file //
	int Result = LzmaDecode( 
		&state,
		( unsigned char* )&_Src->Data[ LZMA_PROPERTIES_SIZE + 8 ],
		_Src->Size,
		&inProcessed,
		( unsigned char* )_Dest->Data,
		UncompressedSize,
		&outProcessed
		);

#ifdef _MSC_VER
	delete [] Probs;
#endif // _MSC_VER //

	// Return the size of the uncompressed data on success //
	return UncompressedSize;
*/
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef __Library_Data_DataBlock_Class_H__
// - ------------------------------------------------------------------------------------------ - //
const cDataBlock cDataBlock::UnpackLZMA( const cDataBlock& _Src ) {
	return cDataBlock( unpack_LZMA_DataBlock( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //
const cDataBlock cDataBlock::UnpackLZMA( const DataBlock* _Src ) {
	return cDataBlock( unpack_LZMA_DataBlock( _Src ) );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_DataBlock_Class_H__ //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_DataBlock_LZMA_H__ //
// - ------------------------------------------------------------------------------------------ - //
