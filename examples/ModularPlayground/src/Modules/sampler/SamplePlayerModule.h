#pragma once
#include <libDSP/include/Modules/DSPModule.h>
#include <libFilesystem/include/File.h>

class SamplePlayerModule : public DSPModule
{
 public:
  explicit SamplePlayerModule(DSPHost* parent);

  void loadSample(const File& sample);
  const File* getSampleFile() const;

  void tickInternals() override;

 private:
  File m_currentFile {};
  std::vector<float> m_samples;
  DSPInputNode* m_playbackSpeed;
  Parameter* m_masterGain;
  DSPOutputNode* m_output;
};