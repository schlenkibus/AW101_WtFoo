#pragma once
#include "../ModularPlaygroundApplication.h"
#include <Wt/WContainerWidget.h>

class PlaygroundToolboxWidget : public Wt::WContainerWidget {
public:
    explicit PlaygroundToolboxWidget(ModularPlaygroundApplication* application);

  private:
    ModularPlaygroundApplication* m_application{};
};