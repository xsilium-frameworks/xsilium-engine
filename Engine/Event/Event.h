/*
 * \file Event.h
 *
 *  Created on: \date 10 mars 2013
 *      Author: \author joda
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

	template<typename Type1, typename Type2>
	void setProperty(Type1 inName, Type2 inValue = "")
	{
		std::string key = toString(inName);
		std::string data = toString(inValue);
		if ( hasProperty(key) ) {
			mProperties.find(key)->second = data;
			return;
		}
		mProperties.insert( std::make_pair(key, data) );
	}

	template<typename Type1>
	std::string getProperty(Type1 inName)
	{
		std::string retour;
		if (hasProperty(inName))
		{
			std::string key = toString(inName);
			retour = mProperties.find(key)->second;
		}
		return retour; 
	}

	template<typename Type1>
	bool hasProperty(Type1 inName)
	{
		std::string key = toString(inName);
		return (mProperties.find(key) != mProperties.end());
	}

	int getCountArgument();

private:

	typedef std::map<std::string, std::string> property_t;
	property_t mProperties;
    
    template<typename T>
    std::string toString(T variable) {
        std::ostringstream ss;
        
        ss << variable;
        
        return ss.str();
    }

};

#endif /* EVENT_H_ */
