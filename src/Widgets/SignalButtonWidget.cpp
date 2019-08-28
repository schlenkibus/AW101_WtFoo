#include "SignalButtonWidget.h"
#include "../Synth/SignalNodes/GenericSignalEmitterNode.h"

SignalButtonWidget::SignalButtonWidget(GenericSignalEmitterNode* node)
  : Wt::WPushButton{"Trigger"}
  , m_node{node}
{
}

void SignalButtonWidget::onClick(Wt::WMouseEvent& e) {
  m_node->setSignal(isChecked());
}
