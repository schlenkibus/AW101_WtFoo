#include "ModularPlaygroundApplication.h"
#include "Audio/ModularAudioDevice.h"
#include <libDSP/include/DSPInfo.h>

ModularPlaygroundApplication::ModularPlaygroundApplication() : m_leftInput{"Audio L", &m_leftSignalNode}, m_rightInput{"Audio R", &m_rightSignalNode} {
  m_audioDevice = std::make_unique<ModularAudioDevice>(
      this, DSPInfo::SampleRate, DSPInfo::FramesPerBuffer);
}

std::vector<std::unique_ptr<DSPModule>> &
ModularPlaygroundApplication::getModules() {
  return m_modules;
}

void ModularPlaygroundApplication::tick() {
  for(auto& module: m_modules) {
    module->tick();
  }

  m_rightInput.tick();
  m_leftInput.tick();
}

Input *ModularPlaygroundApplication::getLeftChannel() { return &m_leftInput; }
Input *ModularPlaygroundApplication::getRightChannel() { return &m_rightInput; }
