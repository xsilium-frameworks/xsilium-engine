/*
 * \file PhysicsDynamicLines.h
 *
 *  Created on: \date 9 janv. 2015
 *      Author: \author joda
 *  \brief :
 */
#ifndef ENGINE_PHYSICS_PHYSICSDYNAMICLINES_H_
#define ENGINE_PHYSICS_PHYSICSDYNAMICLINES_H_


#include "PhysicsDynamicRenderable.h"


namespace Engine {


enum {
	POSITION_BINDING,
	TEXCOORD_BINDING
};


/*
 *
 */
class PhysicsDynamicLines : public PhysicsDynamicRenderable {

	typedef Ogre::RenderOperation::OperationType OperationType;


public:
	PhysicsDynamicLines(OperationType opType=Ogre::RenderOperation::OT_LINE_STRIP);
	virtual ~PhysicsDynamicLines();

	/// Add a point to the point list
	void addPoint(const Ogre::Vector3 &p);
	/// Add a point to the point list
	void addPoint(Ogre::Real x, Ogre::Real y, Ogre::Real z);

	/// Change the location of an existing point in the point list
	void setPoint(unsigned short index, const Ogre::Vector3 &value);

	/// Return the location of an existing point in the point list
	const Ogre::Vector3& getPoint(unsigned short index) const;

	/// Return the total number of points in the point list
	unsigned short getNumPoints(void) const;

	/// Remove all points from the point list
	void clear();

	/// Call this to update the hardware buffer after making changes.
	void update();

	/** Set the type of operation to draw with.
	 * @param opType Can be one of
	 *    - RenderOperation::OT_LINE_STRIP
	 *    - RenderOperation::OT_LINE_LIST
	 *    - RenderOperation::OT_POINT_LIST
	 *    - RenderOperation::OT_TRIANGLE_LIST
	 *    - RenderOperation::OT_TRIANGLE_STRIP
	 *    - RenderOperation::OT_TRIANGLE_FAN
	 *    The default is OT_LINE_STRIP.
	 */
	void setOperationType(OperationType opType);
	OperationType getOperationType() const;

protected:
	/// Implementation DynamicRenderable, creates a simple vertex-only decl
	virtual void createVertexDeclaration();
	/// Implementation DynamicRenderable, pushes point list out to hardware memory
	virtual void fillHardwareBuffers();

private:
	std::vector<Ogre::Vector3> mPoints;
	bool mDirty;
};

} /* namespace Engine */

#endif /* ENGINE_PHYSICS_PHYSICSDYNAMICLINES_H_ */
