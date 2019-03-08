#ifndef CONTROLEUR_H
#define CONTROLEUR_H



/***************************************
	Déclaration des structures de contrôle	 
****************************************/



typedef struct temps{
	int tps;					/* nombre de secondes écoulées */
	guint chrono;				/* variable servant à stocker l'ID de l'événement lié au chrono */
	booleen booleen_temps;		/* booléen servant à arrêter ou redémarrer le chrono */
}temps;



typedef struct s_controleur ctrl;
typedef struct s_sous_controleur ctrl_case;


/* sous-contrôleur au niveau des case de la grille de jeu */
struct s_sous_controleur{
	int x;								/* position horizontale d'une case dans la grille de jeu */
	int y;								/* position verticale d'une case dans la grille de jeu */
	ctrl *parent;						/* adresse du contrôleur parent, celui de la partie entière */
};


/* contrôleur de la partie */
struct s_controleur{
	demineur *modele;							/* adresse d'une structure du modèle */
	vue *interface;								/* adresse d'une structure de la vue */
	ctrl_case grille[CASE_Y_MAX][CASE_X_MAX];	/* tableau/grille des contrôleurs niveau case */
	temps *timer;								/* adresse de la structure permettant la gestion du temps */
};






/******************************************************
	Prototypes des fonctions de construction de la partie 
*******************************************************/
/* 
	@pré-conditions pour toutes ces fonctions : 
		- gtk_init a été préalablement appelée
		- à l'adresse contenue dans 'partie' se trouve bien une structure 'ctrl'
*/


	/* Créer le menu de départ de choix du niveau */
void ctrl_vue_menu(ctrl* partie);


	/* Construction : construit, initialise et imbrique les widget de la fenêtre de jeu */
void ctrl_vue_construire(ctrl* partie);




/***********************************
	Prototypes des fonctions de rappel 
************************************/
/* 
	@pré-conditions pour toutes ces fonctions : 
		- gtk_init a été préalablement appelée
		- à l'adresse contenue dans 'data' se trouve bien une structure 'ctrl' (ou ctrl_case pour cback_carre_clique)
*/



	/* Initialise une partie en initialisant le modèle, selon le choix de l'utilisateur, et la vue,
		 lorsque l'utilisateur sélectionne son niveau dans le menu en cliquant le bouton voulu */
void cback_choix(GtkWidget* bouton, ctrl* data);


	/* Appelle la fonction ctrl_jouer_coup lors d'un clic gauche sur une case, et ctrl_drapeau_placer si clic droit
	@pré-conditions : 
		- carre est l'adresse d'un GtkWidget
		- clic est l'adresse d'un GdkEventButton */
gboolean cback_carre_clique(GtkWidget* carre, GdkEventButton* clic, ctrl_case* data);


	/* Initialise une nouvelle partie en affichant le menu de départ (fonction appelée lors d'un clic sur le bouton 'Nouvelle Partie')
	@pré-condition : 
		- nouvelle_partie est l'adresse d'un GtkWidget */
void cback_nouvelle_partie(GtkWidget* nouvelle_partie, ctrl* data);


	/* Réinitialise la partie en cours dans le modèle, puis nettoie la vue (fonction appelée lors d'un clic sur le bouton 'Rejouer')
	@pré-condition : 
		- rejouer est l'adresse d'un GtkWidget */
void cback_rejouer(GtkWidget* rejouer, ctrl* data);


	/* Démarre ou arrête le chronomètre selon le libelle du bouton Pause
	@pré-condition : 
		- pause est l'adresse d'un GtkWidget */
void cback_pause(GtkWidget* pause, ctrl* data);


	/* Démarre ou arrête l'aide selon le libelle du bouton Aide
	@pré-condition : 
		- aide est l'adresse d'un GtkWidget */
void cback_aide(GtkWidget* aide, ctrl* data);


	/* Comptabilise les secondes passées puis synchronise la vue */
gint cback_temps(ctrl* partie);


	/* Libère la mémoire allouée pour le contrôleur, la vue et le modèle et quitte la boucle événementielle 
		 (fonction appelée lors d'un clic sur le bouton 'Quitter' ou sur la croix de la fenêtre principale)
	@pré-condition : 
		- quitter est l'adresse d'un GtkWidget */
void cback_quitter(GtkWidget* quitter, ctrl* data);




/*******************************************************
	Prototypes des fonctions de manipulation du contrôleur  
********************************************************/
/* 
	@pré-conditions pour toutes ces fonctions : 
		- gtk_init a été préalablement appelée
		- à l'adresse contenue dans 'partie' se trouve bien une structure 'ctrl'
*/


	/* Joue un coup dans le modèle, puis synchronise la vue (fonction appelée lors d'un clic gauche sur un bouton 'carre')
			@pré-condition : 
			- x et y sont deux entiers représentant les coordonnées de la case cliquée */
void ctrl_jouer_coup(ctrl* partie, int x, int y);


	/* Place une marque dans le modèle, puis synchronise la vue (fonction appelée lors d'un clic droit sur un bouton 'carre')
		@pré-condition : 
		- x et y sont deux entiers représentant les coordonnées de la case cliquée */
void ctrl_drapeau_placer(ctrl* partie, int x, int y);




/*********************************************
	Prototypes des fonctions de gestion du temps  
**********************************************/
/* 
	@pré-conditions pour toutes ces fonctions : 
		- à l'adresse contenue dans 'partie' se trouve bien une structure 'ctrl'
		- à l'adresse contenue dans 'timer' se trouve bien une structure 'temps'
*/


	/* Initialise les variables de la structure temps */
void initialiser_temps(temps *timer);


	/* Démarre le chronomètre de la partie */
void start_chrono(ctrl* partie);


	/* Arrête le chronomètre préalablement lancé */
void stop_chrono(ctrl* partie);




#endif