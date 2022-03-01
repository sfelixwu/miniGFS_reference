
#ifndef _SHADOW_DIRECTORY_H_
#define _SHADOW_DIRECTORY_H_

#include "Directory.h"

class Shadow_Directory: public Directory
{
 private:
 public:
  Shadow_Directory(std::string, std::string, std::string, std::string);
  virtual Json::Value ObtainChunkURL(std::string, std::string, std::string);
  virtual Json::Value LookUp(std::string, std::string);
  virtual Json::Value Create(std::string, std::string, std::string);
  virtual Json::Value * dumpJ();
  virtual bool Jdump(Json::Value *);
};

#endif // _SHADOW_DIRECTORY_H_
