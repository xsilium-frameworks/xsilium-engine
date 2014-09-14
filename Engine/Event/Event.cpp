/*
 * \file Event.cpp
 *
 *  Created on: \date 10 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Event.h"

Event::Event() {
	// TODO Auto-generated constructor stub

}

Event::~Event() {
	// TODO Auto-generated destructor stub
}

void Event::setProperty(const std::string inName, const std::string inValue) {
	if ( hasProperty(inName) ) {
		mProperties.find(inName)->second = inValue;
		return;
	}
	mProperties.insert( std::make_pair(inName, inValue) );
}

std::string Event::getProperty(std::string inName) {
	return mProperties.find(inName)->second;
}

bool Event::hasProperty(std::string inName) {
	return (mProperties.find(inName) != mProperties.end());
}

int Event::getCountArgument()
{
	return mProperties.size();
}


