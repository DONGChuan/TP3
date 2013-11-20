#include "dictionnaire.h"
#include <stdlib.h>

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
*/
long int nb_chaines_dictionnaire(const t_dictionnaire * ptr_dictionnaire)
{
	return ptr_dictionnaire->nb_chaines;
}

/*
	AJOUTER_UNE_CHAINE

	Cette fonction ajoute une chaine dans le dictionnaire. Cette chaine se voit
	automatiquement assignee le code correspondant au nombre de chaines dans
	le dictionnaire avant l'ajout.

	A NOTER : On suppose que la chaine n'est pas deja presente et qu'elle
			  n'est pas vide. On ne verifie pas pour des raisons de vitesse.
*/
int ajouter_une_chaine(t_dictionnaire * ptr_dictionnaire,
					   const t_chaine * ptr_chaine)
{
	int i;

	// groupe_par_caractere
	for(i=0;i<NB_CODES_ASCII;i++)
	{
		if(ptr_chaine->caracteres[0] ==
			ptr_dictionnaire->groupe_par_caractere[i].queue->chaine.caracteres[0])
		{
			unsigned int code; // code???? comment le faire

			return ajouter_fin_liste(ptr_dictionnaire->groupe_par_caractere,
							         ptr_chaine,
					                 code);
		}
	}


	//groupe_par_code
    //ToDo
	

	/* Augmenter la taille */
	ptr_dictionnaire->nb_chaines++;

	return 1;
	return 0;
}



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
*/
void vider_dictionnaire(t_dictionnaire * ptr_dictionnaire)
{
	vider_liste(ptr_dictionnaire->groupe_par_caractere);
	vider_liste(ptr_dictionnaire->groupe_par_code);
	
	ptr_dictionnaire->nb_chaines = 0;
}