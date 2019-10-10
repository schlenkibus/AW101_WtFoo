#include "ArgumentParser.h"
#include "ModularPlaygroundApplication.h"
#include "WebUI/ModularWebUI.h"
#include "library_loading_ugly_stuff.cpp"

#include <Wt/WApplication.h>
#include <any>
#include <simple-websocket-server/server_ws.hpp>
#include <thread>

int main(int argc, char **argv) {

  SimpleWeb::SocketServer<SimpleWeb::WS> server;
  server.config.port = 18700;
  server.config.address = "101.101.101.101";
  auto &testEndPoint = server.endpoint["/test/"];
  testEndPoint.on_message = [](auto connection, auto message) {
    auto str = message->string();
    std::cout << str << std::endl;
  };

  testEndPoint.on_open = [](auto connection) {
    std::cout << connection.get() << std::endl;
  };

  server.start();

  ArgumentParser parser({"docroot", "http-listen", "module-path"}, argc, argv);

  ModularPlaygroundApplication application;

  Directory d(parser.getArgumentValue("module-path"));
  loadPlugins(&application, d);

  auto webUI = std::thread([&]() {
    return Wt::WRun(argc, argv, [&](const auto &env) {
      return std::make_unique<ModularWebUI>(env, application,
                                            "/home/justus/Music");
    });
  });

  return 0;
}
