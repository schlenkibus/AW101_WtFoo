#pragma once
#include "../../../DSPNodes/DSPNode.h"
#include "../../../Modules/DSPModule.h"
#include "../GenericWidgets/DragWidget.h"

class DSPOutputWidget : public DragWidget<Output> {
public:
  explicit DSPOutputWidget(Output &node)
      : DragWidget<Output>{&m_node, "images/signal-out.png",
                           "images/signal-out-small.png", "signal-out"},
        m_node{node} {}

protected:
  Output &m_node;
};
