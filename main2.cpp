#include "gameengine.h"
#include <iostream>
#include <exception>

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "    SUBWAY SURFERS - ENHANCED EDITION   " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Game Features:" << endl;
    cout << "  - Main Menu System" << endl;
    cout << "  - Save/Load Game Progress" << endl;
    cout << "  - Pause/Resume Functionality" << endl;
    cout << "  - Day/Night Mode Toggle" << endl;
    cout << "  - Moving Obstacles" << endl;
    cout << "  - Power-ups: Shield, Jetpack, Magnet, Double Coin" << endl;
    cout << "  - High Score Tracking" << endl;
    cout << endl;
    cout << "Controls:" << endl;
    cout << "  A/Left Arrow  - Move Left" << endl;
    cout << "  D/Right Arrow - Move Right" << endl;
    cout << "  W/Up/Space    - Jump" << endl;
    cout << "  S/Down        - Slide" << endl;
    cout << "  P/Escape      - Pause" << endl;
    cout << "  N             - Toggle Day/Night" << endl;
    cout << endl;
    cout << "Starting game..." << endl;
    cout << "========================================" << endl;
    cout << endl;

    try {
        GameEngine game;
        game.run();
    }
    catch (const exception& e) {
        cerr << endl;
        cerr << "========================================" << endl;
        cerr << "ERROR: " << e.what() << endl;
        cerr << "========================================" << endl;
        cerr << "Press Enter to exit..." << endl;
        cin.get();
        return 1;
    }

    cout << endl;
    cout << "Thank you for playing Subway Surfers!" << endl;
    cout << "Game closed successfully." << endl;

    return 0;
}