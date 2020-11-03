================== Arbre Binaire de Recherche ==================
Module realise par Eldar Kasmamytov


===== Fonctionnalites presentes dans le module =====

- Constructeur par copie (copie profonde)
	Possibilite de faire une copie a partir d'un noeud 'n'.

- Surcharge de l'operateur d'affectation (copie profonde)

- Recherche d'un element

- Insertion d'un element

- Suppression d'un element
	- Si le noeud est une feuille,
	  alors le noeud est supprime simplement.
	- Si le noeud possede un fils,
	  alors le noeud est supprime, et son fils
	  est rebranche au pere du noeud supprime.
	- Si le noeud possede deux fils,
	  alors le noeud est supprime et remplace par
	  son plus proche predecesseur.

- Parcours de l'arbre dans differents ordres:
	- Ordre INFIX
	- Ordre PREFIX (1)
	- Ordre POSTFIX (2)
	Fonction qui prend en parametre un pointeur de fonction 'handler',
	qui est appele pour chaque element lors de parcours. Par defaut,
	la fonction de traitement est 'list_elements' qui affiche les elements
	dans l'ordre indique.
	Par exemple, a est de type ABR.
		Insertion des elements dans a dans l'ordre suivant:
		6,3,9,8,4,2,10,5,1,11.

		Appel a 'a.parcours(0)' (ordre INFIX):
		1 2 3 4 5 6 8 9 10 11 

		Appel a 'a.parcours(1)' (ordre PREFIX):
		6 3 2 1 4 5 9 8 10 11 

		Appel a 'a.parcours(2)' (ordre POSTFIX):
		1 2 5 4 3 8 11 10 9 6 

		Appel a 'a.parcours(1, mult_by_two)' (ordre PREFIX, fonction MULTIPLICATION par 2): 
		12 6 4 2 8 10 18 16 20 22 
		a est change.

- Affichage de l'ABR entier ou d'un sous-ABR sous forme d'un arbre
	(en utilisant parcours en largeur).
	Possibilite d'afficher les informations supplementaires,
	si le parametre 'extra' specifie.
	Par exemple, a est de type ABR.
		Insertion des elements dans a dans l'ordre suivant:
		6,3,9,8,4,2,10,5,1,11.

		Appel a 'a.draw(true)' affiche l'arbre suivant:
			Number of Elements         : 10
			Depth (Number of Levels)   : 4
			Max Elements on Last Level : 8

			   ┌───6───┐   
			 ┌─3─┐   ┌─9─┐ 
			┌2   4┐  8   10┐
			1     5       11

- Accesseur du premier noeud
- Accesseur du pere d'un element
- Accesseur de la profondeur de l'ABR (nombre de niveaux)