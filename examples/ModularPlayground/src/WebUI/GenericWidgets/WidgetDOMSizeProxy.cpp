#include "WidgetDOMSizeProxy.h"
#include <Wt/WJavaScript.h>
#include <Wt/Signals/signals.hpp>

WidgetDOMSizeProxy::WidgetDOMSizeProxy(Wt::WWidget *widget) : m_widget{widget}, m_position{widget, "position"}, m_scale{widget, "scale"} {


  m_scale.connect([this](int w, int h) { onSize(w, h); });
  m_position.connect([this](int x, int y) { onPosition(x, y); });

  requestUpdate();
}

void WidgetDOMSizeProxy::onPosition(int x, int y) {
  m_x = x;
  m_y = y;
}

void WidgetDOMSizeProxy::onSize(int w, int h) {
  m_w = w;
  m_h = h;
}

void WidgetDOMSizeProxy::requestUpdate() {
  auto ref = m_widget->jsRef();

  m_widget->doJavaScript(ref + ".payload = getDOMPosition(" + ref + ");");
  m_widget->doJavaScript("Wt.emit(" + ref + ", 'position', " + ref + ".payload.left, " + ref + ".payload.top);");
  m_widget->doJavaScript("Wt.emit(" + ref + ", 'scale', Number("+ ref +".offsetWidth), Number("+ ref +".offsetHeight));");
}
