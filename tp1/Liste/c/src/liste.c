#include "liste.h"

void initialiseListeDefaut(Liste *l) {
	l->ad = NULL;
	l->count = 0;
}

void testamentListe(Liste *l) {
	Cellule* current_address = l->ad;

	Cellule* next_address;
	if (current_address != NULL)
		next_address = current_address->suivant;

	for (unsigned int i=0; i<=l->count; ++i) {
		free(current_address);

		if (next_address != NULL) {
			current_address = next_address;
			next_address = next_address->suivant;
		}
	}
}

void ajoutEnTeteListe(Elem e, Liste *l) {
	Cellule* temp = l->ad;
	l->ad = malloc(sizeof(Cellule));
	l->ad->info = e;
	l->ad->suivant = temp;
	l->count++;
}

void affichageListe(Liste l) {
	unsigned int i = 0;
	Cellule* current_address = l.ad;

	while(current_address != NULL) {
		printf("%u: \n", i);
		printf("  info: %u\n", current_address->info);
		printf("  suivant: %p\n", current_address->suivant);

		++i;
		current_address = current_address->suivant;
	}
}