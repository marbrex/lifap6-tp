#ifndef _HASH_FUNCTIONS
#define _HASH_FUNCTIONS

#include "element.h"

unsigned int hash_modulo (const Key& k, unsigned int size) {
	return k % size;
}

unsigned int pas_de_hash_lin (const Key& k, unsigned int numero_essai) {
	return 1;
}

#endif