#ifndef _TABLE
#define _TABLE

#include <assert.h>
#include "key.h"
#include "info.h"

template<class T>
class Table;

template<class T>
class Case {
	friend class Table<T>;

	private:
		Key key;
		Info<T> info;
		bool free;

	public:
		Case() : free(true) {}
		Case(const Key& k) : key(k), free(false) {}

		void set_key(const Key& k) { key=k; free=false; }
		Key get_key() const { return key; }

		bool isFree() const { return free; }
};

template<class T>
class Table {
	private:
		Case<T>* elements;

		unsigned int max_elements;
		unsigned int nb_elements;

		unsigned int (*hash)(const Key&, unsigned int);
		unsigned int (*rehash)(const Key&, unsigned int);

		static unsigned int hash_modulo (const Key& k, unsigned int size);
		static unsigned int rehash_linear (const Key& k, unsigned int try_nb);

	public:
		Table(unsigned int size, unsigned int (*hash)(const Key&, unsigned int)=hash_modulo);
		~Table();

		void set_hash(unsigned int (*hash)(const Key&, unsigned int));
		void set_rehash(unsigned int (*rehash)(const Key&, unsigned int));

		void add(const Key& e, const Info<T>& info);
		void remove(unsigned int hash_code);
		void show() const;

};

template<class T>
unsigned int Table<T>::hash_modulo (const Key& k, unsigned int size) { return k % size; }

template<class T>
unsigned int Table<T>::rehash_linear (const Key& k, unsigned int try_nb) { return 1; }

template<class T>
Table<T>::Table (unsigned int size, unsigned int (*hash)(const Key&, unsigned int))
	: max_elements(size), nb_elements(0), hash(hash) {
	elements = new Case<T>[size];
	rehash = rehash_linear;
}

template<class T>
Table<T>::~Table () { delete [] elements; }

template<class T>
void Table<T>::add (const Key& key, const Info<T>& info) {
	assert(nb_elements < max_elements);

	unsigned int hash_code = hash(key, max_elements);
	unsigned int try_nb = 1;

	while(!elements[hash_code].free) {
		hash_code += rehash(key, try_nb++);
		if(hash_code >= max_elements) {
			hash_code = hash_code % max_elements;
		}
	}

	if (elements[hash_code].free) {
		elements[hash_code].key = key;
		elements[hash_code].info.set(info.get());
		elements[hash_code].free = false;
		++nb_elements;
	}
}

template<class T>
void Table<T>::show () const {
	std::cout << "Maximum elements: " << max_elements << std::endl;
	std::cout << "Elements stored: " << nb_elements << std::endl;
	for(unsigned int i=0; i<max_elements; ++i) {
		if(!elements[i].free) {
			std::cout << "[" << elements[i].key << "->";
			std::cout << elements[i].info << "]";
		}
		else std::cout << "[ ]";

		if (i==max_elements-1) std::cout << std::endl;
		else std::cout << "  ";
	}
}

template<class T>
void Table<T>::set_hash(unsigned int (*hash)(const Key&, unsigned int)) { this->hash = hash; }

template<class T>
void Table<T>::set_rehash(unsigned int (*rehash)(const Key&, unsigned int)) { this->rehash = rehash; }

#endif