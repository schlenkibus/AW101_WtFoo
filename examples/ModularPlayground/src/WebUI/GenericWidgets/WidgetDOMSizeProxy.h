#pragma once
#include <Wt/WWidget.h>

class WidgetDOMSizeProxy {
public:
    explicit WidgetDOMSizeProxy(Wt::WWidget* widget);
    void requestUpdate();
    void onPosition(int x, int y);
    void onSize(int w, int h);

    int m_x = 0;
    int m_y = 0;
    int m_w = 0;
    int m_h = 0;

protected:
    Wt::JSignal<int, int> m_position;
    Wt::JSignal<int, int> m_scale;

    Wt::WWidget* m_widget;
};
