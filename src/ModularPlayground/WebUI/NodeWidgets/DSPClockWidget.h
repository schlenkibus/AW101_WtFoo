#pragma once

#include "../../../DSPNodes/DSPClock.h"
#include <Wt/WContainerWidget.h>

class DSPClockWidget : public Wt::WContainerWidget {
public:
    explicit DSPClockWidget(DSPClock* clock);
};
