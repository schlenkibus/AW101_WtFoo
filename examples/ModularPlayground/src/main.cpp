#include "AudioAnalizer/AudioAnalyzer.h"
#include "ConsoleUI/StreamUI.h"
#include "ModularPlaygroundApplication.h"
#include "Modules/BangModule.h"
#include "Modules/DrumModule.h"
#include "WebUI/ModularWebUI.h"

#include <Wt/WApplication.h>
#include <thread>

int main(int argc, char **argv) {

  ModularPlaygroundApplication application;

  AudioAnalyzer analizer(800, 500, application.getAudioDevice());

  std::thread webUIThread{[&] {
      ModularUseCases modularUseCases{application};
      StreamUI ui{std::cin};
      ui.addUseCases(&modularUseCases);
      return ui.run();
  }};


  //application.createModule<DrumModule>();

  auto bangOut = application.createModule<BangModule>(&application);
  if(auto dspBang = bangOut->findOutput("BANG"))
    application.getAudioOut().connect(*dspBang);

  return Wt::WRun(argc, argv, [&](const auto &env) {
    return std::make_unique<ModularWebUI>(env, application,
                                          "/home/justus/Music");
  });



  /*
  DSPHost dspHost{};

  return Wt::WRun(argc, argv, [&dspHost, argv](const auto &env) {
    auto ret = std::make_unique<DSPHostUserInterfaceApplication>(env, dspHost,
  "/home/justus/Music"); ret->useStyleSheet(Wt::WLink{"mixer.css"}); return
  std::move(ret);
  });
   */
}
