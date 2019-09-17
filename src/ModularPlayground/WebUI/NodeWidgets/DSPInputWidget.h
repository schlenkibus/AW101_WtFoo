#pragma once

#include "../../../DSPNodes/DSPInput.h"
#include "../GenericWidgets/DragWidget.h"
#include "../GenericWidgets/DropWidget.h"
#include "DSPSignalOutDragWidget.h"
#include <Wt/WContainerWidget.h>

class DSPInputWidget : public DropWidget<DSPSignalOutDragWidget> {
public:
  explicit DSPInputWidget(DSPInput* node);
  void onDropHappened(DSPSignalOutDragWidget *dropped) override;
private:
  DSPInput* m_node;
};

