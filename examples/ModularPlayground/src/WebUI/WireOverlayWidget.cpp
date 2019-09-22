#include "WireOverlayWidget.h"
#include <Wt/WPaintDevice.h>
#include <Wt/WPainter.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WRectF.h>
#include <Wt/WTimer.h>

WireOverlayWidget::WireOverlayWidget(ModularPlaygroundApplication *app, ModularWebUI* webUI) : m_application{app}, m_webUI{webUI} {
  resize(m_webUI->root()->width(), m_webUI->root()->height());

  setStyleClass("overlay");

  auto timer = addChild(std::make_unique<Wt::WTimer>());
  timer->setInterval(std::chrono::milliseconds(250));
  timer->setSingleShot(false);
  timer->timeout().connect([this]{
    auto w = m_webUI->getWindowX();
    auto h = m_webUI->getWindowY();
    resize(w, h);
    update(Wt::PaintFlag::Update);
    scheduleRender(Wt::RepaintFlag::SizeAffected);
  });
  timer->start();

  setAttributeValue("height", "100%");
  setAttributeValue("width", "100%");
}

void WireOverlayWidget::paintEvent(Wt::WPaintDevice *paintDevice) {
    Wt::WPainter painter(paintDevice);
    Wt::WBrush brush;
    Wt::WColor color;
    color.setRgb(255, 0, 0);
    brush.setColor(color);
    Wt::WRectF rect;

    //m_webUI->traverseAllWidgets([](auto* widget) {

    //});

    rect.setWidth(200);
    rect.setHeight(100);
    rect.setX(width().value() / 2.0);
    rect.setY(height().value() / 2.0);
    painter.setBrush(brush);
    painter.drawText(rect, Wt::AlignmentFlag::Center, "Foooo!");
}
