#include "AudioAnalizer.h"

AudioAnalizer::AudioAnalizer(int w, int h, AudioDevice *device) : m_device{device},
                                                                  m_window{{static_cast<unsigned int>(w),
                                                                            static_cast<unsigned int>(h)},
                                                                           "Sample Analizer", sf::Style::Close} {

}

void AudioAnalizer::redraw() {

    auto &ringBuffer = m_device->getRingBuffer();
    auto &data = ringBuffer.getData();

    const auto w = m_window.getSize().x;
    const auto h = m_window.getSize().y;
    const auto baseline = h - h/2;
    const auto range = h/2;
    const auto step = w / static_cast<float>(data.size());

    m_window.clear(sf::Color::Black);

    shape.setPosition(0, baseline);

    for (auto i = ringBuffer.getWritePos(); i < ringBuffer.getData().size(); i++) {
        shape.setPosition(i * step, baseline + range * data[i].l);
        m_window.draw(shape);
    }
    for (auto i = 0; i < ringBuffer.getWritePos(); i++) {
        shape.setPosition(i * step, baseline + range * data[i].l);
        m_window.draw(shape);
    }
    m_window.display();
}
