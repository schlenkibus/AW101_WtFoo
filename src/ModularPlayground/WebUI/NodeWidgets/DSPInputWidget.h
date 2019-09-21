#pragma once

#include "../../../DSPNodes/DSPInputNode.h"
#include "../../../Modules/DSPModule.h"
#include "../GenericWidgets/DragWidget.h"
#include "../GenericWidgets/DropWidget.h"
#include "DSPOutputWidget.h"
#include <Wt/WContainerWidget.h>

class DSPInputWidget : public DropWidget {
public:
  explicit DSPInputWidget(Input &input);
  void onDropHappened(Wt::WObject *dropped) override;

private:
  Input &m_node;
};
