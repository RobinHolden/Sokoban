#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "deplacement.h"

/**
	* @file sauvegarde.c
	* @brief Ce fichier contient les fonctions permettant de sauvegarder le jeu et de reprendre depuis la dernière sauvegarde.
	* @author Groupe 9
	*/


/**
 * @brief La fonction vient prendre le numéro du niveau ainsi que les mouvements stockés dans la pile de la structure de déplacement pour les
 * stocker dans un fichier de sauvegarde.
 *
 * @author Groupe 9
 * @param[out] pile			 pile de stockage des déplacements
 * @param[in] numNiveau			Numéro du niveau courant
 * @return int
 */

int
sauvegarderNiveau(char *fSauvegarde, int numNiveau, Dep *pile, char *mode)
{
	FILE *wfp;
	int longStrNumNiveau;
	char *strNumNiveau;
	Dep *tampon;

	wfp = efopen(fSauvegarde, mode);
	longStrNumNiveau = (int)log10(numNiveau) + 1;
        strNumNiveau = emalloc(sizeof(char) * (longStrNumNiveau + 1));
        snprintf(strNumNiveau, longStrNumNiveau + 1, "%d", numNiveau);

	if (fputc('!', wfp) == EOF){
		free(strNumNiveau);
		efclose(wfp);
		return 1;
	}
	if (fputs(strNumNiveau, wfp) == EOF){
		free(strNumNiveau);
		efclose(wfp);
		return 1;
	}
	if (fputc(';', wfp) == EOF){
		free(strNumNiveau);
		efclose(wfp);
		return 1;
	}

	while (pile->prev != NULL){
		tampon = pile;
		pile = pile->prev;
		if (fputc(tampon->direction + 48, wfp) == EOF){
			free(strNumNiveau);
			efclose(wfp);
			return 1;
		}
	}
	if (fputc('\n', wfp) == EOF){
		free(strNumNiveau);
		efclose(wfp);
		return 1;
	}
	free(strNumNiveau);
	efclose(wfp);
	return 0;
}

/** @brief Cette fonction a pour but de verifier l'existance d'un fichier de sauvegarde.
 *
 * @param[in] fSauvegarde 			Chaine de caractère contenant le fichier de sauvegarde
 * @return int
 */

int
detecterSauvegarde(char *fSauvegarde)
{
	FILE *rfp;

	rfp = fopen(fSauvegarde, "r");
	if (rfp == NULL)
		return 1;
	if (fgetc(rfp) == EOF){
		efclose(rfp);
		return 1;
	}
	efclose(rfp);
	return 0;
}


/**
 * @brief Cette fonction permet de relancer le jeu à l'état dans lequel il a été sauvegardé
 * à l'aide du fichier sauvegarde créé précédemment.
 *
 * @param[in] fSauvegarde 			Chaine de caractère contenant le fichier de sauvegarde
 * @param[out] pile 			Pile de stockage des déplacements
 * @param[in] pNiveau				Structure contenant les différents paramètres du niveau courant
 * @param[out] compteurCoups			Compteur du nombre de déplacements effectués
 * @return int
 */

int
repriseSauvegarde(char *fSauvegarde, Niveau *pNiveau, Dep **pile, int *compteurCoups)
{
	FILE *rfp;
	int c;

	if (detecterSauvegarde(fSauvegarde)){
		printf("Aucun déplacement sauvegardé\n");
		return 1;
	}
	rfp = efopen(fSauvegarde, "r");
	fseek(rfp, -2, SEEK_END);
	while ((c = fgetc(rfp)) != ';'){
		if (c == EOF){
			efclose(rfp);
			return 1;
		}
		deplacement(pNiveau, c - 48, pile, compteurCoups, 0, fSauvegarde);
		fseek(rfp, -2, SEEK_CUR);
	}
	return 0;
}

/**
 * @brief Cette fonction permet de récupérer le numéro du niveau dont les déplacements ont étés sauvegardés à l'aide de la
 * fonction sauvegarderNiveau.
 * @param fSauvegarde Chaine de caractère contenant le fichier de sauvegarde
 *
 * @return int
 */

int
detecterNumNiveau(char *fSauvegarde)
{
	FILE *rfp;
	int c, longStrNumNiveau, numNiveau;
	char *strNumNiveau;

	if (detecterSauvegarde(fSauvegarde)){
		printf("Pas de sauvegarde trouvée");
		return 0;
	}
	longStrNumNiveau = 0;
	rfp = fopen(fSauvegarde, "r");
	if ((c = fgetc(rfp)) == EOF){
		printf("Pas de numéro de niveau dans la sauvegarde\n");
		fclose(rfp);
		return 0;
	}

	for (longStrNumNiveau = 0; (c = fgetc(rfp)) != ';'; longStrNumNiveau++){
		if (c == EOF){
			printf("Pas de numéro de niveau dans la sauvegarde\n");
			fclose(rfp);
			return 0;
		}
	}
	strNumNiveau = emalloc(sizeof(char) * (longStrNumNiveau + 1));
	fseek(rfp, 1, SEEK_SET);
	fgets(strNumNiveau, longStrNumNiveau + 1, rfp);
	numNiveau = (int)strtol(strNumNiveau, NULL, 10);
	free(strNumNiveau);
	fclose(rfp);
	return numNiveau;
}
