// - ------------------------------------------------------------------------------------------ - //
#ifndef __TEXT_OUT_H__
#define __TEXT_OUT_H__
// - ------------------------------------------------------------------------------------------ - //
void OutInit();
void OutExit();

void Out( const char* Text, ... );
void Out_( const char* Text, ... );	// No newline //
void OutFlush();

// Extended Features //
void OutColor( const int Color );
void OutResetColor();

void OutClear();

int GetCh();
int GetRows();
int GetColumns();

// - ------------------------------------------------------------------------------------------ - //
enum {
	OUT_BLACK 				= 0,
	OUT_RED 				= 1,
	OUT_GREEN 				= 2,
	OUT_BROWN 				= 3,
	OUT_BLUE 				= 4,
	OUT_MAGENTA 			= 5,
	OUT_CYAN 				= 6,
	OUT_LIGHT_GRAY			= 7,
	OUT_DARK_GRAY 			= 8,
	OUT_LIGHT_RED 			= 9,
	OUT_LIGHT_GREEN			= 10,
	OUT_YELLOW 				= 11,
	OUT_LIGHT_BLUE 			= 12,
	OUT_LIGHT_MAGENTA 		= 13,
	OUT_LIGHT_CYAN 			= 14,
	OUT_WHITE 				= 15,

	OUT_INV_BLACK 			= 16+0,
	OUT_INV_RED 			= 16+1,
	OUT_INV_GREEN 			= 16+2,
	OUT_INV_BROWN 			= 16+3,
	OUT_INV_BLUE 			= 16+4,
	OUT_INV_MAGENTA 		= 16+5,
	OUT_INV_CYAN 			= 16+6,
	OUT_INV_LIGHT_GRAY		= 16+7,
	OUT_INV_DARK_GRAY 		= 16+8,
	OUT_INV_LIGHT_RED 		= 16+9,
	OUT_INV_LIGHT_GREEN		= 16+10,
	OUT_INV_YELLOW 			= 16+11,
	OUT_INV_LIGHT_BLUE 		= 16+12,
	OUT_INV_LIGHT_MAGENTA 	= 16+13,
	OUT_INV_LIGHT_CYAN 		= 16+14,
	OUT_INV_WHITE 			= 16+15,

	OUT_BOLD				= 8,
	OUT_INV					= 16,
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __TEXT_OUT_H__ //
// - ------------------------------------------------------------------------------------------ - //
