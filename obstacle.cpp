#include "obstacle.h"
#include "player.h"
#include <cstdlib>

Obstacle::Obstacle(int l, float y, float s, bool changeLane)
    : lane(l), yPosition(y), speed(s), canChangeLane(changeLane), laneChangeTimer(0.0f) {
}

Obstacle::~Obstacle() {}

void Obstacle::update(float deltaTime) {
    yPosition += speed * deltaTime;

    if (canChangeLane) {
        laneChangeTimer += deltaTime;
        if (laneChangeTimer >= 2.0f) {
            laneChangeTimer = 0.0f;
            int newLane = rand() % 3;
            if (newLane != lane) {
                lane = newLane;
            }
        }
    }

    shape.setPosition(sf::Vector2f(250.0f + lane * 150.0f + 55.0f, yPosition));
}

void Obstacle::render(sf::RenderWindow& window) {
    window.draw(shape);
}

float Obstacle::getYPosition() const { return yPosition; }
int Obstacle::getLane() const { return lane; }
sf::FloatRect Obstacle::getBounds() const { return shape.getGlobalBounds(); }

Train::Train(int l, float y, float s, bool moving)
    : Obstacle(l, y, s, moving)
{
    float x = 250.f + lane * 150.f + 52.f;

    body.setSize(sf::Vector2f(60.f, 120.f));
    body.setFillColor(sf::Color(220, 40, 40));
    body.setOutlineThickness(4.f);
    body.setOutlineColor(sf::Color::Black);
    body.setPosition(sf::Vector2f(x, yPosition));

    frontPanel.setSize(sf::Vector2f(60.f, 25.f));
    frontPanel.setFillColor(sf::Color(255, 220, 220));
    frontPanel.setOutlineThickness(3.f);
    frontPanel.setOutlineColor(sf::Color::Black);
    frontPanel.setPosition(sf::Vector2f(x, yPosition));

    stripe.setSize(sf::Vector2f(60.f, 10.f));
    stripe.setFillColor(sf::Color(255, 200, 60));
    stripe.setPosition(sf::Vector2f(x, yPosition + 30.f));

    windowL.setSize(sf::Vector2f(22.f, 22.f));
    windowL.setFillColor(sf::Color(120, 180, 255));
    windowL.setOutlineThickness(3.f);
    windowL.setOutlineColor(sf::Color::Black);
    windowL.setPosition(sf::Vector2f(x + 6.f, yPosition + 55.f));

    windowR.setSize(sf::Vector2f(22.f, 22.f));
    windowR.setFillColor(sf::Color(120, 180, 255));
    windowR.setOutlineThickness(3.f);
    windowR.setOutlineColor(sf::Color::Black);
    windowR.setPosition(sf::Vector2f(x + 32.f, yPosition + 55.f));

    headlightL.setRadius(8.f);
    headlightL.setFillColor(sf::Color(255, 255, 150));
    headlightL.setOutlineThickness(3.f);
    headlightL.setOutlineColor(sf::Color::Black);
    headlightL.setPosition(sf::Vector2f(x + 10.f, yPosition + 90.f));

    headlightR.setRadius(8.f);
    headlightR.setFillColor(sf::Color(255, 255, 150));
    headlightR.setOutlineThickness(3.f);
    headlightR.setOutlineColor(sf::Color::Black);
    headlightR.setPosition(sf::Vector2f(x + 38.f, yPosition + 90.f));
}

void Train::update(float dt) {
    yPosition += speed * dt;
    float x = 250.f + lane * 150.f + 52.f;

    body.setPosition(sf::Vector2f(x, yPosition));
    frontPanel.setPosition(sf::Vector2f(x, yPosition));
    stripe.setPosition(sf::Vector2f(x, yPosition + 30.f));
    windowL.setPosition(sf::Vector2f(x + 6.f, yPosition + 55.f));
    windowR.setPosition(sf::Vector2f(x + 32.f, yPosition + 55.f));
    headlightL.setPosition(sf::Vector2f(x + 10.f, yPosition + 90.f));
    headlightR.setPosition(sf::Vector2f(x + 38.f, yPosition + 90.f));
}

void Train::render(sf::RenderWindow& win) {
    win.draw(body);
    win.draw(frontPanel);
    win.draw(stripe);
    win.draw(windowL);
    win.draw(windowR);
    win.draw(headlightL);
    win.draw(headlightR);
}

bool Train::checkCollision(Player& player) {
    if (player.getLane() != lane) return false;
    if (player.getHasJetpack()) return false;

    sf::FloatRect p = player.getBounds();
    if (p.findIntersection(body.getGlobalBounds()).has_value()) {
        if (player.getState() == PlayerState::JUMPING)
            return p.position.y + p.size.y > body.getPosition().y + 20.f;
        return true;
    }
    return false;
}
Barrier::Barrier(int l, float y, float s) : Obstacle(l, y, s, false) {
    float x = 250.f + lane * 150.f + 52.f;

    body.setSize(sf::Vector2f(55.f, 55.f));
    body.setFillColor(sf::Color(255, 140, 0));
    body.setOutlineThickness(3.f);
    body.setOutlineColor(sf::Color::Black);
    body.setPosition(sf::Vector2f(x, yPosition));

    stripe1.setSize(sf::Vector2f(55.f, 8.f));
    stripe1.setFillColor(sf::Color::White);
    stripe1.setPosition(sf::Vector2f(x, yPosition + 12.f));

    stripe2.setSize(sf::Vector2f(55.f, 8.f));
    stripe2.setFillColor(sf::Color::White);
    stripe2.setPosition(sf::Vector2f(x, yPosition + 30.f));

    legLeft.setSize(sf::Vector2f(10.f, 18.f));
    legLeft.setFillColor(sf::Color(80, 80, 80));
    legLeft.setOutlineThickness(2.f);
    legLeft.setOutlineColor(sf::Color::Black);
    legLeft.setPosition(sf::Vector2f(x + 5.f, yPosition + 52.f));

    legRight.setSize(sf::Vector2f(10.f, 18.f));
    legRight.setFillColor(sf::Color(80, 80, 80));
    legRight.setOutlineThickness(2.f);
    legRight.setOutlineColor(sf::Color::Black);
    legRight.setPosition(sf::Vector2f(x + 40.f, yPosition + 52.f));
}

void Barrier::update(float dt) {
    yPosition += speed * dt;
    float x = 250.f + lane * 150.f + 52.f;

    body.setPosition(sf::Vector2f(x, yPosition));
    stripe1.setPosition(sf::Vector2f(x, yPosition + 12.f));
    stripe2.setPosition(sf::Vector2f(x, yPosition + 30.f));
    legLeft.setPosition(sf::Vector2f(x + 5.f, yPosition + 52.f));
    legRight.setPosition(sf::Vector2f(x + 40.f, yPosition + 52.f));
}

void Barrier::render(sf::RenderWindow& win) {
    win.draw(body);
    win.draw(stripe1);
    win.draw(stripe2);
    win.draw(legLeft);
    win.draw(legRight);
}

bool Barrier::checkCollision(Player& player) {
    if (player.getLane() != lane) return false;
    if (player.getHasJetpack()) return false;

    sf::FloatRect p = player.getBounds();
    sf::FloatRect b = body.getGlobalBounds();

    if (p.findIntersection(b).has_value()) {
        if (player.getState() == PlayerState::JUMPING)
            return false;
        return true;
    }
    return false;
}

Cone::Cone(int l, float y, float s) : Obstacle(l, y, s, false) {
    float x = 250.f + lane * 150.f + 30.f;

    cone.setPointCount(4);
    cone.setPoint(0, sf::Vector2f(10.f, 0.f));
    cone.setPoint(1, sf::Vector2f(30.f, 0.f));
    cone.setPoint(2, sf::Vector2f(35.f, 40.f));
    cone.setPoint(3, sf::Vector2f(5.f, 40.f));
    cone.setFillColor(sf::Color(255, 120, 0));
    cone.setOutlineThickness(3.f);
    cone.setOutlineColor(sf::Color::Black);
    cone.setPosition(sf::Vector2f(x, yPosition));

    stripe.setSize(sf::Vector2f(28.f, 6.f));
    stripe.setFillColor(sf::Color::White);
    stripe.setPosition(sf::Vector2f(x + 6.f, yPosition + 14.f));

    base.setSize(sf::Vector2f(40.f, 10.f));
    base.setFillColor(sf::Color(80, 80, 80));
    base.setOutlineThickness(2.f);
    base.setOutlineColor(sf::Color::Black);
    base.setPosition(sf::Vector2f(x + 3.f, yPosition + 40.f));
}

void Cone::update(float dt) {
    yPosition += speed * dt;
    float x = 250.f + lane * 150.f + 30.f;

    cone.setPosition(sf::Vector2f(x, yPosition));
    stripe.setPosition(sf::Vector2f(x + 6.f, yPosition + 14.f));
    base.setPosition(sf::Vector2f(x + 2.f, yPosition + 40.f));
}

void Cone::render(sf::RenderWindow& win) {
    win.draw(cone);
    win.draw(stripe);
    win.draw(base);
}

bool Cone::checkCollision(Player& player) {
    if (player.getLane() != lane) return false;
    if (player.getHasJetpack()) return false;

    sf::FloatRect p = player.getBounds();
    sf::FloatRect c = cone.getGlobalBounds();

    if (p.findIntersection(c).has_value()) {
        if (player.getState() == PlayerState::SLIDING)
            return false;
        return true;
    }
    return false;
}

Fence::Fence(int l, float y, float s) : Obstacle(l, y, s, false) {
    float x = 250.f + lane * 150.f + 50.f;

    plank1.setSize(sf::Vector2f(15.f, 70.f));
    plank1.setFillColor(sf::Color(160, 90, 40));
    plank1.setOutlineThickness(3.f);
    plank1.setOutlineColor(sf::Color::Black);
    plank1.setPosition(sf::Vector2f(x, yPosition));

    plank2.setSize(sf::Vector2f(15.f, 70.f));
    plank2.setFillColor(sf::Color(160, 90, 40));
    plank2.setOutlineThickness(3.f);
    plank2.setOutlineColor(sf::Color::Black);
    plank2.setPosition(sf::Vector2f(x + 18.f, yPosition));

    plank3.setSize(sf::Vector2f(15.f, 70.f));
    plank3.setFillColor(sf::Color(160, 90, 40));
    plank3.setOutlineThickness(3.f);
    plank3.setOutlineColor(sf::Color::Black);
    plank3.setPosition(sf::Vector2f(x + 36.f, yPosition));

    beamTop.setSize(sf::Vector2f(56.f, 10.f));
    beamTop.setFillColor(sf::Color(120, 60, 20));
    beamTop.setOutlineThickness(3.f);
    beamTop.setOutlineColor(sf::Color::Black);
    beamTop.setPosition(sf::Vector2f(x - 3.f, yPosition + 8.f));

    beamBottom.setSize(sf::Vector2f(56.f, 10.f));
    beamBottom.setFillColor(sf::Color(120, 60, 20));
    beamBottom.setOutlineThickness(3.f);
    beamBottom.setOutlineColor(sf::Color::Black);
    beamBottom.setPosition(sf::Vector2f(x - 3.f, yPosition + 45.f));
}

void Fence::update(float dt) {
    yPosition += speed * dt;
    float x = 250.f + lane * 150.f + 50.f;

    plank1.setPosition(sf::Vector2f(x, yPosition));
    plank2.setPosition(sf::Vector2f(x + 18.f, yPosition));
    plank3.setPosition(sf::Vector2f(x + 36.f, yPosition));
    beamTop.setPosition(sf::Vector2f(x - 3.f, yPosition + 8.f));
    beamBottom.setPosition(sf::Vector2f(x - 3.f, yPosition + 45.f));
}

void Fence::render(sf::RenderWindow& win) {
    win.draw(plank1);
    win.draw(plank2);
    win.draw(plank3);
    win.draw(beamTop);
    win.draw(beamBottom);
}

bool Fence::checkCollision(Player& player) {
    if (player.getLane() != lane) return false;
    if (player.getHasJetpack()) return false;

    sf::FloatRect p = player.getBounds();

    if (p.findIntersection(plank1.getGlobalBounds()).has_value()) return true;
    if (p.findIntersection(plank2.getGlobalBounds()).has_value()) return true;
    if (p.findIntersection(plank3.getGlobalBounds()).has_value()) return true;

    return false;
}