/*
-------------------------------------------------------------------------------
    This file is part of OgreKit.
    http://gamekit.googlecode.com/

    Copyright (c) 2006-2010 Xavier T.

    Contributor(s): none yet.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/

#ifndef AKMATHUTILS_H
#define AKMATHUTILS_H

#include <float.h>

#include "utCommon.h"


#if !defined(ANIMKIT_DOUBLE_PRECISION)
	#ifdef ANIMKIT_USE_SSE_IF_AVAILABLE
		#ifdef ANIMKIT_GCC_SUPPORT_SSE
			#define ANIMKIT_USE_SSE
		#elif (defined (_WIN32) && (_MSC_VER) && _MSC_VER >= 1400)
			#define ANIMKIT_USE_SSE
		#endif
	#endif
#endif


#ifdef ANIMKIT_USE_SSE
#include "sse/vectormath_aos.h"
#else
#include "scalar/vectormath_aos.h"
#endif

typedef Vectormath::Aos::Vector3    akVector3;
typedef Vectormath::Aos::Vector4    akVector4;
typedef Vectormath::Aos::Quat       akQuat;
typedef Vectormath::Aos::Matrix3    akMatrix3;
typedef Vectormath::Aos::Matrix4    akMatrix4;
typedef Vectormath::Aos::Transform3 akTransform3;
typedef Vectormath::Aos::Point3     akPoint3;

#ifdef ANIMKIT_DOUBLE_PRECISION
	typedef double akScalar;
	# define AK_EPSILON   DBL_EPSILON
	# define AK_INFINITY  DBL_MAX
#else
	typedef float akScalar;
	# define AK_EPSILON   FLT_EPSILON
	# define AK_INFINITY  FLT_MAX
#endif

#define akPi        akScalar(3.141592653589793238)
#define akPi2       akScalar(6.283185307179586476)
#define akPih       akScalar(1.570796326794896619)
#define akRPD       akScalar(0.017453292519943295)
#define akDPR       akScalar(57.295779513082320876)

UT_INLINE akScalar akAbs(const akScalar& v)
{
	return v < 0.0 ? -v : v;
}

UT_INLINE akScalar akClampf(const akScalar& v, const akScalar& a, const akScalar& b)
{
	return v < a ? a : v > b ? b : v;
}

UT_INLINE UTint32 akClampi(const UTint32& v, const UTint32& a, const UTint32& b)
{
	return v < a ? a : v > b ? b : v;
}

UT_INLINE akScalar akMax(const akScalar& a, const akScalar& b )
{
	return a < b ? b : a;
}

UT_INLINE bool akFuzzy(const akScalar& v)
{
	return akAbs(v) <= AK_EPSILON;
}

UT_INLINE bool akFuzzy(const akScalar& x, const akScalar& y)
{
	return akAbs(x-y) <= AK_EPSILON;
}

UT_INLINE bool akFuzzyT(const akScalar& x, const akScalar& tol)
{
	return akAbs(x) <= tol;
}

UT_INLINE bool akEq(const akScalar& v)
{
	return v >= -AK_EPSILON && v <= 1.+AK_EPSILON;
}

template <class T>
UT_INLINE static T* akOffsetPointer(T* ptr, UTsize offset)
{
	return (T*)((char*)(ptr) + offset);
}

template <class T>
UT_INLINE static void akAdvancePointer(T*& ptr, UTsize offset)
{
	ptr = akOffsetPointer(ptr, offset);
}


class akMathUtils
{
public:
	static akVector3 getScale(const akMatrix3& m);
	static akVector3 getScale(const akMatrix4& m);
	static akMatrix4 setScale(const akMatrix4& m, const akVector3& scale);
	
	static akMatrix3 normalized(const akMatrix3& m);
	static akMatrix4 normalizedUpper3x3(const akMatrix4& m);
	static akMatrix3 orthoNormalized(const akMatrix3& m);
	
	static void normalize(akMatrix3& m);
	static void normalizeUpper3x3(akMatrix4& m);
	static void orthoNormalize(akMatrix3& m);
	
	static void extractTransform(const akMatrix4& mat, akVector3 &loc, akQuat &rot, akVector3 &scale);
};

#endif // AKMATHUTILS_H
