#ifndef _TABLE
#define _TABLE

#include "key.h"
#include <assert.h>

class Table;

class Case {
	friend class Table;

	private:
		Key key;
		bool free;

	public:
		Case() : free(true) {}
		Case(const Key& k) : key(k), free(false) {}

		void set(const Key& k) { key=k; free=false; }
		Key get() const { return key; }

		bool isFree() const { return free; }
};

class Table {
	private:
		Case* elements;

		unsigned int max_elements;
		unsigned int nb_elements;

		unsigned int (*hash)(const Key&, unsigned int);
		unsigned int (*hash_step)(const Key&, unsigned int);

	public:
		Table(unsigned int size);
		~Table();

		void add(const Key& e);
		void remove(unsigned int hash_code);
		void show() const;

};

#endif