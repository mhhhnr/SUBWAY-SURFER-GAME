#include "powerup.h"
#include "player.h"

PowerUp::PowerUp(int l, float y, float s) : lane(l), yPosition(y), speed(s) {
    shape.setRadius(15.0f);
}

PowerUp::~PowerUp() {}

void PowerUp::update(float deltaTime) {
    yPosition += speed * deltaTime;
    shape.setPosition(sf::Vector2f(250.0f + lane * 150.0f + 65.0f, yPosition));
}

void PowerUp::render(sf::RenderWindow& window) {
    window.draw(shape);
}

float PowerUp::getYPosition() const { return yPosition; }
int PowerUp::getLane() const { return lane; }
sf::FloatRect PowerUp::getBounds() const { return shape.getGlobalBounds(); }

// ===================== MAGNET POWER =====================
MagnetPower::MagnetPower(int l, float y, float s) : PowerUp(l, y, s) {
    float x = 250.f + lane * 150.f + 65.f;

    shape.setRadius(16.f);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(0.f);
    shape.setPosition(sf::Vector2f(x, yPosition));

    diamondOuter.setPointCount(4);
    diamondOuter.setPoint(0, sf::Vector2f(15.f, 0.f));
    diamondOuter.setPoint(1, sf::Vector2f(30.f, 15.f));
    diamondOuter.setPoint(2, sf::Vector2f(15.f, 30.f));
    diamondOuter.setPoint(3, sf::Vector2f(0.f, 15.f));
    diamondOuter.setFillColor(sf::Color(200, 60, 200));
    diamondOuter.setOutlineThickness(3.f);
    diamondOuter.setOutlineColor(sf::Color(120, 20, 120));
    diamondOuter.setPosition(sf::Vector2f(x, yPosition));

    diamondInner.setPointCount(4);
    diamondInner.setPoint(0, sf::Vector2f(15.f, 4.f));
    diamondInner.setPoint(1, sf::Vector2f(26.f, 15.f));
    diamondInner.setPoint(2, sf::Vector2f(15.f, 26.f));
    diamondInner.setPoint(3, sf::Vector2f(4.f, 15.f));
    diamondInner.setFillColor(sf::Color(255, 120, 255));
    diamondInner.setOutlineThickness(1.f);
    diamondInner.setOutlineColor(sf::Color(255, 180, 255));
    diamondInner.setPosition(sf::Vector2f(x, yPosition));

    shine.setSize(sf::Vector2f(14.f, 4.f));
    shine.setFillColor(sf::Color(255, 255, 255, 160));
    shine.setRotation(sf::degrees(-25.f));
    shine.setPosition(sf::Vector2f(x + 10.f, yPosition + 6.f));

    shadow.setRadius(18.f);
    shadow.setFillColor(sf::Color(0, 0, 0, 55));
    shadow.setPointCount(40);
    shadow.setPosition(sf::Vector2f(x - 3.f, yPosition + 4.f));
}

void MagnetPower::update(float dt) {
    yPosition += speed * dt;
    float x = 250.f + lane * 150.f + 65.f;

    shadow.setPosition(sf::Vector2f(x - 3.f, yPosition + 4.f));
    diamondOuter.setPosition(sf::Vector2f(x, yPosition));
    diamondInner.setPosition(sf::Vector2f(x, yPosition));
    shine.setPosition(sf::Vector2f(x + 10.f, yPosition + 6.f));
    shape.setPosition(sf::Vector2f(x, yPosition));
}

void MagnetPower::render(sf::RenderWindow& win) {
    win.draw(shadow);
    win.draw(diamondOuter);
    win.draw(diamondInner);
    win.draw(shine);
}

void MagnetPower::applyEffect(Player& player) {
    player.activateMagnet(5.0f);
}

JetpackPower::JetpackPower(int l, float y, float s) : PowerUp(l, y, s) {
    float x = 250.f + lane * 150.f + 65.f;

    shape.setRadius(16.f);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(0.f);
    shape.setPosition(sf::Vector2f(x, yPosition));

    diamondOuter.setPointCount(4);
    diamondOuter.setPoint(0, sf::Vector2f(15.f, 0.f));
    diamondOuter.setPoint(1, sf::Vector2f(30.f, 15.f));
    diamondOuter.setPoint(2, sf::Vector2f(15.f, 30.f));
    diamondOuter.setPoint(3, sf::Vector2f(0.f, 15.f));
    diamondOuter.setFillColor(sf::Color(255, 200, 0));
    diamondOuter.setOutlineThickness(3.f);
    diamondOuter.setOutlineColor(sf::Color(180, 120, 0));
    diamondOuter.setPosition(sf::Vector2f(x, yPosition));

    diamondInner.setPointCount(4);
    diamondInner.setPoint(0, sf::Vector2f(15.f, 4.f));
    diamondInner.setPoint(1, sf::Vector2f(26.f, 15.f));
    diamondInner.setPoint(2, sf::Vector2f(15.f, 26.f));
    diamondInner.setPoint(3, sf::Vector2f(4.f, 15.f));
    diamondInner.setFillColor(sf::Color(255, 230, 70));
    diamondInner.setOutlineThickness(1.f);
    diamondInner.setOutlineColor(sf::Color(250, 200, 40));
    diamondInner.setPosition(sf::Vector2f(x, yPosition));

    shine.setSize(sf::Vector2f(14.f, 4.f));
    shine.setFillColor(sf::Color(255, 255, 255, 150));
    shine.setRotation(sf::degrees(-25.f));
    shine.setPosition(sf::Vector2f(x + 10.f, yPosition + 6.f));

    shadow.setRadius(18.f);
    shadow.setFillColor(sf::Color(0, 0, 0, 60));
    shadow.setPointCount(40);
    shadow.setPosition(sf::Vector2f(x - 3.f, yPosition + 4.f));
}

void JetpackPower::update(float dt) {
    yPosition += speed * dt;
    float x = 250.f + lane * 150.f + 65.f;

    shadow.setPosition(sf::Vector2f(x - 3.f, yPosition + 4.f));
    diamondOuter.setPosition(sf::Vector2f(x, yPosition));
    diamondInner.setPosition(sf::Vector2f(x, yPosition));
    shine.setPosition(sf::Vector2f(x + 10.f, yPosition + 6.f));
    shape.setPosition(sf::Vector2f(x, yPosition));
}

void JetpackPower::render(sf::RenderWindow& win) {
    win.draw(shadow);
    win.draw(diamondOuter);
    win.draw(diamondInner);
    win.draw(shine);
}

void JetpackPower::applyEffect(Player& player) {
    player.activateJetpack(4.0f);
}

ShieldPower::ShieldPower(int l, float y, float s) : PowerUp(l, y, s) {
    float x = 250.f + lane * 150.f + 65.f;

    shape.setRadius(16.f);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(0.f);
    shape.setPosition(sf::Vector2f(x, yPosition));

    diamondOuter.setPointCount(4);
    diamondOuter.setPoint(0, sf::Vector2f(15.f, 0.f));
    diamondOuter.setPoint(1, sf::Vector2f(30.f, 15.f));
    diamondOuter.setPoint(2, sf::Vector2f(15.f, 30.f));
    diamondOuter.setPoint(3, sf::Vector2f(0.f, 15.f));
    diamondOuter.setFillColor(sf::Color(0, 220, 255));
    diamondOuter.setOutlineThickness(3.f);
    diamondOuter.setOutlineColor(sf::Color(0, 150, 180));
    diamondOuter.setPosition(sf::Vector2f(x, yPosition));

    diamondInner.setPointCount(4);
    diamondInner.setPoint(0, sf::Vector2f(15.f, 4.f));
    diamondInner.setPoint(1, sf::Vector2f(26.f, 15.f));
    diamondInner.setPoint(2, sf::Vector2f(15.f, 26.f));
    diamondInner.setPoint(3, sf::Vector2f(4.f, 15.f));
    diamondInner.setFillColor(sf::Color(180, 255, 255));
    diamondInner.setOutlineThickness(1.f);
    diamondInner.setOutlineColor(sf::Color(120, 220, 240));
    diamondInner.setPosition(sf::Vector2f(x, yPosition));

    shine.setSize(sf::Vector2f(14.f, 4.f));
    shine.setFillColor(sf::Color(255, 255, 255, 160));
    shine.setRotation(sf::degrees(-25.f));
    shine.setPosition(sf::Vector2f(x + 10.f, yPosition + 6.f));

    shadow.setRadius(18.f);
    shadow.setFillColor(sf::Color(0, 0, 0, 55));
    shadow.setPointCount(40);
    shadow.setPosition(sf::Vector2f(x - 3.f, yPosition + 4.f));
}

void ShieldPower::update(float dt) {
    yPosition += speed * dt;
    float x = 250.f + lane * 150.f + 65.f;

    shadow.setPosition(sf::Vector2f(x - 3.f, yPosition + 4.f));
    diamondOuter.setPosition(sf::Vector2f(x, yPosition));
    diamondInner.setPosition(sf::Vector2f(x, yPosition));
    shine.setPosition(sf::Vector2f(x + 10.f, yPosition + 6.f));
    shape.setPosition(sf::Vector2f(x, yPosition));
}

void ShieldPower::render(sf::RenderWindow& win) {
    win.draw(shadow);
    win.draw(diamondOuter);
    win.draw(diamondInner);
    win.draw(shine);
}

void ShieldPower::applyEffect(Player& player) {
    player.activateShield(6.0f);
}

DoubleCoinPower::DoubleCoinPower(int l, float y, float s) : PowerUp(l, y, s) {
    float x = 250.f + lane * 150.f + 65.f;

    shape.setRadius(16.f);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(0.f);
    shape.setPosition(sf::Vector2f(x, yPosition));

    diamondOuter.setPointCount(4);
    diamondOuter.setPoint(0, sf::Vector2f(15.f, 0.f));
    diamondOuter.setPoint(1, sf::Vector2f(30.f, 15.f));
    diamondOuter.setPoint(2, sf::Vector2f(15.f, 30.f));
    diamondOuter.setPoint(3, sf::Vector2f(0.f, 15.f));
    diamondOuter.setFillColor(sf::Color(80, 220, 70));
    diamondOuter.setOutlineThickness(3.f);
    diamondOuter.setOutlineColor(sf::Color(40, 140, 40));
    diamondOuter.setPosition(sf::Vector2f(x, yPosition));

    diamondInner.setPointCount(4);
    diamondInner.setPoint(0, sf::Vector2f(15.f, 4.f));
    diamondInner.setPoint(1, sf::Vector2f(26.f, 15.f));
    diamondInner.setPoint(2, sf::Vector2f(15.f, 26.f));
    diamondInner.setPoint(3, sf::Vector2f(4.f, 15.f));
    diamondInner.setFillColor(sf::Color(160, 255, 140));
    diamondInner.setOutlineThickness(1.f);
    diamondInner.setOutlineColor(sf::Color(210, 255, 200));
    diamondInner.setPosition(sf::Vector2f(x, yPosition));

    shine.setSize(sf::Vector2f(14.f, 4.f));
    shine.setFillColor(sf::Color(255, 255, 255, 160));
    shine.setRotation(sf::degrees(-25.f));
    shine.setPosition(sf::Vector2f(x + 10.f, yPosition + 6.f));

    shadow.setRadius(18.f);
    shadow.setFillColor(sf::Color(0, 0, 0, 55));
    shadow.setPointCount(40);
    shadow.setPosition(sf::Vector2f(x - 3.f, yPosition + 4.f));
}

void DoubleCoinPower::update(float dt) {
    yPosition += speed * dt;
    float x = 250.f + lane * 150.f + 65.f;

    shadow.setPosition(sf::Vector2f(x - 3.f, yPosition + 4.f));
    diamondOuter.setPosition(sf::Vector2f(x, yPosition));
    diamondInner.setPosition(sf::Vector2f(x, yPosition));
    shine.setPosition(sf::Vector2f(x + 10.f, yPosition + 6.f));
    shape.setPosition(sf::Vector2f(x, yPosition));
}

void DoubleCoinPower::render(sf::RenderWindow& win) {
    win.draw(shadow);
    win.draw(diamondOuter);
    win.draw(diamondInner);
    win.draw(shine);
}

void DoubleCoinPower::applyEffect(Player& player) {
    player.activateDoubleCoin(8.0f);
}