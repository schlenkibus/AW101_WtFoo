#pragma once

#include <Wt/WContainerWidget.h>

class DSPHost;

class ViewPortWidget : public Wt::WContainerWidget
{
 public:
  ViewPortWidget(DSPHost& app);

 protected:
  DSPHost& m_app;
};
