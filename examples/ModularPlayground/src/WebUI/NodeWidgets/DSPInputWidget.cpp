#include "DSPInputWidget.h"
#include <Wt/WLabel.h>
#include <examples/ModularPlayground/src/WebUI/ModuleWidgets/ModuleWidget.h>

DSPInputWidget::DSPInputWidget(Input *input) : m_node{input}, domProxy{this} {
  auto image = addWidget(std::make_unique<Wt::WImage>("images/signal-in.png"));
  image->load();
  acceptDrops("signal-out");
  addWidget(std::make_unique<Wt::WLabel>())->setText(m_node->name);
  setStyleClass("input-widget");
  setStyleClass("style-base");

  doubleClicked().connect([this](Wt::WMouseEvent event) {
    if(auto mod = getModule()) {
        mod->disconnectNodes(m_node);
    }
  });

  domProxy.requestUpdate();
}

void DSPInputWidget::onDropHappened(Wt::WObject *dropped) {
  if (auto dragWidget = dynamic_cast<DragWidgetProxy<Output> *>(dropped)) {
    m_node->connect(dragWidget->m_data);
  }
}

const Input* DSPInputWidget::getInput() const {
    return m_node;
}

DSPModule *DSPInputWidget::getModule() {
  if(auto mod = dynamic_cast<ModuleWidget*>(parent()->parent())) {
    if(auto module = mod->getModule()) {
      return module;
    }
  }
  return nullptr;
}
