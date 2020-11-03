#include "SkipList.h"

SkipList::SkipList () {
	ad = new Cellule;
	ad->niveaux.push_back(nullptr);
	count = 0;
	nb_niveaux = 1;
}

SkipList::~SkipList () {
	
}

bool SkipList::estVide() { return count == 0; }

void SkipList::inserer (const Elem& e) {
	if (estVide()) {
		Cellule* snt = new Cellule;
		snt->info = e;
		snt->niveaux.push_back(nullptr);
		ad->niveaux[0] = snt;
		// ad = new Cellule;
		// ad->info = e;
		// ad->niveaux.push_back(nullptr);
		++count;
	}
	else if (count == 1) {
		if (e < ad->niveaux[0]->info) {
			Cellule* temp = ad->niveaux[0];
			ad->niveaux[0] = new Cellule;
			ad->niveaux[0]->info = e;
			ad->niveaux[0]->niveaux.push_back(temp);

			srand(time(NULL));
			unsigned int rand_num = rand() % 2;

			while(rand_num) {
				ad->niveaux[0]->niveaux.push_back(nullptr);
				ad->niveaux.push_back(ad->niveaux[0]);
				++nb_niveaux;

				rand_num = rand() % 2;
			}

			// Cellule* temp = ad;
			// ad = new Cellule;
			// ad->info = e;
			// ad->niveaux.push_back(temp);

			// srand(time(NULL));
			// unsigned int rand_num = rand() % 2;

			// while(rand_num) {
			// 	ad->niveaux.push_back(nullptr);
			// 	++nb_niveaux;

			// 	rand_num = rand() % 2;
			// }

			++count;
		}
		else if (e > ad->niveaux[0]->info) {

			Cellule* temp = new Cellule;
			temp->info = e;
			temp->niveaux.push_back(nullptr);
			ad->niveaux[0]->niveaux[0] = temp;

			srand(time(NULL));
			unsigned int rand_num = rand() % 2;

			while(rand_num) {
				temp->niveaux.push_back(nullptr);
				ad->niveaux.push_back(temp);
				++nb_niveaux;

				rand_num = rand() % 2;
			}

			// Cellule* temp = new Cellule;
			// temp->info = e;
			// temp->niveaux.push_back(nullptr);
			// ad->niveaux[0] = temp;

			// srand(time(NULL));
			// unsigned int rand_num = rand() % 2;

			// while(rand_num) {
			// 	temp->niveaux.push_back(nullptr);
			// 	++nb_niveaux;

			// 	rand_num = rand() % 2;
			// }

			++count;
		}
	}
	else {
		unsigned int i = ad->niveaux.size()-1;

		if(e < ad->niveaux.at(i)->info) {
		}
	}
}

void SkipList::afficher() const {
	Cellule* current_address;
	unsigned int current_lvl = nb_niveaux;
	unsigned int current_lvl_index = current_lvl == 1 ? 0 : current_lvl-1;

	while(current_lvl != 0) {
		current_address = ad->niveaux[current_lvl_index];

		std::cout << "LEVEL " << current_lvl << " | ";

		while(current_address != nullptr) {
			std::cout << "[" << current_address->info << "] -> ";

			current_address = current_address->niveaux[current_lvl_index];
		}

		if (current_address == nullptr) {
			std::cout << "NULL";
		}

		std::cout << std::endl;

		--current_lvl_index;
		--current_lvl;
	}
}

// void SkipList::etablirProchainNiveau () {
// 	Cellule* current_address = ad;
// 	Cellule* temp = ad; // Derniere cellule sur laquelle on a eu pile

// 	unsigned int rand_num;
// 	while(current_address != nullptr) {
// 		srand(time(NULL));
// 		rand_num = rand() % 2;

// 		if (rand_num && temp != ad) {
// 			temp->niveaux.push_back(current_address);
// 			temp = current_address;
// 		}

// 		current_address = current_address->niveaux[current_address->niveaux.size()-1];
// 	}
// }