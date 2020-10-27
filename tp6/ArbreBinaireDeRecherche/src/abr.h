#ifndef _ABR
#define _ABR

#include "element.h"

struct Node;
// Fonction de traitement des noeuds par defaut (utilisee dans la fonction membre 'parcours')
void list_elements(Node* n);

struct Node {
	Elem element;
	Node* left;
	Node* right;
};

class ABR {
	private:
		Node* head;
		unsigned int count;

		// Postcondition: Commence son chemin a partir d'un noeud n
		//				  e est apres insere dans un bon endroit
		void insert_from_node (const Elem& e, Node*& n);

		// Preconditions: length = la longeur de la ligne a dessiner
		// Postcondition: Dessine UNE ligne avec un noeud (element) au milieu
		// Resultat: Retourne la colonne sur la-quelle on s'est arrete apres l'affichage d'un noeud
		unsigned int draw_node(const Node* n, unsigned int length) const;

	public:
		ABR();
		~ABR();

		Node* get_head() const;

		bool isEmpty() const;

		// Postcondition: Si e n'est pas present dans l'ABR,
		//				  alors un noeud avec l'element e dedans est insere dans l'ABR
		//				  Si e est deja present, alors ne fait rien
		void insert(const Elem& e);

		// Postcondition: Si l'ABR n'est pas vide, dessine l'ABR entier
		//				  (parcours en largeur, cad niveau apres niveau)
		//				  Si l'ABR est vide, alors affiche une chaine de caracteres
		void draw(bool extra=true) const;

		void draw_from_node(const Node* n, bool extra=true) const;

		void parcours(void (*handler)(Node*)=list_elements, int mode=0);

		void parcours_infix_from(Node* n, void (*handler)(Node*)=list_elements);
		void parcours_prefix_from(Node* n, void (*handler)(Node*)=list_elements);
		void parcours_postfix_from(Node* n, void (*handler)(Node*)=list_elements);

		Node* find(const Elem& e) const;

		Node* find_from_node(const Elem& e, Node* n) const;

		unsigned int get_depth() const;

		unsigned int get_depth_from_node(Node* n, unsigned int depth_count=0) const;
};

#endif