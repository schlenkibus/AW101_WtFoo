#pragma once

#include "../Audio/PortAudioDevice.h"
#include "../LibDSP/DSPNodes/DSPNode.h"
#include "../LibDSP/Modules/DSPModule.h"

class ModularPlaygroundApplication : DSPNode {
public:
    ModularPlaygroundApplication();
    AudioDevice* getAudioDevice();

    std::vector<std::unique_ptr<DSPModule>>& getModules();

    template<class tModule, typename ... tArgs>
    tModule* createModule(tArgs ... args) {
        auto ret = dynamic_cast<tModule*>(m_modules.emplace_back(std::make_unique<tModule>(args...)).get());
        onModulesChanged();
        return ret;
    }

    Input& getAudioOut();

  private:
    void onModulesChanged();
    void tick() override;
    void reset() override;
    const char *TYPE() const override;
  protected:
    DSPInputNode m_rootNode;
    Input m_rootNodeInput;

    std::vector<std::unique_ptr<DSPModule>> m_modules;
    std::unique_ptr<AudioDevice> m_audioDevice;

    //Signal<void,void> m_modulesChanged;

    friend class AudioDevice;
};
