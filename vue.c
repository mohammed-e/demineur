#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "vue.h"




/**************************************************
	Définitions des fonctions : Accesseurs en lecture
***************************************************/



	/* @renvoie : la fenêtre principale */
GtkWidget* vue_get_fenetre(vue* interface){

	return interface->fenetre;
}


	/* @renvoie : la case 'carre', de la table grille, d'indice (x,y) */
GtkWidget* vue_get_carre(vue* interface, int x, int y){

	return interface->carre[y][x];
}


	/* @renvoie : le libelle 'temps' indiquant le temps écoulé */
GtkWidget* vue_get_temps(vue* interface){

	return interface->temps;
}


	/* @renvoie : le libelle 'drapeau' indiquant le nombre de drapeau placé */
GtkWidget* vue_get_drapeau(vue* interface){

	return interface->drapeau;
}


	/* @renvoie : le bouton 'Rejouer' */
GtkWidget* vue_get_rejouer(vue* interface){

	return interface->rejouer;
}


	/* @renvoie : le bouton 'Nouvelle Partie' */
GtkWidget* vue_get_nouvelle_partie(vue* interface){

	return interface->nouvelle_partie;
}


	/* @renvoie : le bouton 'Pause' */
GtkWidget* vue_get_pause(vue* interface){

	return interface->pause;
}


/***************************************************
	Définitions des fonctions : Accesseurs en écriture
****************************************************/



	/* Modifie le titre de la fenetre selon la chaîne de caractère passée en paramètre */
void vue_set_titre(vue* interface, char* titre){

	gtk_window_set_title(GTK_WINDOW(vue_get_fenetre(interface)), titre);
}


	/* Active ou désactive le bouton 'Rejouer', selon si vrai vaut 1 ou 0 */
void vue_set_rejouer_active(vue* interface, int vrai){

	if(vrai)
		gtk_widget_set_sensitive(vue_get_rejouer(interface), TRUE);
	else
		gtk_widget_set_sensitive(vue_get_rejouer(interface), FALSE);
}


	/* Active ou désactive le bouton 'Nouvelle Partie', selon si vrai vaut 1 ou 0 */
void vue_set_nouvelle_partie_active(vue* interface, int vrai){

	if(vrai)
		gtk_widget_set_sensitive(vue_get_nouvelle_partie(interface), TRUE);
	else
		gtk_widget_set_sensitive(vue_get_nouvelle_partie(interface), FALSE);
}


	/* Active ou désactive le bouton 'Pause', selon si vrai vaut 1 ou 0 */
void vue_set_pause_active(vue* interface, int vrai){

	if(vrai)
		gtk_widget_set_sensitive(vue_get_pause(interface), TRUE);
	else
		gtk_widget_set_sensitive(vue_get_pause(interface), FALSE);
}


	/* Active ou désactive la case 'carre', de la grille 'table', d'indices passsés en paramètre (selon si vrai vaut 1 ou 0) */
void vue_set_carre_active(vue* interface, int x, int y, int vrai){

	if(vrai)
		gtk_widget_set_sensitive(vue_get_carre(interface, x, y), TRUE);
	else
		gtk_widget_set_sensitive(vue_get_carre(interface, x, y), FALSE);
}


	/* Affiche une image mine sur une case */
void vue_set_carre_mine(vue* interface, int x, int y){

	GtkWidget* image_mine = NULL;

	image_mine = gtk_image_new_from_file("images/mine.png");

	gtk_button_set_image(GTK_BUTTON(vue_get_carre(interface, x, y)), image_mine);
}


	/* Affiche une image nombre sur une case, selon la valeur de nb */
void vue_set_carre_nb(vue* interface, int x, int y, int nb){

	GtkWidget* image_nb = NULL;

	switch(nb){
		case 0:
			image_nb = gtk_image_new_from_file("images/defaut.png"); break;
		case 1:
			image_nb = gtk_image_new_from_file("images/un.png"); break;
		case 2:
			image_nb = gtk_image_new_from_file("images/deux.png"); break;
		case 3:
			image_nb = gtk_image_new_from_file("images/trois.png"); break;
		case 4:
			image_nb = gtk_image_new_from_file("images/quatre.png"); break;
		case 5:
			image_nb = gtk_image_new_from_file("images/cinq.png"); break;
		case 6:
			image_nb = gtk_image_new_from_file("images/six.png"); break;
		case 7:
			image_nb = gtk_image_new_from_file("images/sept.png"); break;
		case 8:
			image_nb = gtk_image_new_from_file("images/huit.png"); break;	
	}

	gtk_button_set_image(GTK_BUTTON(vue_get_carre(interface, x, y)), image_nb);
}


	/* Affiche une image drapeau sur une case, selon la valeur de marque
		 marque vaut soit MARQUE_AUCUNE, MARQUE_MINE, MARQUE_MINE_INTERRO ou 3 dans le cas 
		 ou l'on révèle un drapeau mal placé */
void vue_set_drapeau_image(vue* interface, int x, int y, int marque){

	GtkWidget* image_drapeau = NULL;

	switch(marque){
		/* MARQUE_AUCUNE */
		case 0:
			gtk_image_clear(GTK_IMAGE(gtk_button_get_image(GTK_BUTTON(vue_get_carre(interface, x, y))))); 
			break;
		/* MARQUE_MINE */
		case 1:
			image_drapeau = gtk_image_new_from_file("images/flag.png"); 
			gtk_button_set_image(GTK_BUTTON(vue_get_carre(interface, x, y)), image_drapeau);
			break;
		/* MARQUE_MINE_INTERRO */
		case 2:
			image_drapeau = gtk_image_new_from_file("images/flag_interro.png"); 
			gtk_button_set_image(GTK_BUTTON(vue_get_carre(interface, x, y)), image_drapeau);
			break;
		/* MARQUE_MINE faux */
		case 3:
			image_drapeau = gtk_image_new_from_file("images/flag_false.png"); 
			gtk_button_set_image(GTK_BUTTON(vue_get_carre(interface, x, y)), image_drapeau);
			break;
	}
}


	/* Actualise l'affichage du nombre de drapeau */
void vue_set_drapeau_nb(vue* interface, int nb_place, int nb_total){

	char flag[CASE_TAILLE] = "";

	sprintf(flag, "%d / %d", nb_place, nb_total);
	gtk_label_set_text(GTK_LABEL(vue_get_drapeau(interface)), flag);
}


	/* Actualise l'affichage du chronomètre */
void vue_set_temps(vue* interface, int tps){
	
	char time[CASE_TAILLE] = "";
	int min = 0, sec = 0;

	min = tps/60;
	sec = tps%60;

	sprintf(time, "%d : %d", min, sec);
	gtk_label_set_text(GTK_LABEL(vue_get_temps(interface)), time);
}
