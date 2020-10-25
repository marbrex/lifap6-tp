#include "abr.h"
#include <iostream>
#include <cmath>
#include <queue>

ABR::ABR () {
	head = nullptr;
	count = 0;
	deep = 0;
}

ABR::~ABR () {

}

bool ABR::isEmpty() const { return count == 0; }

unsigned int ABR::draw_node(const Node* n, unsigned int length) const {
	if (n) {
		unsigned int mid;
		if (length%2 == 0) mid = length/2;
		else mid = length/2 +1;

		unsigned int left;
		if (mid%2 == 0) left = mid/2;
		else left = mid/2 +1;

		unsigned int right = mid+left;

		unsigned int curr_col = 0;

		// On dessine la ligne avec l'element n->element au milieu
		for(++curr_col; curr_col<left; ++curr_col)
			std::cout << " ";

		if (n->left) {
			std::cout << "┌";
			for(++curr_col; curr_col<mid; ++curr_col) std::cout << "─";
		}
		else {
			std::cout << " ";
			for(++curr_col; curr_col<mid; ++curr_col)
				std::cout << " ";
		}

		std::cout << n->element;

		if (n->right) {
			for(++curr_col; curr_col<right; ++curr_col) std::cout << "─";
			std::cout << "┐";
		}
		else {
			for(++curr_col; curr_col<right; ++curr_col)
				std::cout << " ";
			std::cout << " ";
		}

		for(++curr_col; curr_col<=length; ++curr_col)
			std::cout << " ";

		// On retourne la valeur decrementee, car la derniere iteration de la boucle for avait l'incrementee
		return --curr_col;
	}
	else {
		unsigned int curr_col = 0;

		for(++curr_col; curr_col<=length; ++curr_col)
			std::cout << " ";

		return --curr_col;
	}
}

void ABR::draw() const {
	if (!isEmpty()) {

		// On initialise les valeurs de depart pour construire le tableau d'affichage
		unsigned int max_elems = pow(2,deep-1); // Nombre maximum d'elements sur le dernier niveau de l'ABR
		unsigned int max_offset = max_elems-1; // Nombre d'espaces entre les noeuds sur le dernier niveau de l'ABR
		unsigned int width = max_elems + max_offset; // Longeur de la grille d'affichage

		std::cout << "deep : " << deep << std::endl;
		std::cout << "max elements on last level : 2^(deep-1) = " << max_elems << std::endl << std::endl;

		// On dessine les noeuds selon la grille d'affichage
		unsigned int curr_col = 0;
		unsigned int tab_width = width;

		std::queue<const Node*> q;
		q.push(head);

		while (!q.empty()) {
			curr_col += draw_node(q.front(), tab_width);

			if (q.front()) {
				if (q.front()->left) q.push(q.front()->left);
				else q.push(nullptr);

				if (q.front()->right) q.push(q.front()->right);
				else q.push(nullptr);
			}

			q.pop();

			// std::cout << "curr_col: " << curr_col;
			// std::cout << " tab_width: " << tab_width;
			// std::cout << " width: " << width << std::endl;

			if (curr_col >= width) {
				std::cout << std::endl;
				curr_col = 0;
				tab_width/=2;
			}
			else {
				if (tab_width%2 != 0) {
					++curr_col;
					std::cout << " ";
				}
			}

		}

		// On affiche un saut de ligne a la fin de l'affichage de l'ABR
		std::cout << std::endl;
	}
	else std::cout << "ABR est vide !" << std::endl;
}

void ABR::insert_from_node (const Elem& e, Node*& n) {
	if (n == nullptr) {
		n = new Node;
		n->element = e;
		n->left = nullptr;
		n->right = nullptr;

		++count;
	}
	else {
		if (!n->left && !n->right) ++deep;

		if (e < n->element) insert_from_node(e, n->left);
		else if (e > n->element) insert_from_node(e, n->right);
	}
}

void ABR::insert (const Elem& e) { insert_from_node(e, head); }