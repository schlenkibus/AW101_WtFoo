#include <examples/ModularPlayground/src/Modules/WaveTableOscillator.h>
#include "SamplePlayerModule.h"

SamplePlayerModule::SamplePlayerModule(DSPHost* parent)
    : DSPModule(parent)
{
  m_output = createOutput("OUT");
  m_playbackSpeed = createInput("Speed");
  m_masterGain = createParameter("Volume", 1.0, 0.0, 1.0, 2);
}

void SamplePlayerModule::tick()
{
  DSPContainer::tick();


}

void SamplePlayerModule::loadSample(const File& sample)
{
  m_currentFile = sample;
}

const File* SamplePlayerModule::getSampleFile() const
{
  return &m_currentFile;
}
