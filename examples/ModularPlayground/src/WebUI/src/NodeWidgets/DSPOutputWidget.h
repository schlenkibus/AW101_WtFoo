#pragma once
#include "../GenericWidgets/DragWidget.h"
#include <Wt/WLabel.h>
#include <GenericWidgets/WidgetDOMSizeProxy.h>
#include <libDSP/include/Modules/Output.h>

class DSPOutputWidget : public DragWidget<Output> {
public:
  explicit DSPOutputWidget(Output *node)
      : DragWidget<Output>{node, "images/signal-out.png",
                           "images/signal-out-small.png", "signal-out"},
        m_node{node} {
    addWidget(std::make_unique<Wt::WLabel>())->setText(m_node->name);
    setStyleClass("output-widget style-base");

    m_outputDivDomProxy = std::make_unique<WidgetDOMSizeProxy>(getImageElement());
    m_outputDivDomProxy->requestUpdate();
  }

  WidgetDOMSizeProxy* getOutputDivProxy() { return m_outputDivDomProxy.get();
  }

  const Output *getOutput() const;

protected:
    std::unique_ptr<WidgetDOMSizeProxy> m_outputDivDomProxy;
    Output *m_node;
};
