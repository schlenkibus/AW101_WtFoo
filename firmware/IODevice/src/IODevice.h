#pragma once

#include <client_ws.hpp>
#include <vector>
#include <memory>
#include <HAL/HAL.h>
#include "HAL/HW/HardwareObject.h"

class IOModule;

class IODevice : public HardwareObject {
public:
    explicit IODevice(const std::string &hello, DSPHost *host, HAL* hal);

    ~IODevice();

    const char *TYPE() override;

    DSPModule *createModule() override;

private:


    std::thread m_inputThread;

    IOModule *m_module;
};
