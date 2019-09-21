#pragma once
#include <SFML/Graphics.hpp>
#include <libAudio/libAudio/AudioDevice.h>
#include <thread>

class AudioAnalyzer {
public:
    AudioAnalyzer(int w, int h, AudioDevice* device);
    ~AudioAnalyzer();
    void redraw(sf::RenderWindow& window);
protected:
    AudioDevice* m_device;
    sf::CircleShape shape;

    std::thread m_backgroundThread;
};


