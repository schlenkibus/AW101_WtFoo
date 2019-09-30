#include "AudioOutModule.h"

AudioOutModule::AudioOutModule(DSPHost *parent) : DSPModule(parent) {
  createInput("Left");
  createInput("Right");

  m_left = findInput("Left");
  m_right = findInput("Right");
}

const char *AudioOutModule::getName() { return "AudioOutModule"; }

Input *AudioOutModule::leftChannel() { return m_left; }
Input *AudioOutModule::rightChannel() { return m_right; }
