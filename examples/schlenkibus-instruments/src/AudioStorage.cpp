#include "AudioStorage.h"

void SoundStorage::loadSoundFromFile(const tPath &p)
{
  m_soundFiles.insert(std::make_pair(p.string(), TestSoundFile(File(p))));
}

TestSoundFile &SoundStorage::getSound(const std::string &name)
{
  try
  {
    return m_soundFiles.at(name);
  }
  catch(...)
  {
    loadSoundFromFile(tPath(name.c_str()));
  }
  return m_soundFiles.at(name);
}

SoundStorage &SoundStorage::get()
{
  static SoundStorage s;
  return s;
}
