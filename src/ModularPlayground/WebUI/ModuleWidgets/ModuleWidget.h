#pragma once
#include "../../../LibDSP/Modules/DSPModule.h"
#include "../NodeWidgets/DSPInputWidget.h"
#include "../NodeWidgets/DSPOutputWidget.h"
#include <Wt/WContainerWidget.h>

class ModuleWidget : public Wt::WContainerWidget {
    public:
    ModuleWidget(DSPModule* module);
    protected:
    DSPModule* m_module;
    std::vector<DSPInputWidget*> m_inputs;
    std::vector<DSPOutputWidget*> m_outputs;
};
