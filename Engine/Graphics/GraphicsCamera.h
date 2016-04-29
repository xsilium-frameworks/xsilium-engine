/*
 * \file GraphicsCamera.h
 *
 *  Created on: \date 31 ao�t 2014
 *      Author: \author xelfe
 *  \brief : Fichier d'en-t�te du gestionnaire d'interface GUI
 */
#ifndef __GraphicsCamera_H__
#define __GraphicsCamera_H__

#include "Ogre.h"
#include <limits>

#include <OISMouse.h>

#include <Singleton/Singleton.h>
#include <Event/Event.h>

/*!
 * \namespace Engine
 * \brief Espace de nommage regroupant les dff�rentes classes du moteur.
 */
namespace Engine {

/*! \enum CameraStyle
 *  \brief Constante de style.
 *
 *  Constante de nom de style de mouvements disponible pour GraphicsCamera
 *
 */
enum CameraStyle {
    CS_FREELOOK, CS_ORBIT, CS_MANUAL, CS_3PERS
};

/*!
 * \class GraphicsCamera
 * \brief Classe de controle de la camera.
 *
 * Classe permettant de g�rer les diff�rent style de camera.
 *
 */
class GraphicsCamera: public Singleton<GraphicsCamera> {

    friend class Singleton<GraphicsCamera> ;

public:
    GraphicsCamera();
    virtual ~GraphicsCamera();

    /*-----------------------------------------------------------------------------
     | Swaps the camera on our camera man for another camera.
     -----------------------------------------------------------------------------*/
    virtual void setCamera(Ogre::Camera* cam);

    virtual Ogre::Camera* getCamera();

    /*-----------------------------------------------------------------------------
     | Sets the target we will revolve around. Only applies for orbit style.
     -----------------------------------------------------------------------------*/
    virtual void setTarget(Ogre::SceneNode* target);
    virtual void setTargetByName(Ogre::String targetName);

    virtual Ogre::SceneNode* getTarget();

    /*-----------------------------------------------------------------------------
     | Sets the spatial offset from the target. Only applies for orbit style.
     -----------------------------------------------------------------------------*/
    virtual void setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist);

    /*-----------------------------------------------------------------------------
     | Sets the camera's top speed. Only applies for free-look style.
     -----------------------------------------------------------------------------*/
    virtual void setTopSpeed(Ogre::Real topSpeed);

    virtual Ogre::Real getTopSpeed();

    /*-----------------------------------------------------------------------------
     | Sets the movement style of our camera man.
     -----------------------------------------------------------------------------*/
    virtual void setStyle(CameraStyle style);

    virtual CameraStyle getStyle();

    /*-----------------------------------------------------------------------------
     | Manually stops the camera when in free-look mode.
     -----------------------------------------------------------------------------*/
    virtual void manualStop();

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    /*-----------------------------------------------------------------------------
     | Processes mouse movement differently for each style.
     -----------------------------------------------------------------------------*/
    virtual void injectMouseMove(const OIS::MouseEvent& evt);

    void processEvent(Event * event);

    void initCamera(Ogre::SceneManager* m_pSceneMgr, Ogre::RenderWindow* m_pRenderWnd);

    Ogre::SceneNode*& getPPitchNode();
    void setPPitchNode(Ogre::SceneNode*& pPitchNode);

    void setPosition(Ogre::Vector3& position);

protected:

    Ogre::Camera* mCamera;
    CameraStyle mStyle;
    Ogre::SceneNode* mTarget;
    bool mOrbiting;
    bool mZooming;
    Ogre::Real mTopSpeed;
    Ogre::Vector3 mVelocity;
    bool mFastMove;
    Ogre::Vector3 direction;

private:

    // Nodes needed for 3rd camera system
    Ogre::SceneNode* m_pNode;		// main node
    Ogre::SceneNode* m_pCamNode;	// camera node attached to main node
    Ogre::SceneNode* m_pPitchNode;  // pitch node attached to camera node
};
}

#endif
