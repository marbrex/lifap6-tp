#ifndef _INFO
#define _INFO

#include <iostream>

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

		friend std::ostream& operator<<(std::ostream& output, const Info<T>& i) { 
			output << i.value;
			return output;
		}

		friend std::istream& operator>>(std::istream& input, Info<T>& i) {
			T temp;
			input >> temp;
			i.value = temp;
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
	this->value = info.value;
	return *this;
}

#endif
