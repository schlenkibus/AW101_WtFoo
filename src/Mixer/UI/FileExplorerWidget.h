#pragma once
#include "../../Defines.h"
#include "../../Filesystem/FileExplorer.h"
#include <Wt/WContainerWidget.h>

class FileExplorerWidget : public Wt::WContainerWidget {
public:
    explicit FileExplorerWidget(const tPath &path,
                              const std::function<void(const File *)> &cb);
  protected:
    void rebuild(const Directory *directory);
    Wt::WLabel* m_currentDirectoryLabel{nullptr};

    struct Entry {
        Wt::WLabel* m_name;
        Wt::WPushButton* m_action;
    };

    Entry entryFactory(const File& file);
    Entry entryFactory(const Directory& file);

    std::function<void(const File*)> m_Filecallback;

    std::vector<Entry> m_entrys;

    FileExplorer m_explorer;
};
