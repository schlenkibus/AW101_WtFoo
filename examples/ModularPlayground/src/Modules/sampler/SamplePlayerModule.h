#pragma once
#include <libDSP/include/Modules/DSPModule.h>
#include <libFilesystem/include/File.h>

class SamplePlayerModule : public DSPModule {
 public:
  explicit SamplePlayerModule(DSPHost* parent);

  void loadSample(const File& sample);
  const File* getSampleFile() const;

  const char* getName() override;
  void tick() override;

private:


    File m_currentFile{};
    std::vector<float> m_samples;
    Input* m_playbackSpeed;
    Parameter* m_masterGain;
    Output* m_output;
};