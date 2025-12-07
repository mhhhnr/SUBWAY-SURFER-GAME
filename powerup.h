#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>

// Forward declaration
class Player;

// ===================== BASE POWERUP CLASS (ABSTRACT) =====================
class PowerUp {
protected:
    int lane;
    float yPosition;
    sf::CircleShape shape;
    float speed;

public:
    PowerUp(int l, float y, float s);
    virtual ~PowerUp();

    virtual void update(float deltaTime);
    virtual void render(sf::RenderWindow& window);
    virtual void applyEffect(Player& player) = 0;  // Pure virtual - must implement

    // Getters
    float getYPosition() const;
    int getLane() const;
    sf::FloatRect getBounds() const;
};

// ===================== MAGNET POWER-UP =====================
class MagnetPower : public PowerUp {
private:
    sf::ConvexShape diamondOuter;
    sf::ConvexShape diamondInner;
    sf::RectangleShape shine;
    sf::CircleShape shadow;

public:
    MagnetPower(int l, float y, float s);

    void update(float dt) override;
    void render(sf::RenderWindow& win) override;
    void applyEffect(Player& player) override;
};

// ===================== JETPACK POWER-UP =====================
class JetpackPower : public PowerUp {
private:
    sf::ConvexShape diamondOuter;
    sf::ConvexShape diamondInner;
    sf::RectangleShape shine;
    sf::CircleShape shadow;

public:
    JetpackPower(int l, float y, float s);

    void update(float dt) override;
    void render(sf::RenderWindow& win) override;
    void applyEffect(Player& player) override;
};

// ===================== SHIELD POWER-UP =====================
class ShieldPower : public PowerUp {
private:
    sf::ConvexShape diamondOuter;
    sf::ConvexShape diamondInner;
    sf::RectangleShape shine;
    sf::CircleShape shadow;

public:
    ShieldPower(int l, float y, float s);

    void update(float dt) override;
    void render(sf::RenderWindow& win) override;
    void applyEffect(Player& player) override;
};

// ===================== DOUBLE COIN POWER-UP =====================
class DoubleCoinPower : public PowerUp {
private:
    sf::ConvexShape diamondOuter;
    sf::ConvexShape diamondInner;
    sf::RectangleShape shine;
    sf::CircleShape shadow;

public:
    DoubleCoinPower(int l, float y, float s);

    void update(float dt) override;
    void render(sf::RenderWindow& win) override;
    void applyEffect(Player& player) override;
};

#endif#pragma once
