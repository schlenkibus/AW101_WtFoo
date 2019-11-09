#pragma once
#include "Path.h"
#include <string>

class File {
public:
  File();
  explicit File(const tPath& filePath);
  const std::string& getAbsoulutePath() const;
  const tPath& getPath() const;
protected:
  std::string m_absolutePath;
  tPath m_path;
};