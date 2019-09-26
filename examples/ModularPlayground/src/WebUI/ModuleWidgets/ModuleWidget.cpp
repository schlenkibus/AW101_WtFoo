#include "ModuleWidget.h"

ModuleWidget::ModuleWidget(DSPModule *module) : m_module{module} {

  auto moduleName = addWidget(std::make_unique<Wt::WLabel>());
  moduleName->setText(module->TYPE());

  auto inputContainer = addWidget(std::make_unique<Wt::WContainerWidget>());
  inputContainer->setStyleClass("input-container");

  for (auto &input : m_module->getInputs()) {
    m_inputs.emplace_back(
        inputContainer->addWidget(std::make_unique<DSPInputWidget>(input)));
  }

  auto outputContainer = addWidget(std::make_unique<Wt::WContainerWidget>());
  outputContainer->setStyleClass("output-container");
  for (auto &output : m_module->getOutputs()) {
    m_outputs.emplace_back(
        outputContainer->addWidget(std::make_unique<DSPOutputWidget>(output)));
  }

  auto parameterContainer = addWidget(std::make_unique<Wt::WContainerWidget>());
  parameterContainer->setStyleClass("parameter-container");
  for (auto &parameter : m_module->getParameters()) {
    m_parameters.emplace_back(
        parameterContainer->addWidget(std::make_unique<ParameterSlider>(parameter)));
  }

  setStyleClass("module-widget");
}

const std::vector<DSPInputWidget*>& ModuleWidget::getInputs() const{
    return m_inputs;
}

const std::vector<DSPOutputWidget *> &ModuleWidget::getOutputs() const {
  return m_outputs;
}
