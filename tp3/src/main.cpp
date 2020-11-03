#include "SkipList.h"
#include <iostream>

int main() {
	SkipList l;

	l.inserer(5);
	l.inserer(6);
	l.inserer(4);

	l.afficher();
	
	return 0;
}