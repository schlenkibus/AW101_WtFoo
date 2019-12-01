#pragma once
#include <libDSP/include/Modules/DSPModule.h>
#include "SoundFile.h"
#include "AudioStorage.h"

class PlayerPlayer : public DSPModule
{
 public:
  explicit PlayerPlayer(DSPHost* host);
  void loadTrack(const File* file);

  void tickInternals() override;

 private:
  void stop();
  void start();

  std::unique_ptr<DSPNode> resetTrigger;
  std::unique_ptr<DSPNode> playTrigger;

  float m_phaseinc { 0.0 };
  float m_head { 0.0 };
  const SoundFile* m_currentFile { nullptr };

  SoundStorage m_sounds;
};
