#pragma once

#include "../Audio/PortAudioDevice.h"
#include "../LibDSP/DSPNodes/DSPNode.h"
#include "../LibDSP/Modules/DSPModule.h"
#include "../LibDSP/DSPHost.h"

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
