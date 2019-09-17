#include "DSPClockWidget.h"
#include "../GenericWidgets/DragWidget.h"
#include "../GenericWidgets/DropWidget.h"
#include "DSPInputWidget.h"
#include "DSPSignalOutDragWidget.h"
#include <Wt/WLabel.h>
#include <Wt/WSlider.h>

DSPClockWidget::DSPClockWidget(DSPClock* clock) {
  auto label = addWidget(std::make_unique<Wt::WLabel>());
  label->setText("CLOCK:" + clock->m_uuid.m_string);

  auto clockLenght = addWidget(std::make_unique<Wt::WSlider>());
  clockLenght->setNativeControl(true);
  clockLenght->setRange(100, 120000);
  clockLenght->changed().connect([this, clock, clockLenght]() {
    clock->setLength(clockLenght->value());
  });

  addWidget(std::make_unique<DSPSignalOutDragWidget>(clock));
  addWidget(std::make_unique<DSPInputWidget>(clock->getInputNode()));
}
