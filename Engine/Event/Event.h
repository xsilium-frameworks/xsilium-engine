/*
 * \file Event.h
 *
 *  Created on: \date 10 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <map>
#include <string>
#include <sstream>

/*
 *
 */
class Event {
public:
	Event();
	virtual ~Event();


	std::string getProperty(std::string inName);
	void setProperty(std::string inName,std::string inValue = "");
	bool hasProperty(std::string inName);

	int getCountArgument();

private:

	  typedef std::map< std::string, std::string > property_t;
	  property_t		mProperties;


};

template <typename T>
  std::string ToString ( T variable )
  {
     std::ostringstream ss;

     ss << variable;

     return ss.str();
  }

#endif /* EVENT_H_ */
