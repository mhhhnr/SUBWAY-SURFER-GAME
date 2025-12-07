#include "coin.h"
#include <cstdlib>   // For rand()
Coin::Coin(int l, float y, float s)
    : lane(l), yPosition(y), speed(s)
{
    float x = 250.f + lane * 150.f + 70.f;

    outerRing.setRadius(18.f);
    outerRing.setPointCount(40);
    outerRing.setFillColor(sf::Color(255, 200, 0));
    outerRing.setOutlineThickness(3.f);
    outerRing.setOutlineColor(sf::Color(180, 120, 0));
    outerRing.setPosition(sf::Vector2f(x, yPosition));

    innerDisk.setRadius(12.f);
    innerDisk.setPointCount(40);
    innerDisk.setFillColor(sf::Color(255, 230, 70));
    innerDisk.setOutlineThickness(1.f);
    innerDisk.setOutlineColor(sf::Color(250, 200, 40));
    innerDisk.setPosition(sf::Vector2f(x + 6.f, yPosition + 6.f));

    shine.setSize(sf::Vector2f(10.f, 4.f));
    shine.setFillColor(sf::Color(255, 255, 255, 150));
    shine.setPosition(sf::Vector2f(x + 12.f, yPosition + 8.f));
    shine.setRotation(sf::degrees(-25.f));

    shadow.setRadius(20.f);
    shadow.setFillColor(sf::Color(0, 0, 0, 50));
    shadow.setPointCount(40);
    shadow.setPosition(sf::Vector2f(x, yPosition + 3.f));
}

void Coin::update(float deltaTime) {
    yPosition += speed * deltaTime;
    float x = 250.f + lane * 150.f + 70.f;

    shadow.setPosition(sf::Vector2f(x, yPosition + 3.f));
    outerRing.setPosition(sf::Vector2f(x, yPosition));
    innerDisk.setPosition(sf::Vector2f(x + 6.f, yPosition + 6.f));
    shine.setPosition(sf::Vector2f(x + 12.f, yPosition + 8.f));
}

void Coin::render(sf::RenderWindow& window) {
    window.draw(shadow);
    window.draw(outerRing);
    window.draw(innerDisk);
    window.draw(shine);
}

float Coin::getYPosition() const { return yPosition; }
int Coin::getLane() const { return lane; }
sf::FloatRect Coin::getBounds() const { return outerRing.getGlobalBounds(); }