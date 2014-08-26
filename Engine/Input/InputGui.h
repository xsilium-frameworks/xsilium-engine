/*
* \file InputGui.h
*
*  Created on: \date 25 août 2014
*      Author: \author xelfe joda
*  \brief : Fichier d'en-tête de la classe InputGui
*/
#ifndef INPUTGUI_H_
#define INPUTGUI_H_

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "Input/InputManager.h"

/*!
* \namespace Engine
* \brief Espace de nommage regroupant les dfférentes classes du moteur.
*/
namespace Engine {

	/*!
	* \class InputGui
	* \brief Classe de gestion des input pour GUI.
	*
	*/
	class InputGui : public OIS::KeyListener, public OIS::MouseListener {
	public:
		/*!
		*  \brief Constructeur.
		*
		*  Constructeur de la classe InputGui.
		*
		*/
		InputGui();

		/*!
		*  \brief Destructeur.
		*
		*  Destructeur abstrait de la classe InputGui.
		*
		*/
		virtual ~InputGui();

		/*!
		*
		* \brief Méthode appellé lorsque touche enfoncé.
		*
		* \return true
		*
		*/
		bool keyPressed(const OIS::KeyEvent &keyEventRef);

		/*!
		*
		* \brief Méthode appellé lorsque touche relâché.
		*
		* \return true
		*
		*/
		bool keyReleased(const OIS::KeyEvent &keyEventRef);

		/*!
		*
		* \brief Méthode appellé lorsque souris en déplacement.
		*
		* \return true
		*
		*/
		bool mouseMoved( const OIS::MouseEvent &e );

		/*!
		*
		* \brief Méthode appellé lorsque souris clic enfoncé.
		*
		* \return true
		*
		*/
		bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );

		/*!
		*
		* \brief Méthode appellé lorsque souris clic relâché.
		*
		* \return true
		*
		*/
		bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

		/*!
		*
		* \brief Méthode d'initialisation de la souris.
		*
		*/
		void initialisationMouse();

	};
}
#endif /* INPUTGUI_H_ */

