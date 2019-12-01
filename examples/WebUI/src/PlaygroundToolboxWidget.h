#pragma once
#include <Wt/WContainerWidget.h>
#include "ModularWebUI.h"

class DSPHost;

class PlaygroundToolboxWidget : public Wt::WContainerWidget
{
 public:
  explicit PlaygroundToolboxWidget(ModularWebUI* parent, DSPHost* application);
 private:
    void onFileSelected(const File* f);
  DSPHost* m_application {};
  ModularWebUI* m_parent;
};