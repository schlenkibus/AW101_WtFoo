#include "libFilesystem/include/Directory.h"

Directory::Directory(const tPath &path) : File{path} {
  for (auto &entry : std::experimental::filesystem::directory_iterator(path)) {
    if (entry.symlink_status().type() ==
        std::experimental::filesystem::file_type::directory) {
      m_directorys.emplace_back(this, entry.path());
    } else if (entry.symlink_status().type() ==
               std::experimental::filesystem::file_type::regular) {
      m_files.emplace_back(entry.path());
    }
  }
}

Directory::Directory(Directory *parent, const tPath &path) : Directory(path) {
  m_parent = parent;
}

const std::vector<File> &Directory::getFiles() const { return m_files; }

const std::vector<Directory> &Directory::getDirectorys() const {
  return m_directorys;
}

const Directory *Directory::getParent() const { return m_parent; }