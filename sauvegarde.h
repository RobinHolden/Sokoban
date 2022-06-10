#ifndef _SAUVEGARDE_H_
#define _SAUVEGARDE_H_

#include "global.h"

/**
 * @brief La fonction vient prendre le numéro du niveau ainsi que les mouvements stockés dans la pile de la structure de déplacement pour les
 * stocker dans un fichier de sauvegarde.
 *
 * @author Groupe 9
 * @param[out] pile			 pile de stockage des déplacements
 * @param[in] numNiveau			Numéro du niveau courant
 * @return int
 */

int sauvegarderNiveau(char *fSauvegarde, int numNiveau, Dep *pile, char *mode);

/** @brief Cette fonction a pour but de verifier l'existance d'un fichier de sauvegarde.
 *
 * @param[in] fSauvegarde 			Chaine de caractère contenant le fichier de sauvegarde
 * @return int
 */

int detecterSauvegarde(char *fSauvegarde);

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

int repriseSauvegarde(char *fSauvegarde, Niveau *pNiveau, Dep **pile, int *compteurCoups);

/**
 * @brief Cette fonction permet de récupérer le numéro du niveau dont les déplacements ont étés sauvegardés à l'aide de la
 * fonction sauvegarderNiveau.
 * @param fSauvegarde Chaine de caractère contenant le fichier de sauvegarde
 *
 * @return int
 */
int detecterNumNiveau(char *fSauvegarde);

#endif
