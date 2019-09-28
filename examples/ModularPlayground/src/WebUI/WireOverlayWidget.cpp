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
    auto& dom = modWidget->getDomProxy();
    double x = dom.m_x;
    double y = dom.m_y;
    double w = dom.m_w;
    double h = dom.m_h;
    painter.drawRect(x, y, w, h);
  }
}

void WireOverlayWidget::requestRedraw() {
  resize(m_webUI->getDomProxy()->m_w, m_webUI->getDomProxy()->m_h);
  update();
}
