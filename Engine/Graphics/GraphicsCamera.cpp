/*
 * \file GraphicsCamera.cpp
 *
 *  Created on: \date 30 ao�t 2014
 *      Author: \author xelfe
 *  \brief : Fichier source de class GraphicsCamera
 */
#include "GraphicsCamera.h"

namespace Engine {

GraphicsCamera::GraphicsCamera() {
	mCamera			= 0;
	mTarget			= 0;
	mOrbiting		= false;
	mZooming		= false;
	mTopSpeed		= 150;
	mVelocity		= Ogre::Vector3::ZERO;
	mFastMove		= false;
	mStyle			= CS_MANUAL;
}

GraphicsCamera::~GraphicsCamera() {
}

void GraphicsCamera::setCamera(Ogre::Camera* cam) {
	mCamera = cam;
}

Ogre::Camera*	GraphicsCamera::getCamera() {
	return mCamera;
}

void GraphicsCamera::setTarget(Ogre::SceneNode* target) {

	if (target != mTarget) {
		mTarget = target;

		if(target) {
			setYawPitchDist(Ogre::Degree(0), Ogre::Degree(15), 150);
			mCamera->setAutoTracking(true, mTarget);
		}

		else {
			mCamera->setAutoTracking(false);
		}
	}
}

Ogre::SceneNode* GraphicsCamera::getTarget() {
	return mTarget;
}

void GraphicsCamera::setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist) {
	mCamera->setPosition(mTarget->_getDerivedPosition());
	mCamera->setOrientation(mTarget->_getDerivedOrientation());
	mCamera->yaw(yaw);
	mCamera->pitch(-pitch);
	mCamera->moveRelative(Ogre::Vector3(0, 0, dist));
}

void GraphicsCamera::setTopSpeed(Ogre::Real topSpeed) {
	mTopSpeed = topSpeed;
}

Ogre::Real GraphicsCamera::getTopSpeed() {
	return mTopSpeed;
}

void GraphicsCamera::setStyle(CameraStyle style) {

	if (mStyle != CS_ORBIT && style == CS_ORBIT) {
		setTarget(mTarget ? mTarget : mCamera->getSceneManager()->getRootSceneNode());
		mCamera->setFixedYawAxis(true);
		manualStop();
		setYawPitchDist(Ogre::Degree(0), Ogre::Degree(15), 150);
	}

	else if (mStyle != CS_FREELOOK && style == CS_FREELOOK) {
		mCamera->setAutoTracking(false);
		mCamera->setFixedYawAxis(true);
	}

	else if (mStyle != CS_MANUAL && style == CS_MANUAL) {
		mCamera->setAutoTracking(false);
		manualStop();
	}

	mStyle = style;
}

CameraStyle GraphicsCamera::getStyle() {
	return mStyle;
}

void GraphicsCamera::manualStop() {

	if (mStyle == CS_FREELOOK) {
		direction = Ogre::Vector3::ZERO;
		mVelocity = Ogre::Vector3::ZERO;
	}

}

bool GraphicsCamera::frameRenderingQueued(const Ogre::FrameEvent& evt) {

	if(mCamera) {

		if (mStyle == CS_FREELOOK) {

			// Vector d'acceleration bas� sur les entr�es
			Ogre::Vector3 accel = Ogre::Vector3::ZERO;
			if (direction.x == 1) accel += mCamera->getDirection();
			if (direction.x == -1) accel -= mCamera->getDirection();
			if (direction.z == 1) accel += mCamera->getRight();
			if (direction.z == -1) accel -= mCamera->getRight();
			//if (mGoingUp) accel += mCamera->getUp();
			//if (mGoingDown) accel -= mCamera->getUp();

			// SI accelerer, temps pour atteindre la vitesse maximal
			Ogre::Real topSpeed = mFastMove ? mTopSpeed * 20 : mTopSpeed;

			if (accel.squaredLength() != 0) {
				accel.normalise();
				mVelocity += accel * topSpeed * evt.timeSinceLastFrame * 10;
			}

			// Si accelere pas, temps pour un arr�t total
			else mVelocity -= mVelocity * evt.timeSinceLastFrame * 10;

			Ogre::Real tooSmall = std::numeric_limits<Ogre::Real>::epsilon();

			// keep camera velocity below top speed and above epsilon
			if (mVelocity.squaredLength() > topSpeed * topSpeed) {
				mVelocity.normalise();
				mVelocity *= topSpeed;
			}

			else if (mVelocity.squaredLength() < tooSmall * tooSmall)
				mVelocity = Ogre::Vector3::ZERO;

			if (mVelocity != Ogre::Vector3::ZERO) mCamera->move(mVelocity * evt.timeSinceLastFrame);
		}
	}

	return true;
}

void GraphicsCamera::injectMouseMove(const OIS::MouseEvent& evt) {

	if (mStyle == CS_ORBIT) {
		Ogre::Real dist = (mCamera->getPosition() - mTarget->_getDerivedPosition()).length();

		if (mOrbiting) {
			// yaw around the target, and pitch locally
			mCamera->setPosition(mTarget->_getDerivedPosition());

			mCamera->yaw(Ogre::Degree(-evt.state.X.rel * 0.25f));
			mCamera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.25f));

			mCamera->moveRelative(Ogre::Vector3(0, 0, dist));

			// don't let the camera go over the top or around the bottom of the target
		}

		else if (mZooming) {
			// move the camera toward or away from the target
			// the further the camera is, the faster it moves
			mCamera->moveRelative(Ogre::Vector3(0, 0, evt.state.Y.rel * 0.004f * dist));
		}

		else if (evt.state.Z.rel != 0) {
			// move the camera toward or away from the target
			// the further the camera is, the faster it moves
			mCamera->moveRelative(Ogre::Vector3(0, 0, -evt.state.Z.rel * 0.0008f * dist));
		}
	}

	else if (mStyle == CS_FREELOOK) {
		mCamera->yaw(Ogre::Degree(-evt.state.X.rel * 0.15f));
		mCamera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.15f));
	}

}

void GraphicsCamera::setDirection(Ogre::Vector3 direction)
{
	this->direction = direction;
}

}
