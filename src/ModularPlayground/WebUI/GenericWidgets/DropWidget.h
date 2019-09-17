#pragma once
#include <Wt/WContainerWidget.h>

template<class tAcceptedDragWidget>
class DropWidget : public Wt::WContainerWidget {
public:
    virtual void onDropHappened(tAcceptedDragWidget* dropped) = 0;
  protected:
    void dropEvent(Wt::WDropEvent dropEvent) override {
        if(auto castedPtr = dynamic_cast<tAcceptedDragWidget*>(dropEvent.source())) {
            onDropHappened(castedPtr);
        }
    }
};
