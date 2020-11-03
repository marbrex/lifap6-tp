// Eldar Kasmamytov

#ifndef _TABLE
#define _TABLE

#include <assert.h>
#include "key.h"
#include "info.h"

// Attention!
// La definition et l'implementation des classes sont dans le meme fichier,
// car ce sont des classes TEMPLATE, en consequence on peut pas diviser
// le definition et l'implementation en deux fichiers.

template<class K, class I>
class Table;

//====================== Case Definition ===========================
template<class K, class I>
class Case {
	friend class Table<K,I>;

	private:
		Key<K> key;
		Info<I> info;
		bool free;	// Indique si la case est libre ou pas

	public:
		Case();
		Case(const Key<K>& k);

		// Resultat: cle contenue dans la case.
		Key<K> get_key() const;

		// Resultat: info contenu dans la case.
		Info<I> get_info() const;

		// Resultat: True si la case est libre,
		//			 False sinon.
		bool isFree() const;

		// Postcondition: L'etat interne de la case est affiche dans le terminal.
		void draw() const;
};

//====================== Case Implementation ===========================
template<class K, class I>
Case<K,I>::Case() : free(true) {}

template<class K, class I>
Case<K,I>::Case(const Key<K>& k) : key(k), free(false) {}

template<class K, class I>
Key<K> Case<K,I>::get_key() const { return key; }

template<class K, class I>
Info<I> Case<K,I>::get_info() const { return info; }

template<class K, class I>
bool Case<K,I>::isFree() const { return free; }

template<class K, class I>
void Case<K,I>::draw() const {
	if(!free) {
		unsigned int try_count = key.get_try_count();
		std::cout << key << "	⏵ " << info;
		std::cout << " (" << try_count << (try_count==1 ? " try" : " tries") << ")" << std::endl;
	}
}



// ======================== Table Definition ==========================
template<class K, class I>
class Table {
	private:
		Case<K,I>* elements;

		unsigned int max_elements; // Le nombre maximum d'elements qu'on peut inserer (taille de la Table)
		unsigned int nb_elements; // Le nombre effectif d'elements presents dans la Table

		unsigned int (*hash)(const K&, unsigned int);
		unsigned int (*rehash)(const K&, unsigned int);

	public:
		// Preconditions: * size=taille de la Table a creer
		//				  * hash=pointeur vers la fonction de hachage
		//					(Key<K>::hash_modulo par defaut)
		//				  * rehash=pointeur vers la fonction de rehachage
		//					(Key<K>::rehash_linear par defaut)
		Table(unsigned int size,
		      unsigned int (*hash)(const K&, unsigned int)=Key<K>::hash_modulo,
		      unsigned int (*rehash)(const K&, unsigned int)=Key<K>::rehash_linear);
		~Table();

		// Preconditions: hash=pointeur vers la fonction de hachage
		// Postcondition: hash est affecte a la donnee membre hash
		void set_hash(unsigned int (*hash)(const K&, unsigned int));

		// Preconditions: rehash=pointeur vers la fonction de rehachage
		// Postcondition: rehash est affecte a la donnee membre rehash
		void set_rehash(unsigned int (*rehash)(const K&, unsigned int));

		// Preconditions: * La taille effective de la Table doit etre inferieure
		//					a la taille maximale,
		//					sinon le reste du code n'est pas execute (assert)
		//				  * Key doit etre unique,
		//					sinon le reste du code n'est pas execute (assert)
		// Postcondition: 'key' et 'info' sont inseres dans la case, dont
		//				  l'indexe est calcule par la fonction 'hash'
		void add(const K& key, const I& info);
		void add(const K& key, const Info<I>& info);
		void add(const Key<K>& key, const Info<I>& info);
		void add(const Key<K>& key, const I& info);

		// Resultat: L'information associee a la cle 'key'
		Info<I> get_info(const K& key) const;
		Info<I> get_info(const Key<K>& key) const;

		// Postcondition: L'information associee a la cle 'key'
		//				  est mise a jour avec 'info'
		void set_info(const K& key, const I& info);
		void set_info(const Key<K>& key, const Info<I>& info);

		// Resultat: L'indexe de la case, dont la cle est identique a 'key'
		unsigned int find(const K& key) const;
		unsigned int find(const Key<K>& key) const;

		// Postcondition: La case dont la cle est 'key'
		//				  est liberee
		void remove(const K& key);

		// Resultat: L'information associee a la cle 'key'
		Info<I> operator[](const K& key) const;

		// Preconditions: extra=afficher ou pas l'information supplementaire
		// Postcondition: L'etat interne de la Table est affiche dans la console
		void show(bool extra=false) const;

};

// ======================== Table Implementation ==========================
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

	if (elements[hash_code].key.get() != key) {
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
}

template<class K, class I>
void Table<K,I>::add (const K& key, const Info<I>& info) { this->add(key,info.get()); }

template<class K, class I>
void Table<K,I>::add (const Key<K>& key, const Info<I>& info) { this->add(key.get(),info.get()); }

template<class K, class I>
void Table<K,I>::add (const Key<K>& key, const I& info) { this->add(key.get(),info); }

template<class K, class I>
void Table<K,I>::show (bool extra) const {
	if (extra) {
		std::cout << "Maximum elements: " << max_elements << std::endl;
		std::cout << "Elements stored: " << nb_elements << std::endl;
	}
	std::cout << "========== Table State ========== \n";
	std::cout << "#INDEX	KEY	⏵ INFO\n";
	for(unsigned int i=0; i<max_elements; ++i) {
		if(!elements[i].free) std::cout << "#" << i << "	";
		elements[i].draw();
	}
	std::cout << "================================= \n";
}

template<class K, class I>
void Table<K,I>::set_hash(unsigned int (*hash)(const K&, unsigned int)) { this->hash = hash; }

template<class K, class I>
void Table<K,I>::set_rehash(unsigned int (*rehash)(const K&, unsigned int)) { this->rehash = rehash; }

template<class K, class I>
Info<I> Table<K,I>::get_info(const K& key) const {
	unsigned int index = find(key);
	return elements[index].info;
}

template<class K, class I>
Info<I> Table<K,I>::get_info(const Key<K>& key) const { return get_info(key.get()); }

template<class K, class I>
unsigned int Table<K,I>::find(const K& key) const {
	unsigned int index = hash(key, max_elements);

	assert(!elements[index].free);
	
	while (elements[index].key.get() != key)
		index += rehash(key, max_elements);
	
	return index;
}

template<class K, class I>
unsigned int Table<K,I>::find(const Key<K>& key) const { return find(key.get()); }

template<class K, class I>
void Table<K,I>::remove(const K& key) {
	unsigned int index = find(key);

	elements[index].free = true;
	--nb_elements;
}

template<class K, class I>
Info<I> Table<K,I>::operator[](const K& key) const { return get_info(key); }

template<class K, class I>
void Table<K,I>::set_info(const K& key, const I& info) {
	unsigned int index = find(key);
	elements[index].info = info;
}

template<class K, class I>
void Table<K,I>::set_info(const Key<K>& key, const Info<I>& info) {
	unsigned int index = find(key);
	elements[index].info = info;
}

#endif