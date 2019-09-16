#pragma once

#include "../Audio/PortAudioDevice.h"
#include "../DSPNodes/DSPContainer.h"
class ModularPlaygroundApplication {
public:
    ModularPlaygroundApplication();

    std::vector<DSPNode*> collectNodes();
    DSPNode* getNode(const LibUUID::UUID& uuid);
    AudioDevice* getAudioDevice();
  protected:
    DSPContainer m_baseContainer;
    std::unique_ptr<AudioDevice> m_audioDevice;
};
