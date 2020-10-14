#ifndef _HASH_FUNCTIONS
#define _HASH_FUNCTIONS

#include "key.h"

unsigned int hash_modulo (const Key& k, unsigned int size) {
	return k % size;
}

unsigned int hash_skip_linear (const Key& k, unsigned int try_nb) {
	return 1;
}

#endif