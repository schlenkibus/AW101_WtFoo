#include "SynthApplication.h"
#include "Widgets/SampleInspectorWidget.h"

SynthApplication::SynthApplication(const Wt::WEnvironment &env, MySynthesizer &synthesizer)
    : Wt::WApplication{env}
    , m_synthesizer{synthesizer}
{
  m_widget = root()->addWidget(std::make_unique<SynthControlWidget>(m_synthesizer));

}

void SynthApplication::signalUpdateInspector() {

  auto* app = dynamic_cast<SynthApplication*>(Wt::WApplication::instance());
  if(app) {
    app->m_widget->getSampleInspector()->redraw();
    app->processEvents();
  } else {
    std::cerr << "App not found!\n";
  }
}