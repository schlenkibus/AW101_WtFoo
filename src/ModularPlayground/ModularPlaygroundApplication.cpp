#include "ModularPlaygroundApplication.h"
#include "../DSPNodes/DSPInfo.h"

ModularPlaygroundApplication::ModularPlaygroundApplication() {
  m_audioDevice = std::make_unique<PortAudioDevice>(
      m_baseContainer, DSPInfo::SampleRate, DSPInfo::FramesPerBuffer);
}

std::vector<DSPNode *> ModularPlaygroundApplication::collectNodes() {
  std::vector<DSPNode *> ret;
  m_baseContainer.collectNodes(ret);
  ret.emplace_back(&m_baseContainer);
  return ret;
}

DSPNode *ModularPlaygroundApplication::getNode(const LibUUID::UUID &uuid) {
  auto nodes = collectNodes();
  for (auto &node : nodes) {
    if (node->m_uuid == uuid)
      return node;
  }

  return nullptr;
}

AudioDevice *ModularPlaygroundApplication::getAudioDevice() {
  return m_audioDevice.get();
}

DSPContainer *ModularPlaygroundApplication::getRootNode() {
  return &m_baseContainer;
}
