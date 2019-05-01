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
TOWER_LIST_O = obj/tower_list.o

MAP_DRAW_O = obj/map_draw.o
WINDOW_O = obj/window.o
SPRITE_O = obj/sprite.o

OBJ = $(MAIN_O) $(IMAGE_O) $(ITD_O) $(NODE_O) $(LINK_O) $(MONSTER_O) $(WAVE_O) $(TOWER_O) $(MAP_DRAW_O) $(WINDOW_O) $(TOWER_LIST_O) $(SPRITE_O)

PROG = bin/program.out

# Regles compilation

all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROG) $(LDFLAGS)
	@echo "*** to execute, type : ./bin/program.out***"

$(MAIN_O) : src/main.c include/itd.h include/node.h include/image.h include/monster.h include/wave.h include/tower.h include/const.h include/map_draw.h include/window.h  include/tower_list.h include/sprite.h
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

$(NODE_O) : src/node.c include/node.h include/const.h include/window.h
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

$(MAP_DRAW_O) : src/map_draw.c include/map_draw.h include/const.h
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "map_draw : done !"

$(WINDOW_O) : src/window.c include/window.h
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "window : done !"

$(TOWER_LIST_O) : src/tower_list.c include/tower_list.h include/tower.h
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Tower Lists : done !"

$(SPRITE_O) : src/sprite.c include/sprite.h
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Sprite : done !"



clean :
	rm -rf $(OBJDIR)*.o
	rm -rf $(BINDIR)*