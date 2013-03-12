/*
 * \file ResolvePaths.h
 *
 *  Created on: \date 3 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef RESOLVEPATHS_H_
#define RESOLVEPATHS_H_

#include <string>
#include "Singleton/Singleton.h"
#include <boost/filesystem.hpp>
#include "XsiliumFramework.h"
#include "Define.h"

#include "Binreloc/binreloc.h"
#include "fcntl.h"

/*
 *
 */
class ResolvePaths : public xsilium::Singleton<ResolvePaths>
{
	friend class xsilium::Singleton<ResolvePaths>;
public:
	ResolvePaths();
	virtual ~ResolvePaths();


    std::string& getRootPath();
    std::string& getTempPath();
    std::string& getBinPath();


private:
    std::string mBinPath;
    std::string mRootPath;
    std::string mTempPath;
    std::string mLogPath;
};

#endif /* RESOLVEPATHS_H_ */
