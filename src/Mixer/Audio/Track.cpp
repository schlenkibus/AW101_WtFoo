#include "Track.h"
#include "../../LibDSP/DSPInfo.h"
#include "SoundFile.h"

const size_t Track::getTrackLenghtInSamples() const {
  if (isTrackLoaded())
    return m_leftSamples->size();
  return 0;
}


const size_t Track::getTrackSampleRate() const {
    if(isTrackLoaded())
      return m_sampleRate;
    return DSPInfo::SampleRate;
}

Track::Track(const unsigned int playbackRate)
    : m_readPos{0}, m_playbackRate{playbackRate},
      m_sampleRate{DSPInfo::SampleRate}, m_playing{false},
      m_rightSamples{nullptr}, m_leftSamples{nullptr}
{
}

void Track::tick() {
  if (m_playing) {
    m_left = m_leftSamples->operator[]((int)m_readPos);
    m_right = m_rightSamples->operator[]((int)m_readPos);

    incPos();

  } else {
    m_left = 0.0;
    m_right = 0.0;
  }
}

inline void Track::incPos() {

  m_readPos += m_phaseInc;

  const auto len = getTrackLenghtInSamples();
  auto start = len * std::min<double>(getLoopStartPercent(), getLoopEndPercent());
  auto end = len * std::max<double>(getLoopEndPercent(), getLoopStartPercent());

  if (m_readPos >= end)
    m_readPos = start;
  else if (m_readPos <= start)
    m_readPos = end;
}

void Track::play() {
  if (!m_playing) {
    m_readPos = std::max<int>(
        0, std::min<int>((int)m_readPos, getTrackLenghtInSamples() - 1));
    m_playing = true;
  }
}

void Track::pause() {
  if (m_playing)
    m_playing = false;
}

bool Track::isPlaying() { return m_playing; }

double Track::getSignalLeft() { return m_left; }

double Track::getSignalRight() { return m_right; }

void Track::setSoundFile(const SoundFile &file) {
  if (!m_playing) {
    m_leftSamples = nullptr;
    m_rightSamples = nullptr;

    m_leftSamples = &file.getLeftSamples();
    m_rightSamples = &file.getRightSamples();
    m_sampleRate = file.getSampleRate();

    m_phaseInc = (static_cast<double>(m_sampleRate) / m_playbackRate) * m_playbackSpeed;
  }
}

bool Track::isTrackLoaded() const {
  return m_leftSamples != nullptr && m_rightSamples != nullptr;
}

const int Track::getPlaybackPosition() const{
    return static_cast<int>(m_readPos);
}

void Track::setPlaybackSpeed(float speedFactor)
{
  m_playbackSpeed = speedFactor;
  m_phaseInc = (static_cast<double>(m_sampleRate) / m_playbackRate) * m_playbackSpeed;
}

float Track::getPlaybackSpeed() const {
  return m_playbackSpeed;
}

void Track::seekTo(double pos){
    m_readPos = pos;
}

double Track::getLoopStartPercent() const {
  return m_loopInfo.m_loopStart;
}

double Track::getLoopEndPercent() const {
  return m_loopInfo.m_loopEnd;
}

void Track::tightenLoop() {
  m_loopInfo.tightenLoop(m_readPos / getTrackLenghtInSamples());
}

void Track::releaseLoop() {
  m_loopInfo.release();
}