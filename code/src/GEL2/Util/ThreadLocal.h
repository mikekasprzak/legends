// - ------------------------------------------------------------------------------------------ - //
#ifndef __UTIL_THREAD_LOCAL_H__
#define __UTIL_THREAD_LOCAL_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Handle exotic platforms
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_THREAD_LOCAL
	#define threadlocal __thread
#else // NO_THREAD_LOCAL //
	#define threadlocal
	#warning NO_THREAD_LOCAL used. Variables of 'threadlocal' type may be compromised.
#endif // NO_THREAD_LOCAL //
// - ------------------------------------------------------------------------------------------ - //
#endif // __UTIL_THREAD_LOCAL_H__ //
// - ------------------------------------------------------------------------------------------ - //
