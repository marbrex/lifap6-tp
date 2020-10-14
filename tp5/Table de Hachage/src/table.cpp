#include "table.h"
#include "hash_functions.cpp"
#include <iostream>

Table::Table (unsigned int size) {
	max_elements = size;
	nb_elements = 0;

	elements = new Case[size];
	hash = hash_modulo;
	hash_step = pas_de_hash_lin;
}

Table::~Table () {
	delete [] elements;
}

void Table::add (const Element& e) {
	assert(nb_elements < max_elements);

	unsigned int hash_code = hash(e.key, max_elements);
	unsigned int numero_essai = 1;

	while(!elements[hash_code].free) {
		hash_code += hash_step(e.key, numero_essai++);
	}

	if (elements[hash_code].free) {
		elements[hash_code].element = e;
		elements[hash_code].free = false;
		++nb_elements;
	}
}

void Table::show () const {
	for(unsigned int i=0; i<max_elements; ++i) {
		if(!elements[i].free) {
			std::cout << "[" << elements[i].element.key << "]";
			if (i==max_elements-1) std::cout << std::endl;
			else std::cout << " , ";
		}
		else {
			std::cout << "[ ]";
			if (i==max_elements-1) std::cout << std::endl;
			else std::cout << " , ";
		}
	}
}