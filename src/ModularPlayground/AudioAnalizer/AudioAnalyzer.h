#pragma once
#include "../../Audio/AudioDevice.h"
#include <SFML/Graphics.hpp>
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


