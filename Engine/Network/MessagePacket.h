/*
 * \file MessagePacket.h
 *
 *  Created on: \date 29 oct. 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef SRC_SERVER_SHARED_NETWORK_MESSAGEPACKET_H_
#define SRC_SERVER_SHARED_NETWORK_MESSAGEPACKET_H_

#include <string>
#include <sstream>
#include <boost/serialization/map.hpp>

namespace Engine {

/*
 *
 */
class MessagePacket {

	friend class boost::serialization::access;

public:
	MessagePacket();
	virtual ~MessagePacket();

	template<typename Type1, typename Type2>
	void setProperty(Type1 inName, Type2 inValue = "") {
		std::string key = toString(inName);
		std::string data = toString(inValue);

		if (hasProperty(key)) {
			content.find(key)->second = data;
			return;
		}
		content.insert(std::make_pair(key, data));
	}

	template<typename Type1>
	bool hasProperty(Type1 inName) {
		std::string key = toString(inName);
		return (content.find(key) != content.end());
	}

	template<typename Type1>
	std::string getProperty(Type1 inName) {
		std::string key = toString(inName);
		return content.find(key)->second;
	}

	int getOpcode();
	int getSousOpcode();

	void setOpcode(int opcode);
	void setSousOpcode(int sousOpcode);

protected:


	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & opcode;
		ar & sousOpcode;
		ar & content;
	}

private:
	int opcode;
	int sousOpcode;
	std::map<std::string, std::string> content;

	template<typename T>
	std::string toString(T variable) {
		std::ostringstream ss;

		ss << variable;

		return ss.str();
	}

};

} /* namespace Engine */

#endif /* SRC_SERVER_SHARED_NETWORK_MESSAGEPACKET_H_ */
