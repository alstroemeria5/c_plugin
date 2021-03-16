#ifndef _DLL_H
#define _DLL_
#if	__GNUC__ >= 4
	#ifdef LIB_CONCISE
		#warning "===library becomes concise.==="
		#define	DLL_PUBLIC	__attribute__((visibility("default")))
		#define DLL_LOCAL	__attribute__((visibility("hidden")))
	#else
		#define DLL_PUBLIC
		#define DLL_LOCAL
	#endif
#else 
	#warning	"===gcc version <4.==="
#endif
#endif
