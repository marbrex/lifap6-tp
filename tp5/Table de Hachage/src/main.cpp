#include "element.h"
#include "table.h"

int main() {
  Table t(10);

  Element e;
  e.key = 5;

  Element e2;
  e2.key = 2;

  t.add(e);
  t.add(e2);
  t.show();

  return 0;
}
