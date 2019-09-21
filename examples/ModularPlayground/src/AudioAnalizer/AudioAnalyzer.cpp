#include "AudioAnalyzer.h"

AudioAnalyzer::AudioAnalyzer(int w, int h, AudioDevice *device)
    : m_device{device} {
  m_backgroundThread = std::thread{[this, w, h] {
    sf::RenderWindow m_window{
        {static_cast<unsigned int>(w), static_cast<unsigned int>(h)},
        "Sample Analyzer",
        sf::Style::Close};

    m_window.setFramerateLimit(30);

    sf::Event e{};
    while (m_window.isOpen()) {
      if (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
          m_window.close();
      }

      redraw(m_window);
    }
  }};

  shape.setRadius(1);
  shape.setFillColor(sf::Color::Red);
}

AudioAnalyzer::~AudioAnalyzer() {
  if (m_backgroundThread.joinable())
    m_backgroundThread.join();
}

void AudioAnalyzer::redraw(sf::RenderWindow &window) {

  auto &ringBuffer = m_device->getRingBuffer();
  auto &data = ringBuffer.getData();

  const auto w = window.getSize().x;
  const auto h = window.getSize().y;
  const auto baseline = h - h / 2;
  const auto range = (h / 2.0) * 0.75;
  const auto step = w / static_cast<float>(data.size());

  window.clear(sf::Color::Black);

  shape.setPosition(0, baseline);

  for (auto i = ringBuffer.getWritePos(); i < ringBuffer.getData().size();
       i++) {
    shape.setPosition(i * step, baseline - (range * data[i].l));
    window.draw(shape);
  }
  for (auto i = 0; i < ringBuffer.getWritePos(); i++) {
    shape.setPosition(i * step, baseline - (range * data[i].l));
    window.draw(shape);
  }

  window.display();
}
