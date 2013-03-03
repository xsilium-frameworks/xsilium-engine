/*
 * \file Fetcher.h
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef FETCHER_H_
#define FETCHER_H_

#include <string>
#include <curl/curl.h>
#include <curl/easy.h>

#include "Downloader/Downloader.h"

class Downloader;

/*! \class Fetcher
 *  \brief
 *  The Fetcher performs all the libcurl requests and does the downloading.
 *  Fetcher instances are spawned in boost::threads.
 */
class Fetcher {
public:
	Fetcher() {};
	Fetcher(const Fetcher& src) {
		clone(src);
	};
	Fetcher& operator=(const Fetcher& rhs) {
		if (this == &rhs)
			return (*this);

		clone(rhs);

		return (*this);
	};
	~Fetcher() { };

	bool download(std::string url, std::string out, int retries=0, bool withProgress = false, CURL* curl=0);

	static size_t write_func(void *ptr, size_t size, size_t nmemb, FILE *stream);
	static size_t read_func(void *ptr, size_t size, size_t nmemb, FILE *stream);
	static size_t handle_headers(void *ptr, size_t size, size_t nmemb, void *stream);
	static int progress_func(void* something, double t, double d, double ultotal, double ulnow);
	static double delta;
	long long fileSize(std::string url, CURL* curl=0);

	static std::string last_content_length;
private:
	void clone(const Fetcher& src) { };
};


#endif /* FETCHER_H_ */
