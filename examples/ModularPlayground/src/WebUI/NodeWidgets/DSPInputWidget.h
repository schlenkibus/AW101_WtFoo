#pragma once

#include "../GenericWidgets/DragWidget.h"
#include "../GenericWidgets/DropWidget.h"
#include "DSPOutputWidget.h"
#include <Wt/WContainerWidget.h>
#include <libDSP/Modules/Input.h>

class DSPInputWidget : public DropWidget {
public:
  explicit DSPInputWidget(Input* input);
  void onDropHappened(Wt::WObject *dropped) override;

private:
  Input *m_node;
};
