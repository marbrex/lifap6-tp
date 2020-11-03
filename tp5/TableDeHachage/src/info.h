#ifndef _INFO
#define _INFO

#include <iostream>
#include <assert.h>

template<class T>
class Info {
	private:
		T value;
		bool empty;

	public:
		Info();
		Info(const T& value);

		T get() const;
		void set(const T& value);

		bool isEmpty() const;

		Info<T>& operator=(const Info<T>& info);
		Info<T>& operator=(const T& info);

		bool operator==(const Info<T>& info) const;
		bool operator==(const T& info) const;

		bool operator!=(const Info<T>& info) const;
		bool operator!=(const T& info) const;

		friend std::ostream& operator<<(std::ostream& output, const Info<T>& i) { 
			output << i.value;
			return output;
		}

		friend std::istream& operator>>(std::istream& input, Info<T>& i) {
			input >> i.value;
			return input;
		}
};

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
