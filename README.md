# Battleship Game in C++
This project is an implementation of the classic Battleship game, built using C++ for a console-based user interface. The game simulates a two-player battle, where each player attempts to sink the opponent's fleet by guessing the locations of their ships on a grid.

## Features
- **Console-based game**: Enjoy the Battleship experience directly from the console.
- **Player vs AI**: The game is designed for a single player to battle against a computer opponent.
- **Random ship placement**: The game randomizes the placement of ships for both the player and the AI to ensure variability.
- **Customizable game grid**: The game features a 10x10 grid for ship placement.
- **Graphical enhancements**: Custom color outputs for an enhanced console experience.
- **Background music support**: The game comes with background music to add an immersive experience (optional).

## Gameplay
Each player has a fleet of ships that are hidden from their opponent. Players take turns guessing coordinates on their opponent’s grid to try and locate and sink their ships. The game continues until all of one player's ships are sunk.

### Ships
The following types of ships are available in the game:
- **Aircraft Carrier**: Occupies 5 cells.
- **Battleship**: Occupies 4 cells.
- **Submarine**: Occupies 3 cells.
- **Cruiser**: Occupies 3 cells.
- **Destroyer**: Occupies 2 cells.

## Getting Started

### Prerequisites
- **C++ Compiler**: You need a C++ compiler that supports C++11 or higher.
- **Audio libraries**: To enable background music, ensure you have the necessary audio libraries (like SFML or other alternatives) installed.

### Running the Project
1. Clone the repository:
    ```bash
    git clone https://github.com/aykhan019/Battleship_Cpp.git
    ```
2. Compile the project:
    ```bash
    g++ Source.cpp -o battleship -std=c++11
    ```
3. Run the game:
    ```bash
    ./battleship
    ```
## Video Demo
[![Battleship Game Demo](https://media.aykhan.net/thumbnails/projects/battleship.jpg)](https://www.youtube.com/watch?v=mobOv9Qd304)

## Controls
- Enter coordinates in the format (e.g., A5) to make your guesses.

## License
This project is licensed under the MIT License. See the [LICENSE](https://github.com/aykhan019/Battleship_Cpp/blob/master/LICENSE) file for more details.
