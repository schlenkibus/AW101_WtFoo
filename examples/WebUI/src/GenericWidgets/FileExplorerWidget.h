#pragma once
#include <Wt/WContainerWidget.h>
#include <libFilesystem/include/FileExplorer.h>

class FileExplorerWidget : public Wt::WContainerWidget
{
 public:
  explicit FileExplorerWidget(const Directory& rootDirectory, std::function<void(const File&)> cb);

 protected:
  void rebuild(const Directory& directory);
  Wt::WLabel* m_currentDirectoryLabel { nullptr };

  struct Entry
  {
    Wt::WLabel* m_name;
    Wt::WPushButton* m_action;

    friend bool operator==(const Entry& l, const Entry& r)
    {
      return l.m_name == r.m_name && l.m_action == r.m_action;
    }
  };

  Entry entryFactory(File file);
  Entry entryFactory(const Directory& file);

  std::function<void(const File&)> m_Filecallback;

  std::vector<Entry> m_entrys;

  FileExplorer m_explorer;
};