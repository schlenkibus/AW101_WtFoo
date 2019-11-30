#include "ModularPlaygroundApplication.h"
#include "Audio/ModularAudioDevice.h"
#include "Modules/BasicModules.h"
#include <libDSP/include/DSPInfo.h>

ModularPlaygroundApplication::ModularPlaygroundApplication()
    : m_audioDevice { this, DSPInfo::SampleRate, DSPInfo::FramesPerBuffer }
{
  BasicModules::registerModules(this);
  m_audioModule = dynamic_cast<AudioOutModule *>(createRootModule(new AudioOutModule(this)));
}

void ModularPlaygroundApplication::slowTick()
{
  if(m_pendingModuleCreations.empty())
    return;

  for(auto &modName : m_pendingModuleCreations)
  {
    if(createModule(modName))
      std::cout << "sucessfully created module: \"" << modName << "\"!";
    else
      std::cerr << "failed to create module: \"" << modName << "\"!";
  }

  m_pendingModuleCreations.clear();
}

void ModularPlaygroundApplication::fillFrame(Frame &frame)
{
  if(m_audioModule)
  {
    auto vol = m_audioModule->getMasterGain()->getValue();
    frame.l = vol * m_audioModule->leftChannel()->getSignal();
    frame.r = vol * m_audioModule->rightChannel()->getSignal();
  }
}

bool ModularPlaygroundApplication::running() const
{
  return m_running;
}