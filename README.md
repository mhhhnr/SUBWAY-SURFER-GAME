## SUBWAY SURFER GAME

In this game we have to idealize the subway surfer game to make a self build game using C++ libraries. We added **SFML libraries** to add a touch of graphics to our game. It is a **three lane 2D game inspired by real Subway Surfer Game**. This entire game demonstrates the use of **encapsulation, polymorphism, templates and composition**. It includes **three lanes based movement, obstacles, coins, powerups, scoring and much more**.

---

## Functionalities

Following are some of the functionalities implemented in our game that was totally inspired by subway surfers:

1. **Player Movement:** The player can move in all four directions i-e  
   - Up               —> Jump Up  
   - Down Key         —> Slide Down  
   - Left Key         —> Move left lane  
   - Right Key        —> Move Right lane  

   Also the forward movement of the player is in **auto mode** i-e we do not have to move the player by ourselves.

2. **Lane System:** The movement is in between three lanes i-e left, middle and right. There is smooth movement in between these lanes and the player cannot go out of these lanes.

3. **Obstacles:** Following are some of the obstacles placed on the way of player randomly:  
   - Barrier  
   - Train  
   - Fence  
   - Cone  

4. **Coins and Scoring:** The coins are placed randomly on lanes. These coins are collected by the player and on each lane.

5. **Power Ups:** Power ups have their own activation and deactivation duration right after the player collects it. In this game, we used following power ups:  
   - Magnet        —> Automatically collect coins  
   - Shield        —> Protects from colliding  
   - Jetpack       —> Flies over obstacles  
   - Double coin   —> Double the coins being collected  

6. **Game Speed:** Our game speed increases gradually after every 20 seconds of continuously playing the game.

7. **Game Over:** When the player collides with obstacles without any shield, the game ends. And a gameover window is shown showing the highest scores and the score obtained by the last player.

---

## Requirements

Following are the requirement fulfilled in this game:

1. **TrackManager:** We manage the track length, respawning of obstacles, powerups and coins in this feature.  
2. **File Handling:** The highscores of players are stored in a separate file where we compare the scores of players and store the highest ones.  
3. **Templates:** We implemented templates such as Template collection class, effect handler and many more.

---

## Game UI

This game uses **SFML** for many features and designing such as:  
1. Player movement  
2. Lanes Scrolling  
3. Lane switch transition  
4. Coins and power up symbols  

---

## Bonus Features

Following are some of the bonus features implemented in our game:  
1. Pause Game  
2. Resume Game  
3. Continue Game  

---
## UML Diagram:

<img width="318" height="213" alt="image" src="https://github.com/user-attachments/assets/d932b589-90c3-4d02-bd40-105e980e326a" />
<img width="468" height="246" alt="image" src="https://github.com/user-attachments/assets/916ebf8a-3faa-4cd6-bbd2-5776cfbaa755" />
<img width="468" height="246" alt="image" src="https://github.com/user-attachments/assets/59281894-40ff-4e7e-9955-2cdbc3f4ca25" />
<img width="468" height="246" alt="image" src="https://github.com/user-attachments/assets/94d9ef8d-5412-4730-9bbe-0b3d2743e055" />

## Templates

The main use of templates is in the class:  

```cpp
template <typename T>
class GameList {
};```




