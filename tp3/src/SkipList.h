#ifndef _SKIPLIST
#define _SKIPLIST

#include "element.h"
#include <iostream>
#include <vector>

class SkipList;

class Cellule {
    friend class SkipList;

    private:
        Elem info;
        std::vector<Cellule*> niveaux;
};

class SkipList {
	public:
        //Constructeurs-------------------------------------------------------------
        SkipList();
        //Postcondition : la SkipList initialisee est vide

        SkipList(const SkipList & l);
        //Postcondition : la SkipList initialisee et l correspondent a des SkipLists identiques
        //                (mais elles sont totalement independantes l'une de l'autre)
        
        //Destructeur---------------------------------------------------------------
        ~SkipList();

        //Fonctions membres---------------------------------------------------------
        void inserer(const Elem& e);
        //Precondition : la Skip List est triee
        //Postcondition : l'element "e" est insere dans la Skip List

        void afficher() const;

        bool estVide();

        // void etablirProchainNiveau();
        
    private:

        //Donnees membres-----------------------------------------------------------
        Cellule *ad;
        unsigned int count;
        unsigned int nb_niveaux;
};

#endif