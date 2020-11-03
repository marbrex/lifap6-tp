#ifndef _TABLE
#define _TABLE

#include <assert.h>
#include "key.h"
#include "info.h"

template<class K, class I>
class Table;

template<class K, class I>
class Case {
	friend class Table<K,I>;

	private:
		Key<K> key;
		Info<I> info;
		bool free;

	public:
		Case() : free(true) {}
		Case(const Key<K>& k) : key(k), free(false) {}

		Key<K> get_key() const { return key; }
		Info<I> get_info() const { return info; }

		bool isFree() const { return free; }
};

template<class K, class I>
class Table {
	private:
		Case<K,I>* elements;

		unsigned int max_elements;
		unsigned int nb_elements;

		unsigned int (*hash)(const K&, unsigned int);
		unsigned int (*rehash)(const K&, unsigned int);

	public:
		Table(unsigned int size,
		      unsigned int (*hash)(const K&, unsigned int)=Key<K>::hash_modulo,
		      unsigned int (*rehash)(const K&, unsigned int)=Key<K>::rehash_linear);
		~Table();

		void set_hash(unsigned int (*hash)(const K&, unsigned int));
		void set_rehash(unsigned int (*rehash)(const K&, unsigned int));

		void add(const K& key, const I& info);
		void add(const K& key, const Info<I>& info);
		void add(const Key<K>& key, const Info<I>& info);
		void add(const Key<K>& key, const I& info);

		Info<I> find(const K& key) const;
		Info<I> find(const Key<K>& key) const;

		void show() const;

};

template<class K, class I>
Table<K,I>::Table (unsigned int size,
				   unsigned int (*hash)(const K&, unsigned int),
				   unsigned int (*rehash)(const K&, unsigned int))
				   : max_elements(size), nb_elements(0), hash(hash), rehash(rehash) {
	elements = new Case<K,I>[size];
}

template<class K, class I>
Table<K,I>::~Table () { delete [] elements; elements = nullptr; }

template<class K, class I>
void Table<K,I>::add (const K& key, const I& info) {
	assert(nb_elements < max_elements);

	unsigned int hash_code = hash(key, max_elements);

	if(!elements[hash_code].free)
		assert(elements[hash_code].key.get() != key);

	unsigned int try_nb = 1;

	while(!elements[hash_code].free) {
		hash_code += rehash(key, try_nb++);
		if(hash_code >= max_elements) {
			hash_code = hash_code % max_elements;
		}
	}

	if (elements[hash_code].free) {
		elements[hash_code].key.set(key);
		elements[hash_code].key.set_try_count(try_nb);
		elements[hash_code].info.set(info);
		elements[hash_code].free = false;
		++nb_elements;
	}
}

template<class K, class I>
void Table<K,I>::add (const K& key, const Info<I>& info) { this->add(key,info.get()); }

template<class K, class I>
void Table<K,I>::add (const Key<K>& key, const Info<I>& info) { this->add(key.get(),info.get()); }

template<class K, class I>
void Table<K,I>::add (const Key<K>& key, const I& info) { this->add(key.get(),info); }

template<class K, class I>
void Table<K,I>::show () const {
	std::cout << "Maximum elements: " << max_elements << std::endl;
	std::cout << "Elements stored: " << nb_elements << std::endl;
	for(unsigned int i=0; i<max_elements; ++i) {
		if(!elements[i].free) {
			std::cout << "[" << elements[i].key << "->";
			std::cout << elements[i].info << "]";
			// std::cout << elements[i].info << "->";
			// std::cout << elements[i].key.get_try_count() << "]";
		}
		else std::cout << "[ ]";

		if (i==max_elements-1) std::cout << std::endl;
		else std::cout << "  ";
	}
}

template<class K, class I>
void Table<K,I>::set_hash(unsigned int (*hash)(const K&, unsigned int)) { this->hash = hash; }

template<class K, class I>
void Table<K,I>::set_rehash(unsigned int (*rehash)(const K&, unsigned int)) { this->rehash = rehash; }

template<class K, class I>
Info<I> Table<K,I>::find(const K& key) const {
	unsigned int index = hash(key, max_elements);

	assert(!elements[index].free);
	
	while (elements[index].key.get() != key)
		index += rehash(key, max_elements);
	
	return elements[index].info;
}

template<class K, class I>
Info<I> Table<K,I>::find(const Key<K>& key) const { return find(key.get()); }

#endif