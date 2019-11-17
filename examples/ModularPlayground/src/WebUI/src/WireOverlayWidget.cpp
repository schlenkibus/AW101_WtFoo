#include "WireOverlayWidget.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WPaintDevice.h>
#include <Wt/WPainter.h>
#include <Wt/WRectF.h>
#include <Wt/WTimer.h>

#include "ModuleWidgets/ModuleContainer.h"

WireOverlayWidget::WireOverlayWidget(ModularPlaygroundApplication *app,
                                     ModularWebUI *webUI)
    : m_application{app}, m_webUI{webUI} {

  setStyleClass("overlay");
  setAttributeValue("height", "100%");
  setAttributeValue("width", "100%");
  resize(m_webUI->root()->width(), m_webUI->root()->height());

  m_color.setRgb(255, 165, 0, 128);
  m_penColor.setRgb(255, 165, 0, 80);
  m_brush.setColor(m_color);
  m_brush.setStyle(Wt::BrushStyle::Solid);
  m_pen.setColor(m_penColor);
  m_pen.setWidth(10);
  m_pen.setJoinStyle(Wt::PenJoinStyle::Bevel);
}

void WireOverlayWidget::paintEvent(Wt::WPaintDevice *paintDevice) {
  Wt::WPainter painter(paintDevice);
  painter.setBrush(m_brush);
  painter.setPen(m_pen);

  auto connections = m_webUI->getConnections();

  for (auto &c : connections) {
    auto from = m_webUI->getModuleContainer()->findWidget(c.m_from);
    auto to = m_webUI->getModuleContainer()->findWidget(c.m_to);

    if (from && to) {
      auto domfrom = from->getOutputDivProxy();
      auto domto = to->getInputDivProxy();
      double x1 = domfrom->m_midX;
      double y1 = domfrom->m_midY;

      double y2 = domto->m_midY;
      double x2 = domto->m_midX;

      double distX = std::abs(x2 - x1);
      double distY = std::abs(y2 - y1);

      painter.drawEllipse(x1 - domfrom->m_w / 2.0, y1 - domfrom->m_h / 2.0,
                          domfrom->m_w, domfrom->m_h);
      painter.drawEllipse(x2 - domto->m_w / 2.0, y2 - domto->m_h / 2.0,
                          domto->m_w, domto->m_h);

      painter.drawLine(x1, y1, x2, y2);

      domfrom->requestUpdate();
      domto->requestUpdate();
    }
  }
}

void WireOverlayWidget::requestRedraw() {
  resize(m_webUI->getDomProxy()->m_w, m_webUI->getDomProxy()->m_h);
  update();
}
