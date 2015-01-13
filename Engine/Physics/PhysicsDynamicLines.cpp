/*
 * \file PhysicsDynamicLines.cpp
 *
 *  Created on: \date 9 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#include "PhysicsDynamicLines.h"

namespace Engine {

PhysicsDynamicLines::PhysicsDynamicLines(OperationType opType) {
	initialize(opType,false);
	setMaterial("BaseWhiteNoLighting");
	mDirty = true;

}

PhysicsDynamicLines::~PhysicsDynamicLines() {
	// TODO Auto-generated destructor stub
}

void PhysicsDynamicLines::setOperationType(OperationType opType)
{
	mRenderOp.operationType = opType;
}
//------------------------------------------------------------------------------------------------
Ogre::RenderOperation::OperationType PhysicsDynamicLines::getOperationType() const
{
	return mRenderOp.operationType;
}
//------------------------------------------------------------------------------------------------
void PhysicsDynamicLines::addPoint(const Ogre::Vector3 &p)
{
	mPoints.push_back(p);
	mDirty = true;
}
//------------------------------------------------------------------------------------------------
void PhysicsDynamicLines::addPoint(Ogre::Real x, Ogre::Real y, Ogre::Real z)
{
	mPoints.push_back(Ogre::Vector3(x,y,z));
	mDirty = true;
}
//------------------------------------------------------------------------------------------------
const Ogre::Vector3& PhysicsDynamicLines::getPoint(unsigned short index) const
{
	assert(index < mPoints.size() && "Point index is out of bounds!!");
	return mPoints[index];
}
//------------------------------------------------------------------------------------------------
unsigned short PhysicsDynamicLines::getNumPoints(void) const
{
	return (unsigned short)mPoints.size();
}
//------------------------------------------------------------------------------------------------
void PhysicsDynamicLines::setPoint(unsigned short index, const Ogre::Vector3 &value)
{
	assert(index < mPoints.size() && "Point index is out of bounds!!");

	mPoints[index] = value;
	mDirty = true;
}
//------------------------------------------------------------------------------------------------
void PhysicsDynamicLines::clear()
{
	mPoints.clear();
	mDirty = true;
}
//------------------------------------------------------------------------------------------------
void PhysicsDynamicLines::update()
{
	if (mDirty) fillHardwareBuffers();
}
//------------------------------------------------------------------------------------------------
void PhysicsDynamicLines::createVertexDeclaration()
{
	Ogre::VertexDeclaration *decl = mRenderOp.vertexData->vertexDeclaration;
	decl->addElement(POSITION_BINDING, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
}
//------------------------------------------------------------------------------------------------
void PhysicsDynamicLines::fillHardwareBuffers()
{
	int size = mPoints.size();

	prepareHardwareBuffers(size,0);

	if (!size) {
		mBox.setExtents(Ogre::Vector3::ZERO,Ogre::Vector3::ZERO);
		mDirty=false;
		return;
	}

	Ogre::Vector3 vaabMin = mPoints[0];
	Ogre::Vector3 vaabMax = mPoints[0];

	Ogre::HardwareVertexBufferSharedPtr vbuf =
			mRenderOp.vertexData->vertexBufferBinding->getBuffer(0);

	Ogre::Real *prPos = static_cast<Ogre::Real*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
	{
		for(int i = 0; i < size; i++)
		{
			*prPos++ = mPoints[i].x;
			*prPos++ = mPoints[i].y;
			*prPos++ = mPoints[i].z;

			if(mPoints[i].x < vaabMin.x)
				vaabMin.x = mPoints[i].x;
			if(mPoints[i].y < vaabMin.y)
				vaabMin.y = mPoints[i].y;
			if(mPoints[i].z < vaabMin.z)
				vaabMin.z = mPoints[i].z;

			if(mPoints[i].x > vaabMax.x)
				vaabMax.x = mPoints[i].x;
			if(mPoints[i].y > vaabMax.y)
				vaabMax.y = mPoints[i].y;
			if(mPoints[i].z > vaabMax.z)
				vaabMax.z = mPoints[i].z;
		}
	}
	vbuf->unlock();

	mBox.setExtents(vaabMin, vaabMax);

	mDirty = false;
}

} /* namespace Engine */
