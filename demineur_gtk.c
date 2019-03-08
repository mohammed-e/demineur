#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "demineur.h"
#include "vue.h"
#include "ctrl.h"



/************/
/*	Main 	*/
/************/


int main(){

	/* Allocation de mémoire */
	ctrl* partie = (ctrl*)malloc(sizeof(ctrl));
	partie->interface = (vue*)malloc(sizeof(vue));
	partie->modele = (demineur*)malloc(sizeof(demineur));
	partie->timer = (temps*)malloc(sizeof(temps));
  
  /* Initialisation */
  srand(time(NULL));
  initialiser_temps(partie->timer);
	gtk_init(NULL,NULL);
	
	/* Lancement de la partie */
  ctrl_vue_menu(partie);
	gtk_main();

	return EXIT_SUCCESS;

}
