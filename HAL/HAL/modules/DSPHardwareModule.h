#pragma once
#include <libDSP/include/Modules/DSPModule.h>

class HardwareObject;

class DSPHardwareModule : public DSPModule {
public:
  explicit DSPHardwareModule(DSPHost *parent, HardwareObject* object);
  void tick() override;
};
