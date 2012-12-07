// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_UNIX
// - ------------------------------------------------------------------------------------------ - //
#include <stdlib.h>			// getenv //
#include <unistd.h>			// environ, getpid //
#include <sys/utsname.h>	// uname //
// - ------------------------------------------------------------------------------------------ - //
namespace System {
// - ------------------------------------------------------------------------------------------ - //
const char* GetUserName() {
	return getenv("USER");
}
// - ------------------------------------------------------------------------------------------ - //
utsname UTS;	// Global, so accessable outside this function //
const char* GetComputerName() {
	uname( &UTS );			// Populate Structure (TODO: Move to Init) //
	
	//return UTS.sysname;	// Linux //
	return UTS.nodename;	// ComputerName //
	//return UTS.release;	// 3.2.0-29-generic-pae //
	//return UTS.version;	// #46-Ubuntu SMP Fri Jul 27 17:25:43 UTC 2012 //
	//return UTS.machine;	// i686 //
}
// - ------------------------------------------------------------------------------------------ - //
const char** GetEnv() {
	return environ;
}
// - ------------------------------------------------------------------------------------------ - //
const char* GetEnv( const char* Var ) {
	return getenv( Var );
}
// - ------------------------------------------------------------------------------------------ - //
const size_t GetMemoryUsage() {
	// http://stackoverflow.com/questions/1558402/memory-usage-of-current-process-in-c
	// A colon delimited file "VmSize:	10222 kB"
	
	//	http://ewx.livejournal.com/579283.html
//	VmPeak                      peak virtual memory size
//	VmSize                      total program size
//	VmLck                       locked memory size
//	VmHWM                       peak resident set size ("high water mark")
//	VmRSS                       size of memory portions
//	VmData                      size of data, stack, and text segments
//	VmStk                       size of data, stack, and text segments
//	VmExe                       size of text segment
//	VmLib                       size of shared library code
//	VmPTE                       size of page table entries
//	VmSwap                      size of swap usage (the number of referred swapents)

	// May need to check if bsd uses the same names //
	
	//FILE* status = fopen( "/proc/self/status", "r" );

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
const int GetPID() {
	return (int)getpid();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace System //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_UNIX //
// - ------------------------------------------------------------------------------------------ - //
