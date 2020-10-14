#include "table.h"

int main() {
  Table t(10);

  t.add(8);
  t.add(2);
  t.add(2);
  t.add(2);
  t.add(3);
  t.add(7);
  t.add(9);
  t.add(4);
  t.add(1);
  t.add(6);

  t.show();

  return 0;
}
