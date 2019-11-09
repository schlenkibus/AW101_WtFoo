#include "libFilesystem/include/File.h"

File::File(const tPath& filePath)
    : m_absolutePath { filePath.string() }
    , m_path { filePath }
{
}

File::File()
    : m_absolutePath { "NONE" }
    , m_path {}
{
}

const std::string& File::getAbsoulutePath() const
{
  return m_absolutePath;
}

const tPath& File::getPath() const
{
  return m_path;
}
