# C Projects

A collection of C projects ranging from data structure implementations to graphical simulations using SDL2.

---

## Projects

### [Cstructures](./Cstructures)
Implementation of various data structures from scratch in C, with an Object-Oriented style using structs and function pointers.

Includes:
- `LinkedList` — singly/doubly linked list
- `Stack` — stack over linked list
- `BinaryTree` — binary search tree
- `NaryTree` — generic N-ary tree
- `HashMap` — hash map with chaining
- `Dictionary` — key-value store
- `NodesNetwork` — 2D and 3D node graphs
- `ListsNetwork` — network of linked lists
- `MobiusNode` — circular/Möbius-style node structure

---

### [projector](./projector)
An SDL2-based graphical tool for visualizing **phasors** and **mathematical functions** in real time.

Defines `Phasor`, `Graph`, and `Func` structures that can be composed and rendered to an 800×600 window. Built with a Makefile using `sdl2-config`.

**Dependencies:** SDL2
**Build:** `make` — **Run:** `make run`

---

### [bouncingBalls](./bouncingBalls)
SDL2 simulation where **clicking anywhere in the window spawns a ball** that launches upward with a randomised angle, then falls under gravity and bounces off every wall.

A **side menu** (240 px panel) lets you control all parameters in real time:

| Control | Range |
|---|---|
| **Gravity** | 50 – 2000 px/s² |
| **Ball size** | 5 – 40 px |
| **Bounce** (restitution) | 0.1 – 1.0 |
| **Spawn speed** | 50 – 600 px/s |
| **Shape** | Circle, Square, Triangle, Diamond, Pentagon |
| **Color** | 8 colour swatches |

Additional features: resizable window (simulation area scales automatically), CLEAR ALL button to reset, up to 500 simultaneous balls.

**Dependencies:** SDL2, SDL2_gfx
**Build:** `make` — **Run:** `make run`

---

### [randomWalks](./randomWalks)
SDL2 simulation of **random walk agents** starting from the center of a window and moving stochastically on a 2D grid.

Accepts the number of agents as a command-line argument (default: 5).

**Dependencies:** SDL2

---

## Planned / Work in Progress

The following folders are placeholders for future projects:

| Folder | Topic |
|---|---|
| `Chinese` | Chinese character rendering |
| `Dithering` | Image dithering algorithms |
| `Exams` | Exam exercises |
| `graphAnimated` | Animated graph rendering |
| `Knots` | Knot theory visualization |
| `mandelbrot` | Mandelbrot set fractal |
| `neuralNetwork` | Neural network from scratch |
| `randomParticleMovement` | Particle simulation |
| `RealPopulation` | Population dynamics model |
| `realTrees` | Procedural tree generation |
| `rotatingCube` | 3D rotating cube |
| `signalNoise` | Signal and noise visualization |
| `Simmetry` | Symmetry patterns |
| `soundWave` | Sound wave visualization |
| `starfield` | Starfield / flying stars effect |
| `Terrain` | Procedural terrain generation |
| `Tessellations` | Tessellation patterns |
| `Torrenting` | BitTorrent protocol exploration |
| `Xrays` | X-ray image processing |
| `Fractals` | Fractals visualizer |

---

## Requirements

- `gcc` (C11 or later)
- `SDL2` — for graphical projects (`sudo apt install libsdl2-dev`)
- `SDL2_gfx` — for shape rendering (`sudo apt install libsdl2-gfx-dev`)
- `make`
