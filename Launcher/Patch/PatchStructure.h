/*
 * \file PatchStructure.h
 *
 *  Created on: \date 2 mars 2013
 *      Author: \author joda
 *  \brief :
 */

#ifndef PATCHSTRUCTURE_H_
#define PATCHSTRUCTURE_H_

#include <string>

typedef enum {
  P_CREATE, //! creates a file locally from a given remote file URL
  P_DELETE, //! deletes a file locally
  P_MODIFY, //! patches a file locally from a given remote diff URL
  P_RENAME,
  P_ARCHIVE
} PATCHOP;

class Repository;
struct PatchStructure {
  inline PatchStructure() { Repo = 0; };
  /*! \brief
   *  convenience constructor
   */
  inline
  PatchStructure(PATCHOP inOp,
             std::string inLocal,
             std::string inRemote = "",
             std::string inChecksum = "",
             Repository* inRepo = 0) {
    Local = inLocal;
    Remote = inRemote;
    Op = inOp;
    Repo = inRepo;
    Checksum = inChecksum;
  }
  inline ~PatchStructure() { Repo = 0; }

  // see ENUM PATCHOP
  PATCHOP Op;

  /*
   * std::string Local:
   *  1) in the case of CREATE, it represents the relative URL from which the dest will be created
   *  2) in the case of MODIFY, it represents the local path of the file to be patched
   *  3) in the case of DELETE, it represents the local path of the file to be deleted
   */
  std::string Local;
  /*
   * std::string Remote:
   *  1) in the case of CREATE, it represents the path at which the file will be created
   *  2) in the case of MODIFY, it represents the relative URL to the diff file to be patched
   *  3) in the case of DELETE, this field is discarded
   */
  std::string Remote;

  // only used in the case of MODIFY, it represents where the diff patch was downloaded to
  std::string Temp;

  // a handle to the repository this entry belongs to
  Repository* Repo;

  /*
   * MD5 checksum used to verify the integrity of downloaded files.
   * In the case of MODIFY entries, the checksum is that of the downloaded diff file,
   * and in the case of CREATE, it's of the downloaded file.
   */
  std::string Checksum;

  long long Filesize; // in bytes

};


#endif /* PATCHSTRUCTURE_H_ */
