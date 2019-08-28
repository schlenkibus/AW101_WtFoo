#pragma once
#include <Wt/WPushButton.h>

class GenericSignalEmitterNode;

class SignalButtonWidget : public Wt::WPushButton {
public:
    SignalButtonWidget(GenericSignalEmitterNode* node);
  protected:
    void onClick(Wt::WMouseEvent& e);
    GenericSignalEmitterNode* m_node;
};
