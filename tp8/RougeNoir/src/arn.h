#ifndef _ARN
#define _ARN

#include "element.h"

struct Node {
	Elem element;
	Node* left;
	Node* right;
};

class ARN {
    private:
        Node* head; // Pointeur vers le premier noeud
		unsigned int count; // Nombre d'elements
    
    public:
        ARN();
        ~ARN();
};

#endif