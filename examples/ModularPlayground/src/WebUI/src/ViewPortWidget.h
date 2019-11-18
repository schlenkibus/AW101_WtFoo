#pragma once

#include <Wt/WContainerWidget.h>
#include <examples/ModularPlayground/src/ModularPlaygroundApplication.h>
class ViewPortWidget : public Wt::WContainerWidget {
public:
    ViewPortWidget(ModularPlaygroundApplication& app);
  protected:
    ModularPlaygroundApplication& m_app;
};
