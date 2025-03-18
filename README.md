🏰 cub3D

A simple 3D game engine inspired by Wolfenstein 3D, built using raycasting and MiniLibX as part of the 42 school curriculum.

🎯 Features

Raycasting Engine – Simulates a 3D perspective using a 2D map.

MiniLibX – Lightweight graphics library for rendering.

Player Movement – Move and rotate smoothly within the game world.

Wall Textures – Textured walls for a more immersive experience.

Doors – Interactable doors that open and close.

Hand Movement Animations – Simulated hand movements when the player moves.

Collision Detection – Prevents the player from walking through walls.


🛠️ Installation

Prerequisites

macOS or Linux (MiniLibX may not work on Windows natively)

make (to compile the project)

gcc or clang (C compiler)


Clone & Compile

git clone https://github.com/yourusername/cub3d.git
cd cub3d
make
./cub3D maps/example.cub

🕹️ Controls

📜 Map Format

The game world is defined in a .cub file. Example:

1111111
1000001
100D001
1000001
1111111

1 → Wall

0 → Walkable space

D → Door (can be opened/closed)


🏗️ Project Structure

cub3d/
│── src/          # Source files
│── includes/     # Header files
│── maps/         # Example map files
│── textures/     # Texture assets
│── Makefile      # Compilation script
│── README.md     # Project documentation

🚀 Future Improvements

Dynamic lighting & shading

More hand movement variations

Sound effects for footsteps and door interactions


📜 License

This project follows the 42 school guidelines. Feel free to use it for learning purposes!
