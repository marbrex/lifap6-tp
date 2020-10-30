#ifndef _ABR
#define _ABR

#include "element.h"

struct Node {
	Elem element;
	Node* left;
	Node* right;
};

class ABR {
	private:
		Node* head; // Pointeur vers le premier noeud
		unsigned int count; // Nombre d'elements

		// Postcondition: Commence son chemin a partir d'un noeud n,
		//				  e est apres insere dans un bon endroit
		void insert_from_node (const Elem& e, Node*& n);

		// Preconditions: length = la longeur de la ligne a dessiner
		// Postcondition: Dessine UNE ligne avec un noeud (element) au milieu
		// Resultat: Retourne la colonne sur la-quelle on s'est arrete apres l'affichage d'un noeud
		unsigned int draw_node(const Node* n, unsigned int length) const;

		// Fonction de traitement des noeuds par defaut (utilisee dans la fonction membre 'parcours').
		// Le mot cle 'static' est utilise, car la fonction 'parcours' exige une fonction 'handler', dont
		// l'entete est 'void *nom* (Node*)', donc qui ne retourne aucune valeur et prend
		// en parametre un seul argument de type 'Node*'. Si 'static' n'est pas utilise
		// alors la fonction devient une fonction membre et donc prend en parametre
		// un argument cache 'this', et en consequance elle ne correspond pas a 'handler'.
		static void list_elements(Node* n);

		// Resultat: pareil que 'get_parent', sauf qu'il commence
		//			 son chemin a partir du noeud n passe en parametre
		Node* get_parent_from_node(const Elem& e, Node* n, Node* parent=nullptr) const;

		// Resultat: retourne le nombre de niveaux dans l'ABR, mais
		//			 commence son chemin a partir du noeud n passe en parametre
		unsigned int get_depth_from_node(Node* n, unsigned int depth_count=0) const;

	public:
		// =========== Constructeurs ===========
		// Constructeur par defaut
		ABR();

		// Constructeur par copie
		// Postcondition: realise un copie profonde d'un arbre entier
		ABR(const ABR& a);

		// Destructeur
		~ABR();

		// =========== Fonctions Membres ===========
		// Resultat: Retourne VRAI si l'ABR n'est pas vide,
		//			 FAUX sinon
		bool isEmpty() const;

		// Postcondition: * Si e n'est pas present dans l'ABR,
		//					alors un noeud avec l'element e dedans est insere dans l'ABR
		//				  * Si e est deja present, alors ne fait rien
		void insert(const Elem& e);

		// Postcondition: Noeud contenant l'element e est supprime de l'ABR
		//				  * Si le noeud est une feuille,
		//					alors le noeud est supprime simplement
		//				  * Si le noeud possede un fils,
		//					alors le noeud est supprime, et son fils
		//					est rebranche au pere du noeud supprime
		//				  * Si le noeud possede deux fils,
		//					alors le noeud est supprime et remplace par
		//					son plus proche predecesseur
		void remove(const Elem& e);

		// Preconditions: extra: afficher ou pas les informations supplementaires
		// Postcondition: * Si l'ABR n'est pas vide, dessine l'ABR entier
		//					(parcours en largeur, cad niveau apres niveau)
		//				  * Si l'ABR est vide, alors affiche une chaine de caracteres
		void draw(bool extra=false) const;

		// Preconditions: extra: afficher ou pas les informations supplementaires
		// Postcondition: Pareil que 'draw', sauf qu'il commence a dessiner
		//				  l'ABR a partir du noeud n passe en parametre
		void draw_from_node(const Node* n, bool extra=false) const;

		// Preconditions: * mode: 1=parcours PREFIX, 2=parcours POSTFIX, tout autre valeur=parcours INFIX
		// 				  * handler: fonction dont l'entete est 'void *nom* (Node*)',
		//					qui est appele pour chaque element dans l'ordre indique
		// Postcondition: La fonction 'handler' est appliquee a chaque element
		//				  de l'ABR dans l'ordre 'mode'
		void parcours(int mode, void (*handler)(Node*)=list_elements);

		// Preconditions: handler: fonction dont l'entete est 'void *nom* (Node*)',
		//				  qui est appele pour chaque element dans l'ordre indique
		// Postcondition: La fonction 'handler' est appliquee a chaque element
		//				  a partir du noeud 'n' dans l'ordre INFIX 
		void parcours_infix_from(Node* n, void (*handler)(Node*)=list_elements);

		// Preconditions: handler: fonction dont l'entete est 'void *nom* (Node*)',
		//				  qui est appele pour chaque element dans l'ordre indique
		// Postcondition: La fonction 'handler' est appliquee a chaque element
		//				  a partir du noeud 'n' dans l'ordre PREFIX 
		void parcours_prefix_from(Node* n, void (*handler)(Node*)=list_elements);

		// Preconditions: handler: fonction dont l'entete est 'void *nom* (Node*)',
		//				  qui est appele pour chaque element dans l'ordre indique
		// Postcondition: La fonction 'handler' est appliquee a chaque element
		//				  a partir du noeud 'n' dans l'ordre POSTFIX 
		void parcours_postfix_from(Node* n, void (*handler)(Node*)=list_elements);

		// Resultat: * Si l'element e est present dans l'ABR,
		//			   alors, retourne le noeud contenant l'element e
		//			 * Sinon retourne un pointeur null
		Node* find(const Elem& e) const;

		// Resultat: Pareil que 'find', sauf qu'il commence
		//			 son chemin a partir du noeud n passe en parametre
		Node* find_from_node(const Elem& e, Node* n) const;

		// Postcondition: Realise une copie profonde a partir du noeud n
		void copy_from_node(const Node* n);

		// =========== Accesseurs ===========
		// Resultat: Premier Noeud de l'ABR
		Node* get_head() const;

		// Resultat: retourne le pere de l'element e passe en parametre
		Node* get_parent(const Elem& e) const;

		// Resultat: retourne le nombre de niveaux dans l'ABR
		unsigned int get_depth() const;

		// =========== Surcharhes des operateurs ===========
		// Postcondition: Realise une affectation (copie profonde)
		// Resultat: Retourne l'adresse de l'ABR
		ABR& operator=(const ABR& a);
};

#endif