// LIFAP6 - Automne 2017 - R. Chaine

#include "element.h"
#include "liste_triee.h"
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

  std::cout << "Ajout en tete de 100 : " << std::endl;
  l.ajoutEnTete(100);
  l.affichage();

  std::cout << "Ajout en tete de 99 : " << std::endl;
  l.ajoutEnTete(99);
  l.affichage();

  std::cout << "Ajout en tete de 98 : " << std::endl;
  l.ajoutEnTete(98);
  l.affichage();

  return 0;
}
