#include "DSPInputWidget.h"
#include <Wt/WLabel.h>
#include <ModuleWidgets/ModuleWidget.h>

DSPInputWidget::DSPInputWidget(DSPInputNode *input)
    : m_node { input }
{
  auto image = addWidget(std::make_unique<Wt::WImage>("images/signal-in.png"));
  image->load();
  acceptDrops("signal-out");
  addWidget(std::make_unique<Wt::WLabel>())->setText(m_node->getName());
  setStyleClass("input-widget style-base");

  doubleClicked().connect([this](Wt::WMouseEvent event) {
    if(auto mod = getModule())
    {
      m_node->clearInput();
    }
  });

  m_inputDivDomProxy = std::make_unique<WidgetDOMSizeProxy>(image);
  m_inputDivDomProxy->requestUpdate();
}

void DSPInputWidget::onDropHappened(Wt::WObject *dropped)
{
  if(auto dragWidget = dynamic_cast<DragWidgetProxy<DSPOutputNode> *>(dropped))
  {
    m_node->connect(dragWidget->m_data);
  }
}

const DSPInputNode *DSPInputWidget::getInput() const
{
  return m_node;
}

DSPModule *DSPInputWidget::getModule()
{
  if(auto mod = dynamic_cast<ModuleWidget *>(parent()->parent()))
  {
    if(auto module = mod->getModule())
    {
      return module;
    }
  }
  return nullptr;
}

WidgetDOMSizeProxy *DSPInputWidget::getInputDivProxy() const
{
  return m_inputDivDomProxy.get();
}
