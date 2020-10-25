#include "element.h"

struct Node {
	Elem element;
	Node* left;
	Node* right;
};

class ABR {
	private:
		Node* head;
		unsigned int count;
		unsigned int deep;

		void insert_from_node (const Elem& e, Node*& n);
		unsigned int draw_node(const Node* n, unsigned int length) const;

	public:
		ABR();
		~ABR();

		bool isEmpty() const;

		void insert(const Elem& e);

		void draw() const;
};