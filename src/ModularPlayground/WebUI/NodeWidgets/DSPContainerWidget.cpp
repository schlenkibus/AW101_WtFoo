#include "DSPContainerWidget.h"
#include "../../../DSPNodes/DSPContainer.h"
#include "DSPClockWidget.h"
#include <Wt/WPushButton.h>
#include <Wt/WSlider.h>

DSPContainerWidget::DSPContainerWidget(DSPContainer *container) {
  m_container = container;

  for(auto& c: m_container->getChildren()) {
    if(strcmp(c->TYPE(), "CONTAINER") == 0 || strcmp(c->TYPE(), "COLLECTION") == 0) {
      addWidget(std::make_unique<DSPContainerWidget>(static_cast<DSPContainer*>(c)));
    } else if(strcmp(c->TYPE(), "CLOCK") == 0) {
      addWidget(std::make_unique<DSPClockWidget>(static_cast<DSPClock*>(c)));
    }
  }
}
