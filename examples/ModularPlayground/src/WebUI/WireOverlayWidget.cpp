#include "WireOverlayWidget.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WPaintDevice.h>
#include <Wt/WPainter.h>
#include <Wt/WRectF.h>
#include <Wt/WTimer.h>

WireOverlayWidget::WireOverlayWidget(ModularPlaygroundApplication *app,
                                     ModularWebUI *webUI)
    : m_application{app}, m_webUI{webUI} {

  setStyleClass("overlay");
  setAttributeValue("height", "100%");
  setAttributeValue("width", "100%");
  //m_webUI->getModuleContainer()
  resize(m_webUI->root()->width(), m_webUI->root()->height());
}

void WireOverlayWidget::paintEvent(Wt::WPaintDevice *paintDevice) {
  Wt::WPainter painter(paintDevice);

  for (auto &modWidget : m_webUI->getModuleContainer()) {
    double x = modWidget->x;
    double y = modWidget->y;
    double w = modWidget->w;
    double h = modWidget->h;
    painter.drawLine(x, y, w, h);
  }
}

void WireOverlayWidget::requestRedraw() {
  resize(m_webUI->root()->width(), m_webUI->root()->height());
  update();
}
