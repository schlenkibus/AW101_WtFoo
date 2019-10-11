#pragma once

#include <examples/ModularPlayground/src/Modules/AudioOutModule.h>
#include <libAudio/include/AudioDevice.h>
#include <libDSP/include/DSPHost.h>

class ModularPlaygroundApplication : public DSPHost {
public:
  ModularPlaygroundApplication();
  std::vector<std::unique_ptr<DSPModule>> &getModules();

  DSPModule *createModule(const std::string &name) override;
  bool pushCreation(const std::string &moduleName);

  bool running() const;

protected:
  DSPInputNode m_leftSignalNode;
  DSPInputNode m_rightSignalNode;

  Input m_leftInput;
  Input m_rightInput;

  std::unique_ptr<AudioDevice> m_audioDevice{nullptr};
  std::vector<std::string> m_pendingModuleCreations;
  AudioOutModule* m_audioModule{nullptr};

private:
  void slowTick();
  void tick() override;

  friend class ModularAudioDevice;
  void fillFrame(Frame & frame);
  bool m_running = true;
};
