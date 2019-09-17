#pragma once

#include "../ModularPlaygroundApplication.h"
#include <Wt/WContainerWidget.h>
class ViewPortWidget : public Wt::WContainerWidget {
public:
    ViewPortWidget(ModularPlaygroundApplication& app);
  protected:
    ModularPlaygroundApplication& m_app;
};
