#include "DSPHostUserInterfaceApplication.h"
#include "MixerWidget.h"

DSPHostUserInterfaceApplication::DSPHostUserInterfaceApplication(
    const Wt::WEnvironment &env, DSPHost &mixer)
    : Wt::WApplication{env}, m_mixer{mixer} {
  m_mixerWidget = root()->addWidget(std::make_unique<MixerWidget>(m_mixer));
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
