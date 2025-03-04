# SapperCpp

SapperCpp is a C++ implementation of the classic Minesweeper game, developed as a course project to fulfill the requirements of a C++ programming course. The game utilizes the Simple and Fast Multimedia Library (SFML) to provide graphical rendering and user interaction.

## Features

- **Graphical User Interface**: Renders the game board and handles user interactions using SFML.
- **Customizable Board**: Allows for different board sizes and difficulty levels by adjusting the number of mines.
- **Interactive Gameplay**: Supports standard Minesweeper functionalities, including revealing cells, flagging mines, and checking for win/loss conditions.

## Prerequisites

- **C++ Compiler**: Ensure you have a C++17 compatible compiler installed.
- **SFML Library**: Install the SFML library for graphical rendering and event handling.

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/SecCodeSmith/SapperCpp.git
   cd SapperCpp
   ```

2. **Install SFML**:
   - **On Ubuntu**:
     ```bash
     sudo apt-get install libsfml-dev
     ```
   - **On Windows**:
     - Download the SFML library from the [official website](https://www.sfml-dev.org/download.php).
     - Follow the provided instructions to set up SFML with your compiler.

3. **Build the Project**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

## Usage

- **Run the Game**:
  ```bash
  ./SapperCpp
  ```
- **Gameplay Instructions**:
  - Left-click to reveal a cell.
  - Right-click to flag or unflag a cell as a mine.
  - The game ends when all non-mine cells are revealed or a mine is clicked.

## Project Structure

- `main.cpp`: Contains the main function to initialize and run the game.
- `Board.cpp` / `Board.h`: Defines the game board and related functionalities.
- `Field.cpp` / `Field.h`: Manages individual cells on the game board.
- `WindowGen.cpp` / `WindowGen.h`: Handles the creation and management of the game window using SFML.
- `Play.cpp` / `Play.h`: Implements the game logic and user interaction.
