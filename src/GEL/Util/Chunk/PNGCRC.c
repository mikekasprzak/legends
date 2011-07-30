// - ------------------------------------------------------------------------------------------ - //
// Taken from the PNG Spec //
// - ------------------------------------------------------------------------------------------ - //
// http://www.libpng.org/pub/png/spec/1.2/PNG-CRCAppendix.html //
// - ------------------------------------------------------------------------------------------ - //
#include "PNGCRC.h"
// - ------------------------------------------------------------------------------------------ - //
/* Table of CRCs of all 8-bit messages. */
unsigned long PNG_CRC_TABLE[256];

/* Flag: has the table been computed? Initially false. */
int PNG_CRC_TABLE_COMPUTED = 0;
// - ------------------------------------------------------------------------------------------ - //
/* Make the table for a fast CRC. */
void make_png_crc_table( void ) {
	unsigned long c;
	int n, k;
	
	for (n = 0; n < 256; n++) {
		c = (unsigned long) n;
		
		for (k = 0; k < 8; k++) {
			if (c & 1)
				c = 0xedb88320L ^ (c >> 1);
			else
				c = c >> 1;
		}
		PNG_CRC_TABLE[n] = c;
	}
	PNG_CRC_TABLE_COMPUTED = 1;
}
// - ------------------------------------------------------------------------------------------ - //  
// Update a running CRC with the bytes buf[0..len-1]--the CRC should be initialized to all 1's, //
//   and the transmitted value is the 1's complement of the final running CRC //
//   (see the crc() routine below)). //
unsigned long update_png_crc( unsigned long crc, unsigned char *buf, int len ) {
	unsigned long c = crc;
	int n;
	
	if (!PNG_CRC_TABLE_COMPUTED)
		make_png_crc_table();
		
	for (n = 0; n < len; n++) {
		c = PNG_CRC_TABLE[(c ^ buf[n]) & 0xff] ^ (c >> 8);
	}
	return c;
}
// - ------------------------------------------------------------------------------------------ - //   
/* Return the CRC of the bytes buf[0..len-1]. */
unsigned long png_crc( unsigned char *buffer, int length ) {
	return update_png_crc(0xffffffffL, buffer, length) ^ 0xffffffffL;
}
// - ------------------------------------------------------------------------------------------ - //
