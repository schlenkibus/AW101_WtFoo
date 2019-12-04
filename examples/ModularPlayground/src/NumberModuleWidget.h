#pragma once
#include <ModuleWidgets/ModuleWidget.h>

namespace Wt
{
  class WTextArea;
}

class NumberModule;

class NumberModuleWidget : public ModuleWidget
{

 public:
  explicit NumberModuleWidget(NumberModule* module);

 private:
  NumberModule* m_module;
  Wt::WTextArea* m_text;
};
