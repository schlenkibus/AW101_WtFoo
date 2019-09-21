#include "FileExplorerWidget.h"
#include <Wt/WLabel.h>
#include <Wt/WPushButton.h>

FileExplorerWidget::FileExplorerWidget(
    const File::tPath &path, const std::function<void(const File *)> &cb)
    : m_explorer{path}, m_Filecallback{cb} {

  m_explorer.onNavigated(
      [this](const Directory *newDirectory) { rebuild(newDirectory); });

  rebuild(&m_explorer.getCurrentDirectory());
}

void FileExplorerWidget::rebuild(const Directory *directory) {
  clear();
  m_entrys.clear();

  m_currentDirectoryLabel = addWidget(std::make_unique<Wt::WLabel>());
  m_currentDirectoryLabel->setText(directory->getAbsoulutePath().data());
  m_currentDirectoryLabel->addStyleClass("current-path-label");

  if (auto parentDir = directory->getParent()) {
    auto entry = entryFactory(*parentDir);
    entry.m_name->setText("..");
    m_entrys.emplace_back(entry);
  }

  for (auto &d : directory->getDirectorys()) {
    m_entrys.emplace_back(entryFactory(d));
  }

  for (auto &f : directory->getFiles()) {
    m_entrys.emplace_back(entryFactory(f));
  }
}

FileExplorerWidget::Entry FileExplorerWidget::entryFactory(const File &file) {
  auto filePtr = &file;

  Entry entry{};
  auto container = addWidget(std::make_unique<Wt::WContainerWidget>());

  entry.m_name = container->addWidget(std::make_unique<Wt::WLabel>());
  entry.m_name->setText(file.getPath().filename().string());
  entry.m_name->addStyleClass("file-label");

  entry.m_action = container->addWidget(std::make_unique<Wt::WPushButton>());
  entry.m_action->setText("->");
  entry.m_action->clicked().connect(
      [this, filePtr] { m_Filecallback(filePtr); });
  entry.m_action->addStyleClass("file-button");

    container->addStyleClass("file-entry");

  return entry;
}

FileExplorerWidget::Entry
FileExplorerWidget::entryFactory(const Directory &directory) {
  auto directoryPtr = &directory;

  Entry entry{};
  auto container = addWidget(std::make_unique<Wt::WContainerWidget>());

  entry.m_name = container->addWidget(std::make_unique<Wt::WLabel>());
  entry.m_name->setText(directory.getPath().filename().string());
  entry.m_name->addStyleClass("directory-label");

  entry.m_action = container->addWidget(std::make_unique<Wt::WPushButton>());
  entry.m_action->setText("Enter");
  entry.m_action->addStyleClass("directory-button");

  entry.m_action->clicked().connect(
      [this, directoryPtr] { m_explorer.navigateTo(directoryPtr); });

  container->addStyleClass("directory-entry");

  return entry;
}
