# Bien penser à ajouter le lien vers les .o dans la variable OBJ
# Penser à rajouter les dépendances des fichiers .h dans les règles de compilation

CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -Llib/lib -lSDL -lGLU -lGL -lm -lSDL_image -lSDL_ttf
INCLUDE = -Ilib/build/include

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

MAIN_O = obj/main.o

GAME_O = obj/game.o
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

TEXT_O = obj/text.o
GRAPHIC_O = obj/graphic.o

ARGS_O = obj/args.o

SDL_ARRAY_O = obj/sdl_array.o

OBJ = $(MAIN_O) $(GAME_O) $(IMAGE_O) $(ITD_O) $(NODE_O) $(LINK_O) $(MONSTER_O) $(WAVE_O) $(TOWER_O) $(MAP_DRAW_O) $(WINDOW_O) $(TOWER_LIST_O) $(SPRITE_O) $(ARGS_O) $(TEXT_O) $(GRAPHIC_O) $(SDL_ARRAY_O)

PROG = bin/program.out

# Regles compilation

all : $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(PROG) $(LDFLAGS)
	@echo ""
	@echo "**********************************************************"
	@echo "*** to execute, type : export LD_LIBRARY_PATH=lib/lib  ***"
	@echo "*** then, type       : ./bin/program.out Map_xx.itd    ***"
	@echo "**********************************************************"

$(MAIN_O) : src/main.c include/game.h include/args.h
	mkdir -p obj
	@echo "compile program"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"

$(GAME_O) : src/game.c include/game.h include/itd.h include/node.h include/link.h include/image.h include/monster.h include/wave.h include/tower.h include/const.h include/map_draw.h include/window.h  include/tower_list.h include/sprite.h include/args.h include/text.h include/graphic.h include/sdl_array.h
	@echo "compile game"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"

$(IMAGE_O) : src/image.c include/image.h
	@echo "compile image"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"

$(ITD_O) : src/itd.c include/itd.h include/node.h
	@echo "compile itd"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"

$(NODE_O) : src/node.c include/node.h include/const.h include/window.h
	@echo "compile node"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"

$(LINK_O) : src/link.c include/link.h
	@echo "compile link"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"

$(MONSTER_O) : src/monster.c include/monster.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "monsters : done !"

$(WAVE_O) : src/wave.c include/monster.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "monster waves : done !"

$(TOWER_O) : src/tower.c include/tower.h include/wave.h include/window.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "towers : done !"

$(MAP_DRAW_O) : src/map_draw.c include/map_draw.h include/const.h include/sprite.h include/window.h include/tower_list.h include/image.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "map_draw : done !"

$(WINDOW_O) : src/window.c include/window.h include/const.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "window : done !"

$(TOWER_LIST_O) : src/tower_list.c include/tower_list.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Tower Lists : done !"

$(SPRITE_O) : src/sprite.c include/sprite.h include/const.h include/window.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Sprite : done !"

$(ARGS_O) : src/args.c include/args.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Arguments : done !"

$(TEXT_O) : src/text.c include/text.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Texts : done !"

$(GRAPHIC_O) : src/graphic.c include/graphic.h include/text.h include/map_draw.h include/sprite.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Graphic : done !"

$(SDL_ARRAY_O) : src/sdl_array.c include/sdl_array.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "SDL Arrays : done !"

clean :
	rm -rf $(OBJDIR)*.o
	rm -rf $(BINDIR)*