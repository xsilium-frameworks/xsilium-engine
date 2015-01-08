/*
 * \file PhysicsDebugDrawer.h
 *
 *  Created on: \date 9 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#ifndef ENGINE_PHYSICS_PHYSICSDEBUGDRAWER_H_
#define ENGINE_PHYSICS_PHYSICSDEBUGDRAWER_H_

#include "PhysicsDynamicLines.h"
#include "PhysicsConvert.h"
#include "LinearMath/btIDebugDraw.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

namespace Engine {

/*
 *
 */
class PhysicsDebugDrawer : public btIDebugDraw {
public:
	PhysicsDebugDrawer(Ogre::SceneNode *node, btDynamicsWorld *world);
	virtual ~PhysicsDebugDrawer();

	void step();

	void drawLine(const btVector3& from,const btVector3& to,const btVector3& color);

	void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);

	void reportErrorWarning(const char* warningString);

	void draw3dText(const btVector3& location,const char* textString);

	//0 for off, anything else for on.
	void setDebugMode(int isOn);

	//0 for off, anything else for on.
	int	getDebugMode() const;


protected:
	Ogre::SceneNode *mNode;
	btDynamicsWorld *mWorld;
	PhysicsDynamicLines *mLineDrawer;
	bool mDebugOn;
};

} /* namespace Engine */

#endif /* ENGINE_PHYSICS_PHYSICSDEBUGDRAWER_H_ */
