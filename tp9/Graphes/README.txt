================== Graph d'un terrain ==================
Module realise par Eldar Kasmamytov


===== Fonctionnalites presentes dans le module =====
Le module fournit:

- Constructeurs
  - un constructeur qui prend en parametres
    les dimensions du terrain, en remplissant
    le tableau des hauteurs avec des zeros.
    (terrain plat)
  - un constructeur qui prend en parametres
    une chaine de caracteres, qui represente
    un fichier a importer.

- Generation d'un terrain
  Genere un terrain a partir les arguments
  passes en parametres. La fonction prend
  en parametres les dimensions du terrain,
  la hauteur maximale et le nom du fichier
  dans lequel les donnees vont etre sauvegardes.

- Consultation et Modification des hauteurs

- Possibilite de recuperer l'indice globale
  d'une case de la grille, en fonction de ses
  coordonnees.
  Ou l'indice globale de l'un de ses voisins,
  s'il y en a.

- Affichage du terrain avec les differents
  couleurs, qui changent en fonction de la
  hauteurs du sommet.
  Affiche egalement un bareme des hauteurs
  intermediaires et des couleurs associees.

- L'algorithme de Dijkstra.
  La fonction prend en parametres l'ensemble
  des points (librairies) et applique
  l'algorithme de Dijkstra pour chaque case
  de la grille vers chaqu'un de ces points.
  La file de priorite est utilisee pour
  gerer l'odre de traitement des noeuds gris.
  Comme resultat les tableaux membres prefixes
  par path_* sont remplis.
  - path_dist: Les plus courts chemins
  - path_clrs: Les couleurs des points
  - path_prev: Les points precedents
  POUR AFFICHER/CACHER LES ETAPES DE
  TRAITEMENT METTRE TRUE/FALSE !



