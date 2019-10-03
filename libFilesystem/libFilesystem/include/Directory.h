#pragma once
#include "File.h"

class Directory : public File {
public:
    explicit Directory(const tPath& path);
    explicit Directory(Directory *parent, const tPath &path);
    const std::vector<File>& getFiles() const;
    const std::vector<Directory>& getDirectorys() const;
    const Directory* getParent() const;

protected:
    std::vector<File> m_files;
    std::vector<Directory> m_directorys;
    Directory* m_parent{nullptr};
};
