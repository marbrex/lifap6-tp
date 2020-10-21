#include "element.h"

struct Node {
	Elem element;
	Node* left;
	Node* right;
};

class ABR {
	private:
		Node* head;

	public:
		ABR();
		~ABR();
};