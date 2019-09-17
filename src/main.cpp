#include "DSPNodes/DSPClock.h"
#include "DSPNodes/DSPCollection.h"
#include "Mixer/Audio/DSPHost.h"
#include "Mixer/UI/DSPHostUserInterfaceApplication.h"
#include "ModularPlayground/AudioAnalizer/AudioAnalyzer.h"
#include "ModularPlayground/ConsoleUI/StreamUI.h"
#include "ModularPlayground/ModularPlaygroundApplication.h"
#include "ModularPlayground/WebUI/ModularWebUI.h"

#include <Wt/WApplication.h>
#include <thread>

int main(int argc, char **argv) {

  ModularPlaygroundApplication application;

  auto non_audio = application.getRootNode()->createNode<DSPCollection>();
  auto clock = non_audio->createNode<DSPClock>(11250);
  clock->getInputNode()->signal = 1.0;

  AudioAnalyzer analizer(800, 500, application.getAudioDevice());

  std::thread webUIThread{[&] {
    return Wt::WRun(argc, argv, [&](const auto &env) {
      return std::make_unique<ModularWebUI>(env, application,
                                            "/home/justus/Music");
    });
  }};

  ModularUseCases modularUseCases{application};
  StreamUI ui{std::cin};
  ui.addUseCases(&modularUseCases);
  return ui.run();

  /*
  DSPHost dspHost{};

  return Wt::WRun(argc, argv, [&dspHost, argv](const auto &env) {
    auto ret = std::make_unique<DSPHostUserInterfaceApplication>(env, dspHost,
  "/home/justus/Music"); ret->useStyleSheet(Wt::WLink{"mixer.css"}); return
  std::move(ret);
  });
   */
}
