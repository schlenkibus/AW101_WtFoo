#include "Synth/MySynthesizer.h"
#include "SynthApplication.h"
#include "Widgets/SampleInspectorWidget.h"
#include "Widgets/SignalButtonWidget.h"
#include "Widgets/SynthControlWidget.h"
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WFlags.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPaintDevice.h>
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>
#include <Wt/WPushButton.h>
#include <Wt/WRectF.h>
#include <Wt/WSlider.h>
#include <Wt/WText.h>
#include <chrono>
#include <thread>
#include <Wt/WServer.h>


//Config: /etc/wt/wt_config.xml

int main(int argc, char **argv)
{
    auto synth = MySynthesizer(DSPInfo::SampleRate, 128);

    return Wt::WRun(argc, argv, [&synth](const Wt::WEnvironment& env) {
        return std::make_unique<SynthApplication>(env, synth);
    });
}