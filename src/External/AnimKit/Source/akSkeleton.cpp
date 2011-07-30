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

#include "akSkeleton.h"
#include "akSkeletonPose.h"

akSkeleton::akSkeleton(UTuint32 numJoints) : m_localBindPose(0), m_modelBindPose(0)
{
	m_joints.resize(numJoints);
}

akSkeleton::~akSkeleton()
{
	m_joints.clear();
	
	if(m_localBindPose)
		delete m_localBindPose;
	
	if(m_modelBindPose)
		delete m_modelBindPose;
		
	if(m_inverseBindPose.size()>0)
		m_inverseBindPose.clear();
}


UTuint8 akSkeleton::addJoint(utHashedString &name, UTuint8 parent)
{
	UTuint32 size = m_joints.size();
	if( size<256 && (parent<size || parent==AK_JOINT_NO_PARENT))
	{
		m_joints.push_back(akJoint(name, parent));
		return size;
	}
	return 0;
}

int akSkeleton::getIndex(const utHashedString &name) const
{	
	for(int i=0; i<m_joints.size(); i++)
	{
		if ( m_joints[i].m_name.hash() == name.hash() )
			return i;
	}
	
	return -1;
}

akJoint* akSkeleton::getJoint(UTuint8 idx)
{
	return &m_joints[idx];
}

akJoint* akSkeleton::getByName(const utHashedString &name)
{
	for(int i=0; i<m_joints.size(); i++)
	{
		if ( m_joints[i].m_name.hash() == name.hash())
			return &m_joints[i];
	}
	
	return 0;
}

bool akSkeleton::setBindingPose(akSkeletonPose *pose)
{
	if(pose->getSkeleton() == this)
	{
		if(m_localBindPose)
			delete m_localBindPose;
		if(m_modelBindPose)
			delete m_modelBindPose;
		if(m_inverseBindPose.size()>0)
			m_inverseBindPose.clear();
		
		pose->toModelSpace(pose);
		
		m_modelBindPose = pose;
		m_localBindPose = new akSkeletonPose(*pose);
		m_localBindPose->toLocalSpace(m_localBindPose);
		
		m_inverseBindPose.resize(m_joints.size());
		
		for(int i=0; i<m_joints.size(); i++)
		{
			m_inverseBindPose[i] = inverse( m_modelBindPose->getJointPose(i)->toMatrix() );
		}
		
		return true;
	}
	return false;
}

