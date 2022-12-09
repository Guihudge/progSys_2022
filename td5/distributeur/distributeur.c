#include "distributeur.h"

static int indice = 0;

int distributeur_suivant()
{
    return indice ++;

}


int distributeur_valeur()
{
    return indice;
}


void raz()
{
    indice = 0;
}
