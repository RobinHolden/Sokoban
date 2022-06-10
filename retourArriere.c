#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "util.h"

/**
*@file retourArriere.c
*@brief Contient les fonctions d'empilage des mouvements et de retour Arrière utilisé dans deplacement.c, qui correspond à un dépilage de la pile.
*@author Groupe 9
*/

/**@brief Empile un par un les déplacements du joueur et les poussées de caisses.
*
*@param[in] char direc		Char correspondant à la direction du mouvement à empiler.
*@param[in] char depCaisse		Char correspondant à une poussée ou non de la caisse.
*
*@param[out] Dep **pile		Pointeur vers pointeur sur structure Dep, correspond à la pile dans laquelle on empile les mouvements.
*
*@return int 	Retourne 0 quand l'empilage est terminé.
*/



int empilerDeplacement(char direc,char depCaisse, Dep  **pile) {   //Fonction pour empiler un déplacement dans la pile de type Dep (cours)
	Dep *deplacement;	
	deplacement= emalloc(sizeof(Dep));
	deplacement->prev = *pile;
	deplacement->direction = direc;
	deplacement->caisse = depCaisse;
	*pile = deplacement;
	return 0;
}

/**@brief Dépile le mouvement précédent de la pile passée en argument, et réalise le mouvement inversé.
*
*@param[out] Niveau *pNiveau		Pointeur vers structure Niveau permettant de modifier le tableau pour revenir en arrière.
*@param[out] Dep **pile			Pointeur vers pointeur de structure Dep, permettant de dépiler la pile et récuperer le mouvement précédent.
*@param[out] int *compteurCoups 	Pointeur vers Int permettant de décrémenter le nombre de coups à chaque retour arrière.
*
*@return int	Renvoie un int selon si le retour arrière à été réussit ou non.
*/


int retourArriere(Niveau *pNiveau, Dep **pile, int *compteurCoups) {   //Fonction pour annuler le coup précédent
	Dep *deplacement;
	
	if ((*pile)->prev == NULL)    //pas de déplacement précédent -> situation initiale
		return 0;

	deplacement = *pile;    //dépilage du dernier déplacement
	*pile = deplacement->prev;	//Connexion de Head avec le deuxième élément
	switch (deplacement->direction) {
		case 1 :
			switch (deplacement->caisse) {
				case 0 : //On vérifie si il y a eu une poussée ou pas, puis on inverse le déplacement dépilé
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[++(pNiveau->lJoueur)][pNiveau->cJoueur] = JOUEUR;
					break;
				case 1 :
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = CAISSE;
					(pNiveau->tabNiveau)[pNiveau->lJoueur - 1][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[++(pNiveau->lJoueur)][pNiveau->cJoueur] = JOUEUR;
					break;
			}
			break;
		case 2 :
			switch (deplacement->caisse) {
				case 0 :
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[--(pNiveau->lJoueur)][pNiveau->cJoueur] = JOUEUR;
					break;
				case 1 :
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = CAISSE;
					(pNiveau->tabNiveau)[pNiveau->lJoueur + 1][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[--(pNiveau->lJoueur)][pNiveau->cJoueur] = JOUEUR;
					break;
			}
			break;
		case 3 :
			switch (deplacement->caisse) {
				case 0 :
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[(pNiveau->lJoueur)][--(pNiveau->cJoueur)] = JOUEUR;
					break;
				case 1 :
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = CAISSE;
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur + 1] = SOL;
					(pNiveau->tabNiveau)[(pNiveau->lJoueur)][--(pNiveau->cJoueur)] = JOUEUR;
					break;
			}
			break;
		case 4 :
			switch (deplacement->caisse) {
				case 0 :
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[(pNiveau->lJoueur)][++(pNiveau->cJoueur)] = JOUEUR;
					break;
				case 1 :
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = CAISSE;
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur - 1] = SOL;
					(pNiveau->tabNiveau)[(pNiveau->lJoueur)][++(pNiveau->cJoueur)] = JOUEUR;
					break;
			}
			break;
		default :
			free(deplacement); //on libère la mémoire utilisée pour le déplacement dépilé
			(*compteurCoups)--;
			return 1;
	}
	free(deplacement);
	(*compteurCoups)--;
	return 0;
}
