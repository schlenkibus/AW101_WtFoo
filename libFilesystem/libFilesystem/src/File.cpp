#include "libFilesystem/include/File.h"

File::File(const tPath& filePath) : m_absolutePath{filePath.string()}, m_path{filePath} {

}

const std::string& File::getAbsoulutePath() const {
  return m_absolutePath;
}

const tPath &File::getPath() const {
  return m_path;
}