/*
 * \file PhysicsDebugDrawer.cpp
 *
 *  Created on: \date 9 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#include "PhysicsDebugDrawer.h"

namespace Engine {

PhysicsDebugDrawer::PhysicsDebugDrawer(Ogre::SceneNode *node, btDynamicsWorld *world) : mNode(node),
		mWorld(world),
		mDebugOn(true) {
	mLineDrawer = new PhysicsDynamicLines(Ogre::RenderOperation::OT_LINE_LIST);
	mNode->attachObject(mLineDrawer);

	if (!Ogre::ResourceGroupManager::getSingleton().resourceGroupExists("BtOgre"))
		Ogre::ResourceGroupManager::getSingleton().createResourceGroup("BtOgre");
	if (!Ogre::MaterialManager::getSingleton().resourceExists("BtOgre/DebugLines"))
	{
		Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create("BtOgre/DebugLines", "BtOgre");
		mat->setReceiveShadows(false);
		mat->setSelfIllumination(1,1,1);
	}

	mLineDrawer->setMaterial("BtOgre/DebugLines");

}

PhysicsDebugDrawer::~PhysicsDebugDrawer() {
	Ogre::MaterialManager::getSingleton().remove("BtOgre/DebugLines");
	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("BtOgre");
	delete mLineDrawer;
}

void PhysicsDebugDrawer::step()
{
	if (mDebugOn)
	{
		mWorld->debugDrawWorld();
		mLineDrawer->update();
		mNode->needUpdate();
		mLineDrawer->clear();
	}
	else
	{
		mLineDrawer->clear();
		mLineDrawer->update();
		mNode->needUpdate();
	}
}

void PhysicsDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{
	mLineDrawer->addPoint(PhysicsConvert::toOgre(from));
	mLineDrawer->addPoint(PhysicsConvert::toOgre(to));
}

void PhysicsDebugDrawer::drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
{
	mLineDrawer->addPoint(PhysicsConvert::toOgre(PointOnB));
	mLineDrawer->addPoint(PhysicsConvert::toOgre(PointOnB) + (PhysicsConvert::toOgre(normalOnB) * distance * 20));
}

void PhysicsDebugDrawer::reportErrorWarning(const char* warningString)
{
	Ogre::LogManager::getSingleton().logMessage(warningString);
}

void PhysicsDebugDrawer::draw3dText(const btVector3& location,const char* textString)
{
}

//0 for off, anything else for on.
void PhysicsDebugDrawer::setDebugMode(int isOn)
{
	mDebugOn = (isOn == 0) ? false : true;

	if (!mDebugOn)
		mLineDrawer->clear();
}

//0 for off, anything else for on.
int	PhysicsDebugDrawer::getDebugMode() const
{
	return mDebugOn;
}


} /* namespace Engine */
