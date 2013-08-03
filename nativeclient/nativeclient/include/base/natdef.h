#pragma once

//#include <cstddef> 
#include <stddef.h>
#include <stdint.h>
namespace Natorium
{

#if defined(_MSC_VER)
	typedef			 bool		natBool;

	typedef unsigned char		natU8;
	typedef unsigned __int16	natU16;
	typedef unsigned __int32	natU32;
	typedef unsigned __int64	natU64;

	typedef	signed	 char		natS8;
	typedef			 char		natChar;
	typedef			 wchar_t	natWChar;
	typedef			 __int16	natS16;
	typedef			 __int32	natS32;
	typedef			 __int64	natS64;

	typedef			 float		natF32;
	typedef			 double		natF64;
#elif defined(__GNUC__)

	typedef			 bool		natBool;

	typedef unsigned char		natU8;
	typedef			 uint16_t	natU16;
	typedef			 uint32_t	natU32;
	typedef			 uint64_t	natU64;

	typedef	signed	 char		natS8;
	typedef			 char		natChar;
	typedef			 wchar_t	natWChar;
	typedef			 int16_t	natS16;
	typedef			 int32_t	natS32;
	typedef			 int64_t	natS64;

	typedef			 float		natF32;
	typedef			 double		natF64;

#else
#error "Compiler not defined"
#endif

	// common type

	typedef			natU32		ref_t;
	typedef			ref_t		tex_t;

// platform declaration
#if defined(_WIN32)

#elif defined(__gnu_linux__)

#elif defined(EMSCRIPTEN)

#else
#error "Platform not defined"
#endif	

}
