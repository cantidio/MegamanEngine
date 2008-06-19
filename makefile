
all: weapon player game ../gorgon_core/static/libgorgon.a  
	g++
	./obj/weapon.o 				\
	./obj/player.o				\
	-o megaman.e				\
	../gorgon_core/static/libgorgon.a	\
	`allegro-config --libs`

weapon: ./src/weapon.c ./include/weapon.h
	g++ -c ./src/weapon.c
	mv weapon.o ./obj/weapon.o

player: ./src/player.c ./include/player.h
	g++ -c ./src/player.c
	mv player.o ./obj/player.o

game: ./src/game.c ./include/game.h