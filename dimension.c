/*
	dimension d'un jeu de démineur : implémentation des fonctions de manipulation
*/

#include "dimension.h"

/* ________
	Accesseurs en ecriture / lecture
	Précondition pour tous : d est l'adresse d'une variable demineur
*/

/* 	Postcondition : si nb_m <= h*l, les champs hauteur, largeur et nb_mines de la variable *d valent respectivement h, l et nb_m
	Renvoie 0 si nb_m <= h*l, 1 sinon  */
int dimension_set(dimension* d, unsigned int h, unsigned int l, unsigned int nb_m)
{
	int res = 1;

	if (nb_m <= l*h)
	{
		d->hauteur = h;
		d->largeur = l;
		d->nb_mines = nb_m;

		res = 0;
	}

	return res;
}

/*	Renvoie le champ hauteur de la variable *d */
unsigned int dimension_get_hauteur(dimension* d)
{
	return d->hauteur;
}

/*	Renvoie le champ largeur de la variable *d */
unsigned int dimension_get_largeur(dimension* d)
{
	return d->largeur;
}

/*	Renvoie le champ nb_mines de la variable *d */
unsigned int dimension_get_nb_mines(dimension* d)
{
	return d->nb_mines;
}

