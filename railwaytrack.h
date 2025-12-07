#ifndef RAILWAYTRACK_H
#define RAILWAYTRACK_H

#include <SFML/Graphics.hpp>
#include "GameList.h"

class RailwayTrack {
private:
    // Track dimensions
    float laneX;
    float width;
    float height;

    // Main track components
    sf::RectangleShape gravelBase;
    sf::RectangleShape leftRail;
    sf::RectangleShape rightRail;

    // Collections of track elements
    GameList<sf::RectangleShape> sleepers;  // Wooden sleepers/ties
    GameList<sf::RectangleShape> gravel;    // Small stones for detail

public:
    // Constructor
    RailwayTrack(float x, float w, float h);

    // Rendering
    void render(sf::RenderWindow& window);
};

#endif#pragma once
