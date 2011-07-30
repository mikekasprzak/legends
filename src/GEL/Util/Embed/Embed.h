// - ------------------------------------------------------------------------------------------ - //
// Embed - Binary Include Data as usable C or C++ types //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rebel_Embed_H__
#define __Rebel_Embed_H__
// - ------------------------------------------------------------------------------------------ - //
// NOTE: # in front of a macro argument is stringification.  Frank becomes "Frank". //
// 		## is used to merge symbols to create new symbols.  #define Mer(Var,Num) Var##_##Num = Num
//		Produces: Mer(Tank,10); -> Tank_10 = 10;
// - ------------------------------------------------------------------------------------------ - //
// Note: could also use ".set _MySymbol_Size, 1f - 1b - 4", and cast it to an int to use it like //
// 		An Enum
// Possibly create macros for embedding a DataBlock, like above.  And others for embedding char*'s.
// The 1f and 1b above says the symbol "1" forward or back from where I am //
// - ------------------------------------------------------------------------------------------ - //
// NOTE: OSX Assembler does not support ".incbin".
//		Also, OSX Assembler uses ".globl" not ".global".
// - ------------------------------------------------------------------------------------------ - //
#define EmbedDataBlock(___Symbol,___File) \
	extern DataBlock ___Symbol; \
	extern int ___Symbol ## _Size; \
asm( \
	"_" #___Symbol ":;" \
	"	.global _" #___Symbol ";" \
	"1:;" \
	"	.set _" #___Symbol "_Size, 1f - 1b - 4;" \
	"	.global _" #___Symbol "_Size;" \
	"	.int 1f - 1b - 4;" \
	"	.incbin \"" ___File "\";" \
	"1:;" \
	)
// - ------------------------------------------------------------------------------------------ - //
// Exactly the same as a DataBlock, but in case you don't have DataBlock defined //
// - ------------------------------------------------------------------------------------------ - //
#define EmbedDataWithSize(___Symbol,___File) \
	extern char ___Symbol[]; \
	extern int ___Symbol ## _Size; \
asm( \
	"_" #___Symbol ":;" \
	"	.global _" #___Symbol ";" \
	"1:;" \
	"	.set _" #___Symbol "_Size, 1f - 1b - 4;" \
	"	.global _" #___Symbol "_Size;" \
	"	.int 1f - 1b - 4;" \
	"	.incbin \"" ___File "\";" \
	"1:;" \
	)
// - ------------------------------------------------------------------------------------------ - //
#define EmbedData(___Symbol,___File) \
	extern char ___Symbol[]; \
	extern int ___Symbol ## _Size; \
asm( \
	"_" #___Symbol ":;" \
	"	.global _" #___Symbol ";" \
	"1:;" \
	"	.set _" #___Symbol "_Size, 1f - 1b - 4;" \
	"	.global _" #___Symbol "_Size;" \
	"	.incbin \"" ___File "\";" \
	"1:;" \
	)
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rebel_Embed_H__ //
// - ------------------------------------------------------------------------------------------ - //
