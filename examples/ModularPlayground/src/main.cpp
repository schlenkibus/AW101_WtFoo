#include "ArgumentParser.h"
#include "ModularPlaygroundApplication.h"
#include "WebUI/ModularWebUI.h"
#include "library_loading_ugly_stuff.cpp"

#include <Wt/WApplication.h>
#include <any>
#include <thread>



int main(int argc, char **argv) {

  ArgumentParser parser({"docroot", "http-listen", "module-path"}, argc, argv);

  ModularPlaygroundApplication application;

  Directory d(parser.getArgumentValue("module-path"));
  loadPlugins(&application, d);

  return Wt::WRun(argc, argv, [&](const auto &env) {
    return std::make_unique<ModularWebUI>(env, application,
                                          "/home/justus/Music");
  });
}
