#pragma once

#include "../../../DSPNodes/DSPInput.h"
#include "../GenericWidgets/DragWidget.h"
#include "../GenericWidgets/DropWidget.h"
#include "DSPSignalOutDragWidget.h"
#include <Wt/WContainerWidget.h>

class DSPInputWidget : public DropWidget {
public:
  explicit DSPInputWidget(DSPInput* node);
  void onDropHappened(Wt::WObject *dropped) override;
private:
  DSPInput* m_node;
};

