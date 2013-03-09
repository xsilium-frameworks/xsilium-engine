/*
 * \file Downloader.cpp
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Downloader.h"

Downloader::Downloader() {

	resolvePaths = ResolvePaths::getInstance();
	mFetcher = new Fetcher();

	mDownloadedBytes = 0;
	mCurrentRepo = 0;

	// find out which OS we're running
#ifdef __linux__
	mOSPrefix = "linux";
#elif __APPLE__
	mOSPrefix = "mac";
#else
	mOSPrefix = "win32";
#endif

	// Build hosts list
	using boost::filesystem::exists;
	using boost::filesystem::path;

	path lPath = path(resolvePaths->getBinPath()) / path(MIRRORS_RESOURCE);
	if (exists(lPath)) {
		std::ifstream lMirrorsFile(lPath.c_str());
		if (lMirrorsFile.is_open() && lMirrorsFile.good()) {
			std::string lMirror;
			while (lMirrorsFile.good()) {
				getline(lMirrorsFile, lMirror);
				// TODO: some sanity checks on the mirror url
				mHosts.push_back(lMirror + mOSPrefix + "/");
			}
			lMirrorsFile.close();
		}
	}

	// add hardcoded/fallback hosts
	//mHosts.push_back("http://127.0.0.1/");
	mHosts.push_back("http://update.xsilium.com/" + mOSPrefix + "/");

	mPatchScriptName = "patch.txt";
	mPatchLogName = "latest_changes.txt";

	mActiveHost = 0;

	curl_global_init(CURL_GLOBAL_ALL);


}

Downloader::~Downloader() {
	curl_global_cleanup();
	mActiveHost = 0;
	mHosts.clear();

}


void Downloader::_fetchPatchScript(std::string out) {

	using boost::filesystem::exists;
	using boost::filesystem::is_directory;
	using boost::filesystem::create_directory;
	using boost::filesystem::path;

	// first of all, we need to prepare the filesystem; directories etc
	if (exists(path(resolvePaths->getTempPath()))) {
		// if it exists but not a directory... something is wrong, remove it
		if (!is_directory(path(resolvePaths->getTempPath())))
			// TODO: do something here, throw an exception maybe
			printf("TMP path exists but is not a directory\n");

	} else {
		// it doesn't exist, let's create our directory
		printf("TMP path doesn't exist, creating it\n");
		create_directory(path(resolvePaths->getTempPath()));
	}

	printf("resolving patch server...");
	// find an active host
	std::list<std::string>::const_iterator _host = mHosts.begin();
	while (!mActiveHost) {
		mActiveHost = (std::string*)&(*_host);
		bool res;
		//try {
		std::string url = (*mActiveHost) + mPatchScriptName;
		printf("server: %s \n",url.c_str());
		res = mFetcher->download(url, out, 3);
		//fetchFile(url, out);
		//} catch (BadRequest& e) {
		if (!res) {
			mActiveHost = 0;
			if ((++_host) == mHosts.end())
				throw BadPatchURL("could not find an active host");
		}
	}

};

void Downloader::_fetchPatchLog(std::string out)
{
	assert(mActiveHost);
	std::string url = (*mActiveHost) + mPatchLogName;
	printf("fetching patch log from %s \n ",url.c_str());

	bool res = mFetcher->download(url, out, 3);
	if (!res) {
		throw BadPatchURL("could not find an active host for patch log!");
	}
}

long long Downloader::calcRepositorySize(Repository* inRepo)
{

	std::cout << "Calculating repositority size " << inRepo->getVersion().toNumber() << "\n";
	int i;
	long long  lSize = 0;
	//int nrEntries = inRepo->getEntries().size();
	std::string lUrl;
	std::vector<PatchStructure*> lEntries;

	CURL *curl = curl_easy_init();

	if (inRepo->isArchived()) {
		PatchStructure* lArchive = inRepo->getArchive();
		lUrl = *mActiveHost + lArchive->Remote;

		lArchive->Filesize = mFetcher->fileSize(lUrl, curl);
		lSize = lArchive->Filesize;

		curl_easy_cleanup(curl);

		inRepo->setSize(lSize);
		return lSize;
	};

	for (i = 0; i < 2; ++i) {
		PATCHOP op = (i == 0) ? P_CREATE : P_MODIFY;

		lEntries = inRepo->getEntries(op);
		PatchStructure* lEntry = 0;
		while (!lEntries.empty()) {
			lEntry = lEntries.back();

			// build up target URL
			lUrl = *mActiveHost + lEntry->Remote;

			lEntry->Filesize = mFetcher->fileSize(lUrl, curl);
			lSize += lEntry->Filesize;

			//std::cout << "Found file with size: " << lEntry->Filesize << "\n";

			lEntry = 0;
			lEntries.pop_back();
		};

	}
	curl_easy_cleanup(curl);

	inRepo->setSize(lSize);

	std::cout << "Repositority " << inRepo->getVersion().toNumber() << " is " << lSize << " bytes large\n";
	return lSize;
}

bool Downloader::_fetchRepository(Repository *inRepo,
		int nrRetries)
{

	using boost::filesystem::exists;
	using boost::filesystem::is_directory;
	using boost::filesystem::create_directory;

	if (nrRetries < 0)
		nrRetries = 0;

	printf("downloading patch files \n");
	this->calcRepositorySize(inRepo);
	//Launcher::getSingleton().getRenderer()->injectPatchSize(inRepo->getSize());

	bool realProgress = false;
#ifdef KARAZEH_REAL_PROGRESS
	mCurrentRepo = inRepo;
	mDownloadedBytes = 0;
	realProgress = true;
#else
	int idx = 0;
	int nrEntries = inRepo->getEntries().size();
#endif

	// download all CREATE and MODIFY entries' remote files
	int i;

	std::string url;
	std::vector<PatchStructure*> lEntries;
	CURL *curl = curl_easy_init();

	// if it's an archived repository, fetch the archive only
	if (inRepo->isArchived()) {

		PatchStructure *lArchive = inRepo->getArchive();
		bool downloaded = false;
		if (exists(lArchive->Temp)) {
			// compare the checksum to verify the file
			MD5 md5;
			if (md5.digestFile((char*)lArchive->Temp.c_str()) == lArchive->Checksum) {
				// no need to download
				downloaded = true;
				printf("Archive already downloaded, skipping \n");
			} else
				printf("MD5 mismatch, re-downloading %s \n ",lArchive->Temp.c_str());
		}

		// TODO: re-try in case of download failure
		std::string lUrl = *mActiveHost + lArchive->Remote;
		printf("downloading archive %s \n",lUrl.c_str());
		if (!downloaded) {
			//fetchFile(url, lEntry->Temp);
			mFetcher->download(lUrl, lArchive->Temp, nrRetries, realProgress, curl);
		}

		curl_easy_cleanup(curl);
		return true;
	};

	// it's not archived, get all the files
	for (i = 0; i < 2; ++i) {
		PATCHOP op = (i == 0) ? P_CREATE : P_MODIFY;

		lEntries = inRepo->getEntries(op);
		PatchStructure* lEntry = 0;
		while (!lEntries.empty()) {
			lEntry = lEntries.back();

			// build up target URL
			url = *mActiveHost + lEntry->Remote;

			// TODO: check if file has been downloaded before
			bool downloaded = false;
			if (exists(lEntry->Temp)) {
				// compare the checksum to verify the file
				MD5 md5;
				if (md5.digestFile((char*)lEntry->Temp.c_str()) == lEntry->Checksum) {
					// no need to download
					downloaded = true;
					printf("File already downloaded, skipping\n");
				} else
					printf("MD5 mismatch, re-downloading %s \n ",lEntry->Temp.c_str());
			}

			// TODO: re-try in case of download failure
			if (!downloaded) {
				//fetchFile(url, lEntry->Temp);
				mFetcher->download(url, lEntry->Temp, nrRetries, realProgress, curl);
			}

			++idx;
			//Launcher::getSingleton().getRenderer()->injectPatchProgress(idx * 1.0f / (nrEntries-1) * 100.0f);

			lEntry = 0;
			lEntries.pop_back();
		};

	}
	curl_easy_cleanup(curl);

	return true;
};

void Downloader::_updateDownloadProgress(double inStep) {
	mDownloadedBytes += inStep;

	//Launcher::getSingleton().getRenderer()->injectPatchProgress(mDownloadedBytes * 1.0f / mCurrentRepo->getSize() * 100.0f);
}

