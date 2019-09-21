#include "File.h"

File::File(const tPath& filePath) : m_absolutePath{filePath.string()}, m_path{filePath} {

}

const std::string_view File::getAbsoulutePath() const {
  return std::string_view(m_absolutePath);
}

const File::tPath &File::getPath() const {
  return m_path;
}
