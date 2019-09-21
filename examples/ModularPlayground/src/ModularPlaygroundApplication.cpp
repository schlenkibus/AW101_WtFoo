#include "ModularPlaygroundApplication.h"
#include <libAudio/libAudio/PortAudioDevice.h>

ModularPlaygroundApplication::ModularPlaygroundApplication() : m_rootNodeInput{"Master Audio", &m_rootNode} {
  m_audioDevice = std::make_unique<PortAudioDevice>(
      *this, DSPInfo::SampleRate, DSPInfo::FramesPerBuffer);
}

AudioDevice *ModularPlaygroundApplication::getAudioDevice() {
  return m_audioDevice.get();
}

std::vector<std::unique_ptr<DSPModule>> &
ModularPlaygroundApplication::getModules() {
  return m_modules;
}

void ModularPlaygroundApplication::tick() {
  for(auto& module: m_modules) {
    module->tick();
  }

  m_rootNodeInput.tick();
}

Input& ModularPlaygroundApplication::getAudioOut(){
    return m_rootNodeInput;
}
