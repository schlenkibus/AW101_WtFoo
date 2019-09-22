#include "AudioAnalizer/AudioAnalyzer.h"
#include "ConsoleUI/StreamUI.h"
#include "ModularPlaygroundApplication.h"
#include "Modules/BangModule.h"
#include "Modules/DrumModule.h"
#include "WebUI/ModularWebUI.h"

#include <Wt/WApplication.h>
#include <thread>

int main(int argc, char **argv) {
    std::cout << argv[0] << std::endl;
  ModularPlaygroundApplication application;

  std::thread webUIThread{[&] {
      ModularUseCases modularUseCases{application};
      StreamUI ui{std::cin};
      ui.addUseCases(&modularUseCases);
      return ui.run();
  }};

  return Wt::WRun(argc, argv, [&](const auto &env) {
    return std::make_unique<ModularWebUI>(env, application,
                                          "/home/justus/Music");
  });
}
