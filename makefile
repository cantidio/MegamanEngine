
all: weapon player background control game ../gorgon_core/static/libgorgon.a  
	gcc					\
	./obj/weapon.o 				\
	./obj/player.o				\
	./obj/background.o			\
	./obj/control.o				\
	./obj/game.o				\
	-o megaman.e				\
	../gorgon_core/static/libgorgon.a	\
	`allegro-config --libs`

weapon: ./src/weapon.c ./include/weapon.h
	gcc -c ./src/weapon.c
	mv weapon.o ./obj/weapon.o

player: ./src/player.c ./include/player.h
	gcc -c ./src/player.c
	mv player.o ./obj/player.o

background: ./src/background.c ./include/background.h
	gcc -c ./src/background.c
	mv background.o ./obj/background.o

control: ./src/control.c ./include/control.h
	gcc -c ./src/control.c
	mv control.o ./obj/control.o
game: ./src/game.c 
	gcc -c ./src/game.c
	mv game.o ./obj/game.o

clean_temp:
	rm ./include/*~
	rm ./src/*~
	rm *~
