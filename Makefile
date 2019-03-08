CC=gcc
CFLAGS=-W -Wall -Wextra 
CFLAGS_GTK=`pkg-config gtk+-2.0 --cflags` -W -Wall -Wextra
LDFLAGS=`pkg-config gtk+-2.0 --libs`
EXEC=demineur.exe


all: $(EXEC)


$(EXEC): dimension.o case.o demineur.o vue.o ctrl.o demineur_gtk.o
	$(CC) $^ -o $@ $(LDFLAGS)


dimension.o: dimension.c dimension.h
	$(CC) -c $< -o $@ $(CFLAGS)


case.o: case.c case.h
	$(CC) -c $< -o $@ $(CFLAGS)


demineur.o: demineur.c dimension.h case.h demineur.h
	$(CC) -c $< -o $@ $(CFLAGS)


vue.o: vue.c vue.h
	$(CC) -c $< -o $@ $(CFLAGS_GTK)


ctrl.o: ctrl.c ctrl.h demineur.h vue.h
	$(CC) -c $< -o $@ $(CFLAGS_GTK)


demineur_gtk.o: demineur_gtk.c demineur.h vue.h ctrl.h
	$(CC) -c $< -o $@ $(CFLAGS_GTK)


clean:
	rm -rf *.o *~


mrproper: clean
	rm -rf $(EXEC)


play:
	./$(EXEC)
