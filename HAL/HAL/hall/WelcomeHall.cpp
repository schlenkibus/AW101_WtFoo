#include "WelcomeHall.h"

WelcomeHall::WelcomeHall() {
  m_server.config.port = 18700;
  m_server.config.address = "101.101.101.101";
  auto &welcomeHallEndPoint = m_server.endpoint["/welcome/"];

  welcomeHallEndPoint.on_message = [this](auto connection, auto message) mutable {
    auto str = message->string();
    onMessage(std::string(str));
    std::cout << str << std::endl;
  };

  welcomeHallEndPoint.on_open = [](auto connection) {
    std::cout << connection.get() << std::endl;
  };

  m_thread = std::thread([&]() { m_server.start(); });
}

WelcomeHall::~WelcomeHall() {
  m_server.stop();

  if (m_thread.joinable())
    m_thread.join();
  else
    m_thread.detach();
}

void WelcomeHall::onDeviceHello(const tCB &cb) {
  m_deviceHelloCallbacks.emplace_back(cb);
}

void WelcomeHall::onMessage(const std::string& s) {
  for(auto& cb: m_deviceHelloCallbacks) {
    cb(std::string(s));
  }
}
