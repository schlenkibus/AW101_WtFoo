#include "Mixer/Audio/DSPHost.h"
#include "Mixer/UI/DSPHostUserInterfaceApplication.h"
#include "Synth/MySynthesizer.h"
#include "SynthApplication.h"
#include "Widgets/SampleInspectorWidget.h"
#include "Widgets/SignalButtonWidget.h"
#include "Widgets/SynthControlWidget.h"

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WFlags.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPaintDevice.h>
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>
#include <Wt/WPushButton.h>
#include <Wt/WRectF.h>
#include <Wt/WServer.h>
#include <Wt/WSlider.h>
#include <Wt/WText.h>
#include <chrono>
#include <thread>

// Config: /etc/wt/wt_config.xml

int main(int argc, char **argv) {
  //   auto synth = MySynthesizer(DSPInfo::SampleRate, 128);
  DSPHost dspHost{};

  /*std::thread t{[&dspHost] {
    while (dspHost.running()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
      Wt::WServer::instance()->postAll(
          &DSPHostUserInterfaceApplication::signalUpdateInspector);
    }
  }};
*/
  return Wt::WRun(argc, argv, [&dspHost, argv](const auto &env) {
    auto ret = std::make_unique<DSPHostUserInterfaceApplication>(env, dspHost, "/home/justus/Music");
    ret->useStyleSheet(Wt::WLink{"mixer.css"});
    return std::move(ret);
  });

  // return Wt::WRun(argc, argv, [&synth](const Wt::WEnvironment& env) {
  //    return std::make_unique<SynthApplication>(env, synth);
  //});
}
