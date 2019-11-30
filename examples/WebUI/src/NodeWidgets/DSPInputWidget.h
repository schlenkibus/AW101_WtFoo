#pragma once

#include "GenericWidgets/DragWidget.h"
#include "GenericWidgets/DropWidget.h"
#include "DSPOutputWidget.h"
#include <Wt/WContainerWidget.h>
#include "GenericWidgets/WidgetDOMSizeProxy.h"
#include <libDSP/include/Modules/DSPModule.h>

class DSPInputWidget : public DropWidget
{
 public:
  explicit DSPInputWidget(DSPInputNode* input);
  void onDropHappened(Wt::WObject* dropped) override;
  const DSPInputNode* getInput() const;
  DSPModule* getModule();
  WidgetDOMSizeProxy* getInputDivProxy() const;

 private:
  std::unique_ptr<WidgetDOMSizeProxy> m_inputDivDomProxy;
  DSPInputNode* m_node;
};
