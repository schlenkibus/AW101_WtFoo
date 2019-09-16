#pragma once
#include "../Audio/DSPHost.h"
#include <Wt/WApplication.h>

class MixerWidget;

class DSPHostUserInterfaceApplication : public Wt::WApplication {
public:
  DSPHostUserInterfaceApplication(const Wt::WEnvironment &env, DSPHost &mixer, const char* basePath);
  static std::string sBasePath;
protected:
  MixerWidget *m_mixerWidget;
  DSPHost &m_mixer;
};

