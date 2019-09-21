#pragma once
#include "../NodeWidgets/DSPOutputWidget.h"
#include <Wt/WContainerWidget.h>

class DropWidget : public Wt::WContainerWidget {
public:
    virtual void onDropHappened(Wt::WObject* dropped) = 0;
  protected:
    void dropEvent(Wt::WDropEvent dropEvent) override {
        onDropHappened(dropEvent.source());
    }
};
