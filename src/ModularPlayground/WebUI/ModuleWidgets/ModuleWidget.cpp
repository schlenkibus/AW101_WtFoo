#include "ModuleWidget.h"
#include "../../../LibDSP/Modules/DSPModule.h"

ModuleWidget::ModuleWidget(DSPModule *module) : m_module{module}{
    for(auto& input: m_module->getInputs()) {
        m_inputs.emplace_back(addWidget(std::make_unique<DSPInputWidget>(input)));
    }

    for(auto& output: m_module->getOutputs()) {
        m_outputs.emplace_back(addWidget(std::make_unique<DSPOutputWidget>(output)));
    }
}
