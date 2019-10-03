#pragma once
#include "Directory.h"
#include <functional>
#include <vector>

namespace FileTools {
static void append(const std::vector<File> &from, std::vector<File> &to,
                   const std::function<bool(const File &)> &filter = nullptr) {
  for (auto &f : from)
    if ((filter && filter(f)) || !filter)
      to.emplace_back(f);
}

static std::vector<File>
recurseDirectory(const Directory &directory,
                 const std::function<bool(const File &)> &filter) {
  std::vector<File> ret;
  for (auto &dir : directory.getDirectorys()) {
    append(recurseDirectory(dir, filter), ret);
  }

  append(directory.getFiles(), ret, filter);

  return ret;
}
}