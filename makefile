# Bien penser à ajouter le lien vers les .o dans la variable OBJ
# Penser à rajouter les dépendances des fichiers .h dans les règles de compilation

CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lSDL -lGLU -lGL -lm -lSDL_image

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/
INCLUDEDIR = include/


MAIN_O = obj/main.o
IMAGE_O = obj/image.o
ITD_O = obj/itd.o
NODE_O = obj/node.o
LINK_O = obj/link.o

MONSTER_O = obj/monster.o
WAVE_O = obj/wave.o
TOWER_O = obj/tower.o

OBJ = $(MAIN_O) $(IMAGE_O) $(ITD_O) $(NODE_O) $(LINK_O) $(MONSTER_O) $(WAVE_O) $(TOWER_O)

PROG = bin/program.out

# Regles compilation

all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROG)
	@echo "*** to execute, type : ./bin/program.out***"

$(MAIN_O) : src/main.c include/itd.h include/node.h include/image.h include/monster.h include/wave.h include/tower.h
	@echo "compile program"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"

$(IMAGE_O) : src/image.c include/image.h
	@echo "compile image"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"

$(ITD_O) : src/itd.c include/itd.h include/node.h
	@echo "compile itd"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"

$(NODE_O) : src/node.c include/node.h
	@echo "compile node"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"

$(LINK_O) : src/link.c include/link.h
	@echo "compile link"
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "done!"

$(MONSTER_O) : src/monster.c include/monster.h
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "monsters : done !"

$(WAVE_O) : src/wave.c include/monster.h
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "monster waves : done !"

$(TOWER_O) : src/tower.c include/tower.h include/wave.h
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "towers : done !"

clean :
	rm -rf $(OBJDIR)*.o
	rm -rf $(BINDIR)*