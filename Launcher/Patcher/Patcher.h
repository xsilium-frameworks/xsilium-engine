/*
 * \file Patcher.h
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef PATCHER_H_
#define PATCHER_H_

#include <bzlib.h>
#include "Patch/PatchStructure.h"
#include "Patch/PatchVersion.h"
#include "Repository/Repository.h"
#include "Launcher.h"
#include <list>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <utility>

#include "ResolvePaths/ResolvePaths.h"


class Launcher;

/*
 *
 */
class Patcher {
public:

	typedef void (Patcher::*t_proc)(PatchStructure*, bool);
	typedef std::map<PATCHOP, t_proc> t_procmap;

	Patcher();
	virtual ~Patcher();


	/*! \brief
	 *  Processes events. This must be called in application's main loop.
	 */
	void update();

	/*! \brief
	 *  Validates current application version against the latest version
	 *  defined in the server patch script.
	 *
	 *  This method triggers the following events:
	 *    \li ValidateStarted
	 *    \li UnableToConnect
	 *    \li ValidateComplete
	 *
	 * \warning
	 *  MUST be called before Downloader::_fetchPatchList() if you're doing it manually
	 */
	void validate();

	/*! \brief
	 *  Builds the Repositories for each patch version, processes all the entries
	 *  and updates the application's version accordingly.
	 *
	 *  This method triggers the following events:
	 *    \li PatchStarted
	 *    \li PatchFailed
	 *    \li PatchComplete
	 *    \li ApplicationUpdated
	 *
	 *  \note
	 *  Must call Patcher::validate() first, else it's done internally.
	 *
	 *  \warning
	 *  Calling this method directly will block the application. To call it from
	 *  within a thread, use either the operator() in boost::thread case, or you
	 *  can also trigger the "Patch" event which will do the same thing.
	 */
	void patch();

	/*! \brief
	 *  Returns the current version of the application.
	 */
	Version& getCurrentVersion();

	/*! \brief
	 *  Calls validate() OR patch() based on the flags.
	 *  This is used by boost::thread to do the patching asynchronously.
	 */
	void start();



protected:
	std::list<Repository*> mRepos;
	std::string mPatchScriptPath, mPatchLogPath;
	Version mCurrentVersion, mTargetVersion;

	/*! \brief
	 *  Builds 1 Repository for every version defined in the patch script
	 *  that we need to patch up to.
	 *
	 *  This is called within the patch() routine. The patch script is parsed
	 *  in this routine, any unrecognized entries are discarded and silently
	 *  ignored. See Pixy::PATCHOP for acceptable patch script entries and tokens.
	 *
	 *  \throw BadFileStream the local patch script can not be read
	 *  \throw BadVersion mCurrentVersion could not be located in the patch script
	 *
	 */
	void buildRepositories();

	/*! \brief
	 *  Verifies the patch script entry for containing the required tokens
	 *  and their validity.
	 */
	bool validateLine(std::vector<std::string>& elements, std::string line);

	/*! \brief
	 *  Convenience function for mapping patch script entry operation to PATCHOP.
	 *
	 *  Conversion map:
	 *    \li M -> \c MODIFY
	 *    \li C -> \c CREATE
	 *    \li R -> \c RENAME
	 *    \li D -> \c DELETE
	 */
	PATCHOP opFromChar(const char* inC);

	t_procmap mProcessors;

	void processArchive(PatchStructure* inEntriy, bool fCommit);

	/*! \brief
	 *  Creates a local file at inEntry->Local, from remote source: inEntry->Remote,
	 *  while stored temporarily in inEntry->Temp.
	 *
	 *  This operation fails if:
	 *  \li inEntry->Local exists
	 *  \li inEntry->Temp checksum does not match inEntry->Checksum (remote one)
	 *  \li there's not enough permission to write on disk.
	 */
	void processCreate(PatchStructure* inEntry, bool fCommit);

	/*! \brief
	 *  Removes file or directory located at inEntry->Local.
	 *
	 *  \remark
	 *  This operation fails if inEntry->Local does not exist, or if there's
	 *  not enough permission to remove.
	 */
	void processDelete(PatchStructure* inEntry, bool fCommit);

	/*! \brief
	 *  Modifies file at inEntry->Local using the diff file at inEntry->Temp.
	 *
	 *  This method fails if:
	 *  \li the checksum of inEntry->Remote (the diff file) does not match inEntry->Checksum
	 *  \li there's not enough permission to write.
	 *
	 *  \remark
	 *  The source file, inEntry->Local, is copied to a temp location, patched there,
	 *  then inEntry->Local is removed, and the patched version is moved to that location.
	 *  The reason this is done is that we can not directly modify the running
	 *  application, but using this approach we can.
	 *
	 */
	void processModify(PatchStructure* inEntry, bool fCommit);

	/*! \brief
	 *  Renames or moves a file from inEntry->Remote to inEntry->Local.
	 *
	 *  Fails if inEntry->Remote doesn't exist, or if inEntry->Local exists.
	 */
	void processRename(PatchStructure* inEntry, bool fCommit);

	/*! \brief
	 *  Validates the PatchEntries in the repository according to the following
	 *  conditions:
	 *    \li \c CREATE: Local must not exist
	 *    \li \c DELETE: Local must exist
	 *    \li \c MODIFY: checksum of Local must match remote one
	 *    \li \c RENAME: dest must not exist and src must exist
	 */
	bool preprocess(Repository* inRepo);

	/*! \brief
	 *  Writes mCurrentVersion to PIXY_RESOURCE_PATH file.
	 */
	void updateVersion(const Version& inVersion);

	bool fHandledArchive;

private:
	bool fValidated; //! set to true if validate() was properly completed
	bool fPatched; //! set to true if patch() was properly completed

	ResolvePaths * resolvePaths;
};


#endif /* PATCHER_H_ */
