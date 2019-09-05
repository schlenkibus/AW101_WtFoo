#include "DSPHostUserInterfaceApplication.h"
#include "MixerWidget.h"

std::string DSPHostUserInterfaceApplication::sBasePath = {};

DSPHostUserInterfaceApplication::DSPHostUserInterfaceApplication(
    const Wt::WEnvironment &env, DSPHost &mixer, const char* basePath)
    : Wt::WApplication{env}, m_mixer{mixer} {
  DSPHostUserInterfaceApplication::sBasePath = basePath;
  m_mixerWidget = root()->addWidget(std::make_unique<MixerWidget>(m_mixer));
  root()->addStyleClass("mixer-container");
}

void DSPHostUserInterfaceApplication::signalUpdateInspector() {
  auto* app = dynamic_cast<DSPHostUserInterfaceApplication*>(Wt::WApplication::instance());
  if(app) {
    app->redraw();
    app->processEvents();
  } else {
    std::cerr << "App not found!\n";
  }
}
void DSPHostUserInterfaceApplication::redraw() {
  m_mixerWidget->redraw();
}
