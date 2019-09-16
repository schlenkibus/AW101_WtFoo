#include "DSPHostUserInterfaceApplication.h"
//#include "../../DSPNodes/DSPContainer.h"
#include "MixerWidget.h"

std::string DSPHostUserInterfaceApplication::sBasePath = {};

DSPHostUserInterfaceApplication::DSPHostUserInterfaceApplication(
    const Wt::WEnvironment &env, DSPHost &mixer, const char* basePath)
    : Wt::WApplication{env}, m_mixer{mixer} {
  DSPHostUserInterfaceApplication::sBasePath = basePath;

  //root()->addWidget(std::make_unique<DSPContainer>(DSPInfo::SampleRate));

  m_mixerWidget = root()->addWidget(std::make_unique<MixerWidget>(m_mixer));
  root()->addStyleClass("mixer-container");
}

