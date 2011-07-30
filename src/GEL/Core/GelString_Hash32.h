// - ------------------------------------------------------------------------------------------ - //
// String - Frontend and common C string functionality //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_String_Hash32_H__
#define __Library_Data_String_Hash32_H__
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
// Taken from Gamedeveloper magazine's InnerProduct (Sean Barrett 2005-03-15)
// 
// circular shift hash -- produces good results if modding by a prime;
// longword at a time would be faster (need alpha-style "is any byte 0"),
// or just use the first longword
// - ------------------------------------------------------------------------------------------ - // 
inline unsigned int hash32_String( const char *str ) {
	if (!str)
		return 0;
 
	unsigned char *n = (unsigned char *) str;
	unsigned int acc = 0x55555555;
	
	while (*n)
		acc = (acc >> 27) + (acc << 5) + *n++;

	return acc;
}
// - ------------------------------------------------------------------------------------------ - //
//}; // namepsace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_String_Hash32_H__ //
// - ------------------------------------------------------------------------------------------ - //
