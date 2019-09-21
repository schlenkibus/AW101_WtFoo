#include "DSPInputWidget.h"
#include <Wt/WLabel.h>

DSPInputWidget::DSPInputWidget(Input *input) : m_node{input} {
  auto image = addWidget(std::make_unique<Wt::WImage>("images/signal-in.png"));
  image->load();
  acceptDrops("signal-out");
  addWidget(std::make_unique<Wt::WLabel>())->setText(m_node->name);
  setStyleClass("input-widget");
}

void DSPInputWidget::onDropHappened(Wt::WObject *dropped) {
  if (auto dragWidget = dynamic_cast<DragWidgetProxy<Output> *>(dropped)) {
    m_node->connect(*dragWidget->m_data);
  }
}
