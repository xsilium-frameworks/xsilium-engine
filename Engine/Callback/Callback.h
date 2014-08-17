/*
 * \file Callback.h
 *
 *  Created on: \date 8 ao�t 2012
 *      Author: \author joda
 *  \brief : Fichier d'en-tête de la classe Callback
 */

#ifndef CALLBACK_H_
#define CALLBACK_H_

#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <map>

/*!
 * \namespace Engine
 * \brief Espace de nommage regroupant les dfférentes classes du moteur
 */
namespace Engine {

typedef boost::function<void(void)> Function;

/*! \class Callback
 * \brief Classe qui gere les callbacks
 *
 *  Classe qui gere les callbacks entre classes afin que l'on est pas de probleme entre threads
 */

class Callback {
public:
	/*!
	 *  \brief Constructeur
	 *
	 *  Constructeur de la classe Callback
	 *
	 */
	Callback();

	/*!
	 *  \brief Destructeur
	 *
	 *  Destructeur de la classe Callback
	 */

	virtual ~Callback();

	/*!
	 *  \brief Ajout d'une function a appeler
	 *
	 *  Methode qui permet d'ajouter une fonction a appeler pour un certain identifiant
	 *
	 *  \param[in] identifiant : Identifiant pour lequel la fonction va etre appeler
	 *  \param[in] function : la fonction qui va etre appel�e
	 *  \return true si la fonction a ete ajout�e sinon false
	 */

	bool addlistenneur(int identifiant, Function function);

	/*!
	 *  \brief Retrait de la fonctions affecter a un identifiant
	 *
	 *  Methode qui permet de retirer la fonction a appeler pour un certain identifiant
	 *
	 *  \param[in] identifiant : Identifiant pour lequel la fonction est enregistre
	 *  \return true si la fonction a ete retirer sinon false
	 */

	bool removelistenneur(int identifiant);

	/*!
	 *  \brief appel de la fonction affecter a un identifiant
	 *
	 *  Methode qui permet appeler la fonction affecter a l'identifiant
	 *
	 *  \param[in] identifiant : Identifiant pour lequel la fonction est enregistre
	 */

	void callback(int identifiant);

protected:

	typedef boost::signals2::signal<void(void)> ContactSignal;

private:

	std::map<int, ContactSignal*> listOfListenner; /*!< liste des fonctions */
	std::map<int, ContactSignal*>::iterator listenner; /*!< fonction courante*/

};

}

#endif /* CALLBACK_H_ */
