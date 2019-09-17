#include "DSPInputWidget.h"
#include <Wt/WLabel.h>

void DSPInputWidget::onDropHappened(DSPSignalOutDragWidget *dropped) {
  m_node->connect(dropped->getUserData());
}

DSPInputWidget::DSPInputWidget(DSPInput *node) {
  m_node = node;
  auto image = addWidget(std::make_unique<Wt::WImage>("images/signal-in.png"));
}

