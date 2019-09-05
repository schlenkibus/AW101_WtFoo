#pragma once
#include "../Defines.h"
#include <string>
#include <string_view>

class File {
public:
    File(const tPath& filePath);
    const std::string_view getAbsoulutePath() const;
    const tPath& getPath() const;
  protected:
    std::string m_absolutePath;
    tPath m_path;
};
