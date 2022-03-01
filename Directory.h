
#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include "Core.h"

// Directory.h
#include <iostream>

class Dirent
{
 private:
 public:
  std::string name;
  std::string fhandle;
  std::string chunk_index;

  // assuming ONE chunk per file
  std::string chunk_url_primary;
  std::string chunk_url_secondary_A;
  std::string chunk_url_secondary_B;

  Dirent();
  Dirent(std::string, std::string);
  virtual Json::Value * dumpJ();
  virtual bool Jdump(Json::Value *);
};

class Directory : public Core
{
 private:
 public:
  std::string name;
  std::string fhandle;
  Dirent the_chunk;
  std::vector<Dirent *> *dirent_vector_ptr;
  Directory(std::string, std::string, std::string,
	    std::string);
  Directory(std::string, std::string, std::string,
	    std::string, std::string, std::string);
  virtual Json::Value ObtainChunkURL(std::string, std::string, std::string);
  virtual Json::Value LookUp(std::string, std::string);
  virtual Json::Value Create(std::string, std::string, std::string);
  virtual Json::Value * dumpJ();
  virtual bool Jdump(Json::Value *);
};

#endif  /* _DIRECTORY_H_ */
