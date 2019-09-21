#include "ModuleWidget.h"

ModuleWidget::ModuleWidget(DSPModule *module) : m_module{module}{

    auto moduleName = addWidget(std::make_unique<Wt::WLabel>());
    moduleName->setText(module->TYPE());

    auto inputContainer = addWidget(std::make_unique<Wt::WContainerWidget>());
    inputContainer->setStyleClass("input-container");

    for(auto& input: m_module->getInputs()) {
        m_inputs.emplace_back(inputContainer->addWidget(std::make_unique<DSPInputWidget>(input)));
    }

    auto outputContainer = addWidget(std::make_unique<Wt::WContainerWidget>());
    outputContainer->setStyleClass("output-container");
    for(auto& output: m_module->getOutputs()) {
        m_outputs.emplace_back(outputContainer->addWidget(std::make_unique<DSPOutputWidget>(output)));
    }

    setStyleClass("module-widget");
}
