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

  std::cout << "Ajout en tete de 97 : " << std::endl;
  l.ajoutEnTete(97);
  l.affichage();


  std::cout << "Insertion de 101 : " << std::endl;
  l.insere(101);
  l.affichage();

  std::cout << "Insertion de 96 : " << std::endl;
  l.insere(96);
  l.affichage();

  std::cout << "Insertion de 98 : " << std::endl;
  l.insere(98);
  l.affichage();

  std::cout << "Etablissement Second Niveau : " << std::endl;
  l.etablissementSecondNiveau();
  l.affichage();

  std::cout << "Affichage Second Niveau : " << std::endl;
  l.affichageSecondNiveau();

  return 0;
}
