#pragma once
#include <Wt/WPushButton.h>

class GenericButtonWidget : public Wt::WPushButton {
public:
  template <class tCaption, class tCB>
  GenericButtonWidget(tCaption caption, tCB cb) {
    clicked().connect([this, cb]() { cb(*this); });
    setText(caption);
  }
};
