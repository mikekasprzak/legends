// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_PAWN
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/Log.h>
// - ------------------------------------------------------------------------------------------ - //
#include <amx.h>
#include <amxaux.h>
// - ------------------------------------------------------------------------------------------ - //
//int aux_LoadProgram(AMX *amx, char *filename, void *memblock)
//{
//	FILE *fp;
//	AMX_HEADER hdr;
//	int result, didalloc;
//	
//	/* step 1: open the file, read and check the header */
//	if ((fp = fopen(filename, "rb")) == NULL)
//		return AMX_ERR_NOTFOUND;
//	
//	fread(&hdr, sizeof hdr, 1, fp);
//	amx_Align16(&hdr.magic);
//	amx_Align32((uint32_t *)&hdr.size);
//	amx_Align32((uint32_t *)&hdr.stp);
//	if (hdr.magic != AMX_MAGIC) {
//		fclose(fp);
//		return AMX_ERR_FORMAT;
//	} /* if */
//	
//	/* step 2: allocate the memblock if it is NULL */
//	didalloc = 0;
//	if (memblock == NULL) {
//		if ((memblock = malloc(hdr.stp)) == NULL) {
//			fclose(fp);
//			return AMX_ERR_MEMORY;
//		} /* if */
//		didalloc = 1;
//		/* after amx_Init(), amx->base points to the memory block */
//	} /* if */
//	
//	/* step 3: read in the file */
//	rewind(fp);
//	fread(memblock, 1, (size_t)hdr.size, fp);
//	fclose(fp);
//	/* step 4: initialize the abstract machine */
//	memset(amx, 0, sizeof *amx);
//	result = amx_Init(amx, memblock);
//	/* step 5: free the memory block on error, if it was allocated here */
//	if (result != AMX_ERR_NONE && didalloc) {
//		free(memblock);
//		amx->base = NULL; /* avoid a double free */
//	} /* if */
//	return result;
//}
//
//int aux_FreeProgram(AMX *amx)
//{
//	if (amx->base!=NULL) {
//		amx_Cleanup(amx);
//		free(amx->base);
//		memset(amx,0,sizeof(AMX));
//	} /* if */
//	return AMX_ERR_NONE;
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
static cell n_Log(AMX *amx, const cell *params)
{
	int r = 0, length;
	cell *cstr;
	char *pname;
	
	amx_GetAddr(amx, params[1], &cstr);
	amx_StrLen(cstr, &length);
	
	if ((pname = (char*)malloc(length + 1)) != NULL) {
		amx_GetString(pname, cstr, 0, UNLIMITED);
		
		//r = Log( pname, (int)params[2] );
		Log( pname );
		
		free(pname);
	} /* if */
	
	return r;
}
// - ------------------------------------------------------------------------------------------ - //
extern "C" int aux_MyLibInit(AMX *amx)
{
	static AMX_NATIVE_INFO mylib_Natives[] = {
		{ "Log", n_Log },
		{ 0, 0 } /* terminator */
		};
	return amx_Register(amx, mylib_Natives, -1);
}
// - ------------------------------------------------------------------------------------------ - //
extern "C" int aux_MyLibCleanup(AMX *amx)
{
	return AMX_ERR_NONE;
}
// - ------------------------------------------------------------------------------------------ - //
extern void CallExp_Pawn();
void CallExp_Pawn() {
	Log("+ Now testing Pawn\n");
	{
		AMX amx;
		int Error;
		cell Ret = 0;
		
		Error = aux_LoadProgram( &amx, (char*)"Content/Misc/hello.amx", NULL );
		if ( Error == 0 ) {
			aux_MyLibInit( &amx );
			
			Error = amx_Exec( &amx, &Ret, AMX_EXEC_MAIN );
			if ( Error ) {
				printf("Run time error %d: \"%s\" on address %ld\n", Error, aux_StrError(Error), (long)amx.cip);
			}
								
			aux_MyLibCleanup( &amx );
			aux_FreeProgram( &amx );
		}
		else {
			Log( "Failed to load Program\n" );
		}
	}
	Log("- Done testing Pawn\n");
	Log("\n");
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_PAWN //
// - ------------------------------------------------------------------------------------------ - //
