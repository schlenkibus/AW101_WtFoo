#pragma once
#include <Wt/WContainerWidget.h>

class DSPHost;

class PlaygroundToolboxWidget : public Wt::WContainerWidget
{
 public:
  explicit PlaygroundToolboxWidget(DSPHost* application);

 private:
  DSPHost* m_application {};
};