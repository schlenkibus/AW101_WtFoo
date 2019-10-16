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

    std::vector<std::unique_ptr<Input>> m_inputs;
    std::vector<std::unique_ptr<SimpleWeb::SocketClient<SimpleWeb::WS>>> m_outputs;

    std::unique_ptr<SimpleWeb::SocketClient<SimpleWeb::WS>> m_inputsClient;

    std::thread m_inputThread;

    IOModule *m_module;
};
