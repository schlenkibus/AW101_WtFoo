#include "DSPClockWidget.h"
#include "../GenericWidgets/DragWidget.h"
#include "../GenericWidgets/DropWidget.h"
#include "DSPInputWidget.h"
#include "DSPSignalOutDragWidget.h"
#include <Wt/WLabel.h>

DSPClockWidget::DSPClockWidget(DSPClock* clock) {
  auto label = addWidget(std::make_unique<Wt::WLabel>());
  label->setText("CLOCK:" + clock->m_uuid.m_string);
  auto clockOut = addWidget(std::make_unique<DSPSignalOutDragWidget>(clock));
  auto runnIn = addWidget(std::make_unique<DSPInputWidget>(clock->getInputNode()));
}
