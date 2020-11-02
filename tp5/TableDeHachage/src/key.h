#ifndef _KEY
#define _KEY

#include <iostream>

template<class T>
class Key {
	private:
		T* value;

	public:
		Key();
		Key(const T& value);
		~Key();

		T get() const;
		void set(const T& value);

		friend std::ostream& operator<<(std::ostream& output, const Key<T>& k) { 
			output << *k.value;
			return output;
		}

		friend std::istream& operator>>(std::istream& input, Key<T>& k) {
			T temp;
			input >> temp;
			k.value = new T(temp);
			return input;
		}

		Key<T>& operator=(const Key<T>& key);
};

template<class T>
Key<T>::Key() { value = nullptr; }

template<class T>
Key<T>::Key(const T& value) { this->value = new T(value); }

template<class T>
Key<T>::~Key() {
	if(value) {
		delete value;
		value = nullptr;
	}
}

template<class T>
T Key<T>::get() const { return *value; }

template<class T>
void Key<T>::set(const T& val) {
	if (!this->value) this->value = new T(val);
	else *this->value = val;
}

template<class T>
Key<T>& Key<T>::operator=(const Key<T>& key) {
	if (!this->value) this->value = new T(*key.value);
	else *this->value = *key.value;
	return *this;
}

#endif
