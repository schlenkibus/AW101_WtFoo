#include "ArgumentParser.h"
#include "ModularPlaygroundApplication.h"
#include "WebUI/ModularWebUI.h"
#include "library_loading_ugly_stuff.cpp"

#include <Wt/WApplication.h>
#include <any>
#include <thread>
#include <HAL/HAL/HAL.h>

int main(int argc, char **argv)
{

  ArgumentParser parser({ "docroot", "http-listen", "module-path" }, argc, argv);

  ModularPlaygroundApplication application;

  auto hostnameWithPort = parser.getArgumentValue("http-listen");
  auto hostname = hostnameWithPort.substr(hostnameWithPort.find(":"));
  HAL hal(&application, hostname);

  Directory d(parser.getArgumentValue("module-path"));
  Directory h(parser.getArgumentValue("hardware-path"));
  loadPlugins(&application, &hal, d, h);

  auto webUI = std::thread([&]() {
    return Wt::WRun(argc, argv, [&](const auto &env) {
      return std::make_unique<ModularWebUI>(env, application, "/home/justus/Music");
    });
  });

  while(application.running())
    std::this_thread::sleep_for(std::chrono::seconds(1));

  return 0;
}
