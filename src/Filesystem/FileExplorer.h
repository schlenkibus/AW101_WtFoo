#pragma once

#include "../Defines.h"
#include "Directory.h"
#include <functional>
class FileExplorer {
public:
    explicit FileExplorer(const tPath& startPath);
    const Directory& getCurrentDirectory() const;
    void navigateTo(const Directory *dir);
    void onNavigated(std::function<void(const Directory*)> cb);
protected:
    Directory m_root;
    const Directory* m_currentDirectory;

    std::vector<std::function<void(const Directory*)>> m_callbacks;
void notify() const;
};
