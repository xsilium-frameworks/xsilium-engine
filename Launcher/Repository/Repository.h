/*
 * \file Repository.h
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include "Patch/PatchStructure.h"
#include "Patch/PatchVersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

/*
 *
 */
class Repository {
public:
	Repository(Version inVersion);
	virtual ~Repository();

	PatchStructure * const registerEntry(PATCHOP op, std::string local,
			std::string remote = "", std::string temp = "",
			std::string checksum = "");

	/*! \brief
	 *  Returns all the entries registered in this repository.
	 */
	const std::vector<PatchStructure*>& getEntries();

	/*! \brief
	 *  Returns all entries belonging to the given operation.
	 */
	std::vector<PatchStructure*> getEntries(PATCHOP op);

	Version const& getVersion();

	long long getSize();
	void setSize(long long inSize);

	void setArchive(PatchStructure* inArchive);
	PatchStructure* const getArchive();
	bool isArchived();

protected:
	std::vector<PatchStructure*> mEntries;
	Version mVersion;

	long long mSize;
	PatchStructure* mArchive;

private:
	// Repositores can not be copied
	Repository(const Repository&);
	Repository& operator=(const Repository&);
};


#endif /* REPOSITORY_H_ */
