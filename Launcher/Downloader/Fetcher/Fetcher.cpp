/*
 * \file Fetcher.cpp
 *
 *  Created on: \date 3 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Downloader/Fetcher/Fetcher.h"

	std::string Fetcher::last_content_length = "";
	double Fetcher::delta = 0;

size_t Fetcher::write_func(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	return fwrite(ptr, size, nmemb, stream);
}

size_t Fetcher::read_func(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	return fread(ptr, size, nmemb, stream);
}

int Fetcher::progress_func(void* something,
		double t, /* dltotal */
		double d, /* dlnow */
		double ultotal,
		double ulnow)
{
	Downloader::getInstance()->_updateDownloadProgress(d - delta);

	//printf("%f / %f (%g %%), delta = %f\n", d, t, d*100.0/t, d - delta);
	delta = d;

	return 0;
}

bool Fetcher::download(std::string url, std::string out, int retries, bool withProgress, CURL* curl) {

	//std::cout << "fetching URL: " << url << " => " << out << "...\n";

	//CURL *curl;
	CURLcode res;
	FILE *outfile;

	bool external = true; // external handle? do we have to clean up?

	if (!curl) {
		curl = curl_easy_init();
		external = false;
	}

	if(curl)
	{
		// TODO: make sure the directory exists and create it if it doesn't
		outfile = fopen(out.c_str(), "w");
		if (!outfile) {
			if (!external)
				curl_easy_cleanup(curl);
			//std::cout << "ERROR! Couldn't open file for writing: " << out;
			return false;
		}

		delta = 0.0;

		curl_easy_reset(curl);

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Fetcher::write_func);
		curl_easy_setopt(curl, CURLOPT_READFUNCTION, Fetcher::read_func);
		if (withProgress) {
			curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
			curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, Fetcher::progress_func);
		}
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, true);
		//curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, Bar);

		// curl_easy_perform() returns 0 on OK
		do {
			//std::cout << "CURL: trying...\n";
			res = curl_easy_perform(curl);
			//std::cout << "CURL: query result = " << res;
		} while ((res != 0) && (--retries) > 0);

		fclose(outfile);
		if (res != 0) {
			remove(out.c_str());
		}

		/* always cleanup */
		if (!external)
			curl_easy_cleanup(curl);

		//std::cout << "done fetching file\n";

		return (res == 0);
	}

	return true;
}

size_t Fetcher::handle_headers(void *ptr, size_t size, size_t nmemb, void *stream)
{
	using std::string;

	//std::cout << "Header str: " << (char*)ptr << "\n";
	//const boost::regex content_length_regex("Content-Length: [0-9]{1,}"); // Regex do video do youtube...
	//const boost::regex content_length_remove_regex("Content-Length: ");
	int numbytes = size*nmemb;
	// The data is not null-terminated, so get the last character, and replace
	// it with '\0'.
	char lastchar = *((char *) ptr + numbytes - 1);
	*((char *) ptr + numbytes - 1) = '\0';
	//string last_char = ((char *)ptr);

	string header((char*)ptr);
	if (header.find("Content-Length") != string::npos)
		last_content_length = header.substr(16); // "Content-Length: "

	/*if (regex_search(last_char,content_length_regex) == 1) // Se for 1, foi retornado sim para o match
    {
      last_content_length = regex_replace(last_char, content_length_remove_regex, nothing);
    }*/

	return size*nmemb;
}

long long Fetcher::fileSize(std::string url, CURL* curl) {
	bool external = (curl != 0);
	if (!curl) {
		curl = curl_easy_init();
	}
	curl_easy_reset(curl);

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, handle_headers);

	CURLcode res = curl_easy_perform(curl);

	if (!external)
		curl_easy_cleanup(curl);

	return atoll(last_content_length.c_str());
};



