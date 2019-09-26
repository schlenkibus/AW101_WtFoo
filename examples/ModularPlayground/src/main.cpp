#include "ModularPlaygroundApplication.h"
#include "WebUI/ModularWebUI.h"

#include "library_loading_ugly_stuff.cpp"

#include <Wt/WApplication.h>
#include <thread>

int main(int argc, char **argv) {
    std::cout << argv[0] << std::endl;
  ModularPlaygroundApplication application;

  loadPlugins(&application);

  return Wt::WRun(argc, argv, [&](const auto &env) {
    return std::make_unique<ModularWebUI>(env, application,
                                          "/home/justus/Music");
  });
}
