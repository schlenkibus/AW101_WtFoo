#pragma once
#include "ModularWebUI.h"
#include <Wt/WPaintedWidget.h>
#include <examples/ModularPlayground/src/ModularPlaygroundApplication.h>

class WireOverlayWidget : public Wt::WPaintedWidget {
public:
    explicit WireOverlayWidget(ModularPlaygroundApplication* app, ModularWebUI* webUI);

protected:
  void paintEvent(Wt::WPaintDevice *paintDevice) override;
  ModularPlaygroundApplication* m_application;
  ModularWebUI* m_webUI;
};
