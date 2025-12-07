#include "trackmanager.h"
#include <cstdlib>
#include <ctime>

TrackManager::TrackManager()
    : spawnTimer(0.0f), coinSpawnTimer(0.0f), powerupSpawnTimer(0.0f),
    baseSpeed(200.0f), currentSpeed(200.0f) {
    srand(static_cast<unsigned int>(time(0)));
}

TrackManager::~TrackManager() {
    clearAll();
}

void TrackManager::clearAll() {
    for (int i = 0; i < obstacles.getSize(); i++) {
        delete obstacles.get(i);
    }
    obstacles.clear();

    for (int i = 0; i < coins.getSize(); i++) {
        delete coins.get(i);
    }
    coins.clear();

    for (int i = 0; i < powerups.getSize(); i++) {
        delete powerups.get(i);
    }
    powerups.clear();
}

void TrackManager::update(float deltaTime, Player& player, ScoreManager& scoreManager) {
    currentSpeed = baseSpeed + (scoreManager.getCurrentScore() / 100.0f) * 20.0f;
    if (currentSpeed > 500.0f) currentSpeed = 500.0f;

    for (int i = obstacles.getSize() - 1; i >= 0; i--) {
        obstacles.get(i)->update(deltaTime);
        if (obstacles.get(i)->getYPosition() > 600.0f) {
            delete obstacles.get(i);
            obstacles.removeAt(i);
        }
    }

    for (int i = coins.getSize() - 1; i >= 0; i--) {
        coins.get(i)->update(deltaTime);

        if (player.getHasMagnet() && coins.get(i)->getLane() == player.getLane()) {
            int coinValue = player.getHasDoubleCoin() ? 100 : 50;
            scoreManager.addScore(coinValue);
            delete coins.get(i);
            coins.removeAt(i);
            continue;
        }

        if (player.getBounds().findIntersection(coins.get(i)->getBounds()).has_value()) {
            int coinValue = player.getHasDoubleCoin() ? 100 : 50;
            scoreManager.addScore(coinValue);
            delete coins.get(i);
            coins.removeAt(i);
        }
        else if (coins.get(i)->getYPosition() > 600.0f) {
            delete coins.get(i);
            coins.removeAt(i);
        }
    }

    for (int i = powerups.getSize() - 1; i >= 0; i--) {
        powerups.get(i)->update(deltaTime);
        if (player.getBounds().findIntersection(powerups.get(i)->getBounds()).has_value()) {
            powerups.get(i)->applyEffect(player);
            delete powerups.get(i);
            powerups.removeAt(i);
        }
        else if (powerups.get(i)->getYPosition() > 600.0f) {
            delete powerups.get(i);
            powerups.removeAt(i);
        }
    }

    spawnTimer += deltaTime;
    float spawnRate = 2.0f - (currentSpeed - baseSpeed) / 300.0f;
    if (spawnRate < 0.8f) spawnRate = 0.8f;

    if (spawnTimer >= spawnRate) {
        spawnTimer = 0.0f;
        spawnObstacle();
    }

    coinSpawnTimer += deltaTime;
    if (coinSpawnTimer >= 0.5f) {
        coinSpawnTimer = 0.0f;
        if (rand() % 100 < 30) {
            spawnCoin();
        }
    }
    powerupSpawnTimer += deltaTime;
    if (powerupSpawnTimer >= 8.0f) {
        powerupSpawnTimer = 0.0f;
        if (rand() % 100 < 40) {
            spawnPowerUp();
        }
    }
}

void TrackManager::spawnObstacle() {
    int lane = rand() % 3;
    int type = rand() % 4;

    Obstacle* obs = nullptr;
    switch (type) {
    case 0:
        obs = new Train(lane, -80.0f, currentSpeed, (rand() % 100 < 30));
        break;
    case 1:
        obs = new Barrier(lane, -60.0f, currentSpeed);
        break;
    case 2:
        obs = new Cone(lane, -40.0f, currentSpeed);
        break;
    case 3:
        obs = new Fence(lane, -70.0f, currentSpeed);
        break;
    }

    if (obs != nullptr) {
        obstacles.add(obs);
    }
}

void TrackManager::spawnCoin() {
    int lane = rand() % 3;
    Coin* coin = new Coin(lane, -20.0f, currentSpeed);
    coins.add(coin);
}

void TrackManager::spawnPowerUp() {
    int lane = rand() % 3;
    int type = rand() % 4;

    PowerUp* power = nullptr;
    switch (type) {
    case 0:
        power = new MagnetPower(lane, -20.0f, currentSpeed);
        break;
    case 1:
        power = new JetpackPower(lane, -20.0f, currentSpeed);
        break;
    case 2:
        power = new ShieldPower(lane, -20.0f, currentSpeed);
        break;
    case 3:
        power = new DoubleCoinPower(lane, -20.0f, currentSpeed);
        break;
    }

    if (power != nullptr) {
        powerups.add(power);
    }
}

void TrackManager::render(sf::RenderWindow& window) {
    for (int i = 0; i < obstacles.getSize(); i++) {
        obstacles.get(i)->render(window);
    }
    for (int i = 0; i < coins.getSize(); i++) {
        coins.get(i)->render(window);
    }
    for (int i = 0; i < powerups.getSize(); i++) {
        powerups.get(i)->render(window);
    }
}

bool TrackManager::checkCollisions(Player& player) {
    for (int i = 0; i < obstacles.getSize(); i++) {
        if (obstacles.get(i)->checkCollision(player)) {
            if (player.getHasShield()) {
                delete obstacles.get(i);
                obstacles.removeAt(i);
                return false;
            }
            return true;
        }
    }
    return false;
}

void TrackManager::reset() {
    clearAll();
    spawnTimer = 0.0f;
    coinSpawnTimer = 0.0f;
    powerupSpawnTimer = 0.0f;
    currentSpeed = baseSpeed;
}

void TrackManager::saveState(std::ofstream& file) {
    file << spawnTimer << " " << coinSpawnTimer << " " << powerupSpawnTimer << " "
        << currentSpeed << std::endl;
}

void TrackManager::loadState(std::ifstream& file) {
    file >> spawnTimer >> coinSpawnTimer >> powerupSpawnTimer >> currentSpeed;
}