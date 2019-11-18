#pragma once
#include <Wt/WContainerWidget.h>
#include <examples/ModularPlayground/src/ModularPlaygroundApplication.h>

class PlaygroundToolboxWidget : public Wt::WContainerWidget {
public:
    explicit PlaygroundToolboxWidget(ModularPlaygroundApplication* application);

  private:
    ModularPlaygroundApplication* m_application{};
};