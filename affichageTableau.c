#include <stdio.h>
#include "global.h"

/**
	* @file affichageTableau.c
	* @brief Ce fichier contient la fonctions permettant d'afficher le niveau courant.
	* @author Groupe 9
	*/

/**
  * @brief Cette fonction vient afficher le niveau courant.
	*
  * @param[in] pNiveau       Structure contenant les différents paramètres du niveau courant
  *
  * @return int
  */

void afficherNiveau(Niveau *pNiveau){
	int iLigne, iColonne;
	char c;

	for (iLigne = 0; iLigne < pNiveau->nLignes; iLigne++){
		for (iColonne = 0; iColonne < pNiveau->nColonnes + 1; iColonne++){ // + 1 pour '\n'
			c = pNiveau->tabNiveau[iLigne][iColonne];
			putchar(c);
			if (c == '\n')
				break;
		}
	}
}
