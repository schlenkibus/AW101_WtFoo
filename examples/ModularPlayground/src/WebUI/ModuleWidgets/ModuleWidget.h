#pragma once
#include "../NodeWidgets/DSPInputWidget.h"
#include "../NodeWidgets/DSPOutputWidget.h"
#include <Wt/WContainerWidget.h>
#include <libDSP/Modules/DSPModule.h>

class ModuleWidget : public Wt::WContainerWidget {
    public:
    ModuleWidget(DSPModule* module);
    protected:
    DSPModule* m_module;
    std::vector<DSPInputWidget*> m_inputs;
    std::vector<DSPOutputWidget*> m_outputs;
};

