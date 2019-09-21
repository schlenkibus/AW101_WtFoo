#include "SoundStorage.h"

void SoundStorage::loadSoundFromFile(const File::tPath &p) {
  m_soundFiles.insert(std::make_pair(p.string(), TestSoundFile(p)));
}

TestSoundFile &SoundStorage::getSound(const std::string &name) {
    try {
        return m_soundFiles.at(name);
    } catch(...) {
        loadSoundFromFile(File::tPath(name.c_str()));
    }
    return m_soundFiles.at(name);
}
