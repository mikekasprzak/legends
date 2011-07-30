// - ------------------------------------------------------------------------------------------ - //
#include "IMAFile_Decoder.h"
// - ------------------------------------------------------------------------------------------ - //
IMAFileDecoder IMAFileDecoderInstance;
// - ------------------------------------------------------------------------------------------ - //
const int adpcm_ima_index_table[16] = {
  -1, -1, -1, -1, 2, 4, 6, 8,
  -1, -1, -1, -1, 2, 4, 6, 8
}; 
// - ------------------------------------------------------------------------------------------ - //
const int adpcm_ima_step_table[89] = { 
  7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 
  19, 21, 23, 25, 28, 31, 34, 37, 41, 45, 
  50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 
  130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
  337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
  876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 
  2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
  5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899, 
  15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767 
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
struct ADPCMStatus {
	int predictor;
	int step_index;
};
// - ------------------------------------------------------------------------------------------ - //
inline int av_clip(int a, int amin, int amax)
{
    if (a < amin)      
    	return amin;
    else if (a > amax) 
    	return amax;
    else               
    	return a;
}
// - ------------------------------------------------------------------------------------------ - //
inline unsigned char av_clip_uint8(int a)
{
    if (a&(~255)) 
    	return (-a)>>31;
    else          
    	return a;
}
// - ------------------------------------------------------------------------------------------ - //
inline signed short av_clip_int16(int a)
{
    if ((a+32768) & ~65535) 
    	return (a>>31) ^ 32767;
    else                    
    	return a;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline short adpcm_ima_expand_nibble( ADPCMStatus *c, char nibble ) {
    int step_index;
    int predictor;
    int sign, delta, diff, step;

    step = adpcm_ima_step_table[c->step_index];
    step_index = c->step_index + adpcm_ima_index_table[(unsigned)nibble];
    if (step_index < 0) 
    	step_index = 0;
    else if (step_index > 88) 
    	step_index = 88;

    sign = nibble & 8;
    delta = nibble & 7;
    
    /* perform direct multiplication instead of series of jumps proposed by
     * the reference ADPCM implementation since modern CPUs can do the mults
     * quickly enough */
    
    diff = ((2 * delta + 1) * step) >> 3;
    predictor = c->predictor;
    if (sign) 
    	predictor -= diff;
    else 
    	predictor += diff;

    c->predictor = av_clip_int16(predictor);
    c->step_index = step_index;

    return (short)c->predictor;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Count is the Size in Bytes of the Source //
// Src stores audio data in Nibbles (4:1) //
// Dest should be Count*4 //
void DecodeADPCM( const void* _src, void* _dest, const size_t Count ) {
	const unsigned char* Src = (const unsigned char*)_src;
	unsigned short* Dest = (unsigned short*)_dest;
	
	ADPCMStatus Status;
	Status.predictor = 0;
	Status.step_index = 0;
	
	for( size_t idx = 0; idx < Count; idx++ ) {
		*Dest++ = adpcm_ima_expand_nibble( &Status, (*Src) & 0xF );
		*Dest++ = adpcm_ima_expand_nibble( &Status, (*Src) >> 4 );
		Src++;
	}
}
// - ------------------------------------------------------------------------------------------ - //

