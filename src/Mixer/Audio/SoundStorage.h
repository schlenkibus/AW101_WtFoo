#pragma once
#include "../../Filesystem/File.h"
#include "SoundFile.h"
#include <map>
#include <string>

class SoundStorage {
public:
    static SoundStorage& get() {
        static SoundStorage sSS;
        return sSS;
    }

    void loadSoundFromFile(const File::tPath& p);
    TestSoundFile &getSound(const std::string &name);
protected:
    SoundStorage() = default;
    std::map<std::string, TestSoundFile> m_soundFiles{};
};
