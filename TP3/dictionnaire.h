/****************************************************************************/
/* Par     : Frederick Henri												*/
/* Date    : 04/11/08														*/
/* Fichier : dictionnaire.h													*/
/*																			*/
/* Ce module permet de conserver un dictionnaire contenant des chaines de	*/
/* caracteres auxquelles un code numerique est associe a chacune.			*/
/* Le nombre maximal de chaines n'est limite que par la memoire du systeme.	*/
/****************************************************************************/




#if !defined(MODULE_DICTIONNAIRE)
#define MODULE_DICTIONNAIRE




#include "liste.h"




/****************************************************************************/
/*							CONSTANTES DE COMPILATION						*/
/****************************************************************************/
#define NB_CODES_ASCII	256		/* La taille de la table ASCII.	*/
#define NB_GROUPE_CODE	100		/* Le nombre de groupes de codes differents
								   servant a accelerer la recherche.		*/




/****************************************************************************/
/*							DEFINITIONS DE TYPES							*/
/****************************************************************************/
/*
	Un dictionnaire de chaines ou le code ASCII du premier caractere d'une
	chaine determine la liste dans laquelle elle se trouve.
*/
typedef struct
{
	/*	Ce tableau contient toutes les chaines regroupees selon leur
		premier caractere. Ainsi, groupe_par_caractere[65] contient une
		liste dont toutes les chaines commencent pas le code ASCII 65.
	*/
	t_liste_chainee groupe_par_caractere[NB_CODES_ASCII];

	/*	Ce tableau contient toutes les chaines regroupees selon la fin de
		leur code. Ainsi, groupe_par_code[65] contient une liste dont le code
		des chaines modulo NB_GROUPE_CODE donnent 65.
	*/
	t_liste_chainee groupe_par_code[NB_GROUPE_CODE];

	/*	Le nombre de chaines/codes dans le dictionnaire. */
	long int nb_chaines;
} t_dictionnaire;




/****************************************************************************/
/*							FONCTIONS PUBLIQUES								*/
/****************************************************************************/
/*
	INITIALISER_DICTIONNAIRE

	Cette fonction initialise le dictionnaire. Au depart, celui-ci est vide.

	PARAMETRE :
		- ptr_dictionnaire : L'adresse du dictionnaire a initialiser
							 (t_dictionnaire *).

	RETOUR : Aucun.

	EXEMPLE D'APPEL :
		t_dictionnaire un_dictionnaire;
		initialiser_dictionnaire(&un_dictionnaire);

	ATTENTION : Cette fonction ne doit etre appelee qu'une seule fois sur
				un meme dictionnaire.
*/
void initialiser_dictionnaire(t_dictionnaire * ptr_dictionnaire);



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




#endif