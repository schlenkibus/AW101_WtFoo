#pragma once
#include <ModuleWidgets/ModuleWidget.h>
#include "ButtonModule.h"

class ButtonModuleWidget : public ModuleWidget
{
 public:
  explicit ButtonModuleWidget(ButtonModule *module);
 private:
  ButtonModule* m_module;
};