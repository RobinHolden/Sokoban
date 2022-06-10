#include <stdio.h>
#include "retourArriere.h"
#include "global.h"
#include "sauvegarde.h"

/**
* @file deplacement.c
* @brief Contient la fonction gérant les entrées clavier du joueur et qui les retranscrit en deplacements ou autres fonctionnalitées
* @author Groupe 9
*/

/** @brief Utilise les entrées clavier de l'utilisateur et les retranscrits en des deplacements, le retour arrière, la réinitialisation ou la sauvegarde
*
*@param[in] int dep	Numéro du deplacement après passage dans litClavier (1,2,3 ou 4 pour les flèches diectionelles etc...).
*@param[in] int numNiveau 	Numéro du level concerné, utilisé pour faire le déplacement dans le bon niveau.
*@param[in] char *fSauvegarde	Fichier de sauvegarde, utilisé dans le cas où S est pressé.
*
*@param[out] Niveau *pNiveau	Pointeur vers structure Niveau, utilisé pour pouvoir "deplacer" les éléments du tableau que la structure contient.
*@param[out] Dep **pile		Pointeur vers pointeur de structure Dep, utilisé pour empiler ou dépiler les déplacements du joueur au fur et à mesure.
*@param[out] int *compteurCoups		Pointeur vers int representant le nombre de coups effectués par le joueur.
*
*@return int		Retourne un entier en fonction de si l'entrée clavier à été traitée ou non
*/






int deplacement(Niveau *pNiveau, char dep, Dep **pile, int *compteurCoups, int numNiveau, char *fSauvegarde){
	switch (dep){
		case HAUT: // flèche directionnelle haut
			switch ((pNiveau->tabNiveau)[pNiveau->lJoueur - 1][pNiveau->cJoueur]){
				case MUR: // Deplacement impossible car mur devant
					return 0;
				case SOL:
				case CIBLE: // Deplacement sans poussée (seul le joueur se déplace)
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[--(pNiveau->lJoueur)][pNiveau->cJoueur] = JOUEUR;
					empilerDeplacement(1,0, pile); //premier argument : direction ; deuxième argument : poussée ou non
					(*compteurCoups)++; //incrémentation compteur de coups 
					return 0;
				case ARRIVE:
				case CAISSE:
					if (((pNiveau->tabNiveau)[pNiveau->lJoueur - 2][pNiveau->cJoueur] == MUR) || ((pNiveau->tabNiveau)[pNiveau->lJoueur - 2][pNiveau->cJoueur] == CAISSE) || ((pNiveau->tabNiveau)[pNiveau->lJoueur - 2][pNiveau->cJoueur] == ARRIVE)) // Deplacement impossible (mur, caisse, étoile)
						return 0;
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[pNiveau->lJoueur - 2][pNiveau->cJoueur] = CAISSE; // Deplacement avec poussée (le joueur et la caisse se déplacent)
					(pNiveau->tabNiveau)[--(pNiveau->lJoueur)][pNiveau->cJoueur] = JOUEUR;
					empilerDeplacement(1,1,pile);
					(*compteurCoups)++;
					return 0;
				default:
					return 1; // Erreur deplacement
			}
		case BAS: // flèche directionnelle bas
			switch ((pNiveau->tabNiveau)[pNiveau->lJoueur + 1][pNiveau->cJoueur]){
				case MUR: // Deplacement impossible
					return 0;
				case SOL:
				case CIBLE: // Deplacement sans poussée
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[++(pNiveau->lJoueur)][pNiveau->cJoueur] = JOUEUR;
					empilerDeplacement(2,0,pile);
					(*compteurCoups)++;
					return 0;
				case ARRIVE:
				case CAISSE:
					if (((pNiveau->tabNiveau)[pNiveau->lJoueur + 2][pNiveau->cJoueur] == MUR) || ((pNiveau->tabNiveau)[pNiveau->lJoueur + 2][pNiveau->cJoueur] == CAISSE) || ((pNiveau->tabNiveau)[pNiveau->lJoueur + 2][pNiveau->cJoueur] == ARRIVE)) // Deplacement impossible(mur, caisse, étoile) 
						return 0;
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[pNiveau->lJoueur + 2][pNiveau->cJoueur] = CAISSE; // Deplacement avec poussée
					(pNiveau->tabNiveau)[++(pNiveau->lJoueur)][pNiveau->cJoueur] = JOUEUR;
					empilerDeplacement(2,1,pile);
					(*compteurCoups)++;
					return 0;
				default:
					return 1; // Erreur deplacement
			}
		case DROITE: // flèche directionnelle droite
			switch ((pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur + 1]){
				case MUR: // Deplacement impossible
					return 0;
				case SOL: 
				case CIBLE: // Deplacement sans poussée
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[pNiveau->lJoueur][++(pNiveau->cJoueur)] = JOUEUR;
					empilerDeplacement(3,0,pile);
					(*compteurCoups)++;
					return 0;
				case ARRIVE:
				case CAISSE:
					if (((pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur + 2] == MUR) || ((pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur + 2] == CAISSE) || ((pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur + 2] == ARRIVE)) // Deplacement impossible (mur, caisse, étoile)
						return 0;
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur + 2] = CAISSE; // Deplacement avec poussée
					(pNiveau->tabNiveau)[pNiveau->lJoueur][++(pNiveau->cJoueur)] = JOUEUR;
					empilerDeplacement(3,1,pile);
					(*compteurCoups)++;
					return 0;
				default:
					return 1; // Erreur deplacement
			}
		case GAUCHE: // flèche directionnelle gauche
			switch ((pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur - 1]){
				case MUR: // Deplacement impossible
					return 0;
				case SOL: 
				case CIBLE: // Deplacement sans poussée
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[pNiveau->lJoueur][--(pNiveau->cJoueur)] = JOUEUR;
					empilerDeplacement(4,0,pile);
					(*compteurCoups)++;
					return 0;	
				case ARRIVE:
				case CAISSE:
					if (((pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur - 2] == MUR) || ((pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur - 2] == CAISSE) || ((pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur -  2] == ARRIVE)) // Deplacement impossible (mur, caisse, étoile)
						return 0;
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur] = SOL;
					(pNiveau->tabNiveau)[pNiveau->lJoueur][pNiveau->cJoueur - 2] = CAISSE; // Deplacement avec poussée 
					(pNiveau->tabNiveau)[pNiveau->lJoueur][--(pNiveau->cJoueur)] = JOUEUR;
					empilerDeplacement(4,1,pile);
					(*compteurCoups)++;
					return 0;
				default:
					return 1;
			}
		case R : //touche r retour en arriere
			retourArriere(pNiveau, pile, compteurCoups); 
			return 0;
		case SUPPR2 :
		case SUPPR : //touche suppression reinitialisation
			 while (((*pile)->prev) != NULL) {     //vidage de la pile de déplacement
				retourArriere(pNiveau, pile, compteurCoups);
			 }
			 *compteurCoups = 0; //reinitialisation du compteur de coups 
			return 0;
		case S:  //touche s pour sauvegarder
			sauvegarderNiveau(fSauvegarde, numNiveau, *pile, "w");
			return 2;
		default:
			return 1;
	}
	return 1;
}
