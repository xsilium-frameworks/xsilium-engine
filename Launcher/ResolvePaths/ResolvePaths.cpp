/*
 * \file ResolvePaths.cpp
 *
 *  Created on: \date 3 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#include "ResolvePaths.h"

ResolvePaths::ResolvePaths() {
	using boost::filesystem::path;
	bool dontOverride = false;



	// locate the binary and build its path
#ifdef __linux__

	XsiliumFramework::getInstance()->getLog()->logMessage("Platform linux");

	// use binreloc and boost::filesystem to build up our paths
	int brres = br_init(0);
	if (brres == 0) {
		std::cerr << "binreloc could not be initialised\n";
	}
	char *p = br_find_exe_dir(".");
	mBinPath = std::string(p);
	free(p);
	mBinPath = path(mBinPath).make_preferred().string();

#elif __APPLE__
	// use NSBundlePath() to build up our paths
	mBinPath = path(Ogre::macBundlePath() + "/Contents/MacOS").make_preferred().string();
	// create the folders if they doesn't exist
	boost::filesystem::create_directory(path(mBinPath + "/../Resources").make_preferred());
	boost::filesystem::create_directory(path(mBinPath + "/../Resources/Log").make_preferred());
	boost::filesystem::create_directory(path(mBinPath + "/../Resources/Temp").make_preferred());

	mLogPath = (path(mBinPath).remove_leaf() / path("/Resources/Log").make_preferred()).string();
	mTempPath = (path(mBinPath).remove_leaf() / path("/Resources/Temp").make_preferred()).string();
	dontOverride = true;
#else
	// use GetModuleFileName() and boost::filesystem to build up our paths on Windows
	TCHAR szPath[MAX_PATH];

	if( !GetModuleFileName( NULL, szPath, MAX_PATH ) )
	{
		printf("Cannot install service (%d)\n", GetLastError());
		return;
	}

	mBinPath = std::string(szPath);
	mBinPath = path(mBinPath).remove_filename().make_preferred().string();
#endif

	// root is PIXY_DISTANCE_FROM_ROOT directories up from the binary's
	path lRoot = path(mBinPath);
	for (int i=0; i < DISTANCE_FROM_ROOT; ++i) {
		lRoot = lRoot.remove_leaf();
	}

	mRootPath = lRoot.make_preferred().string();
	if (!dontOverride) {
		mTempPath = (path(mRootPath) / path(PROJECT_TEMP_DIR)).make_preferred().string();
		mLogPath = (path(mRootPath) / path(PROJECT_LOG_DIR)).make_preferred().string();
	}

}

ResolvePaths::~ResolvePaths() {
	// TODO Auto-generated destructor stub
}


std::string& ResolvePaths::getRootPath() {
    return mRootPath;
  };
  std::string& ResolvePaths::getTempPath() {
    return mTempPath;
  };
  std::string& ResolvePaths::getBinPath() {
    return mBinPath;
  };
