#pragma once

#include "Modules/AudioOutModule.h"
#include <libAudio/include/AudioDevice.h>
#include <libDSP/include/DSPHost.h>
#include <libDSP/include/plugin/PluginLoader.h>
#include <Audio/ModularAudioDevice.h>

class ModularPlaygroundApplication : public DSPHost
{
 public:
  ModularPlaygroundApplication();

  bool running() const;

  template <typename LibraryLoader> void createLibraryLoader()
  {
    m_libaryLoader = std::make_unique<LibraryLoader>(this);
  }

 protected:
  std::vector<std::string> m_pendingModuleCreations;
  AudioOutModule *m_audioModule { nullptr };

 private:
  ModularAudioDevice m_audioDevice;
  std::unique_ptr<PluginLoader> m_libaryLoader;
  void slowTick();

  friend class ModularAudioDevice;
  void fillFrame(Frame &frame);
  bool m_running = true;
};
