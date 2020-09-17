#include "liste.h"

Liste::Liste() {
	this->ad = nullptr;
	this->count = 0;
}

Liste::Liste(const Liste & l) {
}

Liste::~Liste() {
	Cellule* current_address = this->ad;

	Cellule* next_address;
	if (current_address != nullptr)
		next_address = current_address->suivant;

	for (unsigned int i=0; i<=this->count; ++i) {
		delete current_address;

		if (next_address != nullptr) {
			current_address = next_address;
			next_address = next_address->suivant;
		}
	}
}

void Liste::ajoutEnTete(const Elem & e) {
	Cellule* temp = this->ad;
	this->ad = new Cellule;
	this->ad->info = e;
	this->ad->suivant = temp;
	++count;
}

void Liste::affichage() const {
	unsigned int i = 0;
	Cellule* current_address = this->ad;

	while(current_address != nullptr) {
		std::cout << i << ": " << std::endl;
		std::cout << "	info: " << current_address->info << std::endl;
		std::cout << "	suivant: " << current_address->suivant << std::endl;

		++i;
		current_address = current_address->suivant;
	}
}