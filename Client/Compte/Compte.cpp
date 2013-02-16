/*
 * \file Compte.cpp
 *
 *  Created on: \date 16 fŽvr. 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Compte/Compte.h"

Compte::Compte() {
	// init variable
    version = 0;
    platform = "";
    os = "";
    country = "";
    login = "";
    password = "";
    etapeDeLogin = 0;


}

Compte::~Compte() {
	// TODO Auto-generated destructor stub
}


void Compte::setEtapeDeLogin(uint8_t etapeDeLogin)
{
	this->etapeDeLogin = etapeDeLogin;
}
uint8_t Compte::getEtapeDeLogin()
{
	return this->etapeDeLogin;
}

void Compte::setLogin(const char * login)
{
	this->login = login;
}

const char * Compte::getLogin()
{
	return this->login;
}

void Compte::setPassWord(const char * password)
{
	this->password = password;
}

const char * Compte::getPassWord()
{
	return this->password;
}

void Compte::setVersion(uint16_t version)
{
	this->version = version;
}
uint16_t Compte::getVersion()
{
	return this->version;
}
