#pragma once
#include "ModularWebUI.h"
#include <Wt/WBrush.h>
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>
#include <Wt/WPen.h>

class WireOverlayWidget : public Wt::WPaintedWidget
{
 public:
  explicit WireOverlayWidget(DSPHost *app, ModularWebUI *webUI);

  void requestRedraw();

 protected:
  Wt::WBrush m_brush;
  Wt::WColor m_color;
  Wt::WColor m_penColor;
  Wt::WPen m_pen;
  void paintEvent(Wt::WPaintDevice *paintDevice) override;
  DSPHost *m_application;
  ModularWebUI *m_webUI;
};
