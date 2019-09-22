#pragma once

#include <libAudio/include/AudioDevice.h>
#include <libDSP/include/DSPHost.h>

class ModularPlaygroundApplication : public DSPHost {
public:
    ModularPlaygroundApplication();
    std::vector<std::unique_ptr<DSPModule>>& getModules();
    Input* getLeftChannel();
    Input* getRightChannel();
  private:
    void tick() override;
  protected:
    DSPInputNode m_leftSignalNode;
    DSPInputNode m_rightSignalNode;

    Input m_leftInput;
    Input m_rightInput;

    std::unique_ptr<AudioDevice> m_audioDevice;

    friend class ModularAudioDevice;
};
