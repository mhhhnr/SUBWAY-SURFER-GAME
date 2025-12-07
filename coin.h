#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>

class Coin {
private:
    // Position and movement
    int lane;
    float yPosition;
    float speed;

    // Visual components
    sf::CircleShape outerRing;      // Gold outer ring
    sf::CircleShape innerDisk;      // Inner disk
    sf::RectangleShape shine;       // Shine/glint effect
    sf::CircleShape shadow;         // Shadow for depth

public:
    // Constructor
    Coin(int l, float y, float s);

    // Game loop methods
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    // Getters
    float getYPosition() const;
    int getLane() const;
    sf::FloatRect getBounds() const;
};

#endif#pragma once
