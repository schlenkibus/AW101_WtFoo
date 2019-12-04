#include <Modules/NumberModule.h>
#include "NumberModuleWidget.h"
#include <Wt/WTextArea.h>

NumberModuleWidget::NumberModuleWidget(NumberModule *module)
    : ModuleWidget(module)
    , m_module { module }
{
  if(m_module) {
    m_text = addWidget(std::make_unique<Wt::WTextArea>());
    m_text->setText(std::to_string(m_module->getOutputs()[0]->getSignal()));
    m_text->blurred().connect([this]() {
        try
        {
          auto number = std::stof(m_text->text());
          m_module->setNumber(number);
        }
        catch(...)
        {
          m_text->setText("0.0");
        }
    });

  }
}
