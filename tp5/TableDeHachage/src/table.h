#ifndef _TABLE
#define _TABLE

#include <assert.h>
#include "key.h"
#include "info.h"

template<class K, class T>
class Table;

template<class K, class T>
class Case {
	friend class Table<K,T>;

	private:
		bool free;

	public:
		Key<K> key;
		Info<T> info;

		Case() : free(true) {}
		Case(const Key<K>& k) : key(k), free(false) {}

		bool isFree() const { return free; }
};

template<class K, class T>
class Table {
	private:
		Case<K,T>* elements;

		unsigned int max_elements;
		unsigned int nb_elements;

		unsigned int (*hash)(const K&, unsigned int);
		unsigned int (*rehash)(const K&, unsigned int);

		static unsigned int hash_modulo (const K& k, unsigned int size);
		static unsigned int rehash_linear (const K& k, unsigned int try_nb);

	public:
		Table(unsigned int size, unsigned int (*hash)(const K&, unsigned int)=hash_modulo);
		~Table();

		void set_hash(unsigned int (*hash)(const K&, unsigned int));
		void set_rehash(unsigned int (*rehash)(const K&, unsigned int));

		void add(const K& key, const T& info);
		void add(const K& key, const Info<T>& info);
		void add(const Key<K>& key, const Info<T>& info);
		void add(const Key<K>& key, const T& info);

		void remove(unsigned int hash_code);
		void show() const;

};

template<class K, class T>
unsigned int Table<K,T>::hash_modulo (const K& k, unsigned int size) { return k % size; }

template<class K, class T>
unsigned int Table<K,T>::rehash_linear (const K& k, unsigned int try_nb) { return 1; }

template<class K, class T>
Table<K,T>::Table (unsigned int size, unsigned int (*hash)(const K&, unsigned int))
	: max_elements(size), nb_elements(0), hash(hash) {
	elements = new Case<K,T>[size];
	rehash = rehash_linear;
}

template<class K, class T>
Table<K,T>::~Table () { delete [] elements; }

template<class K, class T>
void Table<K,T>::add (const K& key, const T& info) {
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
		elements[hash_code].key.set(key);
		elements[hash_code].info.set(info);
		elements[hash_code].free = false;
		++nb_elements;
	}
}

template<class K, class T>
void Table<K,T>::add (const K& key, const Info<T>& info) { this->add(key,info.get()); }

template<class K, class T>
void Table<K,T>::add (const Key<K>& key, const Info<T>& info) { this->add(key.get(),info.get()); }

template<class K, class T>
void Table<K,T>::add (const Key<K>& key, const T& info) { this->add(key.get(),info); }

template<class K, class T>
void Table<K,T>::show () const {
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

template<class K, class T>
void Table<K,T>::set_hash(unsigned int (*hash)(const K&, unsigned int)) { this->hash = hash; }

template<class K, class T>
void Table<K,T>::set_rehash(unsigned int (*rehash)(const K&, unsigned int)) { this->rehash = rehash; }

#endif