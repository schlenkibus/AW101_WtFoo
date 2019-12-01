#include "PlaygroundToolboxWidget.h"
#include "ModularWebUI.h"
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WFileUpload.h>
#include <libDSP/include/DSPHost.h>
#include <GenericWidgets/FileExplorerWidget.h>

PlaygroundToolboxWidget::PlaygroundToolboxWidget(ModularWebUI* parent, DSPHost* application)
    : m_application { application }
    , m_parent { parent }
{
  auto combobox = addWidget(std::make_unique<Wt::WComboBox>());
  for(auto& avail : m_application->getAvailableModules())
  {
    if(avail != "AudioOutModule")
      combobox->addItem(avail);
  }

  auto createButton = addWidget(std::make_unique<Wt::WPushButton>());
  createButton->clicked().connect([this, combobox]() {
    auto name = combobox->currentText();
    auto str = name.toUTF8();
    m_application->createModule(str);
  });

  auto fe = addWidget(std::make_unique<FileExplorerWidget>(Directory(".."), [this](auto f) { onFileSelected(f); }));
  fe->addStyleClass("explorer-widget");

  createButton->setText("Create selected module");
}

void PlaygroundToolboxWidget::onFileSelected(const File* f)
{
  m_application->getPluginLoader()->loadPlugin(*f);
  m_parent->getPluginLoader()->loadPlugin(*f);
}