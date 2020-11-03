#ifndef _KEY
#define _KEY

#include <iostream>

template<class T>
class Key {
	private:
		T value;
		bool empty;
		unsigned int try_count;

	public:
		Key();
		Key(const T& value);

		T get() const;
		void set(const T& value);

		bool isEmpty() const;

		Key<T>& operator=(const Key<T>& key);

		unsigned int get_try_count() const;
		void set_try_count(unsigned int nb);

		static unsigned int hash_modulo (const T& k, unsigned int size);
		static unsigned int rehash_linear (const T& k, unsigned int try_nb);

		friend std::ostream& operator<<(std::ostream& output, const Key<T>& k) { 
			output << k.value;
			return output;
		}

		friend std::istream& operator>>(std::istream& input, Key<T>& k) {
			T temp;
			input >> temp;
			k.value = temp;
			return input;
		}
};

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
void Key<T>::set(const T& val) { this->value = val; }

template<class T>
unsigned int Key<T>::get_try_count() const { return try_count; }

template<class T>
void Key<T>::set_try_count(unsigned int nb) { try_count = nb; }

template<class T>
Key<T>& Key<T>::operator=(const Key<T>& key) {
	this->value = key.value;
	return *this;
}

#endif
