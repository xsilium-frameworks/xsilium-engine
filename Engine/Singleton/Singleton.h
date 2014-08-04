/*
 * \file Singleton.h
 *
 *  Created on: \date 2 aožt 2014
 *      Author: \author joda
 *  \brief :
 */
#ifndef SINGLETON_H_
#define SINGLETON_H_


#include "stdlib.h"

namespace Engine
{
template <typename Tsingleton>
class Singleton
{
public:
	static Tsingleton *getInstance ()
	{
		if(NULL == _singleton)
			_singleton = new Tsingleton;

		return _singleton ;
	}

	static void DestroyInstance()
	{
		if (NULL != _singleton)
		{
			delete _singleton;
			_singleton = NULL;
		}
	}

protected:
	Singleton (){}
	~Singleton() {}

private:
	static Tsingleton * _singleton ;


};
}
template <typename Tsingleton>
Tsingleton *Engine::Singleton<Tsingleton>::_singleton = NULL;




#endif /* SINGLETON_H_ */
