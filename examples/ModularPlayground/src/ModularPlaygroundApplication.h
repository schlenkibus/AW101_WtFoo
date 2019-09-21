#pragma once

#include <libAudio/libAudio/AudioDevice.h>
#include <libDSP/DSPHost.h>

class ModularPlaygroundApplication : public DSPHost {
public:
    ModularPlaygroundApplication();
    AudioDevice* getAudioDevice();

    std::vector<std::unique_ptr<DSPModule>>& getModules();



    Input& getAudioOut();

  private:
    void tick() override;
  protected:
    DSPInputNode m_rootNode;
    Input m_rootNodeInput;

    std::unique_ptr<AudioDevice> m_audioDevice;

    friend class AudioDevice;
};
