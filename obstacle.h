#pragma once
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

// Forward declaration
class Player;

// ===================== BASE OBSTACLE CLASS (ABSTRACT) =====================
class Obstacle {
protected:
    int lane;
    float yPosition;
    sf::RectangleShape shape;
    float speed;
    bool canChangeLane;
    float laneChangeTimer;

public:
    // Constructor and destructor
    Obstacle(int l, float y, float s, bool changeLane = false);
    virtual ~Obstacle();

    // Game loop methods
    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);
    virtual bool checkCollision(Player& player) = 0;  // Pure virtual - must implement

    // Getters
    float getYPosition() const;
    int getLane() const;
    sf::FloatRect getBounds() const;
};

// ===================== TRAIN OBSTACLE =====================
class Train : public Obstacle {
private:
    // Train visual components
    sf::RectangleShape body;
    sf::RectangleShape frontPanel;
    sf::RectangleShape stripe;
    sf::RectangleShape windowL;
    sf::RectangleShape windowR;
    sf::CircleShape headlightL;
    sf::CircleShape headlightR;

public:
    Train(int l, float y, float s, bool moving = false);

    void update(float dt) override;
    void render(sf::RenderWindow& win) override;
    bool checkCollision(Player& player) override;
};

// ===================== BARRIER OBSTACLE =====================
class Barrier : public Obstacle {
private:
    // Barrier visual components
    sf::RectangleShape body;
    sf::RectangleShape stripe1;
    sf::RectangleShape stripe2;
    sf::RectangleShape legLeft;
    sf::RectangleShape legRight;

public:
    Barrier(int l, float y, float s);

    void update(float dt) override;
    void render(sf::RenderWindow& win) override;
    bool checkCollision(Player& player) override;
};

// ===================== CONE OBSTACLE =====================
class Cone : public Obstacle {
private:
    // Cone visual components
    sf::ConvexShape cone;
    sf::RectangleShape stripe;
    sf::RectangleShape base;

public:
    Cone(int l, float y, float s);

    void update(float dt) override;
    void render(sf::RenderWindow& win) override;
    bool checkCollision(Player& player) override;
};

// ===================== FENCE OBSTACLE =====================
class Fence : public Obstacle {
private:
    // Fence visual components
    sf::RectangleShape plank1;
    sf::RectangleShape plank2;
    sf::RectangleShape plank3;
    sf::RectangleShape beamTop;
    sf::RectangleShape beamBottom;

public:
    Fence(int l, float y, float s);

    void update(float dt) override;
    void render(sf::RenderWindow& win) override;
    bool checkCollision(Player& player) override;
};

#endif