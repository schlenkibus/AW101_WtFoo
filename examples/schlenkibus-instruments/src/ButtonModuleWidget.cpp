#include "ButtonModuleWidget.h"
#include "ButtonModule.h"
#include <Wt/WPushButton.h>

ButtonModuleWidget::ButtonModuleWidget(ButtonModule *module)
    : ModuleWidget(module)
    , m_module{module}
{
  auto b = addWidget(std::make_unique<Wt::WPushButton>());
  b->setText("Bang!");
  b->mouseWentDown().connect([=](){module->setState(true);});
  b->mouseWentUp().connect([=](){module->setState(false);});
}
