#pragma once

#include <libDSP/include/DSPNodes/DSPOutputNode.h>
class Connection
{
 public:
  Connection(const DSPOutputNode* from, const DSPInputNode* to);
  const DSPOutputNode* m_from;
  const DSPInputNode* m_to;
};
