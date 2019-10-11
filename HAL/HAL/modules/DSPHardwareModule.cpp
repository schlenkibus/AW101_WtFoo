
#include "DSPHardwareModule.h"
#include <HAL/HW/HardwareObject.h>

DSPHardwareModule::DSPHardwareModule(DSPHost *parent, HardwareObject *object)
    : DSPModule(parent) {}

void DSPHardwareModule::tick() { DSPContainer::tick(); }
