/*
 * \file Utility.h
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <typeinfo>
#include <vector>
#include <sstream>
#include <string>

#include "Exception/Exception.h"

class Utility {

public:

	/* splits a string s using the delimiter delim */
	inline static
	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		std::stringstream ss(s);
		std::string item;
		while(std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}

	template<typename T>
	inline static std::string stringify(const T& x)
	{
		std::ostringstream o;
		if (!(o << x))
			throw BadConversion(std::string("stringify(")
		+ typeid(x).name() + ")");
		return o.str();
	}

	// helper; converts an integer-based type to a string
	template<typename T>
	inline static void convert(const std::string& inString, T& inValue,
			bool failIfLeftoverChars = true)
	{
		std::istringstream _buffer(inString);
		char c;
		if (!(_buffer >> inValue) || (failIfLeftoverChars && _buffer.get(c)))
			throw BadConversion(inString);
	}

	template<typename T>
	inline static T convertTo(const std::string& inString,
			bool failIfLeftoverChars = true)
	{
		T _value;
		convert(inString, _value, failIfLeftoverChars);
		return _value;
	}

};




#endif /* UTILITY_H_ */
