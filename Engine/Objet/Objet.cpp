/*
 * \file Objet.cpp
 *
 *  Created on: \date 2 mai 2014
 *      Author: \author joda
 *  \brief :
 */
#include "Objet.h"

Objet::Objet(Ogre::SceneManager* sceneMgr,const char * nomObjet,const char * fileMesh) {

	setNom(nomObjet);
	this->sceneMgr = sceneMgr;

	usure = 0;
	typeObjet = 0;

	objetEnt = sceneMgr->createEntity(nomObjet, fileMesh);

}

Objet::~Objet() {
	sceneMgr->destroyEntity(objetEnt);
}

void Objet::setNom(const char * nom)
{
	this->nom = new std::string(nom);
}

std::string * Objet::getNom()
{
	return this->nom ;
}

Ogre::Entity* Objet::getObjet()
{
	return this->objetEnt;
}

void Objet::setType(int typeObjet)
{
	this->typeObjet = typeObjet;
}
int Objet::getType()
{
	return this->typeObjet;
}
