#include "DSPInputWidget.h"
#include <Wt/WLabel.h>

DSPInputWidget::DSPInputWidget(DSPInput *node) {
  m_node = node;
  auto image = addWidget(std::make_unique<Wt::WImage>("images/signal-in.png"));
  image->load();
  acceptDrops("signal-out");
}

void DSPInputWidget::onDropHappened(Wt::WObject *dropped) {
  m_node->connect(dynamic_cast<DragWidgetProxy<DSPNode>*>(dropped)->m_data);
}

