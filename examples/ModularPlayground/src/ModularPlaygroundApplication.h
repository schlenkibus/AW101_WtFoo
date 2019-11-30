#pragma once

#include "Modules/AudioOutModule.h"
#include <libAudio/include/AudioDevice.h>
#include <libDSP/include/DSPHost.h>
#include <libDSP/include/plugin/PluginLoader.h>

class ModularPlaygroundApplication : public DSPHost
{
 public:
  ModularPlaygroundApplication();

  bool pushCreation(const std::string &moduleName);
  bool running() const;

  template <typename LibraryLoader> void createLibraryLoader()
  {
    m_libaryLoader = std::make_unique<LibraryLoader>(this);
  }

  const std::vector<DSPModule *> &getModules() const;

 protected:
  std::unique_ptr<AudioDevice> m_audioDevice { nullptr };
  std::vector<std::string> m_pendingModuleCreations;
  AudioOutModule *m_audioModule { nullptr };

 private:
  std::unique_ptr<PluginLoader> m_libaryLoader;
  void slowTick();

  friend class ModularAudioDevice;
  void fillFrame(Frame &frame);
  bool m_running = true;
};
