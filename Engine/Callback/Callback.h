/*
 * \file Callback.h
 *
 *  Created on: \date 8 ao�t 2012
 *      Author: \author joda
 *  \brief :
 */
 /*! \class Callback
   * \brief
   */
#ifndef CALLBACK_H_
#define CALLBACK_H_

#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <map>


/*
 *
 */

	typedef boost::function<void(void)> Function;

class Callback {
public:
	Callback();
	virtual ~Callback();

	bool addlistenneur(int identifiant,Function function);
	bool removelistenneur(int identifiant);
	void callback(int identifiant);

protected:
	typedef boost::signals2::signal<void (void)> ContactSignal;

private:

    std::map<int,ContactSignal*> listOfListenner ;
    std::map<int,ContactSignal*>::iterator listenner ;


};

#endif /* CALLBACK_H_ */
