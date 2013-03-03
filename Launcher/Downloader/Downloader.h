/*
 * \file Downloader.h
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef DOWNLOADER_H_
#define DOWNLOADER_H_

#include "Downloader/Fetcher/Fetcher.h"
#include "Repository/Repository.h"
#include "ResolvePaths/ResolvePaths.h"
#include <list>
#include <fstream>
#include "MD5/md5.hpp"

#include "Define.h"


class Fetcher;

/*
 *
 */
class Downloader : public xsilium::Singleton<Downloader>
{
	friend class xsilium::Singleton<Downloader>;
public:
	Downloader();
	virtual ~Downloader();

	/*! \brief
	 *  Attempts to retrieve the patch list from any of the registered
	 *  patch servers.
	 *
	 *  The patch list is stored in PROJECT_TEMP_DIR, which is created if it
	 *  does not exist. Further, this method could throw a BadPatchURL exception
	 *  in the case where something goes wrong while retrieving the list.
	 *
	 *  \note
	 *  This is called internally in the Patcher::validate() routine.
	 */
	void _fetchPatchScript(std::string out);

	/*! \brief
	 *  Attempts to retrieve the patch log (latest changes) from the
	 *  active host.
	 *
	 *  \note
	 *  This is called internally in the Patcher::validate() routine.
	 *
	 *  \warn
	 *  MUST be called aftrer _fetchPatchScript && mActiveHost != 0
	 */
	void _fetchPatchLog(std::string out);

	/*!
	 * \brief
	 *  Downloads all the files and diffs needed by every repository only if
	 *  they have not already been downloaded. This method transmits the
	 *  PatchProgress which injects Renderers with the download progress.
	 *
	 * \remark
	 *  When a file is downloaded, its MD5 checksum is calculated and compared
	 *  against the original remote one, in case of a mismatch, the file is
	 *  re-downloaded up to nrRetries times, if still invalid, an exception will
	 *  be thrown of type BadPatchFile which contains the respective PatchEntry.
	 *
	 * TODO:
	 *  Use some kind of persistent volume to track which files have been
	 *  already downloaded in case of interruption so the list won't have to
	 *  be re-downloaded entirely.
	 *
	 * \return
	 *  true if all files were successfully downloaded, false otherwise
	 *
	 * \warn
	 *  MUST be called before the Patcher is ordered to process
	 */
	bool _fetchRepository(Repository* inRepo, int nrRetries = 3);

	void _updateDownloadProgress(double inStep);

protected:
	Repository *mCurrentRepo;
	long long mDownloadedBytes;

	//! grabs a file from url using libcurl and dumps it to out
	void fetchFile(std::string url, std::string out);

	long long calcRepositorySize(Repository* inRepo);

	std::list<std::string> mHosts;
	std::string* mActiveHost;
	std::string mPatchScriptName, mPatchLogName;

	/* Karazeh expects the patch server repository to host three
	 * directories for each OS;
	 *  "mac" for Apple patches
	 *  "win32" for Windows patches
	 *  "linux" for Linux patches
	 * mOSPrefix will be set to one of the above and will be appended
	 * to the ActiveHost or mirror
	 */
	std::string mOSPrefix;

private:

	Fetcher * mFetcher;
	ResolvePaths * resolvePaths;

};

#endif /* DOWNLOADER_H_ */
