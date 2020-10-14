#include "table.h"
#include "hash_functions.cpp"
#include <iostream>

Table::Table (unsigned int size) {
	max_elements = size;
	nb_elements = 0;

	elements = new Case[size];
	hash = hash_modulo;
	hash_step = hash_skip_linear;
}

Table::~Table () {
	delete [] elements;
}

void Table::add (const Key& key) {
	assert(nb_elements < max_elements);

	unsigned int hash_code = hash(key, max_elements);
	unsigned int try_nb = 1;

	while(!elements[hash_code].free) {
		hash_code += hash_step(key, try_nb++);
		if(hash_code >= max_elements) {
			hash_code = hash_code % max_elements;
		}
	}

	if (elements[hash_code].free) {
		elements[hash_code].key = key;
		elements[hash_code].free = false;
		++nb_elements;
	}
}

void Table::show () const {
	std::cout << "Maximum elements: " << max_elements << std::endl;
	std::cout << "Elements stored: " << nb_elements << std::endl;
	for(unsigned int i=0; i<max_elements; ++i) {
		if(!elements[i].free) std::cout << "[" << elements[i].key << "]";
		else std::cout << "[ ]";

		if (i==max_elements-1) std::cout << std::endl;
		else std::cout << "  ";
	}
}