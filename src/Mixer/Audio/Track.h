#pragma once
#include "SoundFile.h"
#include <atomic>
#include <vector>

class Track {
public:
  Track(unsigned int playbackRate);
  void tick();

  void play();
  void pause();

  const int getPlaybackPosition() const;
  void seekTo(double pos);

  void tightenLoop();
  void releaseLoop();

  double getLoopStartPercent() const;
  double getLoopEndPercent() const;

  bool isPlaying();

  const size_t getTrackLenghtInSamples() const;
  const size_t getTrackSampleRate() const;

  double getSignalLeft();
  double getSignalRight();
  void setSoundFile(const SoundFile &file);

  bool isTrackLoaded() const;

  template <class tCB> void forEachSample(tCB cb) {
    for (auto i = 0; i < getTrackLenghtInSamples(); i++)
      cb(m_leftSamples[0].operator[](i));
  }

  template <class tCB> void samplesAroundHead(int around, tCB cb) {
    auto start = std::max<int>(0, static_cast<int>(m_readPos) - around);
    auto end = std::min<int>(getTrackLenghtInSamples(),
                             static_cast<int>(m_readPos) + around);
    for (auto i = start; i < end; i++) {
      cb(m_leftSamples->operator[](i));
    }
  }

  template <size_t nth, class tCB>
  void nThSamplesAroundHead(int around, tCB cb) {
    auto start = std::max<int>(0, static_cast<int>(m_readPos) - around);
    auto end = std::min<int>(getTrackLenghtInSamples(),
                             static_cast<int>(m_readPos) + around);
    for (auto i = start; i < end; i++) {
      if (i % nth == 0)
        cb(m_leftSamples->operator[](i));
    }
  }

  void setPlaybackSpeed(float speedFactor);
  float getPlaybackSpeed() const;

protected:
  const std::vector<double> *m_leftSamples;
  const std::vector<double> *m_rightSamples;

  unsigned int m_sampleRate{};
  unsigned int m_playbackRate{};
  double m_readPos{};
  double m_phaseInc{1};

  struct LoopInfo {

    void tightenLoop(double current) {
      if(m_loopStart == 0.0 && m_loopEnd == 1.0)
        m_loopStart = current;
      else
        m_loopEnd = current;
    }

    void release() {
      m_loopStart = 0.0;
      m_loopEnd = 1.0;
    }

    double m_loopStart{0.0};
    double m_loopEnd{1.0};
  };

  LoopInfo m_loopInfo{};

  double m_left{};
  double m_right{};
  double m_playbackSpeed{1.0};

  bool m_playing;

  inline void incPos();
};
