#include "libFilesystem/include/FileExplorer.h"

FileExplorer::FileExplorer(const Directory &rootDirectory)
    : m_root { rootDirectory }
{
  m_currentDirectory = &m_root;
}

const Directory &FileExplorer::getCurrentDirectory() const
{
  return *m_currentDirectory;
}

void FileExplorer::navigateTo(const Directory *dir)
{
  if(dir == m_currentDirectory->getParent())
  {
    m_currentDirectory = dir;
    notify();
    return;
  }

  for(auto &d : m_currentDirectory->getDirectorys())
  {
    if(d.getPath() == dir->getPath())
    {
      m_currentDirectory = dir;
      notify();
      return;
    }
  }
}

void FileExplorer::notify() const
{
  for(auto &cb : m_callbacks)
  {
    cb(m_currentDirectory);
  }
}

void FileExplorer::onNavigated(std::function<void(const Directory *)> cb)
{
  m_callbacks.emplace_back(cb);
}