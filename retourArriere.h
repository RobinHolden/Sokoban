#ifndef _RETOUR_ARRIERE_H_
#define _RETOUR_ARRIERE_H_

#include "global.h"

int empilerDeplacement(char direc, char depCaisse, Dep **pile);
int retourArriere(Niveau *pNiveau, Dep **pile, int *compteurCoups);

#endif
