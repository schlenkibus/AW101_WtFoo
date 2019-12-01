#pragma once
#include "SoundFile.h"
#include <map>
#include <string>

class SoundStorage
{
 public:
  SoundStorage() = default;
  TestSoundFile& getSound(const std::string& name);

 protected:
  void loadSoundFromFile(const tPath& p);
  std::map<std::string, TestSoundFile> m_soundFiles {};
};