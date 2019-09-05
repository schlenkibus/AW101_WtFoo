#include "SoundStorage.h"

void SoundStorage::loadSoundFromFile(const tPath &p) {
  m_soundFiles.insert(std::make_pair(p.string(), TestSoundFile(p)));
}

const TestSoundFile &SoundStorage::getSound(const std::string &name) const {
  return m_soundFiles.at(name);
}
