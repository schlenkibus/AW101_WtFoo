#pragma once
#include <SFML/Graphics.hpp>
#include "../../Audio/AudioDevice.h"

class AudioAnalizer {
public:
    AudioAnalizer(int w, int h, AudioDevice* device);
    void redraw();
protected:
    AudioDevice* m_device;
    sf::RenderWindow m_window;
    sf::CircleShape shape;
};


