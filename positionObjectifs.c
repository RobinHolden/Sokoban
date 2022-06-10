#include "global.h"

/**
	* @file positionObjectifs.c
	* @brief Ce fichier contient les fonctions permettant de vérifier la victoire du joueur, ainsi que celle permettant de remplacer les cibles correctement.
	* @author Groupe 9
	*/

/**
  * @brief Cette fonction fait en sorte que, sur les cibles, si nous n'avons rien alors on remet une cible, et si il s'agit d'une caisse
  * alors nous venons la changer pour une caisse arrivée.
  *
  * @param[in] pNiveau       Structure contenant les différents paramètres du niveau courant
  *
  * @return int
  */

int remplacerObjectifs(Niveau *pNiveau){
  int iCible;

  for (iCible = 0; iCible < pNiveau->nCibles; iCible++){

    if (pNiveau->tabNiveau[pNiveau->tabCibles[iCible][0]][pNiveau->tabCibles[iCible][1]]==SOL){
      pNiveau->tabNiveau[pNiveau->tabCibles[iCible][0]][pNiveau->tabCibles[iCible][1]]=CIBLE;
    }

    else if (pNiveau->tabNiveau[pNiveau->tabCibles[iCible][0]][pNiveau->tabCibles[iCible][1]]==CAISSE){
      pNiveau->tabNiveau[pNiveau->tabCibles[iCible][0]][pNiveau->tabCibles[iCible][1]]=ARRIVE;
    }
  }
  return 1;
}

/**
  * @brief Cette fonction fait en sorte que si nous n'avons autant de cibles au débbut que de caisses arrivées,
  * alors le niveau est compté comme réussi.
  *
  * @param[in] pNiveau       Structure contenant les différents paramètres du niveau courant
  *
  * @return int
  */

int verifierVictoire(Niveau *pNiveau){

  int iCible, arrive;

  arrive = 0;

  for (iCible = 0; iCible < pNiveau->nCibles; iCible++){
    if (pNiveau->tabNiveau[pNiveau->tabCibles[iCible][0]][pNiveau->tabCibles[iCible][1]]==ARRIVE){
      arrive++;
    }
    if (arrive==pNiveau->nCibles) return 0;
  }
  return 1;
}
