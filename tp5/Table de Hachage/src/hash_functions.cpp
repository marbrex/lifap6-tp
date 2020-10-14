#ifndef _HASH_FUNCTIONS
#define _HASH_FUNCTIONS

#include "element.h"

unsigned int hash_modulo (const Key& k, unsigned int size) {
	return k % size;
}

#endif