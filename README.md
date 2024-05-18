# Minesweeper Game

## Introduction
This is a Minesweeper game developed in C++ using the SFML library for graphics rendering. The game allows users to click on tiles to reveal whether they contain a mine or a number indicating the count of adjacent mines. The objective is to uncover all non-mine tiles without triggering a mine.

## Features
- Classic Minesweeper gameplay.
- Dynamically generated minefield.
- Left-click to reveal tiles.
- Right-click to flag tiles suspected of containing mines.
- Game-over detection upon clicking a mine.
- Text-based and color-coded tile representation.

## Prerequisites
- C++17 or later.
- [SFML library](https://www.sfml-dev.org/download.php) (Simple and Fast Multimedia Library).

## Setup Instructions
1. **Clone the repository:**
    ```sh
    git clone https://github.com/your-username/minesweeper.git
    cd minesweeper
    ```

2. **Install SFML:**
   Follow the instructions on the [SFML website](https://www.sfml-dev.org/tutorials/2.6/#getting-started) to download and install the SFML library for your platform.

3. **Build the project:**
    - **On Windows (using Visual Studio):**
      - Open the project in Visual Studio.
      - Configure the project to link against the SFML libraries.
      - Build the project.
    - **On macOS/Linux (using Make):**
      - Ensure SFML is installed and accessible.
      - Use the provided Makefile or create your own to compile the project.
      - Example Makefile command:
        ```sh
        make
        ```

4. **Run the game:**
    - Execute the compiled binary to start the game.
    - Example command:
      ```sh
      ./minesweeper
      ```

## Usage
- **Left-click** on a tile to reveal it.
- **Right-click** on a tile to flag/unflag it as a mine.
- The game ends when you reveal a mine, displaying a "Game Over" message.

## Code Overview
### Game Class
The `Game` class manages the Minesweeper game logic, including board generation, user interactions, and game state updates.

#### Key Methods:
- `Init()`: Initializes the game, loads the font, and sets the random seed.
- `GetGrid()`: Returns the current game grid.
- `DrawBoard()`: Draws the game board based on the current state.
- `ClearBoard()`: Clears the visual representations of the board.
- `LeftClick(sf::Vector2i coord)`: Handles the left-click event to reveal a tile.
- `RightClick(sf::Vector2i coord)`: Handles the right-click event to flag/unflag a tile.
- `IsGameOver()`: Checks if the game is over.
- `GameOverStart(sf::RenderWindow& window)`: Displays the game-over message.

### Main Function
The `main` function sets up the SFML window, handles user input, and continuously updates and renders the game board.

## Notes
- The game uses a grid of size 30x16 with 99 mines.
- Ensure the `arial.ttf` font file is in the same directory as the executable.
- Modify `DEBUG_MODE` to `true` in the `Game` class for debug information during development.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments
- This project uses the [SFML library](https://www.sfml-dev.org/).
- Inspired by the classic Minesweeper game.