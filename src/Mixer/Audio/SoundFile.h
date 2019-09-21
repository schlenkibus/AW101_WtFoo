#pragma once

#include <SFML/Audio.hpp>
#include "../../Filesystem/File.h"

class SoundFile {
public:
  virtual int getSampleRate() const = 0;

  const std::vector<double> &getLeftSamples() const {
      return m_leftBuffer;
  }

  const std::vector<double> &getRightSamples() const {
      return m_rightBuffer;
  }
  std::vector<double> m_leftBuffer;
  std::vector<double> m_rightBuffer;
};

class TestSoundFile : public SoundFile {
public:
    explicit TestSoundFile(const File::tPath& path) {


        auto loopRange = [](auto* begin, const auto count, auto cb) {
            for(auto i = 0; i < count; i++) {
                cb(begin[i]);
            }
        };

        if(!m_buffer.loadFromFile(path.string()))
            throw std::runtime_error("could not load file: " + path.string());


        auto currentMax = 1.0;
        loopRange(m_buffer.getSamples(), m_buffer.getSampleCount(), [&currentMax](const sf::Int16& in) {
            currentMax = std::max<double>(in, currentMax);
        });

        if(m_buffer.getChannelCount() == 1) {
            for(auto i = 0; i < m_buffer.getSampleCount(); i++) {
                auto sample = m_buffer.getSamples()[i] / currentMax;
                m_rightBuffer.emplace_back(sample);
                m_leftBuffer.emplace_back(sample);
            }
        } else if(m_buffer.getChannelCount() == 2) {
            for(auto i = 0; i + 1 < m_buffer.getSampleCount(); i+=2) {
                auto left = m_buffer.getSamples()[i] / currentMax;
                auto right = m_buffer.getSamples()[i+1] / currentMax;
                m_leftBuffer.emplace_back(left);
                m_rightBuffer.emplace_back(right);
            }
        } else {
            throw std::runtime_error("unsupported channel count! is: " + std::to_string(m_buffer.getChannelCount()));
        }
    }
    int getSampleRate() const override {
        return m_buffer.getSampleRate();
    }
protected:
    sf::SoundBuffer m_buffer;
};