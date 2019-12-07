#include "AudioOutModule.h"

AudioOutModule::AudioOutModule(DSPHost *parent)
    : DSPModule(parent)
{
  createInput("Left");
  createInput("Right");

  m_master = createParameter("Master Gain", 1.0, 0.0, 1.0, 2);

  m_left = findInput("Left");
  m_right = findInput("Right");
}

const char *AudioOutModule::getTypeName() const
{
  return "Audio Out";
}

DSPInputNode *AudioOutModule::leftChannel()
{
  return m_left;
}

DSPInputNode *AudioOutModule::rightChannel()
{
  return m_right;
}

Parameter *AudioOutModule::getMasterGain()
{
  return m_master;
}
