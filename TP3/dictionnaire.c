#include "dictionnaire.h"
#include <stdlib.h>

/*
	INITIALISER_DICTIONNAIRE

	Cette fonction initialise le dictionnaire. Au depart, celui-ci est vide.
*/
void initialiser_dictionnaire(t_dictionnaire * ptr_dictionnaire)
{
	int i;

	for(i=0;i<NB_CODES_ASCII;i++)
	{
		initialiser_liste(&(ptr_dictionnaire->groupe_par_caractere[i]));
	}

	for(i=0;i<NB_GROUPE_CODE;i++)
	{
		initialiser_liste(&(ptr_dictionnaire->groupe_par_code[i]));
	}

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
	int flag_par_caractere = 0;
	int flag_par_code = 0;

	int code_ASCII = (int)(ptr_chaine->caracteres[0]);
	int code_mudulo = code_ASCII % 100;

	flag_par_caractere = ajouter_fin_liste(&(ptr_dictionnaire->groupe_par_caractere[code_ASCII]),
										   ptr_chaine,
										   nb_chaines_dictionnaire(ptr_dictionnaire));

	flag_par_code = ajouter_fin_liste(&(ptr_dictionnaire->groupe_par_code[code_mudulo]),
										   ptr_chaine,
										   nb_chaines_dictionnaire(ptr_dictionnaire));

	ptr_dictionnaire->nb_chaines++;

	if(flag_par_caractere && flag_par_code)
	{
		return 1;
	}
	else
	{
		return 0;
	}
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

*/
int code_de_la_chaine(const t_dictionnaire * ptr_dictionnaire,
					  const t_chaine * ptr_chaine,
					  unsigned int * ptr_code)
{
	int code_ASCII = (int)(ptr_chaine->caracteres[0]);

	return chercher_chaine_dans_liste(&(ptr_dictionnaire->groupe_par_caractere[code_ASCII]),
							          ptr_chaine,
							          ptr_code);
}



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
*/
int chaine_du_code(const t_dictionnaire * ptr_dictionnaire,
				   unsigned int code,
				   t_chaine * ptr_chaine)
{
	int code_mudulo = code % 100;

	return chercher_code_dans_liste(&(ptr_dictionnaire->groupe_par_code[code_mudulo]),
							        code,
							        ptr_chaine);
}



/*
	VIDER_DICTIONNAIRE

	Cette fonction vide le dictionnaire recu.
*/
void vider_dictionnaire(t_dictionnaire * ptr_dictionnaire)
{
	int i;

	for(i=0;i<NB_CODES_ASCII;i++)
	{
		vider_liste(&(ptr_dictionnaire->groupe_par_caractere[i]));
	}

	for(i=0;i<NB_GROUPE_CODE;i++)
	{
		vider_liste(&(ptr_dictionnaire->groupe_par_code[i]));
	}
	
	ptr_dictionnaire->nb_chaines = 0;
}