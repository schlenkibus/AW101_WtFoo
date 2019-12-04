#include "ArgumentParser.h"
#include "ModularPlaygroundApplication.h"
#include "library_loading_ugly_stuff.cpp"
#include "NumberModuleWidget.h"
#include <ModularWebUI.h>

#include <Wt/WApplication.h>
#include <any>
#include <thread>
#include <HAL/HAL/HAL.h>
#include <Modules/NumberModule.h>

int main(int argc, char** argv)
{
  ArgumentParser parser({ "docroot", "http-listen", "module-path", "hal-enable" }, argc, argv);

  auto application = ModularPlaygroundApplication{};

  auto hostnameWithPort = parser.getArgumentValue("http-listen");
  auto hostname = hostnameWithPort.substr(0, hostnameWithPort.find(':'));

  std::unordered_map<std::string, std::function<std::unique_ptr<ModuleWidget>(DSPModule*)>> webUiPluginStorage;

  webUiPluginStorage["NumberModule"] = [](DSPModule* m) -> std::unique_ptr<ModuleWidget> { return std::move(std::make_unique<NumberModuleWidget>(dynamic_cast<NumberModule*>(m))); };

  auto webUI = std::thread([&]() {
    return Wt::WRun(argc, argv, [&](const auto& env) { return std::make_unique<ModularWebUI>(env, application, webUiPluginStorage); });
  });


  while(application.running())
    std::this_thread::sleep_for(std::chrono::seconds(1));

  return 0;
}
