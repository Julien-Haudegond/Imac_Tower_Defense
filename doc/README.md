# Imac_Tower_Defense
Projet Algorithmique Avancée et Synthèse d'Images n°1

## How to

### I. Install the libraries
If **SDL_ttf** and **TrueType** are not installed on your computer, please install them with the following commands : <br/>
`sudo apt-get install libsdl-ttf2.0-dev` <br/>
`sudo apt-get install libfreetype6-dev` <br/>

If you can't access to the root rights, no matter, they are precompiled in the repository (yep, it's not a good practice but it's easier for us to run the program on the university's computers).

### II. Run the program
Open a shell inside the repository folder : <br/>
`make` <br/>
`export LD_LIBRARY_PATH=./lib/lib` (only if the libraries are not installed on your computer) <br/>
`./bin/program.out Map_xx.itd` (specify the map you want to use in the game) <br/>