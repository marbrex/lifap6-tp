#include "abr.h"
#include <iostream>
#include <cmath>
#include <queue>

// Fonction de traitement des noeuds par defaut (utilisee dans la fonction 'parcours')
void list_elements(Node* n) { std::cout << n->element << " "; }

ABR::ABR () {
	head = nullptr;
	count = 0;
}

ABR::~ABR () {

}

Node* ABR::get_head() const { return head; }

bool ABR::isEmpty() const { return count == 0; }

unsigned int ABR::get_depth_from_node(Node* n, unsigned int depth_count) const {
	if (n) {
		++depth_count;

		if (n->left && n->right) {
			unsigned int left = get_depth_from_node(n->left, depth_count);
			unsigned int right = get_depth_from_node(n->right, depth_count);

			if (left > right) return left;
			return right;
		}
		else {
			if (n->left) return get_depth_from_node(n->left, depth_count);
			if (n->right) return get_depth_from_node(n->right, depth_count);
		}
	}
	return depth_count;
}

unsigned int ABR::get_depth() const { return get_depth_from_node(head); }

unsigned int ABR::draw_node(const Node* n, unsigned int length) const {
	if (n) {
		unsigned int mid = length/2;
		if (length%2 != 0) ++mid;

		unsigned int left = mid/2;
		if (mid%2 != 0) ++left;

		unsigned int right = mid+left;

		// On dessine la ligne avec l'element n->element au milieu
		unsigned int curr_col = 0;
		// Si la longeur est 1, alors on est sur le dernier niveau
		// => donc on n'affiche pas les espaces et fleches
		if (length != 1) {
			for(++curr_col; curr_col<left; ++curr_col)
				std::cout << " ";

			if (n->left) {
				std::cout << "┌";
				for(++curr_col; curr_col<mid; ++curr_col) std::cout << "─";
			}
			else {
				for(; curr_col<mid; ++curr_col)
					std::cout << " ";
			}
		}

		std::cout << n->element;

		// Si la longeur est 1, alors on est sur le dernier niveau
		// => donc on n'affiche pas les espaces et fleches
		if (length != 1) {
			if (n->right) {
				for(++curr_col; curr_col<right; ++curr_col) std::cout << "─";
				std::cout << "┐";
			}
			else {
				for(; curr_col<right; ++curr_col)
					std::cout << " ";
			}

			for(++curr_col; curr_col<=length; ++curr_col)
				std::cout << " ";
		}

		return length;
	}
	else {
		unsigned int curr_col = 0;

		for(++curr_col; curr_col<=length; ++curr_col)
			std::cout << " ";

		// On retourne la valeur decrementee, car la derniere iteration de la boucle for avait l'incrementee
		return --curr_col;
	}
}

void ABR::draw_from_node(const Node* n, bool extra) const {
	if (!isEmpty()) {

		// On initialise les valeurs de depart pour construire le tableau d'affichage
		unsigned int depth = get_depth();
		unsigned int max_elems = pow(2,depth-1); // Nombre maximum d'elements sur le dernier niveau de l'ABR
		unsigned int max_offset = max_elems-1; // Nombre d'espaces entre les noeuds sur le dernier niveau de l'ABR
		unsigned int width = max_elems + max_offset; // Longeur de la grille d'affichage

		if (extra) {
			std::cout << "Number of Elements         : " << count << std::endl;
			std::cout << "Depth (Number of Levels)   : " << depth << std::endl;
			std::cout << "Max Elements on Last Level : " << max_elems << std::endl << std::endl;
		}

		// On dessine les noeuds selon la grille d'affichage
		unsigned int curr_col = 0;
		unsigned int tab_width = width;

		std::queue<const Node*> q;
		q.push(n);

		while (!q.empty()) {
			// On dessine le noeud actuel et on sauvegarde la colonne ou on s'est arrete
			curr_col += draw_node(q.front(), tab_width);

			// On se prepare pour la prochaine iteration.
			// Si le pointeur sur le noeud actuel n'est pas NULL, alors
			if (q.front()) {
				// Si le noeud actuel possede un fils gauche,
				//  alors on enfile un pointeur vers son fils gauche
				// sinon on enfile un pointeur null
				if (q.front()->left) q.push(q.front()->left);
				else q.push(nullptr);

				// Si le noeud actuel possede un fils droit,
				//  alors on enfile un pointeur vers son fils droit
				// sinon on enfile un pointeur null
				if (q.front()->right) q.push(q.front()->right);
				else q.push(nullptr);
			}

			// On defile le pointeur vers le noeud actuel,
			// car on en a plus besoin (deja dessine)
			q.pop();

			// std::cout << "curr_col: " << curr_col;
			// std::cout << " tab_width: " << tab_width;
			// std::cout << " width: " << width << std::endl;

			// Si on a atteint la fin de la table d'affichage, alors
			// on affiche un saut de ligne et on remet la colonne actuelle a 0,
			// et on divise aussi la largeur de la ligne actuelle par 2.
			if (curr_col >= width) {
				std::cout << std::endl;
				curr_col = 0;
				tab_width/=2; // Largeur de la prochaine ligne a dessiner sera 2 fois plus petite
			}
			// Si on a pas encore atteint la fin de la table d'affichage
			else {
				// Si la largeur de la ligne actuelle est impaire,
				// on dessine un espace, car la colonne est represente par 'int'
				// (ex. 15/7=2 => il nous manque un espace a dessiner)
				if (tab_width%2 != 0) {
					std::cout << " ";
					++curr_col;
				}
			}

		}

		// On affiche un saut de ligne a la fin de l'affichage de l'ABR
		std::cout << std::endl;
	}
	else std::cout << "ABR est vide !" << std::endl;
}

void ABR::draw(bool extra) const { draw_from_node(head, extra); }

void ABR::parcours(void (*handler)(Node*)=list_elements, int mode) {
	switch(mode) {
		case 1: // Ordre PREFIX
			parcours_prefix_from(head, handler);
			std::cout << std::endl << std::endl;
			break;
		case 2: // Ordre POSTFIX
			parcours_postfix_from(head, handler);
			std::cout << std::endl << std::endl;
			break;
		default: // Ordre INFIX
			parcours_infix_from(head, handler);
			std::cout << std::endl << std::endl;
			break;
	}
}

void ABR::parcours_infix_from(Node* n, void (*handler)(Node*)=list_elements) {
	if (n) {
		parcours_infix_from(n->left, handler);
		handler(n);
		parcours_infix_from(n->right, handler);
	}
}

void ABR::parcours_prefix_from(Node* n, void (*handler)(Node*)=list_elements) {
	if (n) {
		handler(n);
		parcours_prefix_from(n->left, handler);
		parcours_prefix_from(n->right, handler);
	}
}

void ABR::parcours_postfix_from(Node* n, void (*handler)(Node*)=list_elements) {
	if (n) {
		parcours_postfix_from(n->left, handler);
		parcours_postfix_from(n->right, handler);
		handler(n);
	}
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
		if (e != n->element) {
			if (e < n->element) insert_from_node(e, n->left);
			else insert_from_node(e, n->right);
		}
	}
}

void ABR::insert (const Elem& e) { insert_from_node(e, head); }

Node* ABR::find_from_node(const Elem& e, Node* n) const {
	if (n) {
		if (e == n->element) return n;
		else {
			if (e < n->element) return find_from_node(e, n->left);
			else return find_from_node(e, n->right);
		}
	}
	return nullptr;
}

Node* ABR::find(const Elem& e) const { return find_from_node(e, head); }