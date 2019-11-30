#pragma once
#include "../GenericWidgets/DragWidget.h"
#include <Wt/WLabel.h>
#include <GenericWidgets/WidgetDOMSizeProxy.h>
#include <libDSP/include/DSPNodes/DSPOutputNode.h>

class DSPOutputWidget : public DragWidget<DSPOutputNode>
{
 public:
  explicit DSPOutputWidget(DSPOutputNode *node);
  WidgetDOMSizeProxy *getOutputDivProxy();
  const DSPOutputNode *getOutput() const;

 protected:
  std::unique_ptr<WidgetDOMSizeProxy> m_outputDivDomProxy;
  DSPOutputNode *m_node;
};
