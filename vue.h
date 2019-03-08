#ifndef VUE_H
#define VUE_H



/****************************
	Définitions des constantes	 
*****************************/


#define CASE_X_MAX 30 			/* nombre de boutons maximal sur une ligne de la grille */
#define CASE_Y_MAX 16			/* nombre de boutons maximal sur une colonne de la grille */

#define CASE_TAILLE 50			/* taille d'une case de la grille */
#define MENU_TAILLE_X 400		/* largeur des boutons du menu */
#define MENU_TAILLE_Y 200		/* hauteur des boutons du menu */



/*********************************
	Déclaration de la structure vue	 
**********************************/


typedef struct s_vue vue;

struct s_vue{
	GtkWidget* menu;									/* la fenêtre menu */
	GtkWidget* fenetre;									/* la fenêtre principale du jeu */
	GtkWidget* grille;									/* la grille de jeu */
	GtkWidget* carre[CASE_Y_MAX][CASE_X_MAX];			/* les cases de la grille */
	GtkWidget* temps;									/* le temps écoulé */
	GtkWidget* drapeau;									/* le nombre de drapeau placé sur le nombre de mines total*/
	GtkWidget* nouvelle_partie;							/* bouton Nouvelle Partie */
	GtkWidget* rejouer;									/* bouton Rejouer */
	GtkWidget* pause;									/* bouton Pause */
	GtkWidget* aide;									/* bouton Aide */
	GtkWidget* quitter;									/* bouton Quitter */
};




/****************************************************
	Prototypes des fonctions de manipulation de la vue  
*****************************************************/


/* Accesseurs en lecture (accès aux widgets, pour les attachements faits par le contrôleur) 
	@pré-conditions pour toutes ces fonctions : 
		- à l'adresse contenue dans 'interface' se trouve une structure 'vue' instanciée	
*/




	/* @renvoie : la fenêtre principale */
GtkWidget* vue_get_fenetre(vue* interface);


	/* @renvoie : la case 'carre', de la table grille, d'indice (x,y) 
	@pré-condition : 
			- x et y sont deux entiers représentant les coordonnées de la case cliquée */
GtkWidget* vue_get_carre(vue* interface, int x, int y);


	/* @renvoie : le libelle 'temps' indiquant le temps écoulé */
GtkWidget* vue_get_temps(vue* interface);


	/* @renvoie : le libelle 'drapeau' indiquant le nombre de drapeau placé */
GtkWidget* vue_get_drapeau(vue* interface);


	/* @renvoie : le bouton 'Rejouer' */
GtkWidget* vue_get_rejouer(vue* interface);


	/* @renvoie : le bouton 'Nouvelle Partie' */
GtkWidget* vue_get_nouvelle_partie(vue* interface);


	/* @renvoie : le bouton 'Pause' */
GtkWidget* vue_get_pause(vue* interface);





/* Accesseurs en écriture 
	@pré-conditions pour toutes ces fonctions : 
		- gtk_init a été préalablement appelée
		- à l'adresse contenue dans 'interface' se trouve une structure 'vue' instanciée
*/



	/* Modifie le titre de la fenetre selon la chaîne de caractère passée en paramètre
	@pré-condition : 
		- titre est une chaîne de caractère contenant le nouveau titre de le fenêtre */
void vue_set_titre(vue* interface, char* titre);


	/* Active ou désactive le bouton 'Rejouer', selon si vrai vaut 1 ou 0 
	@pré-condition : 
		- vrai est un entier valant 0 ou 1 */
void vue_set_rejouer_active(vue* interface, int vrai);


	/* Active ou désactive le bouton 'Nouvelle Partie', selon si vrai vaut 1 ou 0 
	@pré-condition : 
		- vrai est un entier valant 0 ou 1 */
void vue_set_nouvelle_partie_active(vue* interface, int vrai);


	/* Active ou désactive le bouton 'Pause', selon si vrai vaut 1 ou 0 
	@pré-condition : 
		- vrai est un entier valant 0 ou 1 */
void vue_set_pause_active(vue* interface, int vrai);


	/* Affiche une image mine sur une case
	@pré-conditions : 
		- x et y sont deux entiers représentant les coordonnées de la case cliquée
		- vrai est un entier valant 0 ou 1 */	 
void vue_set_carre_active(vue* interface, int x, int y, int vrai);


	/* Affiche une image mine sur une case 
	@pré-conditions : 
		- x et y sont deux entiers représentant les coordonnées de la case cliquée */
void vue_set_carre_mine(vue* interface, int x, int y);


	/* Affiche une image nombre sur une case, selon la valeur de nb
	@pré-conditions : 
		- x et y sont deux entiers représentant les coordonnées de la case cliquée
		- nb est un entier représentant le nombre de mines adjacentes */
void vue_set_carre_nb(vue* interface, int x, int y, int nb);


	/* Affiche une image drapeau sur une case, selon la valeur de marque
		 marque vaut soit MARQUE_AUCUNE, MARQUE_MINE, MARQUE_MINE_INTERRO ou 3 dans le cas 
		 ou l'on révèle un drapeau mal placé
	@pré-conditions : 
		- x et y sont deux entiers représentant les coordonnées de la case cliquée
		- marque est un entier valant 0, 1, 2 ou 3 */
void vue_set_drapeau_image(vue* interface, int x, int y, int marque);


	/* Actualise l'affichage du nombre de drapeau
	@pré-condition : 
		- nb_place et nb_total sont deux entiers représentant le nombre de drapeau placé et total */
void vue_set_drapeau_nb(vue* interface, int nb_place, int nb_total);


	/* Actualise l'affichage du chronomètre 
	@pré-condition : 
		- tps est un entier représentant le nombre de secondes écoulées */
void vue_set_temps(vue* interface, int tps);




#endif