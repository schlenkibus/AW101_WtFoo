#pragma once
#include <Wt/WWidget.h>

class WidgetDOMSizeProxy {
public:
    explicit WidgetDOMSizeProxy(Wt::WWidget* widget);
    void requestUpdate();
    void onPosition(int x, int y);
    void onSize(int w, int h);
    void onMiddle(int x, int y);

    int m_x = 0;
    int m_y = 0;
    int m_w = 0;
    int m_h = 0;

    int m_midX = 0;
    int m_midY = 0;

protected:
    Wt::JSignal<int, int> m_position;
    Wt::JSignal<int, int> m_scale;
    Wt::JSignal<int, int> m_middle;

    Wt::WWidget* m_widget;
};
