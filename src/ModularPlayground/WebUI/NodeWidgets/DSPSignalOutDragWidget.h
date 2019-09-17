#pragma once
#include "../../../DSPNodes/DSPNode.h"
#include "../GenericWidgets/DragWidget.h"

class DSPSignalOutDragWidget : public DragWidget<DSPNode> {
public:
    explicit DSPSignalOutDragWidget(DSPNode* data) : DragWidget<DSPNode>{data, "images/signal-out.png", "images/signal-out-small.png", "signal-out"} {
        m_node = data;
    }

  protected:
    DSPNode* m_node;
};
