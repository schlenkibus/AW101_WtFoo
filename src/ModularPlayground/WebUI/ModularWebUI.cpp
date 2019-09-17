#include "ModularWebUI.h"
#include "../../DSPNodes/DSPContainer.h"
#include "../../DSPNodes/DSPNode.h"
#include "../ModularPlaygroundApplication.h"
#include "NodeWidgets/DSPClockWidget.h"
#include "NodeWidgets/DSPContainerWidget.h"

ModularWebUI::ModularWebUI(const Wt::WEnvironment &env,
                           ModularPlaygroundApplication &app,
                           const char *basePath)
    : Wt::WApplication{env}, m_application{app} {

  addChild(std::make_unique<DSPContainerWidget>(app.getRootNode()));
}
