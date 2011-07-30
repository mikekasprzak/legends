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

#ifndef AKTRANSFORMSTATE_H
#define AKTRANSFORMSTATE_H

#include "utCommon.h"
#include "akMathUtils.h"

#include "btAlignedAllocator.h"

UT_ATTRIBUTE_ALIGNED_CLASS16(class) akTransformState
{
public:
	akVector3 loc;
	akQuat    rot;
	akVector3 scale;
	
public:
	akTransformState(const akVector3& oloc = akVector3(0,0,0),
					 const akQuat&    orot = akQuat::identity(),
					 const akVector3& oscl = akVector3(1,1,1))
	{
		loc = oloc;
		rot = orot;
		scale = oscl;
	}
	
	UT_INLINE akTransform3 toTransform3(void) const
	{
		akTransform3 t3(rot, loc);
		return appendScale(t3, scale);
	}
	
	UT_INLINE akMatrix4 toMatrix(void) const
	{
		return akMatrix4(toTransform3());
	}
	
	UT_INLINE static akTransformState identity()
	{
		return akTransformState(akVector3(0,0,0), akQuat::identity(), akVector3(1,1,1));
	}
	
	UT_INLINE const akTransformState& operator= (const akTransformState& o)
	{
		loc = o.loc;
		rot = o.rot;
		scale = o.scale;
		return *this;
	}
	
	BT_DECLARE_ALIGNED_ALLOCATOR();
};

#endif // AKTRANSFORMSTATE_H
