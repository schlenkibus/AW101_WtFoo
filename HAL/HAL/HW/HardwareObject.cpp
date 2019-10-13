#include "HardwareObject.h"
#include <libDSP/include/DSPHost.h>

HardwareObject::HardwareObject(const std::string& hello, DSPHost* host)
    : m_host { host }
{
}
