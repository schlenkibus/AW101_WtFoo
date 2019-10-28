#pragma once
#include <libFilesystem/libFilesystem/include/File.h>

class DSPHost;

class PluginLoader
{
 public:
  explicit PluginLoader(DSPHost* host);
  virtual void loadPlugin(const File& sharedFile) = 0;

 protected:
  DSPHost* const m_host;
};
