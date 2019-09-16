#include "Mixer/Audio/DSPHost.h"
#include "Mixer/UI/DSPHostUserInterfaceApplication.h"
#include "ModularPlayground/AudioAnalizer/AudioAnalyzer.h"
#include "ModularPlayground/ConsoleUI/StreamUI.h"
#include "ModularPlayground/ModularPlaygroundApplication.h"

#include <Wt/WApplication.h>
#include <thread>


int main(int argc, char **argv) {

  ModularPlaygroundApplication application;

  AudioAnalyzer analizer(800, 500, application.getAudioDevice());

  ModularUseCases modularUseCases{application};
  StreamUI ui{std::cin};
  ui.addUseCases(&modularUseCases);
  return ui.run();

  /*
  DSPHost dspHost{};

  return Wt::WRun(argc, argv, [&dspHost, argv](const auto &env) {
    auto ret = std::make_unique<DSPHostUserInterfaceApplication>(env, dspHost, "/home/justus/Music");
    ret->useStyleSheet(Wt::WLink{"mixer.css"});
    return std::move(ret);
  });
   */
}
