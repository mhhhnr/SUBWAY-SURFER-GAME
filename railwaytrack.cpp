#include "railwaytrack.h"
#include <cstdlib>

RailwayTrack::RailwayTrack(float x, float w, float h)
    : laneX(x), width(w), height(h)
{
    gravelBase.setSize(sf::Vector2f(width, height));
    gravelBase.setFillColor(sf::Color(120, 120, 120));
    gravelBase.setPosition(sf::Vector2f(laneX, 0.f));  // Add .f

    leftRail.setSize(sf::Vector2f(6.f, height));  // Add .f
    rightRail.setSize(sf::Vector2f(6.f, height)); // Add .f

    leftRail.setFillColor(sf::Color(200, 200, 220));
    rightRail.setFillColor(sf::Color(200, 200, 220));

    leftRail.setPosition(sf::Vector2f(laneX + 20.f, 0.f));  // Add .f
    rightRail.setPosition(sf::Vector2f(laneX + width - 26.f, 0.f));  // Add .f

    // Create sleepers
    for (int i = 0; i < 20; i++) {
        sf::RectangleShape s;
        s.setSize(sf::Vector2f(width - 40.f, 7.f));  // Add .f
        s.setFillColor(sf::Color(160, 110, 60));
        s.setOutlineThickness(2.f);  // Add .f
        s.setOutlineColor(sf::Color(70, 40, 20));

        float y = i * (height / 20.f) + 10.f;  // Add .f
        s.setPosition(sf::Vector2f(laneX + 20.f, y));  // Add .f

        sleepers.add(s);
    }

    // Create gravel stones
    for (int i = 0; i < 30; i++) {
        sf::RectangleShape g;
        g.setSize(sf::Vector2f(5.f, 5.f));  // Add .f
        g.setFillColor(sf::Color(110, 100, 90));

        float gx = laneX + 10.f + (rand() % (int)(width - 20));  // Add .f
        float gy = (float)(rand() % (int)height);  // Cast to float

        g.setPosition(sf::Vector2f(gx, gy));

        gravel.add(g);
    }
}

void RailwayTrack::render(sf::RenderWindow& window)
{
    window.draw(gravelBase);

    for (int i = 0; i < sleepers.getSize(); i++)
        window.draw(sleepers.get(i));

    window.draw(leftRail);
    window.draw(rightRail);

    for (int i = 0; i < gravel.getSize(); i++)
        window.draw(gravel.get(i));
}