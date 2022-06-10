#ifndef _GLOBAL_H_
#define _GLOBAL_H_

/** @brief	Structure représentant un niveau et ses différents paramètres.
 *
 * @param char **tabNiveau	Tableau à deux dimensions contenant le niveau.
 * @param int nLignes		Entier contenant le nombre de lignes du niveau.
 * @param int nColonnes		Entier contenant le nombre de colonnes du niveau.
 * @param int lJoueur		Entier contenant le numéro de ligne où se situe le joueur dans le niveau.
 * @param int cJoueur		Entier contenant le numéro de colonne où se situe le joueur dans le niveau.
 * @param int **tabCibles	Tableau à deux dimensions contenant les positions des cibles dans le niveau.
 * @param int nCibles		Entier contenant le nombre de cibles dans le niveau.
 */
typedef struct Niveau{
	char **tabNiveau;
	int nLignes;
	int nColonnes;
	int lJoueur;
	int cJoueur;
	int **tabCibles;
	int nCibles;
}Niveau;

/** @brief 	Structure représentant une liste chaînée de déplacements.
 * @param char direction	Caractère contenant la direction dans laquelle le joueur s'est déplacé.
 * @param char caisse		Caractère indiquant si une caisse a été déplacée ou non.
 * @param struct Dep *prev	Pointeur vers une structure Dep contenant le précedent déplacement.
 */
typedef struct Dep {
	char direction;
	char caisse;
	struct Dep *prev;
}Dep;
/// @brief Enumération des objets du niveau, afin qu'ils soient plus facilement lisibles.
enum objets{SOL = ' ', MUR = '#', CAISSE = '$', JOUEUR = '@', CIBLE = '.', ARRIVE = '*'};
/// @brief Enumération des entrées clavier afin qu'elles soient plus facilement lisibles.
enum touches{HAUT = 1, BAS = 2, DROITE = 3, GAUCHE = 4, R = 114, S = 115, SUPPR = 127, SUPPR2 = 8};

#endif
