#pragma once
#include <server_ws.hpp>

class WelcomeHall {
private:
    using tCB = std::function<void(std::string)>;
public:
    WelcomeHall();
    ~WelcomeHall();
    void onDeviceHello(const tCB& cb);
private:
    void onMessage(const std::string& s);
    std::vector<tCB> m_deviceHelloCallbacks;
    std::thread m_thread;
    SimpleWeb::SocketServer<SimpleWeb::WS> m_server;
};
