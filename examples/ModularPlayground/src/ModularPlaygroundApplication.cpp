#include "ModularPlaygroundApplication.h"
#include "Audio/ModularAudioDevice.h"
#include "Modules/BasicModules.h"
#include <libDSP/include/DSPInfo.h>

ModularPlaygroundApplication::ModularPlaygroundApplication()
    : m_leftInput{"Audio L", &m_leftSignalNode}, m_rightInput{
                                                     "Audio R",
                                                     &m_rightSignalNode} {
  m_audioDevice = std::make_unique<ModularAudioDevice>(
      this, DSPInfo::SampleRate, DSPInfo::FramesPerBuffer);

  BasicModules::registerModules(this);
}

std::vector<std::unique_ptr<DSPModule>> &
ModularPlaygroundApplication::getModules() {
  return m_modules;
}

void ModularPlaygroundApplication::tick() {
  for (auto &module : m_modules) {
    if (module)
      module->tick();
  }

  m_rightInput.tick();
  m_leftInput.tick();
}

Input *ModularPlaygroundApplication::getLeftChannel() { return &m_leftInput; }
Input *ModularPlaygroundApplication::getRightChannel() { return &m_rightInput; }

bool ModularPlaygroundApplication::pushCreation(const std::string &moduleName) {
  m_pendingModuleCreations.emplace_back(moduleName);
}

void ModularPlaygroundApplication::slowTick() {
  if (m_pendingModuleCreations.empty())
    return;

  for (auto &modName : m_pendingModuleCreations) {
    if (createModule(modName))
      std::cout << "sucessfully created module: \"" << modName << "\"!";
    else
      std::cerr << "failed to create module: \"" << modName << "\"!";
  }

  m_pendingModuleCreations.clear();
}
const std::unique_ptr<AudioDevice> &
ModularPlaygroundApplication::getAudioDevice() const {
  return m_audioDevice;
}
