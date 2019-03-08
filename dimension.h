/*
	dimension d'un jeu de démineur

	Un jeu de dimensions est caractérisé par
	- une hauteur (>= 0)
	- une largeur (>= 0)
	- un nombre de mines (>= 0) 

	Contraintes d'intégrité :
	- nombre de mines <= hauteur * largeur
*/

#ifndef DIMENSION_H

#define DIMENSION_H

/* ________
	Structures de données
*/

struct s_dimension
{
	unsigned int hauteur;
	unsigned int largeur;
	unsigned int nb_mines;	/* nb_mines <= largeur * hauteur */
};

typedef struct s_dimension dimension;

/* ________
	Fonctions de manipulation
*/

/* Accesseurs en ecriture / lecture
	Précondition pour tous : d est l'adresse d'une variable demineur
*/

/* 	Postcondition : si nb_m <= h*l, les champs hauteur, largeur et nb_mines de la variable *d valent respectivement h, l et nb_m
	Renvoie 0 si nb_m <= h*l, 1 sinon  */
int dimension_set(dimension* d, unsigned int h, unsigned int l, unsigned int nb_m);

/*	Renvoie le champ hauteur de la variable *d */
unsigned int dimension_get_hauteur(dimension* d);

/*	Renvoie le champ largeur de la variable *d */
unsigned int dimension_get_largeur(dimension* d);

/*	Renvoie le champ nb_mines de la variable *d */
unsigned int dimension_get_nb_mines(dimension* d);



#endif