MAIN_O = src/obj/main.o
MONSTER_O = src/obj/monster.o
WAVE_O = src/obj/wave.o
TOWER_O = src/obj/tower.o
OBJ = src/obj/main.o src/obj/monster.o src/obj/wave.o src/obj/tower.o

PROG = bin/itd

CC = gcc
CFLAGS = -Wall -O2 -g3

all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROG)

$(MAIN_O) : src/main.c include/monster.h
		$(CC) $(CFLAGS) -c $< -o $@
		@echo "main : done !"

$(MONSTER_O) : src/monster.c include/monster.h
		$(CC) $(CFLAGS) -c $< -o $@
		@echo "monsters : done !"

$(WAVE_O) : src/wave.c include/monster.h
		$(CC) $(CFLAGS) -c $< -o $@
		@echo "monster waves : done !"

$(TOWER_O) : src/tower.c include/tower.h include/wave.h
		$(CC) $(CFLAGS) -c $< -o $@
		@echo "towers : done !"