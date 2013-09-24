/*
 * \file Callback.cpp
 *
 *  Created on: \date 30 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Callback.h"

Callback::Callback()
{

}

Callback::~Callback()
{
	for (listenner=listOfListenner.begin(); listenner !=listOfListenner.end(); ++listenner)
	{
		delete listenner->second;
		listOfListenner.erase(listenner);
	}
}

bool Callback::addlistenneur(int identifiant,Function function)
{


	listenner = listOfListenner.find(identifiant) ;
	if ( listenner == listOfListenner.end())
	{
		ContactSignal * signal = new ContactSignal() ;
		signal->connect(function);
		listOfListenner[identifiant] = signal ;
		return true;
	}
	else
	{
		listenner->second->connect(function);
		return true;
	}
	return false;
}

void Callback::callback(int identifiant)
{
	listenner = listOfListenner.find(identifiant) ;
	if ( listenner != listOfListenner.end())
	{
		(*listenner->second)();
	}
}

bool Callback::removelistenneur(int identifiant)
{
	listenner = listOfListenner.find(identifiant) ;
	if ( listenner != listOfListenner.end())
	{
		delete listenner->second;
		listOfListenner.erase(listenner);
		return true ;
	}
	return false ;
}
