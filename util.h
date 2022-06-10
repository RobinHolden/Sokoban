#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include "global.h"

// Macro permettant de trouver le max de deux nombres
#define MAX(a,b) (a>b?a:b)

void *emalloc(unsigned int n);
FILE *efopen(const char *fichier, const char *mode);
void efclose(FILE *stream);
void error(const char *msg);
void freeNiveau(Niveau *pNiveau);

#endif
