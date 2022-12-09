CFLAGS += -g -D_REENTRANT
LDLIBS = -lpthread

distribuer: distribuer.o distributeur.o
distribuer.o: distribuer.c distributeur.h 
distributeur.o: distributeur.h distributeur.c 

clean:
	rm *.o distribuer
