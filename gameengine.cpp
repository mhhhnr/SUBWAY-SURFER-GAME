#include "gameengine.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;
using namespace std;

GameEngine::GameEngine()
    : window(sf::VideoMode(sf::Vector2u(800, 600)), "Subway Surfers - Enhanced"),
    gameState(GameState::MAIN_MENU), survivalTimer(0.0f), isDayMode(true), selectedMenuItem(0) {

    window.setFramerateLimit(60);

    if (!font.openFromFile("arial.ttf")) {
        cout << "Warning: Could not load font." << endl;
    }

    menuLabels[0] = "Start Game";
    menuLabels[1] = "Continue Game";
    menuLabels[2] = "High Scores";
    menuLabels[3] = "Exit";

    for (int i = 0; i < 4; i++) {
        menuItems[i].setSize(sf::Vector2f(400.0f, 60.0f));
        menuItems[i].setPosition(sf::Vector2f(200.0f, 220.0f + i * 80.0f));
        menuItems[i].setFillColor(sf::Color(50, 50, 100));
    }

    if (!backgroundMusic.openFromFile("music.wav")) {
        cout << "Warning: Could not load music.wav" << endl;
    }
    else {
        backgroundMusic.setLooping(true);
        backgroundMusic.setVolume(50);
        backgroundMusic.play();
    }

    trackLeft = new RailwayTrack(250.f, 140.f, 600.f);
    trackMid = new RailwayTrack(400.f, 140.f, 600.f);
    trackRight = new RailwayTrack(550.f, 140.f, 600.f);

    sf::Color grassGreen(90, 180, 90);
    sideArea[0].setSize(sf::Vector2f(250.0f, 600.0f));
    sideArea[0].setPosition(sf::Vector2f(0.0f, 0.0f));
    sideArea[0].setFillColor(grassGreen);

    sideArea[1].setSize(sf::Vector2f(250.0f, 600.0f));
    sideArea[1].setPosition(sf::Vector2f(700.0f, 0.0f));
    sideArea[1].setFillColor(grassGreen);
}

GameEngine::~GameEngine() {
    delete trackLeft;
    delete trackMid;
    delete trackRight;
}

void GameEngine::processInput() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (gameState == GameState::MAIN_MENU) {
                handleMenuInput(keyPressed->code);
            }
            else if (gameState == GameState::HIGH_SCORES) {
                if (keyPressed->code == sf::Keyboard::Key::Escape ||
                    keyPressed->code == sf::Keyboard::Key::Enter) {
                    gameState = GameState::MAIN_MENU;
                }
            }
            else if (gameState == GameState::PAUSED) {
                handlePauseInput(keyPressed->code);
            }
            else if (gameState == GameState::GAME_OVER) {
                handleGameOverInput(keyPressed->code);
            }
            else if (gameState == GameState::PLAYING) {
                handlePlayingInput(keyPressed->code);
            }
        }
    }
}

void GameEngine::handleMenuInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Key::Up) {
        selectedMenuItem = (selectedMenuItem - 1 + 4) % 4;
    }
    else if (key == sf::Keyboard::Key::Down) {
        selectedMenuItem = (selectedMenuItem + 1) % 4;
    }
    else if (key == sf::Keyboard::Key::Enter) {
        switch (selectedMenuItem) {
        case 0: startNewGame(); break;
        case 1: loadGame(); break;
        case 2: gameState = GameState::HIGH_SCORES; break;
        case 3: window.close(); break;
        }
    }
    else if (key == sf::Keyboard::Key::Escape) {
        window.close();
    }
}

void GameEngine::handlePauseInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Key::P || key == sf::Keyboard::Key::Escape) {
        gameState = GameState::PLAYING;
        clock.restart();
        backgroundMusic.play();
    }
    else if (key == sf::Keyboard::Key::S) {
        saveGame();
    }
    else if (key == sf::Keyboard::Key::M) {
        gameState = GameState::MAIN_MENU;
    }
    else if (key == sf::Keyboard::Key::N) {
        toggleDayNight();
    }
    else if (key == sf::Keyboard::Key::Equal) {
        float currentVol = backgroundMusic.getVolume();
        if (currentVol < 100) {
            backgroundMusic.setVolume(currentVol + 10);
            cout << "Volume: " << (currentVol + 10) << "%" << endl;
        }
    }
    else if (key == sf::Keyboard::Key::Hyphen) {
        float currentVol = backgroundMusic.getVolume();
        if (currentVol > 0) {
            backgroundMusic.setVolume(currentVol - 10);
            cout << "Volume: " << (currentVol - 10) << "%" << endl;
        }
    }
    else if (key == sf::Keyboard::Key::Num0) {
        backgroundMusic.setVolume(0);
        cout << "Volume: Muted" << endl;
    }
}

void GameEngine::handleGameOverInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Key::R) {
        startNewGame();
    }
    else if (key == sf::Keyboard::Key::M || key == sf::Keyboard::Key::Escape) {
        gameState = GameState::MAIN_MENU;
    }
}

void GameEngine::handlePlayingInput(sf::Keyboard::Key key) {
    switch (key) {
    case sf::Keyboard::Key::A:
    case sf::Keyboard::Key::Left:
        player.moveLeft();
        break;
    case sf::Keyboard::Key::D:
    case sf::Keyboard::Key::Right:
        player.moveRight();
        break;
    case sf::Keyboard::Key::W:
    case sf::Keyboard::Key::Up:
    case sf::Keyboard::Key::Space:
        player.jump();
        break;
    case sf::Keyboard::Key::S:
    case sf::Keyboard::Key::Down:
        player.slide();
        break;
    case sf::Keyboard::Key::P:
    case sf::Keyboard::Key::Escape:
        gameState = GameState::PAUSED;
        backgroundMusic.pause();
        break;
    case sf::Keyboard::Key::N:
        toggleDayNight();
        break;
    default:
        break;
    }
}

void GameEngine::update(float deltaTime) {
    if (gameState != GameState::PLAYING) return;

    player.update(deltaTime);
    trackManager.update(deltaTime, player, scoreManager);

    if (trackManager.checkCollisions(player)) {
        gameState = GameState::GAME_OVER;
        scoreManager.saveHighScore();
    }

    survivalTimer += deltaTime;
    if (survivalTimer >= 1.0f) {
        survivalTimer = 0.0f;
        scoreManager.addScore(10);
    }
}

void GameEngine::drawRoads() {
    sf::Color bgColor = isDayMode ? sf::Color(135, 206, 250) : sf::Color(25, 25, 112);
    window.clear(bgColor);

    for (int i = 0; i < 2; i++)
        window.draw(sideArea[i]);

    trackLeft->render(window);
    trackMid->render(window);
    trackRight->render(window);
}

void GameEngine::renderMenu() {
    window.clear(sf::Color(20, 20, 40));

    sf::Text title(font);
    title.setString("SUBWAY SURFERS");
    title.setCharacterSize(64);
    title.setFillColor(sf::Color::Yellow);
    title.setStyle(sf::Text::Bold);
    title.setPosition(sf::Vector2f(150.0f, 80.0f));
    window.draw(title);

    for (int i = 0; i < 4; i++) {
        if (i == selectedMenuItem) {
            menuItems[i].setFillColor(sf::Color(100, 100, 200));
        }
        else {
            menuItems[i].setFillColor(sf::Color(50, 50, 100));
        }
        window.draw(menuItems[i]);

        sf::Text text(font);
        text.setString(menuLabels[i]);
        text.setCharacterSize(32);
        text.setFillColor(sf::Color::White);
        text.setPosition(sf::Vector2f(menuItems[i].getPosition().x + 50.0f,
            menuItems[i].getPosition().y + 15.0f));
        window.draw(text);
    }

    sf::Text instructions(font);
    instructions.setString("Use UP/DOWN arrows and ENTER to select");
    instructions.setCharacterSize(20);
    instructions.setFillColor(sf::Color(150, 150, 150));
    instructions.setPosition(sf::Vector2f(180.0f, 520.0f));
    window.draw(instructions);

    window.display();
}

void GameEngine::renderHighScores() {
    window.clear(sf::Color(20, 20, 40));

    sf::Text title(font);
    title.setString("HIGH SCORES");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(sf::Vector2f(250.0f, 100.0f));
    window.draw(title);

    sf::Text highScore(font);
    highScore.setString("Top Score: " + to_string(scoreManager.getHighScore()));
    highScore.setCharacterSize(36);
    highScore.setFillColor(sf::Color::White);
    highScore.setPosition(sf::Vector2f(250.0f, 250.0f));
    window.draw(highScore);

    sf::Text player(font);
    player.setString("Player: " + scoreManager.getHighScorePlayer());
    player.setCharacterSize(32);
    player.setFillColor(sf::Color::Cyan);
    player.setPosition(sf::Vector2f(250.0f, 320.0f));
    window.draw(player);

    sf::Text back(font);
    back.setString("Press ENTER or ESC to return");
    back.setCharacterSize(24);
    back.setFillColor(sf::Color(150, 150, 150));
    back.setPosition(sf::Vector2f(220.0f, 480.0f));
    window.draw(back);

    window.display();
}

void GameEngine::renderPause() {
    drawRoads();
    trackManager.render(window);
    player.render(window);

    sf::RectangleShape overlay(sf::Vector2f(800.0f, 600.0f));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    sf::Text pauseText(font);
    pauseText.setString("PAUSED");
    pauseText.setCharacterSize(64);
    pauseText.setFillColor(sf::Color::Yellow);
    pauseText.setPosition(sf::Vector2f(280.0f, 150.0f));
    window.draw(pauseText);

    sf::Text options(font);
    options.setString("P - Resume\nS - Save Game\nN - Toggle Day/Night\nM - Main Menu\n= - Music Louder\n- - Music Quieter\n0 - Mute");
    options.setCharacterSize(28);
    options.setFillColor(sf::Color::White);
    options.setPosition(sf::Vector2f(250.0f, 280.0f));
    window.draw(options);

    window.display();
}

void GameEngine::renderGameOver() {
    drawRoads();
    trackManager.render(window);
    player.render(window);

    sf::RectangleShape overlay(sf::Vector2f(800.0f, 600.0f));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    sf::Text gameOverText(font);
    gameOverText.setString("GAME OVER!");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(sf::Vector2f(250.0f, 180.0f));
    window.draw(gameOverText);

    sf::Text finalScoreText(font);
    finalScoreText.setString("Final Score: " + to_string(scoreManager.getCurrentScore()));
    finalScoreText.setCharacterSize(32);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition(sf::Vector2f(250.0f, 260.0f));
    window.draw(finalScoreText);

    if (scoreManager.getCurrentScore() > scoreManager.getHighScore()) {
        sf::Text newRecord(font);
        newRecord.setString("NEW HIGH SCORE!");
        newRecord.setCharacterSize(28);
        newRecord.setFillColor(sf::Color::Yellow);
        newRecord.setPosition(sf::Vector2f(260.0f, 320.0f));
        window.draw(newRecord);
    }

    sf::Text restartText(font);
    restartText.setString("R - Restart | M - Main Menu");
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(sf::Vector2f(220.0f, 420.0f));
    window.draw(restartText);

    window.display();
}

void GameEngine::renderPlaying() {
    drawRoads();
    trackManager.render(window);
    player.render(window);

    sf::Text scoreText(font);
    scoreText.setString("Score: " + to_string(scoreManager.getCurrentScore()));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(10.0f, 10.0f));
    window.draw(scoreText);

    sf::Text highScoreText(font);
    highScoreText.setString("High: " + to_string(scoreManager.getHighScore()));
    highScoreText.setCharacterSize(20);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(sf::Vector2f(10.0f, 40.0f));
    window.draw(highScoreText);

    sf::Text modeText(font);
    modeText.setString(isDayMode ? "DAY" : "NIGHT");
    modeText.setCharacterSize(20);
    modeText.setFillColor(isDayMode ? sf::Color::Yellow : sf::Color::Cyan);
    modeText.setPosition(sf::Vector2f(720.0f, 10.0f));
    window.draw(modeText);

    sf::Text pauseHint(font);
    pauseHint.setString("P-Pause");
    pauseHint.setCharacterSize(16);
    pauseHint.setFillColor(sf::Color(200, 200, 200));
    pauseHint.setPosition(sf::Vector2f(700.0f, 570.0f));
    window.draw(pauseHint);

    window.display();
}

void GameEngine::render() {
    switch (gameState) {
    case GameState::MAIN_MENU: renderMenu(); break;
    case GameState::PLAYING: renderPlaying(); break;
    case GameState::PAUSED: renderPause(); break;
    case GameState::GAME_OVER: renderGameOver(); break;
    case GameState::HIGH_SCORES: renderHighScores(); break;
    }
}

void GameEngine::startNewGame() {
    player.reset();
    trackManager.reset();
    scoreManager.reset();
    survivalTimer = 0.0f;
    gameState = GameState::PLAYING;
    clock.restart();
}

void GameEngine::saveGame() {
    ofstream file(saveFileName);
    if (file.is_open()) {
        file << scoreManager.getCurrentScore() << " " << survivalTimer << " " << isDayMode << endl;
        player.saveState(file);
        trackManager.saveState(file);
        file.close();
        cout << "Game saved successfully!" << endl;
    }
}

void GameEngine::loadGame() {
    ifstream file(saveFileName);
    if (file.is_open()) {
        int score;
        file >> score >> survivalTimer >> isDayMode;
        scoreManager.setCurrentScore(score);
        player.loadState(file);
        trackManager.loadState(file);
        file.close();
        gameState = GameState::PLAYING;
        clock.restart();
        cout << "Game loaded successfully!" << endl;
    }
    else {
        cout << "No save file found. Starting new game." << endl;
        startNewGame();
    }
}

void GameEngine::toggleDayNight() {
    isDayMode = !isDayMode;
    sf::Color grassGreen = isDayMode ? sf::Color(34, 139, 34) : sf::Color(20, 60, 20);
    for (int i = 0; i < 2; i++) {
        sideArea[i].setFillColor(grassGreen);
    }
}

void GameEngine::run() {
    cout << "=== SUBWAY SURFERS - ENHANCED ===" << endl;
    cout << "Features:" << endl;
    cout << "  - Main Menu System" << endl;
    cout << "  - Save/Load Game" << endl;
    cout << "  - Pause/Resume" << endl;
    cout << "  - Day/Night Mode" << endl;
    cout << "  - Moving Obstacles" << endl;
    cout << "  - Power-up Visual Feedback" << endl;
    cout << "==================================" << endl;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        if (deltaTime > 0.1f) deltaTime = 0.1f;

        processInput();
        update(deltaTime);
        render();
    }
}