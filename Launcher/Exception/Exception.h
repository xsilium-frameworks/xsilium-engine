/*
 * \file Exception.h
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <stdlib.h>
#include <stdexcept>

  /*! \brief
   * raised when our app version could not be located in the remote patch list
   */
	class BadVersion : public std::runtime_error {
	public:
		inline BadVersion(const std::string& s)
		: std::runtime_error(s)
		{ }
	};

  /*! \brief
   * raised when the downloader is unable to fetch the patch list from the patch
   * server
   */
	class BadPatchURL : public std::runtime_error {
	public:
		inline BadPatchURL(const std::string& s)
		: std::runtime_error(s)
		{ }
	};

  /*! \brief
   * raised when the Downloader has a problem fetching a file
   */
	class BadRequest : public std::runtime_error {
	public:
		inline BadRequest(const std::string& s)
		: std::runtime_error(s)
		{ }
	};

	/*! \brief
	 * raised when the received patch list from the server is malformed
	 */
	class BadPatchList : public std::runtime_error {
	public:
		inline BadPatchList(const std::string& s)
		: std::runtime_error(s)
		{ }
	};

	/*! \brief
	 * raised when the remote patch list either could not be saved to local temp
	 * file or that temp file could not be opened
	 */
	class BadFileStream : public std::runtime_error {
	public:
		inline BadFileStream(const std::string& s)
		: std::runtime_error(s)
		{ }
	};

	/*! \brief
	 * raised if Utility::convertTo<T> faces an issue
	 */
	class BadConversion : public std::runtime_error {
	public:
		inline BadConversion(const std::string& s)
		: std::runtime_error(s)
		{ }
	};

	/*! \brief
	 * raised if there was an error extracting or decompressing a BZ2 tar archive
	 */
	class BadArchive : public std::runtime_error {
	public:
		inline BadArchive(const std::string& s)
		: std::runtime_error(s)
		{ }
	};

	struct PatchStructure;
	class PatchException : public std::runtime_error {
	public:
	  inline PatchException(const std::string& s, PatchStructure* e)
	  : std::runtime_error(s)
	  { Entry = e; };
	  PatchStructure* Entry;
	};

	/*! \brief
	 * raised when a CREATE op is told to create an already existing file
	 */
	class FileAlreadyCreated : public PatchException {
	public:
		inline FileAlreadyCreated(const std::string& s, PatchStructure* e)
		: PatchException(s, e)
		{ }
	};

	/*! \brief
	 * raised when a DELETE op is told to delete a non-existent file
	 */
	class FileDoesNotExist : public PatchException {
	public:
		inline FileDoesNotExist(const std::string& s, PatchStructure* e )
		: PatchException(s, e)
		{ }
	};

	/*! \brief
	 * raised when a MODIFY op is told to patch an up-to-date file
	 */
	class FileAlreadyModified : public PatchException {
	public:
		inline FileAlreadyModified(const std::string& s, PatchStructure* e)
		: PatchException(s, e)
		{ }
	};



#endif /* EXCEPTION_H_ */
