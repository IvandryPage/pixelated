# 🎾 Pong Game - SFML Implementation

## 📜 Description
This is a **Pong game** developed using **C++ and SFML**. The project explores fundamental **game development concepts**, including **real-time input handling, collision detection, entity management, and physics-based movement**.

## 🎮 Features
- **Player vs Player (2-player mode)**
- **Smooth ball physics** with realistic collision handling
- **SFML-based rendering and input system**
- **Custom entity-component system for game objects**
- **Score tracking** for both players
- **Dynamic memory management and STL usage**

## 🛠️ Technologies Used
- **C++ (Modern C++)**
- **SFML (Simple and Fast Multimedia Library)**
- **STL Containers** (std::map, std::vector, std::tuple)
- **Custom entity-component system**

## 📜 How to Play
- **Player 1 (Left Side)**:
  - Move **Up** → `W`
  - Move **Down** → `S`
- **Player 2 (Right Side)**:
  - Move **Up** → `Up Arrow`
  - Move **Down** → `Down Arrow`
- **Score a point by hitting the ball past your opponent!**

## 🔧 Setup & Installation
1. **Install SFML**
   - Download SFML from [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)
   - Link SFML libraries to your C++ project

2. **Clone the Repository**
   ```sh
   git clone https://github.com/your-repo/pong-game.git
   cd pong-game
   ```

3. **Compile the Project**
   - Using `g++`:
     ```sh
     g++ -std=c++17 main.cpp -o pong -lsfml-graphics -lsfml-window -lsfml-system
     ```
   - Using 'make':
     ```sh
     make run
     ```

4. **Run the Game**
   ```sh
   ./build/launcher
   ```

## 🛠️ Future Improvements
- **AI opponent for single-player mode**
- **Power-ups & new mechanics**
- **UI enhancements** (better fonts, animations)
- **Better collision physics for more dynamic gameplay**

## 📜 Devlog Highlights
- **March 2025**: Learning **C++ STL, pointers, dynamic memory allocation**
- **Implemented SFML Shapes, Mouse Input, and Real-Time Input Handling**
- **Optimized ball physics using vector math**
- **Built a student database mini-project using `std::map` and `std::tuple`**

## 💡 Lessons Learned
- Importance of **managing dynamic memory** correctly to prevent leaks
- How **collision normals** affect physics-based movement
- Using **std::optional and STL containers** for flexible game data management
- Handling **SFML mouse and keyboard events** effectively

---
_Developed by @ivandrypage_ 🚀


