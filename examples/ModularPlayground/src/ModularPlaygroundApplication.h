#pragma once

#include "Modules/AudioOutModule.h"
#include <libAudio/include/AudioDevice.h>
#include <libDSP/include/DSPHost.h>
#include <libDSP/include/plugin/PluginLoader.h>
#include <Audio/ModularAudioDevice.h>
#include "library_loading_ugly_stuff.cpp"

class ModularPlaygroundApplication : public DSPHost
{
 public:
  ModularPlaygroundApplication();

  bool running() const;

 protected:
  std::vector<std::string> m_pendingModuleCreations;
  AudioOutModule *m_audioModule { nullptr };

 private:
  ModularAudioDevice m_audioDevice;
  void slowTick();

  friend class ModularAudioDevice;
  void fillFrame(Frame &frame);
  bool m_running = true;
};
