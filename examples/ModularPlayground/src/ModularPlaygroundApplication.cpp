#include "ModularPlaygroundApplication.h"
#include "Audio/ModularAudioDevice.h"
#include "Modules/BasicModules.h"
#include <libDSP/include/DSPInfo.h>

ModularPlaygroundApplication::ModularPlaygroundApplication()
    : m_leftInput{"Audio L", &m_leftSignalNode}, m_rightInput{
                                                     "Audio R",
                                                     &m_rightSignalNode} {
  BasicModules::registerModules(this);
  m_audioModule =
      dynamic_cast<AudioOutModule *>(createModule("AudioOutModule"));

  m_audioDevice = std::make_unique<ModularAudioDevice>(
      this, DSPInfo::SampleRate, DSPInfo::FramesPerBuffer);
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
}

bool ModularPlaygroundApplication::pushCreation(const std::string &moduleName) {
  m_pendingModuleCreations.emplace_back(moduleName);
  return true;
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

DSPModule *ModularPlaygroundApplication::createModule(const std::string &name) {
  auto ret = DSPHost::createModule(name);
  m_audioModule = findModule<AudioOutModule>("AudioOutModule");
  return ret;
}

void ModularPlaygroundApplication::fillFrame(Frame &frame) {
  if (m_audioModule) {
    auto vol = m_audioModule->getMasterGain()->getValue();
    frame.l = vol * m_audioModule->leftChannel()->getSignal();
    frame.r = vol * m_audioModule->rightChannel()->getSignal();
  }
}

bool ModularPlaygroundApplication::running() const { return m_running; }
