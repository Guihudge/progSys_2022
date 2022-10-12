ALL: exemple-essayer oui-ou-non

exemple-essayer: exemple-essayer.o essayer.o

oui-ou-non: oui-ou-non.o executer-avant-delai.o essayer.o

essayer.o : essayer.c essayer.h

exemple-essayer.o : essayer.h exemple-essayer.c

executer-avant-delai.o : executer-avant-delai.c executer-avant-delai.h essayer.h

clean: 
	rm -f essayer.o exemple-essayer.o oui-ou-non.o executer-avant-delai.o exemple-essayer oui-ou-non