#ifndef _INFO
#define _INFO

#include <iostream>

template<class T>
class Info {
	private:
		T* value;

	public:
		Info();
		Info(const T& value);
		~Info();

		T get() const;
		void set(const T& value);

		friend std::ostream& operator<<(std::ostream& output, const Info<T>& i) { 
			output << *i.value;
			return output;
		}

		friend std::istream& operator>>(std::istream& input, Info<T>& i) {
			T temp;
			input >> temp;
			i.value = new T(temp);
			return input;
		}

		Info<T>& operator=(const Info<T>& info);
};

template<class T>
Info<T>::Info() { value = nullptr; }

template<class T>
Info<T>::Info(const T& value) { this->value = new T(value); }

template<class T>
Info<T>::~Info() {
	if(value) {
		delete value;
		value = nullptr;
	}
}

template<class T>
T Info<T>::get() const { return *value; }

template<class T>
void Info<T>::set(const T& val) {
	if (!this->value) this->value = new T(val);
	else *this->value = val;
}

template<class T>
Info<T>& Info<T>::operator=(const Info<T>& info) {
	if (!this->value) this->value = new T(*info.value);
	else *this->value = *info.value;
	return *this;
}

#endif
