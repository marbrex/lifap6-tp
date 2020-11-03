// Eldar Kasmamytov

#ifndef _KEY
#define _KEY

#include <iostream>

// Attention!
// La definition et l'implementation des classes sont dans le meme fichier,
// car ce sont des classes TEMPLATE, en consequence on peut pas diviser
// le definition et l'implementation en deux fichiers.

//====================== Key Definition ===========================
template<class T>
class Key {
	private:
		T value;
		bool empty; // Indique si 'value' est vide ou pas
		unsigned int try_count; // Le nombre d'essais lors de l'insertion (0 a la declaration)

	public:
		// Constructeurs
		Key();
		Key(const T& value);

		// Resultat: La cle stockee dans la variable 'value' de la classe.
		T get() const;

		// Postcondition: La cle est initialisee ou mise a jour par la valeur 'value'.
		void set(const T& value);

		// Resultat: True si la cle Key ne contient pas de valeur,
		//			 False sinon.
		bool isEmpty() const;

		// Resultat: Retourne la cle Key affectee.
		// Postcondition: La cle est initialisee ou mise a jour par la valeur 'key'.
		Key<T>& operator=(const Key<T>& key);
		Key<T>& operator=(const T& key);

		// Resultat: True si les clefs des deux Key sont identiques,
		//			 False sinon.
		bool operator==(const Key<T>& key) const;
		bool operator==(const T& key) const;

		// Resultat: True si les clefs des deux Key ne sont pas identiques,
		//			 False sinon.
		bool operator!=(const Key<T>& key) const;
		bool operator!=(const T& key) const;

		// Resultat: Le nombre d'essais d'insertion
		unsigned int get_try_count() const;

		// Postcondition: Le nombre d'essais d'insertion et mis a jour par 'nb'
		void set_try_count(unsigned int nb);

		// Fonction de hachage pour 'k' de type nombre
		// Resultat: Retourne le reste de la division de 'size' par 'k'
		static unsigned int hash_modulo (const T& k, unsigned int size);

		// Fonction de rehachage pour 'k' de type nombre
		// Resultat: Retourne 1, que l'on apres va ajouter a l'index
		static unsigned int rehash_linear (const T& k, unsigned int try_nb);

		// Surcharhe de l'operateur '<<'
		friend std::ostream& operator<<(std::ostream& output, const Key<T>& k) { 
			output << k.value;
			return output;
		}

		// Surcharhe de l'operateur '>>'
		friend std::istream& operator>>(std::istream& input, Key<T>& k) {
			input >> k.value;
			return input;
		}
};

//====================== Key Implementation ===========================
template<class T>
Key<T>::Key() : empty(true), try_count(0) {}

template<class T>
Key<T>::Key(const T& val) : value(val), empty(false), try_count(0) {}

template<class T>
bool Key<T>::isEmpty() const { return empty; }

template<class T>
unsigned int Key<T>::hash_modulo (const T& k, unsigned int size) { return k % size; }

template<class T>
unsigned int Key<T>::rehash_linear (const T& k, unsigned int try_nb) { return 1; }

template<class T>
T Key<T>::get() const { return value; }

template<class T>
void Key<T>::set(const T& val) {
	this->value = val;
	empty = false;
}

template<class T>
unsigned int Key<T>::get_try_count() const { return try_count; }

template<class T>
void Key<T>::set_try_count(unsigned int nb) { try_count = nb; }

template<class T>
Key<T>& Key<T>::operator=(const Key<T>& key) {
	set(key.value);
	return *this;
}

template<class T>
Key<T>& Key<T>::operator=(const T& key) {
	set(key);
	return *this;
}

template<class T>
bool Key<T>::operator==(const Key<T>& key) const {
	assert(!empty && !key.empty);
	return this->value == key.value;
}

template<class T>
bool Key<T>::operator==(const T& key) const {
	assert(!empty);
	return this->value == key;
}

template<class T>
bool Key<T>::operator!=(const Key<T>& key) const {
	assert(!empty && !key.empty);
	return this->value != key.value;
}

template<class T>
bool Key<T>::operator!=(const T& key) const {
	assert(!empty);
	return this->value != key;
}

#endif
