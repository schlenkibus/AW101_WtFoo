#pragma once
#include "../Audio/DSPHost.h"
#include <Wt/WApplication.h>

class MixerWidget;

class DSPHostUserInterfaceApplication : public Wt::WApplication {
public:
  DSPHostUserInterfaceApplication(const Wt::WEnvironment &env, DSPHost &mixer, const char* basePath);
  static void signalUpdateInspector();
  static std::string sBasePath;
protected:
  void redraw();
  MixerWidget *m_mixerWidget;
  DSPHost &m_mixer;
};

