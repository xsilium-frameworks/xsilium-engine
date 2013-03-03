/*
 * \file Repository.cpp
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#include "Repository.h"

Repository::Repository(Version inVersion) : mVersion(inVersion) {

	mVersion = inVersion;
	mSize = 0;
	mArchive = 0;


}

Repository::~Repository() {


	PatchStructure* lEntry = 0;
	while (!mEntries.empty()) {
	  lEntry = mEntries.back();
	  mEntries.pop_back();
	  delete lEntry;
	}
	lEntry = 0;
}


PatchStructure* const Repository::registerEntry(PATCHOP Op,std::string Local,std::string Remote,std::string Temp,std::string Checksum)
  {

    PatchStructure *lEntry = new PatchStructure();
    lEntry->Op = Op;
    lEntry->Local = Local;
    lEntry->Remote = Remote;
    lEntry->Temp = Temp;
    lEntry->Checksum = Checksum;
    lEntry->Repo = this;

    mEntries.push_back(lEntry);
    return lEntry;
  }

std::vector<PatchStructure*>
Repository::getEntries(PATCHOP inOp) {

  std::vector<PatchStructure*> entries;
  std::vector<PatchStructure*>::const_iterator _itr;
  for (_itr = mEntries.begin(); _itr != mEntries.end(); ++_itr) {
    if ((*_itr)->Op == inOp)
      entries.push_back((*_itr));
  }

  return entries;
}

const std::vector<PatchStructure*>&
Repository::getEntries() {
  return mEntries;
}

const Version& Repository::getVersion() {
  return mVersion;
}

long long Repository::getSize() {
  return mSize;
}
void Repository::setSize(long long inSize) {
  mSize = inSize;

}

void Repository::setArchive(PatchStructure* inArchive) {
  mArchive = inArchive;
}
PatchStructure* const Repository::getArchive() {
  return mArchive;
}
bool Repository::isArchived() {
  return mArchive != NULL;
}

