#pragma once

#include <Wt/WContainerWidget.h>
class DSPContainer;
class DSPContainerWidget : public Wt::WContainerWidget {
public:
    explicit DSPContainerWidget(DSPContainer* container);
protected:
    DSPContainer* m_container;
};
