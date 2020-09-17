// LIFAP6 - Automne 2017 - R. Chaine

#include "element.h"
#include "liste.h"
#include <cstdio>

int main()
{
  // Liste lili;
  // std::printf("Lili\n");
  // lili.affichage();
  // for(int i=1;i<5;i++)
  //   lili.ajoutEnTete(i);
  // std::printf("Lili\n");
  // lili.affichage();
  // for(int i=10;i<15;i++)
  //   lili.ajoutEnQueue(i);
  // std::printf("Lili\n");
  // lili.affichage();
  // Liste lolo(lili);
  // std::printf("Lolo\n");
  // lolo.affichage();
  // lili.vide();
  // std::printf("Lolo\n");
  // lolo.affichage();
  // lolo=lili;
  // printf("Lolo\n");
  // lolo.affichage();

  Liste l;

  std::cout << "Ajout en tete de 5 : " << std::endl;
  l.ajoutEnTete(5);
  l.affichage();

  std::cout << "Ajout en tete de 2 : " << std::endl;
  l.ajoutEnTete(2);
  l.affichage();

  std::cout << "Ajout en tete de 8 : " << std::endl;
  l.ajoutEnTete(8);
  l.affichage();

  return 0;
}
