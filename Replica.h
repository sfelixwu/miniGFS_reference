
#ifndef _REPLICA_H_
#define _REPLICA_H_

#include "Core.h"

// Replica.h
#include <iostream>

class Chunk
{
 private:
 public:
  std::string data; // base64 encoding
  Chunk();
  Chunk(std::string);
  virtual Json::Value * dumpJ();
  virtual bool Jdump(Json::Value *);
};

class Replica : public Core
{
 private:
 public:
  std::string name;
  std::string fhandle;
  std::string chunk_index;
  Chunk committed_data;
  Chunk uncommitted_data;
  Replica(std::string, std::string, std::string,
	  std::string);
  Replica(std::string, std::string, std::string,
	  std::string, std::string);
  virtual Json::Value PushChunk2Replica(std::string, std::string, std::string, std::string);
  virtual Json::Value CommitAbort(std::string, std::string, std::string, std::string);
  virtual Json::Value * dumpJ();
  virtual bool Jdump(Json::Value *);
};

#endif  /* _REPLICA_H_ */
