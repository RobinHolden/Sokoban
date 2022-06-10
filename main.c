#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "lectureTableau.h"
#include "affichageTableau.h"
#include "deplacement.h"
#include "io.h"
#include "positionObjectifs.h"
#include "util.h"
#include "retourArriere.h"
#include "sauvegarde.h"

int main(int argc, char *argv[])
{
	int numNiveau, *compteurCoups, d;
	char *fichierNiveaux = "levels.lvl", *fSauvegarde = ".sauvegarde", *fSolutions = ".solutions";
	Niveau *pNiveau;
	Dep *pile;

	pile = emalloc(sizeof(Dep));
	pile->prev = NULL;
	compteurCoups = emalloc(sizeof(int));
	*compteurCoups = 0;

	if ((numNiveau = detecterNumNiveau(fSauvegarde)) == 0){
		printf("Pas de numéro de niveau sauvegardé");
		numNiveau = 1;
	}
	while (numNiveau <= 88) {
		pNiveau = creerNiveau(fichierNiveaux, numNiveau);
		if (pNiveau == NULL){ // Creation niveau
			printf("Erreur création niveau %d, arrêt du programme.\n", numNiveau);
			free(compteurCoups);
			free(pile);
			return 1;
		}
		repriseSauvegarde(fSauvegarde, pNiveau, &pile, compteurCoups);
		remplacerObjectifs(pNiveau);
		if (configureTerminal())
			printf("Erreur configuration terminal\n");
		
		printf("\033[H\033[2J");
		printf("Niveau %d\nCoups : %d\n", numNiveau, *compteurCoups);
		afficherNiveau(pNiveau);

		while (verifierVictoire(pNiveau)) {
			if ((d = deplacement(pNiveau, litClavier(), &pile, compteurCoups, numNiveau, fSauvegarde)) == 1)
				printf("déplacement non permit\n");
			if (d == 2)
				break;
			remplacerObjectifs(pNiveau);
			printf("\033[H\033[2J"); //equivalent au system clear
			printf("Niveau %d\nCoups : %d\n", numNiveau, *compteurCoups);
			afficherNiveau(pNiveau);
		}
		if (d != 2)
			sauvegarderNiveau(fSolutions, numNiveau, pile, "a");
		while ((pile->prev) != NULL){
			retourArriere(pNiveau, &pile, compteurCoups);
		}
		freeNiveau(pNiveau);
		if (d == 2)
			break;
		*compteurCoups = 0;
		numNiveau++;
	}
	free(compteurCoups);
	free(pile);
	return 0;
}
