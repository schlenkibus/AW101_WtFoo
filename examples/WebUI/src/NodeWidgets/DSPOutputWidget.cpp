#include <libDSP/include/DSPNodes/DSPOutputNode.h>
#include "DSPOutputWidget.h"

DSPOutputWidget::DSPOutputWidget(DSPOutputNode* node)
        : DragWidget<DSPOutputNode> { node, "images/signal-out.png", "images/signal-out-small.png", "signal-out" }
        , m_node { node }
{
    addWidget(std::make_unique<Wt::WLabel>())->setText(m_node->getName());
    setStyleClass("output-widget style-base");

    m_outputDivDomProxy = std::make_unique<WidgetDOMSizeProxy>(getImageElement());
    m_outputDivDomProxy->requestUpdate();
}

const DSPOutputNode* DSPOutputWidget::getOutput() const
{
  return m_node;
}
WidgetDOMSizeProxy* DSPOutputWidget::getOutputDivProxy()
{
  return m_outputDivDomProxy.get();
}
