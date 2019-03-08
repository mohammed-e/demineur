#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "demineur.h"
#include "vue.h"
#include "ctrl.h"




/******************************************
	Définitions des fonctions de construction
*******************************************/


	/* Créer le menu de départ de choix du niveau */
void ctrl_vue_menu(ctrl* partie){

	/* Déclarations des variables */

	vue *interface = (vue*)malloc(sizeof(vue));

	GtkWidget* conteneur_boutons = NULL;
	GtkWidget* conteneur_boutons_left = NULL;
	GtkWidget* conteneur_boutons_center = NULL;
	GtkWidget* conteneur_boutons_right = NULL;

	GtkWidget* debutant = NULL;
	GtkWidget* moyen = NULL;
	GtkWidget* expert = NULL;
	GtkWidget* logo = NULL;
	GtkWidget* quitter = NULL;

	/* couleur des boutons */
	GdkColor couleur_fond;
	GdkColor couleur_debutant;
	GdkColor couleur_moyen;
	GdkColor couleur_expert;
	GdkColor couleur_quitter;
	gdk_color_parse("#F5ECCE", &couleur_fond);
  gdk_color_parse("#F7BE81", &couleur_debutant);
  gdk_color_parse("#F79F81", &couleur_moyen);
  gdk_color_parse("#F78181", &couleur_expert);
  gdk_color_parse("#D8D8D8", &couleur_quitter);
  

	/* Menu */

	interface->menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(interface->menu), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_title(GTK_WINDOW(interface->menu), "Démineur");
	gtk_widget_modify_bg(interface->menu, GTK_STATE_NORMAL, &couleur_fond);

	g_signal_connect(G_OBJECT(interface->menu), "destroy", G_CALLBACK(gtk_main_quit), NULL);


	/** conteneur_boutons **/

	conteneur_boutons = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(interface->menu), conteneur_boutons);


	/** conteneur_boutons_left **/

	conteneur_boutons_left = gtk_vbox_new(TRUE, 50);
	gtk_box_pack_start(GTK_BOX(conteneur_boutons), conteneur_boutons_left, FALSE, FALSE, 25);


	/** conteneur_boutons_center **/

	conteneur_boutons_center = gtk_vbox_new(TRUE, 0);
	gtk_box_pack_start(GTK_BOX(conteneur_boutons), conteneur_boutons_center, FALSE, FALSE, 0);	


	/** conteneur_boutons_right **/

	conteneur_boutons_right = gtk_vbox_new(TRUE, 50);
	gtk_box_pack_start(GTK_BOX(conteneur_boutons), conteneur_boutons_right, FALSE, FALSE, 25);


	/*** debutant ***/

	debutant = gtk_button_new_with_label("Débutant");
	gtk_widget_set_size_request(debutant, MENU_TAILLE_X, MENU_TAILLE_Y);
	gtk_box_pack_start(GTK_BOX(conteneur_boutons_left), debutant, FALSE, TRUE,	25);
	gtk_widget_modify_bg(debutant, GTK_STATE_PRELIGHT, &couleur_debutant);

	g_signal_connect(G_OBJECT(debutant), "clicked", G_CALLBACK(cback_choix), partie);


	/*** moyen ***/

	moyen = gtk_button_new_with_label("Moyen");
	gtk_widget_set_size_request(moyen, MENU_TAILLE_X, MENU_TAILLE_Y);
	gtk_box_pack_start(GTK_BOX(conteneur_boutons_right), moyen, FALSE, TRUE,	25);
	gtk_widget_modify_bg(moyen, GTK_STATE_PRELIGHT, &couleur_moyen);

	g_signal_connect(G_OBJECT(moyen), "clicked", G_CALLBACK(cback_choix), partie);


	/*** expert ***/

	expert = gtk_button_new_with_label("Expert");
	gtk_widget_set_size_request(expert, MENU_TAILLE_X, MENU_TAILLE_Y);
	gtk_box_pack_start(GTK_BOX(conteneur_boutons_left), expert, FALSE, TRUE,	25);
	gtk_widget_modify_bg(expert, GTK_STATE_PRELIGHT, &couleur_expert);

	g_signal_connect(G_OBJECT(expert), "clicked", G_CALLBACK(cback_choix), partie);


	/*** logo ***/

	logo = gtk_image_new_from_file("images/logo.png");
	gtk_box_pack_start(GTK_BOX(conteneur_boutons_center), logo, FALSE, TRUE,	0);


	/*** quitter ***/

	quitter = gtk_button_new_with_label("Quitter");
	gtk_widget_set_size_request(quitter, MENU_TAILLE_X, MENU_TAILLE_Y);
	gtk_box_pack_start(GTK_BOX(conteneur_boutons_right), quitter, FALSE, TRUE,	25);
	gtk_widget_modify_bg(quitter, GTK_STATE_PRELIGHT, &couleur_quitter);

	g_signal_connect(G_OBJECT(quitter), "clicked", G_CALLBACK(gtk_main_quit), NULL);


	/** fin **/

	gtk_widget_show_all(interface->menu);

}


	/* Construction : construit, initialise et imbrique les widget de la fenêtre de jeu */
void ctrl_vue_construire(ctrl* partie){

	/* Déclarations des variables */

	unsigned int i = 0, j = 0;
	char drapeau[CASE_Y_MAX] = ""; 	/* permet d'afficher le nombre de drapeau total en début de partie */

	GtkWidget* conteneur_principale = NULL;
	GtkWidget* conteneur_info = NULL;
	GtkWidget* conteneur_temps = NULL;
	GtkWidget* conteneur_drapeau = NULL;
	GtkWidget* conteneur_boutons = NULL;

	GtkWidget* icone_temps = NULL;
	GtkWidget* icone_drapeau = NULL;

	
	/* couleur des boutons */
	GdkColor couleur_fond;
	GdkColor couleur_case;
	GdkColor couleur_aide;
	GdkColor couleur_boutons;
	gdk_color_parse("#F5ECCE", &couleur_fond);
  gdk_color_parse("#CED8F6", &couleur_case);
  gdk_color_parse("#F78181", &couleur_aide);
  gdk_color_parse("#D8D8D8", &couleur_boutons);


	/* Fenetre */

	partie->interface->fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(partie->interface->fenetre), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_title(GTK_WINDOW(partie->interface->fenetre), "Démineur");
	gtk_widget_modify_bg(partie->interface->fenetre, GTK_STATE_NORMAL, &couleur_fond);

	g_signal_connect(G_OBJECT(partie->interface->fenetre), "destroy", G_CALLBACK(cback_quitter), NULL);


	/* conteneur_principale */

	conteneur_principale = gtk_hbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(partie->interface->fenetre), conteneur_principale);


	/** grille **/

	partie->interface->grille = gtk_table_new(dimension_get_largeur(&(partie->modele->dim)), dimension_get_hauteur(&(partie->modele->dim)), FALSE);
	gtk_box_pack_start(GTK_BOX(conteneur_principale), partie->interface->grille, TRUE, TRUE, 50);


	/** carre **/

	for(i = 0; i < dimension_get_hauteur(&(partie->modele->dim)); i++){
		for(j = 0; j < dimension_get_largeur(&(partie->modele->dim)); j++){
			partie->interface->carre[i][j] = gtk_button_new();

			/* définition de la taille des cases en fonction de la difficulté */
			if((int)dimension_get_nb_mines(&(partie->modele->dim)) == 10)
				gtk_widget_set_size_request(partie->interface->carre[i][j], CASE_TAILLE, CASE_TAILLE);
			else if((int)dimension_get_nb_mines(&(partie->modele->dim)) == 40)
				gtk_widget_set_size_request(partie->interface->carre[i][j], CASE_TAILLE-10, CASE_TAILLE-10);
			else
				gtk_widget_set_size_request(partie->interface->carre[i][j], CASE_TAILLE-15, CASE_TAILLE-15);

			/* attachement des case à la table */
			gtk_table_attach(GTK_TABLE(partie->interface->grille), partie->interface->carre[i][j], j, j+1, i, i+1, GTK_EXPAND|GTK_FILL, GTK_EXPAND|GTK_FILL, 1, 1);

			/* coloration des cases */
			gtk_widget_modify_bg(partie->interface->carre[i][j], GTK_STATE_PRELIGHT, &couleur_case);

			partie->grille[i][j].parent = partie;
  		partie->grille[i][j].y = i;
  		partie->grille[i][j].x = j;

			g_signal_connect(G_OBJECT(partie->interface->carre[i][j]), "button-press-event", G_CALLBACK(cback_carre_clique), &partie->grille[i][j]);
		}
	}


	/** conteneur_info **/

	conteneur_info = gtk_vbox_new(FALSE, 20);
	gtk_box_pack_start(GTK_BOX(conteneur_principale), conteneur_info, FALSE, FALSE, 25);


	/*** conteneur_temps ***/

	conteneur_temps = gtk_vbox_new(FALSE, 20);
	gtk_box_pack_start(GTK_BOX(conteneur_info), conteneur_temps, FALSE, FALSE, 20);

	/**** icone_temps ****/

	icone_temps = gtk_image_new_from_file("images/chrono.png"); 
	gtk_box_pack_start(GTK_BOX(conteneur_temps), icone_temps, FALSE, FALSE,	0);

	/**** temps ****/

	partie->interface->temps = gtk_label_new("0 : 0");
	gtk_box_pack_start(GTK_BOX(conteneur_temps), partie->interface->temps, FALSE, FALSE,	0);


	/*** conteneur_drapeau ***/

	conteneur_drapeau = gtk_vbox_new(FALSE, 20);
	gtk_box_pack_start(GTK_BOX(conteneur_info), conteneur_drapeau, FALSE, FALSE, 0);

	/**** icone_drapeau ****/

	icone_drapeau = gtk_image_new_from_file("images/flag.png"); 
	gtk_box_pack_start(GTK_BOX(conteneur_drapeau), icone_drapeau, FALSE, FALSE,	0);

	/**** drapeau ****/

	sprintf(drapeau, "0 / %d", (int)dimension_get_nb_mines(&(partie->modele->dim)));
	partie->interface->drapeau = gtk_label_new(drapeau);
	gtk_box_pack_start(GTK_BOX(conteneur_drapeau), partie->interface->drapeau, FALSE, FALSE,	0);


	/*** conteneur_boutons ***/

	conteneur_boutons = gtk_vbox_new(FALSE, 20);
	gtk_box_pack_start(GTK_BOX(conteneur_info), conteneur_boutons, FALSE, FALSE, 20);

	/**** nouvelle_partie ****/

	partie->interface->nouvelle_partie = gtk_button_new_with_label("Nouvelle Partie");
	gtk_box_pack_start(GTK_BOX(conteneur_boutons), partie->interface->nouvelle_partie, FALSE, FALSE,	0);
	vue_set_nouvelle_partie_active(partie->interface, 0);
	gtk_widget_modify_bg(partie->interface->nouvelle_partie, GTK_STATE_PRELIGHT, &couleur_boutons);

	g_signal_connect(G_OBJECT(partie->interface->nouvelle_partie), "clicked", G_CALLBACK(cback_nouvelle_partie), partie);


	/**** rejouer ****/

	partie->interface->rejouer = gtk_button_new_with_label("Rejouer");
	gtk_box_pack_start(GTK_BOX(conteneur_boutons), partie->interface->rejouer, FALSE, FALSE,	0);
	vue_set_rejouer_active(partie->interface, 0);
	gtk_widget_modify_bg(partie->interface->rejouer, GTK_STATE_PRELIGHT, &couleur_boutons);

	g_signal_connect(G_OBJECT(partie->interface->rejouer), "clicked", G_CALLBACK(cback_rejouer), partie);


	/**** pause ****/

	partie->interface->pause = gtk_button_new_with_label("Pause");
	gtk_box_pack_start(GTK_BOX(conteneur_boutons), partie->interface->pause, FALSE, FALSE,	0);
	vue_set_pause_active(partie->interface, 0);
	gtk_widget_modify_bg(partie->interface->pause, GTK_STATE_PRELIGHT, &couleur_boutons);

	g_signal_connect(G_OBJECT(partie->interface->pause), "clicked", G_CALLBACK(cback_pause), partie);


	/**** aide ****/

	partie->interface->aide = gtk_button_new_with_label("Activer Aide");
	gtk_box_pack_start(GTK_BOX(conteneur_boutons), partie->interface->aide, FALSE, FALSE,	0);
	gtk_widget_modify_bg(partie->interface->aide, GTK_STATE_PRELIGHT, &couleur_boutons);

	g_signal_connect(G_OBJECT(partie->interface->aide), "clicked", G_CALLBACK(cback_aide), partie);


	/**** quitter ****/

	partie->interface->quitter = gtk_button_new_with_label("Quitter");
	gtk_box_pack_start(GTK_BOX(conteneur_boutons), partie->interface->quitter, FALSE, FALSE,	0);
	gtk_widget_modify_bg(partie->interface->quitter, GTK_STATE_PRELIGHT, &couleur_boutons);

	g_signal_connect(G_OBJECT(partie->interface->quitter), "clicked", G_CALLBACK(cback_quitter), NULL);


	/* Fin */

	gtk_widget_show_all(partie->interface->fenetre);
}




/************************************
	Définitions des fonctions de rappel 
*************************************/



	/* Initialise une partie en initialisant le modèle, selon le choix de l'utilisateur, et la vue,
		 lorsque l'utilisateur sélectionne son niveau dans le menu en cliquant le bouton voulu */
void cback_choix(GtkWidget* bouton, ctrl* data){

	demineur_niveau niveau;
	char *choix = (char*)gtk_button_get_label(GTK_BUTTON(bouton));
	data->interface->menu = gtk_widget_get_toplevel(bouton);

	/* on fait disparaître la fenêtre du menu */
	gtk_widget_hide(data->interface->menu);

	if(strcmp(choix, "Débutant") == 0)
		niveau = DEMINEUR_NIVEAU_DEBUTANT;
	else if(strcmp(choix, "Moyen") == 0)
		niveau = DEMINEUR_NIVEAU_MOYEN;
	else
		niveau = DEMINEUR_NIVEAU_EXPERT;

	/* on construit le modèle selon la difficulté choisie */
	demineur_set_niveau(data->modele, niveau);
	/* on construit la fenêtre de jeu */
	ctrl_vue_construire(data);
}


	/* Appelle la fonction ctrl_jouer_coup lors d'un clic gauche sur une case, et ctrl_drapeau_placer si clic droit */
gboolean cback_carre_clique(GtkWidget* carre, GdkEventButton* clic, ctrl_case* data){

	/* Clic gauche et partie en cours */
	if(clic->button == 1 && gtk_widget_is_sensitive(data->parent->interface->rejouer) == FALSE){
		gtk_widget_set_sensitive(carre, FALSE);
		ctrl_jouer_coup(data->parent, data->x, data->y);
	}
	/* Clic droit */
	else if(clic->button == 3){
		ctrl_drapeau_placer(data->parent, data->x, data->y);
		/* on actualise le nombre de drapeau que si le nombre maximal n'est pas atteint */
		if((int)dimension_get_nb_mines(&(data->parent->modele->dim)) >= demineur_get_nb_mines_restant_a_deviner(data->parent->modele))
			vue_set_drapeau_nb(data->parent->interface, (int)dimension_get_nb_mines(&(data->parent->modele->dim)) - demineur_get_nb_mines_restant_a_deviner(data->parent->modele), (int)dimension_get_nb_mines(&(data->parent->modele->dim)));
	}
	else{} ;

	return FALSE;
}


	/* Initialise une nouvelle partie en affichant le menu de départ (fonction appelée lors d'un clic sur le bouton 'Nouvelle Partie') */
void cback_nouvelle_partie(GtkWidget* nouvelle_partie, ctrl* data){

	gtk_widget_set_sensitive(nouvelle_partie, FALSE);

	/* on fait disparaître la fenêtre de jeu actuelle */
	gtk_widget_hide(data->interface->fenetre);

	/* on réinitialise le modèle et le temps */
	data->modele = demineur_construire();
  initialiser_temps(data->timer);

  /* on construit une nouvelle fenêtre */
  ctrl_vue_menu(data);
}


/* Réinitialise la partie en cours dans le modèle, puis nettoie la vue (fonction appelée lors d'un clic sur le bouton 'Rejouer') */
void cback_rejouer(GtkWidget* rejouer, ctrl* data){

	int i = 0, j = 0;
	/* couleurs des cases */
	GdkColor couleur_case;
  gdk_color_parse("#CED8F6", &couleur_case);

	/* on désactive les boutons qui doivent l'être en début de partie */
	gtk_widget_set_sensitive(rejouer, FALSE);
	vue_set_nouvelle_partie_active(data->interface, 0);
	vue_set_pause_active(data->interface, 0);
	/* on réinitialise l'affichage du temps et des drapeaux */
	vue_set_temps(data->interface, 0);
	vue_set_drapeau_nb(data->interface, 0, (int)dimension_get_nb_mines(&(data->modele->dim)));
	/* on réinitialise les libellés */
	gtk_window_set_title(GTK_WINDOW(data->interface->fenetre), "Démineur");
	gtk_button_set_label(GTK_BUTTON(data->interface->pause), "Pause");


	/* on nettoie la grille */
	for(j = 0 ; j < (int)dimension_get_hauteur(&(data->modele->dim)) ; j++){
		for(i = 0 ; i < (int)dimension_get_largeur(&(data->modele->dim)) ; i++){
			/* suppression des couleurs des cases cliquées */
			gtk_widget_modify_bg(data->interface->carre[j][i], GTK_STATE_INSENSITIVE, 0);
			/* activation des boutons cliqués */
			vue_set_carre_active(data->interface, i, j, 1);
			if(gtk_button_get_image(GTK_BUTTON(data->interface->carre[j][i])) != NULL)
				/* suppression des images affichées */
				gtk_image_clear(GTK_IMAGE(gtk_button_get_image(GTK_BUTTON(data->interface->carre[j][i]))));
			/* réinitialisation des couleurs sans aide */
			gtk_widget_modify_bg(data->interface->carre[j][i], GTK_STATE_PRELIGHT, &couleur_case);
		}
	}

	/* on réinitialise le modèle en fonction du nombre de mines donc du niveau */
	demineur_nouvelle_partie(data->modele);
	/* on réinitialise le temps */
  initialiser_temps(data->timer);
  /* on réinitialise le libellé aide */
  gtk_button_set_label(GTK_BUTTON(data->interface->aide), "Activer Aide");
}


	/* Démarre ou arrête le chronomètre selon le libellé du bouton Pause (fonction appelée lors d'un clic sur le bouton 'Pause') */
void cback_pause(GtkWidget* pause, ctrl* data){

	/* quand le jeu est en pause */
	if(strcmp(gtk_button_get_label(GTK_BUTTON(data->interface->pause)), "Pause") == 0){
		/* le temps s'arrête */
		stop_chrono(data);
		/* on change le libellé */
		gtk_button_set_label(GTK_BUTTON(pause), "Reprendre");
		/* les boutons Rejouer et Nouvelle Partie sont activés */
		vue_set_rejouer_active(data->interface, 1);
		vue_set_nouvelle_partie_active(data->interface, 1);
	}
	/* quand le jeu reprend */
	else{
		/* le temps redémarre */
		start_chrono(data);
		/* on remet le libellé à la normal */
		gtk_button_set_label(GTK_BUTTON(pause), "Pause");
		/* les boutons Rejouer et Nouvelle Partie sont de nouveaux inactifs */
		vue_set_rejouer_active(data->interface, 0);
		vue_set_nouvelle_partie_active(data->interface, 0);
	}
}


	/* Démarre ou arrête l'aide selon le libelle du bouton Aide
	@pré-condition : 
		- aide est l'adresse d'un GtkWidget */
void cback_aide(GtkWidget* aide, ctrl* data){

	int i = 0, j = 0;
	/* couleurs des cases */
	GdkColor couleur_case;
	GdkColor couleur_aide;
  gdk_color_parse("#CED8F6", &couleur_case);
  gdk_color_parse("#F78181", &couleur_aide);

  /* quand l'aide est activée */
	if(strcmp(gtk_button_get_label(GTK_BUTTON(aide)), "Activer Aide") == 0){
		/* on change le libellé */
		gtk_button_set_label(GTK_BUTTON(aide), "Désactiver Aide");
		/* on active la coloration des cases selon la présence des mines */
		for(j = 0 ; j < (int)dimension_get_hauteur(&(data->modele->dim)) ; j++){
			for(i = 0 ; i < (int)dimension_get_largeur(&(data->modele->dim)) ; i++){
				if(demineur_case_est_minee(data->modele, j, i))
					gtk_widget_modify_bg(data->interface->carre[j][i], GTK_STATE_PRELIGHT, &couleur_aide);
				else
					gtk_widget_modify_bg(data->interface->carre[j][i], GTK_STATE_PRELIGHT, &couleur_case);
			}
		}
	}
	/* quand l'aide est désactivée */
	else{
		/* on remet le libellé à la normal */
		gtk_button_set_label(GTK_BUTTON(aide), "Activer Aide");
		/* on active la coloration simple des cases */
		for(j = 0 ; j < (int)dimension_get_hauteur(&(data->modele->dim)) ; j++){
			for(i = 0 ; i < (int)dimension_get_largeur(&(data->modele->dim)) ; i++)
				gtk_widget_modify_bg(data->interface->carre[j][i], GTK_STATE_PRELIGHT, &couleur_case);
		}
	}
}


	/* Comptabilise les secondes passées depuis le premier clic puis synchronise la vue */
gint cback_temps(ctrl* data){

	if(data->timer->booleen_temps){
		data->timer->tps++;
		vue_set_temps(data->interface, data->timer->tps);
		return data->timer->booleen_temps;	/* cette fonction n'est plus appelée quand le booléen est faux */
	}
	return data->timer->booleen_temps;
}


	/* Libère la mémoire allouée pour le contrôleur, la vue et le modèle et quitte la boucle événementielle 
(fonction appelée lors d'un clic sur le bouton 'Quitter' ou sur la croix de la fenêtre principale) */
void cback_quitter(GtkWidget* quitter, ctrl* data){

	if (data != NULL){
		gtk_widget_set_sensitive(quitter, FALSE);

		demineur_detruire(&(data->modele));

		free(data->interface);
		data->interface = NULL;

		free(data);
		data = NULL;
	}

	gtk_main_quit();
}



/******************************************
	Définitions des fonctions de manipulation
*******************************************/


	/* Joue un coup dans le modèle, puis synchronise la vue (fonction appelée lors d'un clic gauche sur un bouton 'carre') */
void ctrl_jouer_coup(ctrl* partie, int x, int y){

	unsigned int i = 0, j = 0;
	/* couleur de la case minée cliquée */
	GdkColor couleur_mine;
  gdk_color_parse("#F78181", &couleur_mine);

	/* si la partie n'est pas fini, on peut jouer */
	if(gtk_widget_is_sensitive(partie->interface->rejouer) == FALSE){

		/* dès que l'on commence la partie en cliquant sur une case, le chrono démarre et on peut faire pause */
		start_chrono(partie);
		vue_set_pause_active(partie->interface, 1);

		/* on dévoile la case dans le modèle */
		demineur_case_devoiler(partie->modele, y, x);


		/* on synchronise la vue */

		/* si la case cliquée est minée */
		if(demineur_case_est_minee(partie->modele, y, x)){
			
			for(j = 0 ; j < dimension_get_hauteur(&(partie->modele->dim)) ; j++){
				for(i = 0 ; i < dimension_get_largeur(&(partie->modele->dim)) ; i++){

					/* on laisse les bons drapeau affichés et on affiche toutes les mines */
					if(demineur_case_est_minee(partie->modele, j, i)){

						if(demineur_case_get_marque_joueur(partie->modele, j, i) == MARQUE_MINE)
							vue_set_drapeau_image(partie->interface, i, j, MARQUE_MINE);
						else
							vue_set_carre_mine(partie->interface, i, j);
					}
					/* on supprime les marquages ? et on indique les mauvais drapeaux */
					else{
						if(demineur_case_get_marque_joueur(partie->modele, j, i) == MARQUE_MINE_INTERRO)
							gtk_image_clear(GTK_IMAGE(gtk_button_get_image(GTK_BUTTON(partie->interface->carre[j][i]))));
						else if(demineur_case_get_marque_joueur(partie->modele, j, i) == MARQUE_MINE && !demineur_case_est_devoilee(partie->modele, j, i))
							vue_set_drapeau_image(partie->interface, i, j, 3);
						else{} ;
					}
				}
			}
			/* on affiche la mine cliquée différente */
			vue_set_carre_mine(partie->interface, x, y);
			gtk_widget_modify_bg(partie->interface->carre[y][x], GTK_STATE_INSENSITIVE, &couleur_mine);
		}

		/* si la case cliquée n'est pas minée (donc dévoilée) */
		else if(demineur_case_est_devoilee(partie->modele, y, x)){

			for(j = 0 ; j < dimension_get_hauteur(&(partie->modele->dim)) ; j++){
				for(i = 0 ; i < dimension_get_largeur(&(partie->modele->dim)) ; i++){

					/* on supprime les marquages inutiles et on dévoile la case */
					if(demineur_case_est_devoilee(partie->modele, j, i)){
						
						if(demineur_case_get_marque_joueur(partie->modele, j, i) == MARQUE_MINE || demineur_case_get_marque_joueur(partie->modele, j, i) == MARQUE_MINE_INTERRO){
							gtk_image_clear(GTK_IMAGE(gtk_button_get_image(GTK_BUTTON(partie->interface->carre[j][i]))));
							vue_set_drapeau_nb(partie->interface, (int)dimension_get_nb_mines(&(partie->modele->dim)) - demineur_get_nb_mines_restant_a_deviner(partie->modele), (int)dimension_get_nb_mines(&(partie->modele->dim)));
						}
						vue_set_carre_active(partie->interface, i, j, 0);
						vue_set_carre_nb(partie->interface, i, j, demineur_case_get_nb_mines_adj(partie->modele, j, i));
					}
				}
			}
		}
		else{} ;


		/* quand la partie est en cours, on affiche un message de jeu en cours */
		if(demineur_est_encours(partie->modele)){
			vue_set_titre(partie->interface, "Déminage en cours");
		}
		/* quand la partie est terminée */
		else{
			/* on arrête le chrono et on active/désactive les boutons qu'il faut */
			stop_chrono(partie);
			vue_set_rejouer_active(partie->interface, 1);
			vue_set_nouvelle_partie_active(partie->interface, 1);
			vue_set_pause_active(partie->interface, 0);

			/* on affiche le message de fin de jeu, selon la victoire ou la défaite */
			if (demineur_est_gagnee(partie->modele)){
				vue_set_titre(partie->interface, "Bravo : vous avez remporté la partie :)");
			}
			else if (demineur_est_perdue(partie->modele)){
				vue_set_titre(partie->interface, "Perdu :(");
			}
			else{} ;
		}
	}
}


	/* Place une marque dans le modèle, puis synchronise la vue (fonction appelée lors d'un clic droit sur un bouton 'carre') */
void ctrl_drapeau_placer(ctrl* partie, int x, int y){
	
	/* si la partie n'est pas fini, on peut placer un drapeau */
	if(gtk_widget_is_sensitive(partie->interface->rejouer) == FALSE){

		/* d'abord dans le modèle */
		demineur_case_marquer(partie->modele, y, x);

		/* puis la vue */
		if(demineur_case_get_marque_joueur(partie->modele, y, x) == MARQUE_AUCUNE)
			vue_set_drapeau_image(partie->interface, x, y, MARQUE_AUCUNE);
		else if(demineur_case_get_marque_joueur(partie->modele, y, x) == MARQUE_MINE){
			/* si le nombre de mines est supérieur au nombre de drapeau */
			if((int)dimension_get_nb_mines(&(partie->modele->dim)) >= (int)dimension_get_nb_mines(&(partie->modele->dim)) - demineur_get_nb_mines_restant_a_deviner(partie->modele))
				/* on affiche le drapeau normal */
				vue_set_drapeau_image(partie->interface, x, y, MARQUE_MINE);
			/* sinon on affiche le drapeau ? ou rien */
			else{
				demineur_case_marquer(partie->modele, y, x);
				vue_set_drapeau_image(partie->interface, x, y, MARQUE_MINE_INTERRO);
			}
		}
		else
			vue_set_drapeau_image(partie->interface, x, y, MARQUE_MINE_INTERRO);
	}
}




/**********************************************
	Définitions des fonctions de gestion du temps
***********************************************/


	/* Initialise les variables de la structure temps */
void initialiser_temps(temps *timer){

	timer->tps = 0;
	timer->chrono = 0;
	timer->booleen_temps = BOOLEEN_FAUX;
}


	/* Démarre le chronomètre de la partie */
void start_chrono(ctrl* partie){

	if(partie->timer->booleen_temps == BOOLEEN_FAUX){
		partie->timer->chrono = g_timeout_add(1000, (GSourceFunc)cback_temps, partie);
		partie->timer->booleen_temps = BOOLEEN_VRAI;
	}
}


	/* Arrête le chronomètre préalablement lancé */
void stop_chrono(ctrl* partie){

	if(partie->timer->booleen_temps == BOOLEEN_VRAI){
		partie->timer->booleen_temps = BOOLEEN_FAUX;
	}
}