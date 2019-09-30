#pragma once

#include "../GenericWidgets/DragWidget.h"
#include "../GenericWidgets/DropWidget.h"
#include "DSPOutputWidget.h"
#include <Wt/WContainerWidget.h>
#include <examples/ModularPlayground/src/WebUI/GenericWidgets/WidgetDOMSizeProxy.h>
#include <libDSP/include/Modules/DSPModule.h>
#include <libDSP/include/Modules/Input.h>

class DSPInputWidget : public DropWidget {
public:
  explicit DSPInputWidget(Input *input);
  void onDropHappened(Wt::WObject *dropped) override;
  const Input *getInput() const;
  DSPModule* getModule();
  WidgetDOMSizeProxy* getInputDivProxy() const;
private:
  std::unique_ptr<WidgetDOMSizeProxy> m_inputDivDomProxy;
  Input *m_node;
};
