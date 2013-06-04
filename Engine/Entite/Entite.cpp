/*
 * \file Entite.cpp
 *
 *  Created on: \date 8 mai 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Entite.h"

Entite::Entite() {
	vieEntite = 0;
	nom = 0;
	charHeight = 0;
	turnSpeed = 0;
	mBodyNode = 0;
	mBodyEnt = 0;

	sceneMgr = 0;

}

Entite::~Entite() {
	delete nom;
}

void Entite::setVieEntite(int Vie)
{
	this->vieEntite = Vie;
}
int Entite::getVieEntite()
{
	return this->vieEntite;
}

void Entite::setNom(std::string nom)
{
	this->nom = new std::string(nom.c_str());
}

std::string * Entite::getNom()
{
	return this->nom ;
}

Ogre::SceneNode* Entite::getBody()
{
	return this->mBodyNode;
}

double Entite::getTurnSpeed()
{
	return this->turnSpeed;
}

int Entite::getRunSpeed()
{
	return this->runSpeed ;
}
