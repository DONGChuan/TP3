#include "dictionnaire.h"

/*
	INITIALISER_DICTIONNAIRE

	Cette fonction initialise le dictionnaire. Au depart, celui-ci est vide.
*/
void initialiser_dictionnaire(t_dictionnaire * ptr_dictionnaire)
{
	initialiser_liste(ptr_dictionnaire->groupe_par_caractere);
	initialiser_liste(ptr_dictionnaire->groupe_par_code);
	ptr_dictionnaire->nb_chaines = 0;
}

/*
	NB_CHAINES_DICTIONNAIRE

	Cette fonction retourne le nombre de chaines presentes dans le
	dictionnaire.

	PARAMETRE :
		- ptr_dictionnaire : L'adresse du dictionnaire a consulter
							 (const t_dictionnaire *).

	RETOUR : Le nombre de chaines dans le dictionnaire.
			 Cette valeur sera toujours >= 0.

	EXEMPLE D'APPEL :
		t_dictionnaire un_dictionnaire;
		initialiser_dictionnaire(&un_dictionnaire);
		printf("%li\n", nb_chaines_dictionnaire(&un_dictionnaire));

	ATTENTION : On suppose que la fonction INITIALISER_DICTIONNAIRE a ete
				appelee une fois sur ptr_dictionnaire.
*/
long int nb_chaines_dictionnaire(const t_dictionnaire * ptr_dictionnaire);



/*
	AJOUTER_UNE_CHAINE

	Cette fonction ajoute une chaine dans le dictionnaire. Cette chaine se voit
	automatiquement assignee le code correspondant au nombre de chaines dans
	le dictionnaire avant l'ajout.

	A NOTER : On suppose que la chaine n'est pas deja presente et qu'elle
			  n'est pas vide. On ne verifie pas pour des raisons de vitesse.

	PARAMETRES :
		- ptr_dictionnaire  : L'adresse du dictionnaire ou l'on souhaite
							  ajouter une chaine (t_dictionnaire *).
	    - ptr_chaine : L'adresse de la chaine a ajouter (const t_chaine *).

	RETOUR : 1 en cas de succes et 0 dans le cas contraire
			 (s'il n'y a plus de memoire).

	EXEMPLE D'APPEL :
		t_dictionnaire un_dictionnaire;
		t_chaine une_chaine;
		initialiser_dictionnaire(&un_dictionnaire);
		vider_chaine(&une_chaine);
		ajouter_caractere(&une_chaine, 'A');
		ajouter_une_chaine(&un_dictionnaire, &une_chaine);

	ATTENTION : On suppose que la fonction INITIALISER_DICTIONNAIRE a ete
				appelee une fois sur ptr_dictionnaire.
*/
int ajouter_une_chaine(t_dictionnaire * ptr_dictionnaire,
					   const t_chaine * ptr_chaine);



/*
	CODE_DE_LA_CHAINE

	Cette fonction recherche une chaine dans le dictionnaire.

	PARAMETRES :
		- ptr_dictionnaire  : L'adresse du dictionnaire que l'on souhaite
							  consulter (const t_dictionnaire *).
	    - ptr_chaine : L'adresse de la chaine a rechercher
					   (const t_chaine *).
		- ptr_code : L'adresse de l'entier ou placer le code de la chaine
					 si l'on trouve celle-ci (unsigned int *).
	
	RETOUR : 1 si la chaine est presente et 0 dans le cas contraire.
			 Si la chaine est presente, l'entier *ptr_indice est modifie.

	EXEMPLE D'APPEL :
		t_dictionnaire un_dictionnaire;
		t_chaine une_chaine;
		unsigned int un_code;
		initialiser_dictionnaire(&un_dictionnaire);
		vider_chaine(&une_chaine);
		ajouter_caractere(&une_chaine, 'A');
		ajouter_une_chaine(&un_dictionnaire, &une_chaine);
		code_de_la_chaine(&un_dictionnaire, &une_chaine, &un_code);

	ATTENTION : On suppose que la fonction INITIALISER_DICTIONNAIRE a ete
				appelee une fois sur ptr_dictionnaire.
*/
int code_de_la_chaine(const t_dictionnaire * ptr_dictionnaire,
					  const t_chaine * ptr_chaine,
					  unsigned int * ptr_code);



/*
	CHAINE_DU_CODE

	Cette fonction trouve la chaine associee a un code.

	PARAMETRES :
		- ptr_dictionnaire : Le dictionnaire que l'on souhaite consulter
							 (const t_liste_chainee *).
		- code	     : Le code recherche (unsigned int).
		- ptr_chaine : L'adresse de la chaine ou placer les informations si
					   l'on trouve le code demande (t_chaine *).

	RETOUR : 1 si le code est present et 0 dans le cas contraire.
			 Si le code est present, la t_chaine *ptr_chaine est modifiee.

	EXEMPLE D'APPEL :
		t_dictionnaire un_dictionnaire;
		t_chaine une_chaine;
		initialiser_dictionnaire(&un_dictionnaire);
		vider_chaine(&une_chaine);
		ajouter_caractere(&une_chaine, 'A');
		ajouter_une_chaine(&un_dictionnaire, &une_chaine);
		vider_chaine(&une_chaine);
		chaine_du_code(&un_dictionnaire, 0, &une_chaine);

	ATTENTION : On suppose que la fonction INITIALISER_DICTIONNAIRE a ete
				appelee une fois sur ptr_dictionnaire.
*/
int chaine_du_code(const t_dictionnaire * ptr_dictionnaire,
				   unsigned int code,
				   t_chaine * ptr_chaine);



/*
	VIDER_DICTIONNAIRE

	Cette fonction vide le dictionnaire recu.

	PARAMETRE :
		- ptr_dictionnaire : L'adresse du dictionnaire a vider
							(t_dictionnaire *).

	RETOUR : Aucun.

	EXEMPLE D'APPEL :
		t_dictionnaire un_dictionnaire;
		initialiser_dictionnaire(&un_dictionnaire);
		vider_dictionnaire(&un_dictionnaire);

	ATTENTION : On suppose que la fonction INITIALISER_DICTIONNAIRE a ete
				appelee une fois sur ptr_dictionnaire.
*/
void vider_dictionnaire(t_dictionnaire * ptr_dictionnaire);