// - ---------------------------------------------------------------------- - //
#ifndef __NET_H__
#define __NET_H__
// - ---------------------------------------------------------------------- - //

extern void netInit();
extern void netExit();

char* netGetHTTPData( const char* URL );
char* netPostHTTPData( const char* URL, const char* Data );
void netDeleteHTTPData( char* Data );

// - ---------------------------------------------------------------------- - //
#endif // __NET_H__ //
// - ---------------------------------------------------------------------- - //
