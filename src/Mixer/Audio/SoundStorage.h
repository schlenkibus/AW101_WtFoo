#pragma once
#include "../../Defines.h"
#include "SoundFile.h"
#include <map>
#include <string>

class SoundStorage {
public:
    void loadSoundFromFile(const tPath& p);
    const TestSoundFile &getSound(const std::string &name) const;
protected:
    std::map<std::string, TestSoundFile> m_soundFiles{};
};
