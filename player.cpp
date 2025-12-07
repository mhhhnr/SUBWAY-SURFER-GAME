#include "player.h"
#include <iostream>

using namespace std;

Player::Player() {
    currentLane = 1;
    state = PlayerState::RUNNING;
    yPosition = 0.0f;
    jumpVelocity = 0.0f;
    slideTimer = 0.0f;
    isMoving = false;
    hasShield = false;
    shieldTimer = 0.0f;
    hasJetpack = false;
    jetpackTimer = 0.0f;
    hasMagnet = false;
    magnetTimer = 0.0f;
    hasDoubleCoin = false;
    doubleCoinTimer = 0.0f;

    setupVisuals();

    playerShape.setSize(sf::Vector2f(35.0f, 50.0f));
    playerShape.setFillColor(sf::Color::Blue);
    playerShape.setPosition(sf::Vector2f(LEFT_MARGIN + currentLane * LANE_WIDTH + 60.0f, 450.0f + yPosition));
}

void Player::setupVisuals() {
    head.setRadius(12.f);
    head.setFillColor(sf::Color(255, 220, 180));
    head.setOutlineThickness(2.f);
    head.setOutlineColor(sf::Color::Black);

    capTop.setSize(sf::Vector2f(26.f, 12.f));
    capTop.setFillColor(sf::Color(200, 40, 40));
    capTop.setOutlineThickness(2.f);
    capTop.setOutlineColor(sf::Color::Black);

    capBrim.setSize(sf::Vector2f(22.f, 5.f));
    capBrim.setFillColor(sf::Color(150, 30, 30));
    capBrim.setOutlineThickness(2.f);
    capBrim.setOutlineColor(sf::Color::Black);

    torso.setSize(sf::Vector2f(28.f, 40.f));
    torso.setFillColor(sf::Color(80, 140, 255));
    torso.setOutlineThickness(2.f);
    torso.setOutlineColor(sf::Color::Black);

    leftArm.setSize(sf::Vector2f(10.f, 28.f));
    rightArm.setSize(sf::Vector2f(10.f, 28.f));
    leftArm.setFillColor(sf::Color(80, 140, 255));
    rightArm.setFillColor(sf::Color(80, 140, 255));
    leftArm.setOutlineThickness(2.f);
    rightArm.setOutlineThickness(2.f);
    leftArm.setOutlineColor(sf::Color::Black);
    rightArm.setOutlineColor(sf::Color::Black);

    leftLeg.setSize(sf::Vector2f(12.f, 32.f));
    rightLeg.setSize(sf::Vector2f(12.f, 32.f));
    leftLeg.setFillColor(sf::Color(40, 40, 40));
    rightLeg.setFillColor(sf::Color(40, 40, 40));
    leftLeg.setOutlineThickness(2.f);
    rightLeg.setOutlineThickness(2.f);
    leftLeg.setOutlineColor(sf::Color::Black);
    rightLeg.setOutlineColor(sf::Color::Black);

    leftShoe.setSize(sf::Vector2f(14.f, 6.f));
    rightShoe.setSize(sf::Vector2f(14.f, 6.f));
    leftShoe.setFillColor(sf::Color::White);
    rightShoe.setFillColor(sf::Color::White);
    leftShoe.setOutlineThickness(2.f);
    rightShoe.setOutlineThickness(2.f);
    leftShoe.setOutlineColor(sf::Color::Black);
    rightShoe.setOutlineColor(sf::Color::Black);

    outfitColor = sf::Color(80, 140, 255);
}

void Player::updateModel() {
    sf::Vector2f pos = playerShape.getPosition();
    sf::Vector2f size = playerShape.getSize();

    float x = pos.x;
    float y = pos.y;
    float w = size.x;
    float h = size.y;

    float headR = w * 0.55f;
    head.setRadius(headR);
    head.setPointCount(30);
    head.setFillColor(sf::Color(255, 224, 189));
    head.setPosition(sf::Vector2f(x + w * 0.00f, y - headR * 1.05f));

    hair.setSize(sf::Vector2f(w * 0.9f, headR * 0.35f));
    hair.setFillColor(sf::Color(120, 80, 40));
    hair.setPosition(sf::Vector2f(x + w * 0.15f, y - headR * 0.70f));

    capTop.setSize(sf::Vector2f(w * 1.0f, headR * 0.55f));
    capTop.setFillColor(sf::Color(220, 40, 40));
    capTop.setPosition(sf::Vector2f(x + w * 0.0f, y - headR * 1.1f));

    capBill.setSize(sf::Vector2f(w * 1.2f, headR * 0.25f));
    capBill.setFillColor(sf::Color(245, 245, 245));
    capBill.setPosition(sf::Vector2f(x - w * 0.1f, y - headR * 0.6f));

    torso.setSize(sf::Vector2f(w * 1.0f, h * 0.62f));
    torso.setFillColor(outfitColor);
    torso.setPosition(sf::Vector2f(x + w * 0.0f, y + h * 0.20f));

    sf::Vector2f armSize(w * 0.25f, h * 0.45f);
    leftArm.setSize(armSize);
    rightArm.setSize(armSize);
    leftArm.setFillColor(sf::Color(255, 224, 189));
    rightArm.setFillColor(sf::Color(255, 224, 189));

    sf::Vector2f legSize(w * 0.35f, h * 0.60f);
    leftLeg.setSize(legSize);
    rightLeg.setSize(legSize);
    sf::Color jeans(30, 60, 160);
    leftLeg.setFillColor(jeans);
    rightLeg.setFillColor(jeans);

    sf::Vector2f shoeSize(w * 0.5f, h * 0.12f);
    leftShoe.setSize(shoeSize);
    rightShoe.setSize(shoeSize);
    leftShoe.setFillColor(sf::Color(250, 250, 250));
    rightShoe.setFillColor(sf::Color(250, 250, 250));

    if (state == PlayerState::RUNNING) {
        leftArm.setPosition(sf::Vector2f(x - w * 0.20f, y + h * 0.25f));
        rightArm.setPosition(sf::Vector2f(x + w * 1.0f, y + h * 0.25f));
        leftLeg.setPosition(sf::Vector2f(x + w * 0.15f, y + h * 0.68f));
        rightLeg.setPosition(sf::Vector2f(x + w * 0.55f, y + h * 0.68f));
        leftShoe.setPosition(sf::Vector2f(x + w * 0.12f, y + h * 0.68f + legSize.y));
        rightShoe.setPosition(sf::Vector2f(x + w * 0.50f, y + h * 0.68f + legSize.y));
    }
    else if (state == PlayerState::JUMPING) {
        leftArm.setPosition(sf::Vector2f(x - w * 0.15f, y + h * 0.05f));
        rightArm.setPosition(sf::Vector2f(x + w * 0.95f, y + h * 0.05f));
        leftLeg.setPosition(sf::Vector2f(x + w * 0.18f, y + h * 0.58f));
        rightLeg.setPosition(sf::Vector2f(x + w * 0.50f, y + h * 0.58f));
        leftShoe.setPosition(sf::Vector2f(x + w * 0.15f, y + h * 0.58f + legSize.y * 0.7f));
        rightShoe.setPosition(sf::Vector2f(x + w * 0.48f, y + h * 0.58f + legSize.y * 0.7f));
    }
    else if (state == PlayerState::SLIDING) {
        torso.setSize(sf::Vector2f(w * 1.2f, h * 0.50f));
        torso.setPosition(sf::Vector2f(x - w * 0.1f, y + h * 0.33f));
        head.setPosition(sf::Vector2f(x + w * 0.15f, y - headR * 0.55f));
        capTop.setPosition(sf::Vector2f(x + w * 0.0f, y - headR * 0.7f));
        capBill.setPosition(sf::Vector2f(x - w * 0.1f, y - headR * 0.4f));
        leftArm.setPosition(sf::Vector2f(x - w * 0.10f, y + h * 0.40f));
        rightArm.setPosition(sf::Vector2f(x + w * 1.05f, y + h * 0.40f));
        leftLeg.setPosition(sf::Vector2f(x + w * 0.22f, y + h * 0.75f));
        rightLeg.setPosition(sf::Vector2f(x + w * 0.55f, y + h * 0.75f));
        leftShoe.setPosition(sf::Vector2f(x + w * 0.22f, y + h * 0.75f + legSize.y));
        rightShoe.setPosition(sf::Vector2f(x + w * 0.52f, y + h * 0.75f + legSize.y));
    }
}

void Player::moveLeft() {
    if (currentLane > 0 && !isMoving) {
        currentLane--;
        isMoving = true;
    }
}

void Player::moveRight() {
    if (currentLane < 2 && !isMoving) {
        currentLane++;
        isMoving = true;
    }
}

void Player::jump() {
    if (state == PlayerState::RUNNING && !hasJetpack) {
        state = PlayerState::JUMPING;
        jumpVelocity = JUMP_STRENGTH;
    }
}

void Player::slide() {
    if (state == PlayerState::RUNNING && !hasJetpack) {
        state = PlayerState::SLIDING;
        slideTimer = SLIDE_DURATION;
    }
}

void Player::activateShield(float duration) {
    hasShield = true;
    shieldTimer = duration;
}

void Player::activateJetpack(float duration) {
    hasJetpack = true;
    jetpackTimer = duration;
    yPosition = -100.0f;
}

void Player::activateMagnet(float duration) {
    hasMagnet = true;
    magnetTimer = duration;
}

void Player::activateDoubleCoin(float duration) {
    hasDoubleCoin = true;
    doubleCoinTimer = duration;
}

void Player::update(float deltaTime) {
    if (hasShield) {
        shieldTimer -= deltaTime;
        if (shieldTimer <= 0.0f) {
            hasShield = false;
            shieldTimer = 0.0f;
        }
    }

    if (hasJetpack) {
        jetpackTimer -= deltaTime;
        if (jetpackTimer <= 0.0f) {
            hasJetpack = false;
            jetpackTimer = 0.0f;
            state = PlayerState::RUNNING;
        }
    }

    if (hasMagnet) {
        magnetTimer -= deltaTime;
        if (magnetTimer <= 0.0f) {
            hasMagnet = false;
            magnetTimer = 0.0f;
        }
    }

    if (hasDoubleCoin) {
        doubleCoinTimer -= deltaTime;
        if (doubleCoinTimer <= 0.0f) {
            hasDoubleCoin = false;
            doubleCoinTimer = 0.0f;
        }
    }

    if (hasJetpack) {
        yPosition = -100.0f;
    }
    else if (state == PlayerState::JUMPING) {
        jumpVelocity += GRAVITY * deltaTime;
        yPosition += jumpVelocity * deltaTime;

        if (yPosition >= 0.0f) {
            yPosition = 0.0f;
            jumpVelocity = 0.0f;
            state = PlayerState::RUNNING;
        }
    }

    if (state == PlayerState::SLIDING) {
        slideTimer -= deltaTime;
        if (slideTimer <= 0.0f) {
            state = PlayerState::RUNNING;
            slideTimer = 0.0f;
        }
    }

    float targetX = LEFT_MARGIN + currentLane * LANE_WIDTH + 60.0f;
    float currentX = playerShape.getPosition().x;

    float laneSpeed = 1000.0f * deltaTime;
    if (currentX < targetX - 1.0f) {
        currentX += laneSpeed;
        if (currentX > targetX) currentX = targetX;
    }
    else if (currentX > targetX + 1.0f) {
        currentX -= laneSpeed;
        if (currentX < targetX) currentX = targetX;
    }
    else {
        currentX = targetX;
        isMoving = false;
    }

    if (state == PlayerState::SLIDING) {
        playerShape.setSize(sf::Vector2f(35.0f, 25.0f));
        playerShape.setPosition(sf::Vector2f(currentX, 475.0f + yPosition));
    }
    else {
        playerShape.setSize(sf::Vector2f(35.0f, 50.0f));
        playerShape.setPosition(sf::Vector2f(currentX, 450.0f + yPosition));
    }

    if (hasShield) {
        playerShape.setFillColor(sf::Color::Cyan);
    }
    else if (hasJetpack) {
        playerShape.setFillColor(sf::Color::Yellow);
    }
    else if (hasMagnet) {
        playerShape.setFillColor(sf::Color::Magenta);
    }
    else if (hasDoubleCoin) {
        playerShape.setFillColor(sf::Color::Green);
    }
    else {
        playerShape.setFillColor(sf::Color::Blue);
    }

    updateModel();
}

void Player::render(sf::RenderWindow& window) {
    window.draw(leftLeg);
    window.draw(rightLeg);
    window.draw(leftShoe);
    window.draw(rightShoe);
    window.draw(torso);
    window.draw(leftArm);
    window.draw(rightArm);
    window.draw(head);
    window.draw(capTop);
    window.draw(capBrim);

    if (hasShield) {
        sf::CircleShape bubble(45.f);
        bubble.setFillColor(sf::Color(0, 0, 0, 0));
        bubble.setOutlineThickness(4.f);
        bubble.setOutlineColor(sf::Color::Cyan);
        bubble.setPosition(sf::Vector2f(torso.getPosition().x - 10.f, torso.getPosition().y - 70.f));
        window.draw(bubble);
    }
}

int Player::getLane() const { return currentLane; }
PlayerState Player::getState() const { return state; }
float Player::getYPosition() const { return yPosition; }
sf::FloatRect Player::getBounds() const { return playerShape.getGlobalBounds(); }
bool Player::getHasShield() const { return hasShield; }
bool Player::getHasMagnet() const { return hasMagnet; }
bool Player::getHasDoubleCoin() const { return hasDoubleCoin; }
bool Player::getHasJetpack() const { return hasJetpack; }

void Player::reset() {
    currentLane = 1;
    state = PlayerState::RUNNING;
    yPosition = 0.0f;
    jumpVelocity = 0.0f;
    slideTimer = 0.0f;
    isMoving = false;
    hasShield = false;
    shieldTimer = 0.0f;
    hasJetpack = false;
    jetpackTimer = 0.0f;
    hasMagnet = false;
    magnetTimer = 0.0f;
    hasDoubleCoin = false;
    doubleCoinTimer = 0.0f;
}

void Player::saveState(ofstream& file) {
    file << currentLane << " " << static_cast<int>(state) << " " << yPosition << " "
        << jumpVelocity << " " << slideTimer << " " << isMoving << " "
        << hasShield << " " << shieldTimer << " " << hasJetpack << " " << jetpackTimer << " "
        << hasMagnet << " " << magnetTimer << " " << hasDoubleCoin << " " << doubleCoinTimer << endl;
}

void Player::loadState(ifstream& file) {
    int stateInt;
    file >> currentLane >> stateInt >> yPosition >> jumpVelocity >> slideTimer >> isMoving
        >> hasShield >> shieldTimer >> hasJetpack >> jetpackTimer
        >> hasMagnet >> magnetTimer >> hasDoubleCoin >> doubleCoinTimer;
    state = static_cast<PlayerState>(stateInt);
}