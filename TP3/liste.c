#include "liste.h"

/*
	INITIALISER_LISTE

	Cette fonction initialise la liste recue. Au depart, la liste est vide.

	PARAMETRE :
		- ptr_liste : L'adresse de la liste a initialiser (t_liste_chainee *).

	RETOUR : Aucun.
*/
void initialiser_liste(t_liste_chainee * ptr_liste)
{
	ptr_liste->tete = NULL;			
	ptr_liste->queue = NULL;				
	ptr_liste->nb_maillons = 0;	
}

/*
	TAILLE_LISTE

	Cette fonction retourne le nombre de maillons dans la liste.

	PARAMETRE :
		- ptr_liste : L'adresse de la liste a consulter
					  (const t_liste_chainee *).

	RETOUR : Le nombre de chaines dans la liste.
*/
long int taille_liste(const t_liste_chainee * ptr_liste)
{
	return ptr_liste->nb_maillons;
}


/*
	AJOUTER_DEBUT_LISTE

	Cette fonction ajoute une chaine et son code au debut d'une liste.
	On ne valide pas si la chaine est deja presente.

	PARAMETRE :
		- ptr_liste  : L'adresse de la liste ou l'on ajoute
					   (const t_liste_chainee *).
	    - ptr_chaine : L'adresse de la chaine a ajouter dans la liste
					   (const t_chaine *).
		- ptr_code   : Le code de la chaine a ajouter dans la liste
					   (unsigned int).

	RETOUR : 1 si l'ajout a fonctionne et 0 dans le cas contraire.

	EXEMPLE D'APPEL :
		t_liste_chainee une_liste;
		t_chaine une_chaine;
		initialiser_liste(&une_liste);
		vider_chaine(&une_chaine);
		ajouter_caractere(&une_chaine, 'A');
		ajouter_debut_liste(&une_liste, &une_chaine, 256);

	ATTENTION : On suppose que la fonction INITIALISER_LISTE a ete
				appelee une fois sur ptr_liste.
*/
int ajouter_debut_liste(t_liste_chainee * ptr_liste,
						const t_chaine * ptr_chaine,
						unsigned int code)
{

	ptr_liste -> tete = ptr_chaine;
}



/*
	AJOUTER_CHAINE_FIN_LISTE

	Cette fonction ajoute une chaine et son code a la fin d'une liste.
	On ne valide pas si la chaine est deja presente.

	PARAMETRE :
		- ptr_liste  : L'adresse de la liste ou l'on ajoute
					   (const t_liste_chainee *).
	    - ptr_chaine : L'adresse de la chaine a ajouter dans la liste
					   (const t_chaine *).
		- ptr_code   : Le code de la chaine a ajouter dans la liste
					   (unsigned int).

	RETOUR : 1 si l'ajout a fonctionne et 0 dans le cas contraire.

	EXEMPLE D'APPEL :
		t_liste_chainee une_liste;
		t_chaine une_chaine;
		initialiser_liste(&une_liste);
		vider_chaine(&une_chaine);
		ajouter_caractere(&une_chaine, 'A');
		ajouter_fin_liste(&une_liste, &une_chaine, 256);

	ATTENTION : On suppose que la fonction INITIALISER_LISTE a ete
				appelee une fois sur ptr_liste.
*/
int ajouter_fin_liste(t_liste_chainee * ptr_liste,
					  const t_chaine * ptr_chaine,
					  unsigned int code);



/*
	CHERCHER_CHAINE_DANS_LISTE

	Cette fonction recherche une chaine dans une liste et renvoie
	le code associe a cette chaine.

	PARAMETRE :
		- ptr_liste  : L'adresse de la liste a consulter
					   (const t_liste_chainee *).
	    - ptr_chaine : L'adresse de la chaine a trouver dans la liste
					   (const t_chaine *).
		- ptr_code   : (SORTIE) L'adresse ou ecrire le code correspondant
					   a la chaine recue (unsigned int *).

	RETOUR : 1 si le code est present et 0 dans le cas contraire. Si le
			 code est present, *ptr_chaine est modifie.

	EXEMPLE D'APPEL :
		t_liste_chainee une_liste;
		t_chaine une_chaine;
		unsigned int code;
		initialiser_liste(&une_liste);
		vider_chaine(&une_chaine);
		ajouter_caractere(&une_chaine, 'A');
		ajouter_fin_liste(&une_liste, &une_chaine, 256);
		chercher_chaine_dans_liste(&une_liste, &une_chaine, &code);

	ATTENTION : On suppose que la fonction INITIALISER_LISTE a ete
				appelee une fois sur ptr_liste.
*/
int chercher_chaine_dans_liste(const t_liste_chainee * ptr_liste,
							   const t_chaine * ptr_chaine,
							   unsigned int * ptr_code);



/*
	CHERCHER_CODE_DANS_LISTE

	Cette fonction recherche un code dans une liste et renvoie la
	chaine associee a ce code.

	PARAMETRE :
		- ptr_liste  : L'adresse de la liste a consulter
					   (const t_liste_chainee *).
	    - code       : Le code a trouver dans la liste (unsigned int).
		- ptr_chaine : (SORTIE) L'adresse ou ecrire la chaine correspondant
					   au code recu (t_chaine *).

	RETOUR : 1 si le code est present et 0 dans le cas contraire. Si le
			 code est present, *ptr_chaine est modifie.

	EXEMPLE D'APPEL :
		t_liste_chainee une_liste;
		t_chaine une_chaine;
		initialiser_liste(&une_liste);
		vider_chaine(&une_chaine);
		ajouter_caractere(&une_chaine, 'A');
		ajouter_fin_liste(&une_liste, &une_chaine, 256);
		vider_chaine(&une_chaine);
		chercher_code_dans_liste(&une_liste, 256, &une_chaine);

	ATTENTION : On suppose que la fonction INITIALISER_LISTE a ete
				appelee une fois sur ptr_liste.
*/
int chercher_code_dans_liste(const t_liste_chainee * ptr_liste,
							 unsigned int code,
							 t_chaine * ptr_chaine);



/*
	VIDER_LISTE

	Cette fonction vide la liste.

	PARAMETRE :
		- ptr_liste : L'adresse de la liste a vider (t_liste_chainee *).

	RETOUR : Aucun. Cependant, la liste pointee est videe.

	EXEMPLE D'APPEL :
		t_liste_chainee une_liste;
		initialiser_liste(&une_liste);
		vider_liste(&une_liste);

	ATTENTION : On suppose que la fonction INITIALISER_LISTE a ete
				appelee une fois sur ptr_liste.
*/
void vider_liste(t_liste_chainee * ptr_liste);
