# Imac_Tower_Defense

*IMAC semester 2:* Coding project (educational).

A 2D Tower Defense game : C, SDL 1.2, OpenGL (old version).

## Table of contents

* [**How to**](#how-to)
	- [**Install libraries**](#install-libraries)
	- [**Run the program**](#run-the-program)
	- [**Inside the program**](#inside-the-program)
		- [**Start game**](#start-game)
		- [**Help window**](#help-window)

* [**More informations**](#more-informations)
	- [**Structure**](#structure)
	- [**Artworks**](#artworks)
	- [**Audio**](#audio)
	- [**Game developpers**](#game-developpers)

## How to

### Install libraries
If **SDL_ttf** and **TrueType** are not installed on your computer, you can install them with the following commands (not necessary):

```bash
sudo apt-get install libsdl-ttf2.0-dev
sudo apt-get install libfreetype6-dev
```

If you can't access to the root rights, no matter, they are precompiled in the repository (yep, it's not a good practice but it's easier for us to run the program on the university's computers).

Moreover, you will need to have **FMOD** library, which is also precompiled in the repository.


### Run the program

You will need to have a gcc compiler (from build-esssential, for instance).

Open a shell inside the repository folder:

```bash
make
export LD_LIBRARY_PATH=lib/lib
./bin/program.out
```

### Inside the program

#### Start game

When you click on **Start Game**, a new window will appear to make you choose the map you want to play with. You will just need to pick one map and the game will start.

If you want to come back to the menu, just click on the **Back** button.

#### Help window

To know how to play, take a look at the help window (press 'h' inside a game).

Here is a brief recap:

--------
SPACESHIPS

* Press 'a' to make a 'laser spaceship'
* Press 'z' to make a 'rocket spaceship'
* Press 'e' to make a 'electric spaceship'
* Press 'r' to make a 'water spaceship'

PLANETS

* Press 'q' to make a 'radar planet'
* Press 's' to make a 'factory planet'
* Press 'd' to make a 'ammo planet'

--------

## More Informations

### Structure

We are beginners so we still don't really know Design Patterns. We tried to do our best.

### Artworks

Most of the sprites have been made by **Mathilde Dumoulin**.

### Audio

Musics have been made by **8 Bit Universe** (a YouTube channel). Actually, we do not own any music rights.

### Game Developpers

- **Mathilde Dumoulin**
- **Julien Haudegond**
