#pragma once
#include "SoundFile.h"
#include <map>
#include <string>

class SoundStorage
{
  SoundStorage() = default;

 public:
  TestSoundFile& getSound(const std::string& name);

  static SoundStorage& get();
 protected:
  void loadSoundFromFile(const tPath& p);
  std::map<std::string, TestSoundFile> m_soundFiles {};
};