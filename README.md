# MazePath Navigator

**MazePath Navigator** is a maze generation and pathfinding tool. It generates random mazes using Depth-First Search (DFS) and solves them using two algorithms: Dijkstra’s algorithm and the Right-Hand Rule.

## Features
- **Random Maze Generation**: Uses Depth-First Search (DFS) to create random mazes.
- **Maze Solving**: 
  - Dijkstra's Algorithm for finding the shortest path.
  - Right-Hand Rule for an alternative maze-solving method.
- **Visualization**: Displayed the maze creation and solving process through text-based output.

## Technologies Used
- **C++**: Core programming language.

## Getting Started

### Prerequisites
- C++ compiler (e.g., GCC, Clang)

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/mazepath-navigator.git
    ```

2. Compile the program:

    ```bash
    g++ maze.cpp -o maze
    ```

3. Run the program:

    ```bash
    ./maze
    ```

## How it Works

### Maze Generation
The maze is generated using a randomized Depth-First Search (DFS) algorithm. It starts from a random cell and recursively visits neighboring cells that have not yet been visited, removing walls between them to form a passage.

### Maze Solving
- **Right-Hand Rule**: A wall-following algorithm that attempts to solve the maze by keeping the right hand in contact with a wall.
- **Dijkstra’s Algorithm**: A more efficient approach to finding the shortest path from the start to the end of the maze.

## How to Customize
- **Maze Size**: You can change the maze size by modifying the `size` constant in the code.
- **Solving Algorithm**: Switch between Dijkstra’s Algorithm and the Right-Hand Rule by modifying the main function.

## Future Enhancements
- Add additional pathfinding algorithms like A*.
- Improve the maze generation with different algorithms.


## License
This project is licensed under the MIT License.
