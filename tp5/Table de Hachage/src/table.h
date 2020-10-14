#ifndef _TABLE
#define _TABLE

typedef int Key;

#include "element.h"

class Table;

class Case {
	friend class Table;

	private:
		Element element;
		bool free;

	public:
		Case() : free(true) {}
		Case(const Element& e) : element(e), free(false) {}

		void set(const Element& e) { element=e; free=false; }
		Element get() const { return element; }

		bool isFree() const { return free; }
};

class Table {
	private:
		Case* elements;

		unsigned int max_elements;
		unsigned int nb_elements;

		unsigned int (*hash)(const Key&, unsigned int);
		unsigned int (*hash_step)(Key, unsigned int);

	public:
		Table(unsigned int size);
		~Table();

		void add(const Element& e);
		void remove(unsigned int hash_code);
		void show() const;

};

#endif