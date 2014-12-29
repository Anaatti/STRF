/** global.hpp **/

#ifndef STRF_GLOBAL_HPP
#define STRF_GLOBAL_HPP

#ifdef _WIN32
	#define DLL
#endif
#ifdef DLL
	#ifdef BUILD_DLL
		#define DLL_EXPORT __declspec(dllexport)
	#else
		#define DLL_EXPORT __declspec(dllimport)
	#endif
	#define DLL_CALL __stdcall
#else
	#define DLL_EXPORT
	#define DLL_CALL
#endif

typedef const bool cbool;

typedef const char cchar;
typedef const signed char cschar;
typedef signed char schar;
typedef const unsigned char cuchar;
typedef unsigned char uchar;

typedef const short cshort;
typedef const unsigned short cushort;
typedef unsigned short ushort;

typedef const int cint;
typedef const unsigned int cuint;
typedef unsigned int uint;

typedef const long clong;
typedef const unsigned long culong;
typedef unsigned long ulong;

typedef const float cfloat;

typedef const double cdouble;
typedef const long double cldouble;
typedef long double ldouble;

typedef const void cvoid;

#endif
