// Eldar Kasmamytov

#ifndef _INFO
#define _INFO

#include <iostream>
#include <assert.h>

// Attention!
// La definition et l'implementation des classes sont dans le meme fichier,
// car ce sont des classes TEMPLATE, en consequence on peut pas diviser
// le definition et l'implementation en deux fichiers.

//====================== Info Definition ===========================
template<class T>
class Info {
	private:
		T value;
		bool empty; // Indique si 'value' est vide ou pas

	public:
		// Constructeurs
		Info();
		Info(const T& value);

		// Resultat: L'information stockee dans la variable 'value' de la classe.
		T get() const;

		// Postcondition: L'information est initialisee ou mise a jour par la valeur 'value'.
		void set(const T& value);

		// Resultat: True si l'Info ne contient pas de valeur,
		//			 False sinon.
		bool isEmpty() const;

		// Resultat: Retourne l'Info affectee.
		// Postcondition: L'information est initialisee ou mise a jour par la valeur 'info'.
		Info<T>& operator=(const T& info);
		Info<T>& operator=(const Info<T>& info);

		// Resultat: True si l'information des deux Infos est identique,
		//			 False sinon.
		bool operator==(const Info<T>& info) const;
		bool operator==(const T& info) const;

		// Resultat: True si les informations des deux Infos ne sont pas identiques,
		//			 False sinon.
		bool operator!=(const Info<T>& info) const;
		bool operator!=(const T& info) const;

		// Surcharhe de l'operateur '<<'
		friend std::ostream& operator<<(std::ostream& output, const Info<T>& i) { 
			output << i.value;
			return output;
		}

		// Surcharhe de l'operateur '>>'
		friend std::istream& operator>>(std::istream& input, Info<T>& i) {
			input >> i.value;
			return input;
		}
};

//====================== Info Implementation ===========================
template<class T>
Info<T>::Info() : empty(true) {}

template<class T>
Info<T>::Info(const T& val) : value(val), empty(false) {}

template<class T>
T Info<T>::get() const { return value; }

template<class T>
void Info<T>::set(const T& val) {
	this->value = val;
	empty = false;
}

template<class T>
bool Info<T>::isEmpty() const { return empty; }

template<class T>
Info<T>& Info<T>::operator=(const Info<T>& info) {
	set(info.value);
	return *this;
}

template<class T>
Info<T>& Info<T>::operator=(const T& info) {
	set(info);
	return *this;
}

template<class T>
bool Info<T>::operator==(const Info<T>& info) const {
	assert(!empty && !info.empty);
	return this->value == info.value;
}

template<class T>
bool Info<T>::operator==(const T& info) const {
	assert(!empty);
	return this->value == info;
}

template<class T>
bool Info<T>::operator!=(const Info<T>& info) const {
	assert(!empty && !info.empty);
	return this->value != info.value;
}

template<class T>
bool Info<T>::operator!=(const T& info) const {
	assert(!empty);
	return this->value != info;
}

#endif
