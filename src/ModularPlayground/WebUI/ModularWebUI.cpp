#include "ModularWebUI.h"
#include "../../DSPNodes/DSPContainer.h"
#include "../../DSPNodes/DSPNode.h"
#include "../ModularPlaygroundApplication.h"
#include "NodeWidgets/DSPClockWidget.h"
#include "NodeWidgets/DSPContainerWidget.h"
#include <Wt/WLabel.h>

ModularWebUI::ModularWebUI(const Wt::WEnvironment &env,
                           ModularPlaygroundApplication &app,
                           const char *basePath)
    : Wt::WApplication{env}, m_application{app} {
    try {
        root()->addWidget(std::make_unique<DSPContainerWidget>(m_application.getRootNode()));
    } catch(...) {
        std::cerr << "Caught Exception!" << std::endl;
    }
}
