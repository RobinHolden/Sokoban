#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

/**
 * @file util.c
 * @brief Contient des fonctions utilitaires, comme une version de malloc avec gestion d'erreurs ou une fonction permettant de libérer la mémoire utilisée par une sructure Niveau.
 *
 * @author Groupe 9
 */

/** @brief Execute **perror** avec **msg** en argument et quitte le programme.
 * 
 * @param[in] const char *msg	Chaîne de caractères contenant le message d'erreur à utiliser.
 */
void
error(const char *msg)
{
	perror(msg);
	exit(1);
}

/** @brief Execute **malloc** avec **nbits** en paramètre et fait appel à **error** s'il y a échec.
 *
 * @param[in] unsigned int nbits	Entier non signé contenant le nombre de bits à allouer.
 */
void *
emalloc(unsigned int nbits){
	void *p;
	
	if ((p = malloc(nbits)) == NULL)
		error("malloc");
	return p;
}
/** @brief Execute **fopen** avec **fichier** et **mode** en paramètres et fait appel à **error** s'il y a échec.
 *
 * @param[in] const char *fichier	Chaîne de caractères contenant le nom du fichier.
 * @param[in] const char *mode		Chaîne de caractères contenant le mode d'ouverture du fichier.
 *
 * @return FILE *			Retourne un pointeur vers FILE correspondant au fichier ouvert.
 */
FILE *
efopen(const char *fichier, const char *mode){
	FILE *fp;

	if ((fp = fopen(fichier, mode)) == NULL)
		error("fopen");
	return fp;
}

/** @brief Execute **fclose** avec **stream** en paramètre et fait appel à **error** s'il y a échec.
 *
 * @param[in] FILE *stream	Pointeur vers FILE représentant le flux à fermer.
 */
void
efclose(FILE *stream){
	if (fclose(stream) == EOF)
		error("fclose");
}

/** @brief Libère la mémoire utilisée par une la structure **pNiveau** complétée.
 *
 * @param[out] Niveau *pNiveau	Structure dont la mémoire doit être libérée.
 */
void
freeNiveau(Niveau *pNiveau)
{
	int iLigne, iCible;

	for (iLigne = 0; iLigne < pNiveau->nLignes; iLigne++)
		free(pNiveau->tabNiveau[iLigne]);
	free(pNiveau->tabNiveau);
	for (iCible = 0; iCible < pNiveau->nCibles; iCible++)
		free(pNiveau->tabCibles[iCible]);
	free (pNiveau->tabCibles);
	free(pNiveau);
}

