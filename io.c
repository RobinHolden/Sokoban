#include <termios.h>
#include <unistd.h> 
#include <stdio.h>

#define MAXSIZE 10 

/**
*@file io.c
*@brief Contient les fonctions permettant de configurer le terminal en canonique (toutes les entrées sont directement envoyées vers le programme sans avoir à appuyer sur entrée) et de convertir les touches directionnelles en code ASCII utilisable.
*@author Groupe 9
*/

/**@brief Configure de terminal en canonique de manière à ce que l'appui sur entrée ne soit pas nécéssaire à chaque mouvement.
*
*@return int 		Retourne 0 si la configuration s'est bien passée.
*/

int configureTerminal()
{
	struct termios new;
	if (tcgetattr(0,&new) == -1)
		return 1;
	new.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
	new.c_lflag &= ~(ECHO);   // les touches tapées ne s'inscriront plus dans le terminal
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	if (tcsetattr(0,TCSANOW,&new) == -1)
		return 1;
	return 0;
}

/**@brief Lit la touche clavier préssée et la convertit en un char utilisable si la touche est une flèche directionnelle (1 pour haut, 2 pour bas, 3 pour droite, 4 pour gauche).
*
*@return int	Renvoit le code ASCII de la touche appuyée, convertie si c'est une flèche directionelle.
*/

int litClavier() 
{
	char r[MAXSIZE]; //Touche appuyée
	int c;

	if ((c = read(0,r,3)) == -1) //condition d'erreur
		return 0; 

	switch (r[0]) {
		case 27 : //Si la touche fait plus d'un caractère
			if ((c == 3) && (r[1] == 91)) //Si la deuxième touche est bien un crochet et que la touche possède 3 caractères
				return (r[2] - 64); //renvoit 1, 2, 3 ou 4 selon la flèche directionnelle séléctionnée
			else
				return 0;
		default:
			return r[0]; //S'il n'y a qu'un seul caractère, il est retourné
	}
}

