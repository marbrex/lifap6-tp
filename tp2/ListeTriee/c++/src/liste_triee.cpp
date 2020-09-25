#include "liste_triee.h"

Liste::Liste() {
	ad = new Cellule;
	ad->suivant = nullptr;
	ad->apres_suiv = nullptr;
	second_link_lvl = false;
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
	ad->apres_suiv = temp ? temp : nullptr;
	ad->suivant->info = e;
	ad->suivant->suivant = temp;
	ad->suivant->apres_suiv = nullptr;
	++count;
}

void Liste::affichage() const {
	if (testVide()) {
		std::cout << "La Liste est VIDE !" << std::endl;
	}
	else {
		unsigned int i = 0;
		Cellule* current_address = ad->suivant;

		while(current_address != nullptr) {
			std::cout << i << ": " << std::endl;
			std::cout << "	@: " << current_address << std::endl;
			std::cout << "	info: " << current_address->info << std::endl;
			std::cout << "	suivant: " << current_address->suivant << std::endl;
			std::cout << "	apres suivant: " << current_address->apres_suiv << std::endl << std::endl;

			++i;
			current_address = current_address->suivant;
		}
	}
}

void Liste::affichageSecondNiveau() const {
	if (testVide()) {
		std::cout << "La Liste est VIDE !" << std::endl;
	}
	else {
		unsigned int i = 0;
		Cellule* current_address = ad->apres_suiv;

		while(current_address != nullptr) {
			std::cout << i << ": " << std::endl;
			std::cout << "	@: " << current_address << std::endl;
			std::cout << "	info: " << current_address->info << std::endl;
			std::cout << "	suivant 2nd niveau: " << current_address->apres_suiv << std::endl;

			++i;
			current_address = current_address->apres_suiv;
		}
	}
}

bool Liste::testVide() const { return count == 0; }

void Liste::insere(const Elem &e) {
	Cellule* current_address = ad->suivant;
	Cellule* prev_address = ad;

	if (testVide()) { // si la liste est VIDE
		std::cout << "VIDE" << std::endl;

		ad->suivant = new Cellule;
		ad->apres_suiv = ad->suivant;
		ad->suivant->info = e;
		ad->suivant->suivant = nullptr;
		ad->suivant->apres_suiv = nullptr;
		++count;
	}

	while(current_address != nullptr) {
		if (e <= current_address->info) { // e est inferieur a l'element actuel (on a trouve sa place)
			std::cout << "<" << std::endl;

			Cellule* temp = current_address;

			current_address = new Cellule;
			current_address->info = e;
			current_address->suivant = temp;
			current_address->apres_suiv = nullptr;
			++count;

			prev_address->suivant = current_address;

			break;
		}
		else if (current_address->suivant == nullptr) { // e est max
			std::cout << "MAX" << std::endl;

			Cellule* temp = new Cellule;
			temp->info = e;
			temp->suivant = nullptr;
			temp->apres_suiv = nullptr;
			++count;

			current_address->suivant = temp;

			break;
		}
		else { // e est superieur a l'element actuel (on paase au suivant)
			std::cout << "NEXT" << std::endl;

			prev_address = current_address;
			current_address = current_address->suivant;
		}
	}
}

void Liste::etablissementSecondNiveau() {
	if (ad->suivant) { // si la liste contient au moins une cellule
		Cellule* current_address = ad->suivant;
		ad->apres_suiv = current_address;

		if (current_address->suivant) { // si la liste contient au moins 2 cellules
			Cellule* next_address = current_address->suivant;
			ad->apres_suiv = next_address;

			while(next_address->suivant != nullptr) { // au moins 3 cellules
				current_address->apres_suiv = next_address->suivant;

				current_address = next_address;
				next_address = current_address->suivant;
			}
		}

		second_link_lvl = true;
	}
	//si la liste est vide, on fait rien
}