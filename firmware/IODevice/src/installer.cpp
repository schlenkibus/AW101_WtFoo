#include <HAL/HAL.h>
#include "IODevice.h"

extern "C"
{
void HAL_registerHardware(HAL* hal)
{
    hal->registerHardware("IO",
                          [](std::string hello, DSPHost* host) { return std::make_unique<IODevice>(hello, host); });
}
}