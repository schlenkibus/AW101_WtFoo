#include "ArgumentParser.h"
#include "ModularPlaygroundApplication.h"
#include "WebUI/ModularWebUI.h"
#include "library_loading_ugly_stuff.cpp"

#include <Wt/WApplication.h>
#include <any>
#include <thread>
#include <HAL/HAL/HAL.h>

int main(int argc, char **argv) {

    ArgumentParser parser({"docroot", "http-listen", "module-path", "hal-enable"}, argc, argv);

    ModularPlaygroundApplication application;

    auto hostnameWithPort = parser.getArgumentValue("http-listen");
    auto hostname = hostnameWithPort.substr(0, hostnameWithPort.find(':'));
    std::unique_ptr<HAL> hal{nullptr};

    if (parser.parseBooleanArgument("hal-enable"))
        hal = std::make_unique<HAL>(&application, hostname);

    Directory d(parser.getArgumentValue("module-path"));
    loadDSPModules(&application, d);
    Directory h(parser.getArgumentValue("hardware-path"));
    loadHardwareModules(hal.get(), h);

    auto webUI = std::thread([&]() {
        return Wt::WRun(argc, argv, [&](const auto &env) {
            return std::make_unique<ModularWebUI>(env, application);
        });
    });

    while (application.running())
        std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}
