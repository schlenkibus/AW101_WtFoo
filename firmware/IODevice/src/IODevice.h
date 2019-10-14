#pragma once

#include <client_ws.hpp>
#include <vector>
#include <memory>
#include <HAL/HAL.h>
#include "HAL/HW/HardwareObject.h"

class IOModule;

class IODevice : public HardwareObject {
public:
    explicit IODevice(const std::string &hello, DSPHost *host);

    ~IODevice();

    const char *TYPE() override;

    DSPModule *createModule() override;

private:
    float m_in;
    float m_out;

    class Input {
    public:
        template<typename tCB>
        Input(const std::string &ip, int port, tCB cb) : m_server{ip, port} {
            m_server.on_message = cb;
            m_bg = std::thread([this]() { m_server.start(); });
        }
    private:
        SimpleWeb::SocketClient<SimpleWeb::WS> m_server;
        std::thread m_bg;
    };

    std::vector<std::unique_ptr<Input>> m_inputs;
    std::vector<std::unique_ptr<SimpleWeb::SocketClient<SimpleWeb::WS>>> m_outputs;

    std::vector<std::unique_ptr<std::thread>> m_bgThreads;

    IOModule *m_module;
};
