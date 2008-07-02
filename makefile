
all: weapon timer player background control menu gui game ../gorgon_core/static/libgorgon.a  
	gcc					\
	./obj/weapon.o 				\
	./obj/timer.o 				\
	./obj/player.o				\
	./obj/background.o			\
	./obj/control.o				\
	./obj/menu.o				\
	./obj/gui.o				\
	./obj/game.o				\
	-o megaman.e				\
	../gorgon_core/static/libgorgon.a	\
	`allegro-config --libs`			\
	../gorgon_core/fmod/lib/libfmodex.so.4.08.08

weapon: ./src/weapon.c ./include/weapon.h
	gcc -c ./src/weapon.c
	mv weapon.o ./obj/weapon.o

timer: ./src/timer.c ./include/timer.h
	gcc -c ./src/timer.c
	mv timer.o ./obj/timer.o

player: ./src/player.c ./include/player.h
	gcc -c ./src/player.c
	mv player.o ./obj/player.o

background: ./src/background.c ./include/background.h
	gcc -c ./src/background.c
	mv background.o ./obj/background.o

control: ./src/control.c ./include/control.h
	gcc -c ./src/control.c
	mv control.o ./obj/control.o

menu: ./src/menu.c ./include/menu.h
	gcc -c ./src/menu.c
	mv menu.o ./obj/menu.o

gui: ./src/gui.c ./include/gui.h
	gcc -c ./src/gui.c
	mv gui.o ./obj/gui.o
	
game: ./src/game.c 
	gcc -c ./src/game.c
	mv game.o ./obj/game.o

clean_temp:
	rm ./include/*~
	rm ./src/*~
	rm *~
