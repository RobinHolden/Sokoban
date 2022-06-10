#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "util.h"

/**
 * @file lectureTableau.c
 * @brief Contient des fonctions permettant ensemble de créer un tableau représentant un niveau donné.
 * @author Groupe 9
 */

/** @brief Place **rfp** à la fin de **strMeta** dans le fichier pointé par **rfp**.
 *
 * @param[in] char *strMeta	Chaine de caractères à trouver dans le fichier.
 * @param[out] FILE *rfp	Pointeur parcourant le fichier déjà ouvert.
 * 
 * @return int			Retourne un entier selon si la métadonnée a été trouvée.
 */
int
trouverMeta(char *strMeta, FILE *rfp)
{
	char *strComp;
	int c, longStrMeta;

	// Creation strComp
	longStrMeta = strlen(strMeta);
	strComp = emalloc(sizeof(char) * longStrMeta + 1);

	// Recherche meta
	while ((c = fgetc(rfp)) != EOF){
		if (c == ';'){
			fgets(strComp, longStrMeta + 1, rfp); // Obtenir meta
			if (!strcmp(strComp, strMeta)){ // Si bonne meta
				free(strComp);
				return 0;
			}
		}
	}
	free(strComp);
	return 1;
}

/** @brief Place **rfp** à la fin de la ligne actuelle dans le fichier pointé par **rfp**.
 * 
 * @param[out] FILE *rfp	Pointeur parcourant le fichier déjà ouvert.
 */
void
lireLigne(FILE *rfp)
{
	int c;

	while (((c = fgetc(rfp)) != EOF) && (c != '\n'));
}

/** @brief Place **rfp** juste avant le premier caractère du niveau **numNiveau**.
 *
 * @param[in] int numNiveau	Entier contenant le numéro du niveau à trouver.
 * @param[out] FILE *rfp	Pointeur parcourant le fichier déjà ouvert.
 *
 * @return int			Retourne un entier selon si le niveau a été trouvé.
 */
int
trouverNiveau(int numNiveau, FILE *rfp)
{
	char *strNiveau;
	int longStrNumNiveau, c;
	
	// Creation strNiveau
	longStrNumNiveau = (int)log10(numNiveau) + 1;
	strNiveau = emalloc(sizeof(char) * (strlen("LEVEL ") + longStrNumNiveau + 2));
	snprintf(strNiveau, strlen("LEVEL ") + longStrNumNiveau + 2, "LEVEL %d\n", numNiveau);
	
	// Recherche Niveau
	if (trouverMeta(strNiveau, rfp)){
		printf("Metadonnée \"%s\" non trouvée\n", strNiveau);
		free(strNiveau);
		return 1;
	}
	free(strNiveau);

	// Traitement d'éventuelles métadonnées
	while ((c = fgetc(rfp)) != EOF){
		if (c == ';')
			lireLigne(rfp);
		else{
			fseek(rfp, -1, SEEK_CUR);
			return 0;
		}
	}
	return 1;
}

/** @brief Détermine les dimensions **nLignes** et **nColonnes*, le nombre de caractères **n** et le nombre de cibles **nCibles** du niveau présent juste après **rfp**.
 *
 * @param[out] FILE *rfp	Pointeur parcourant le fichier déjà ouvert.
 *
 * @return int *		Retourne un "tableau" (pointeur vers entier) contenant les paramètres déterminés du niveau.
 */
int *
tailleNiveau(FILE *rfp)
{
	int nLignes, nColonnes, n, *tabTaille, nColonnesTemp, nCibles;
	int c;
	
	n = nLignes = nColonnes = nColonnesTemp = nCibles = 0;
	
	while (((c = fgetc(rfp)) != EOF) && (c != ';')){
		n++;
		if (c == '\n'){
			nLignes++;
			nColonnes = MAX(nColonnesTemp, nColonnes);
			nColonnesTemp = 0;
		}else{
			if (c == CIBLE)
				nCibles++;
			nColonnesTemp++;
		}
	}
	if (c == EOF){
		n--;
		nColonnes = MAX(nColonnesTemp, nColonnes);
	}
	if (nLignes == 0 || nColonnes == 0)
		return NULL;

	tabTaille = emalloc(4*sizeof(int));
	tabTaille[0] = nLignes;
	tabTaille[1] = nColonnes;
	tabTaille[2] = n;
	tabTaille[3] = nCibles;
	return tabTaille;
}

/** @brief Crée un "tableau" à deux dimensions du niveau **numNiveau** présent dans le fichier **fichierNiveaux**.
 * 
 * @param[in] char *fichierNiveaux	Chaîne de caractères contenant le nom du fichier de niveaux.
 * @param[in] int numNiveau		Entier contenant le numéro du niveau à transformer en tableau.
 *
 * @return Niveau *			Retourne un pointeur vers une structure Niveau complétée.
 */
Niveau *
creerNiveau(char *fichierNiveaux, int numNiveau)
{
	Niveau *pNiveau;
	FILE *rfp;
	int iLigne, iColonne, *tabTaille, iCible;
	int c;
	
	// Positionnement de rfp avant le niveau
	rfp = efopen(fichierNiveaux, "r");
	if (trouverNiveau(numNiveau, rfp)){
		efclose(rfp);
		printf("Niveau %d non trouvé\n", numNiveau);
		return NULL;
	}

	// Determination taille niveau
	if ((tabTaille = tailleNiveau(rfp)) == NULL){
		efclose(rfp);
		free(tabTaille);
		printf("Taille du niveau %d non trouvée\n", numNiveau);
		return NULL;
	}
	fseek(rfp, -(tabTaille[2] + 1), SEEK_CUR);	// Retour de rfp avant le niveau

	pNiveau = emalloc(sizeof(Niveau));
	
	// Affectation taille niveau
	pNiveau->nLignes = tabTaille[0];
	pNiveau->nColonnes = tabTaille[1];
	pNiveau->nCibles = tabTaille[3];	
	free(tabTaille);

	// Allocation mémoire tableau cibles
	pNiveau->tabCibles = emalloc(sizeof(int *) * pNiveau->nCibles);
	for (iCible = 0; iCible < pNiveau->nCibles; iCible++){
		pNiveau->tabCibles[iCible] = emalloc(sizeof(int) * 2);
	}
	iCible = 0;
	
	// Allocation mémoire tableau niveau
	pNiveau->tabNiveau = emalloc(sizeof(char *) * pNiveau->nLignes);
	for (iLigne = 0; iLigne < pNiveau->nLignes; iLigne++){
		pNiveau->tabNiveau[iLigne] = emalloc(sizeof(char) * (pNiveau->nColonnes + 1)); // + 1 pour '\n'
		for (iColonne = 0; iColonne < (pNiveau->nColonnes + 1); iColonne++){
			pNiveau->tabNiveau[iLigne][iColonne] = SOL;
		}
	}

	// Remplissage du tableau niveau
	for (iLigne = 0; iLigne < pNiveau->nLignes; iLigne++){
		for (iColonne = 0; iColonne < (pNiveau->nColonnes + 1); iColonne++){
			c = fgetc(rfp);
			pNiveau->tabNiveau[iLigne][iColonne] = c;
			if (c == JOUEUR){
				pNiveau->lJoueur = iLigne;
				pNiveau->cJoueur = iColonne;
			}else if (c == CIBLE){
				pNiveau->tabCibles[iCible][0] = iLigne;
				pNiveau->tabCibles[iCible][1] = iColonne;
				iCible++;
			}else if (c == '\n')
				break;
		}
	}

	efclose(rfp);
	return pNiveau;
}

