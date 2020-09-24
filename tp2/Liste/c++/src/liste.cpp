#include "liste.h"

Liste::Liste() {
	ad = new Cellule;
	ad->suivant = nullptr;
	ad->apres_suiv = nullptr;
	count = 0;
}

Liste::Liste(const Liste & l) {
}

Liste::~Liste() {
	Cellule* current_address = ad;

	Cellule* next_address;
	if (current_address != nullptr)
		next_address = current_address->suivant;

	for (unsigned int i=0; i<=count+1; ++i) {
		delete current_address;

		if (next_address != nullptr) {
			current_address = next_address;
			next_address = next_address->suivant;
		}
	}
}

void Liste::ajoutEnTete(const Elem & e) {
	Cellule* temp = ad->suivant;
	ad->suivant = new Cellule;
	ad->suivant->info = e;
	ad->suivant->suivant = temp;
	ad->suivant->apres_suiv = temp ? (temp->suivant ? temp->suivant : nullptr) : nullptr;
	++count;
}

void Liste::affichage() const {
	unsigned int i = 0;
	Cellule* current_address = ad->suivant;

	while(current_address != nullptr) {
		std::cout << i << ": " << std::endl;
		std::cout << "	info: " << current_address->info << std::endl;
		std::cout << "	suivant: " << current_address->suivant << std::endl;
		std::cout << "	apres suivant: " << current_address->apres_suiv << std::endl;

		++i;
		current_address = current_address->suivant;
	}
}

bool Liste::testVide() const { return count == 0; }