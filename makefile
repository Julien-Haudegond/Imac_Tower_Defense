# Bien penser à ajouter le lien vers les .o dans la variable OBJ
# Penser à rajouter les dépendances des fichiers .h dans les règles de compilation

CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -Llib/lib -lSDL -lGLU -lGL -lm -lSDL_image -lSDL_ttf -lfmod
INCLUDE = -Ilib/include -Iinclude

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

MAIN_O = obj/main.o
SAVE_O = obj/save.o

INTRO_O = obj/intro.o
END_GAME_O = obj/end_game.o
EXPLOSION_O = obj/explosion.o

GAME_O = obj/game.o
MENU_O = obj/menu.o

TOWER_O = obj/tower.o
TOWER_LIST_O = obj/tower_list.o
BUILDING_O = obj/building.o
BUILDING_LIST_O = obj/building_list.o

IMAGE_O = obj/image.o
TEXT_O = obj/text.o
GRAPHIC_O = obj/graphic.o
MAP_DRAW_O = obj/map_draw.o
WINDOW_O = obj/window.o
SPRITE_O = obj/sprite.o

MONSTER_O = obj/monster.o
WAVE_O = obj/wave.o

ITD_O = obj/itd.o
NODE_O = obj/node.o
LINK_O = obj/link.o


CONST_H = include/const.h
SAVE_H = include/save.h

END_GAME_H = include/animations/end_game.h
EXPLOSION_H = include/animations/explosion.h
INTRO_H = include/animations/intro.h

GAME_H = include/app/game.h
MENU_H = include/app/game.h

BUILDING_LIST_H = include/constructions/building_list.h
BUILDING_H = include/constructions/building.h
TOWER_LIST_H = include/constructions/tower_list.h
TOWER_H = include/constructions/tower.h

GRAPHIC_H = include/gui/graphic.h
IMAGE_H = include/gui/image.h
MAP_DRAW_H = include/gui/map_draw.h
SPRITE_H = include/gui/sprite.h
TEXT_H = include/gui/text.h
WINDOW_H = include/gui/window.h

MONSTER_H = include/monsters/monster.h
WAVE_H = include/monsters/wave.h

ITD_H = include/nodes/itd.h
LINK_H = include/nodes/link.h
NODE_H = include/nodes/node.h



OBJ = $(MAIN_O) $(INTRO_O) $(MENU_O) $(GAME_O) $(IMAGE_O) $(ITD_O) $(NODE_O) $(LINK_O) $(MONSTER_O) $(WAVE_O) $(TOWER_O) $(MAP_DRAW_O) $(WINDOW_O) $(TOWER_LIST_O) $(BUILDING_O) $(BUILDING_LIST_O) $(SPRITE_O) $(END_GAME_O) $(TEXT_O) $(GRAPHIC_O) $(EXPLOSION_O) $(SAVE_O)

PROG = bin/program.out

# Regles compilation

all : $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(PROG) $(LDFLAGS)
	@echo ""
	@echo "**********************************************************"
	@echo "*** to execute, type : export LD_LIBRARY_PATH=lib/lib  ***"
	@echo "*** then, type       : ./bin/program.out               ***"
	@echo "**********************************************************"


$(MAIN_O) : src/main.c $(INTRO_H) $(GAME_H) $(MENU_H)
	mkdir -p obj
	@echo "compile program"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"

$(SAVE_O) : src/save.c $(SAVE_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Save : done !"


$(END_GAME_O) : src/animations/end_game.c $(END_GAME_H) $(MAP_DRAW_H) $(GRAPHIC_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Sprite : done !"

$(EXPLOSION_O) : src/animations/explosion.c $(EXPLOSION_H) $(CONST_H) $(WINDOW_H) $(SPRITE_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Explosion : done !"

$(INTRO_O) : src/animations/intro.c $(INTRO_H) $(CONST_H) $(MENU_H) $(WINDOW_H) $(SPRITE_H) $(GRAPHIC_H)
	@echo "compile intro"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"


$(GAME_O) : src/app/game.c $(GAME_H) $(CONST_H) $(SAVE_H) $(END_GAME_H) $(EXPLOSION_H) $(GAME_H) $(TOWER_H) $(TOWER_LIST_H) $(BUILDING_H) $(BUILDING_LIST_H) $(IMAGE_H) $(MAP_DRAW_H) $(WINDOW_H) $(SPRITE_H) $(TEXT_H) $(GRAPHIC_H) $(MONSTER_H) $(WAVE_H) $(ITD_H) $(NODE_H) $(LINK_H)
	@echo "compile game"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"

$(MENU_O) : src/app/menu.c $(MENU_H) $(CONST_H) $(SAVE_H) $(GAME_H) $(WINDOW_H) $(SPRITE_H) $(GRAPHIC_H)
	@echo "compile menu"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"


$(BUILDING_LIST_O) : src/constructions/building_list.c $(BUILDING_LIST_H) $(WINDOW_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Building List : done !"

$(BUILDING_O) : src/constructions/building.c $(BUILDING_H) $(WINDOW_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Building : done !"

$(TOWER_LIST_O) : src/constructions/tower_list.c $(TOWER_LIST_H) $(WINDOW_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Tower Lists : done !"

$(TOWER_O) : src/constructions/tower.c $(TOWER_H) $(WINDOW_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "towers : done !"


$(GRAPHIC_O) : src/gui/graphic.c $(GRAPHIC_H) $(CONST_H) $(TEXT_H) $(MAP_DRAW_H) $(SPRITE_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Graphic : done !"

$(IMAGE_O) : src/gui/image.c $(IMAGE_H)
	@echo "compile image"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"

$(MAP_DRAW_O) : src/gui/map_draw.c $(MAP_DRAW_H) $(CONST_H) $(SPRITE_H) $(WINDOW_H) $(IMAGE_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "map_draw : done !"

$(SPRITE_O) : src/gui/sprite.c $(SPRITE_H) $(CONST_H) $(WINDOW_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Sprite : done !"

$(TEXT_O) : src/gui/text.c $(TEXT_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "Texts : done !"

$(WINDOW_O) : src/gui/window.c $(WINDOW_H) $(CONST_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "window : done !"


$(MONSTER_O) : src/monsters/monster.c $(MONSTER_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "monsters : done !"

$(WAVE_O) : src/monsters/wave.c $(WAVE_H) $(MONSTER_H)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "monster waves : done !"


$(ITD_O) : src/nodes/itd.c $(ITD_H) $(NODE_H)
	@echo "compile itd"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"

$(LINK_O) : src/nodes/link.c $(LINK_H)
	@echo "compile link"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"

$(NODE_O) : src/nodes/node.c $(NODE_H) $(CONST_H) $(TOWER_H) $(WINDOW_H)
	@echo "compile node"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "done!"



clean :
	rm -rf $(OBJDIR)*.o
	rm -rf $(BINDIR)*