#pragma once
#include <libFilesystem/include/File.h>

class DSPHost;

class PluginLoader
{
 public:
  typedef void (*tRegisterModule)(DSPHost* h);

  explicit PluginLoader(DSPHost* host);
  virtual void loadPlugin(const File& sharedFile) = 0;

 protected:
  DSPHost* const m_host;
};
