#pragma once
#include "ModularWebUI.h"
#include <Wt/WBrush.h>
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>
#include <Wt/WPen.h>
#include <examples/ModularPlayground/src/ModularPlaygroundApplication.h>

class WireOverlayWidget : public Wt::WPaintedWidget {
public:
  explicit WireOverlayWidget(ModularPlaygroundApplication *app,
                             ModularWebUI *webUI);

  void requestRedraw();

protected:
  Wt::WBrush m_brush;
  Wt::WColor m_color;
  void paintEvent(Wt::WPaintDevice *paintDevice) override;
  ModularPlaygroundApplication *m_application;
  ModularWebUI *m_webUI;
};
