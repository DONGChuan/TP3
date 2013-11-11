/****************************************************************************/
/* Par     : Frederick Henri												*/
/* Date    : 04/11/08														*/
/* Fichier : chaine.h														*/
/*																			*/
/* Ce module implemente le type t_chaine.									*/
/* Celui-ci permet de conserver une chaine de caractere pouvant contenir	*/
/* jusqu'a TAILLE_MAXIMALE_CHAINE characteres. De plus, a la difference des	*/
/* chaines de caracteres en C, le caractere '\0' n'indique pas la fin d'un  */
/* t_chaine.																*/
/****************************************************************************/




#if !defined(MODULE_CHAINE)
#define MODULE_CHAINE




#include <stdio.h>




/****************************************************************************/
/*						DEFINITIONS DE CONSTANTES							*/
/****************************************************************************/
/*	La longueur maximale de la chaine. */
#define TAILLE_MAXIMALE_CHAINE	1024




/****************************************************************************/
/*							DEFINITIONS DE TYPES							*/
/****************************************************************************/
/*	On definit le type t_chaine qui permet de conserver une chaine de
	caracteres pouvant contenir le caractere '\0'.
*/
typedef struct
{
	unsigned char caracteres[TAILLE_MAXIMALE_CHAINE];
	int nb_caracteres;
} t_chaine;




/****************************************************************************/
/*							FONCTIONS PUBLIQUES								*/
/****************************************************************************/
/*
	VIDER_CHAINE

	Cette fonction vide la chaine recue.

	PARAMETRE :
		- ptr_chaine : L'adresse de la chaine a vider (t_chaine *).

	RETOUR : Aucun. Cependant, la chaine a l'adresse recue ne contient plus
			 de caracteres.

	EXEMPLE D'APPEL :
		t_chaine une_chaine;
		vider_chaine(&une_chaine);
*/
void vider_chaine(t_chaine * ptr_chaine);



/*
	AJOUTER_CARACTERE

	Cette fonction ajoute un caractere au bout de la chaine recue.

	PARAMETRES :
		- ptr_chaine : L'adresse de la chaine a modifier (t_chaine *).
		- ajout      : Le caractere a ajouter a la chaine.

	RETOUR : 1 en cas de succes et 0 si la chaine est pleine.

	EXEMPLE D'APPEL :
		t_chaine une_chaine;
		vider_chaine(&une_chaine);
		ajouter_caractere(&une_chaine, 'A');

	ATTENTION : La fonction suppose que le pointeur pointe vers une chaine
			    initialisee a l'aide de la fonction vider_chaine.
*/
int ajouter_caractere(t_chaine * ptr_chaine, unsigned char ajout);



/*
	CONSULTER_CARACTERE

	Cette fonction consulte le caractere dans une chaine a l'indice demande.

	PARAMETRES :
		- ptr_chaine : L'adresse de la chaine a consulter (const t_chaine *).
		- indice     : L'indice du caractere a consulter (int).
					   Si cet indice n'est pas dans l'intervalle
					   [0, taille_chaine(ptr_chaine)[, le programme se termine.
	    - ptr_caractere_lu : (SORTIE) L'adresse ou le caractere lu doit etre
							 ecrit en cas de succes (unsigned char *).

	RETOUR : Le caractere a l'indice demande en cas de succes. Si l'indice n'est
			 pas valide, le programme se termine (assert).

	EXEMPLE D'APPEL :
		t_chaine une_chaine;
		unsigned char caractere_obtenu;
		vider_chaine(&une_chaine);
		ajouter_caractere(&une_chaine, 'A');
		consulter_caractere(&une_chaine, 0, &caractere_obtenu);

	ATTENTION : La fonction suppose que le pointeur pointe vers une chaine
			    initialisee a l'aide de la fonction vider_chaine.
*/
unsigned char consulter_caractere(const t_chaine * ptr_chaine, int indice);



/*
	TAILLE_CHAINE

	Cette fonction retourne le nombre de caracteres dans une chaine.

	PARAMETRE :
		- ptr_chaine : L'adresse de la chaine a consulter (const t_chaine *).

	RETOUR : Le nombre de caracteres de la chaine. Cette valeur est toujours
			 dans l'intervalle [0, TAILLE_MAXIMALE_CHAINE].

	EXEMPLE D'APPEL :
		t_chaine une_chaine;
		vider_chaine(&une_chaine);
		printf("%i\n", taille_chaine(&une_chaine));

	ATTENTION : La fonction suppose que le pointeur pointe vers une chaine
			    initialisee a l'aide de la fonction vider_chaine.
*/
int taille_chaine(const t_chaine * ptr_chaine);



/*
	CHAINES_SEMBLABLES

	Cette fonction verifie si deux chaines sont identiques.

	PARAMETRES :
		- ptr_chaine1 : L'adresse d'une des deux chaines a comparer
						(const t_chaine *).
		- ptr_chaine2 : L'adresse de l'autre chaine a comparer
						(const t_chaine *).

	RETOUR : 1 si les chaines sont identiques et 0 dans le cas contraire.

	EXEMPLE D'APPEL :
		t_chaine chaine1, chaine2;
		vider_chaine(&chaine1);
		vider_chaine(&chaine2);
		printf("%i\n", chaines_semblables(&chaine1, &chaine2));


	ATTENTION : La fonction suppose que les pointeur pointent vers des chaines
			    initialisees a l'aide de la fonction vider_chaine.
*/
int chaines_semblables(const t_chaine * ptr_chaine1,
					   const t_chaine * ptr_chaine2);



/*
	ECRIRE_CHAINE_FICHIER

	Cette fonction ecrit la chaine pointee dans le fichier recu.

	PARAMETRES :
		- fichier_destination : Le fichier ou l'on souhaite ecrire la chaine
								(FILE *). Ce fichier doit etre ouvert en
								mode ecriture / binaire.
		- ptr_chaine : L'adresse de la chaine a ecrire (const t_chaine *).

	RETOUR : Aucun.

	EXEMPLE D'APPEL :
		t_chaine une_chaine;
		FILE * fichier = fopen("test.txt", "wb");
		if (fichier != NULL)
		{
			vider_chaine(&une_chaine);
			ajouter_caractere(&une_chaine, 'A');
			ecrire_chaine_fichier(fichier, &une_chaine);
		}
		fclose(fichier);

	ATTENTION : La fonction suppose que le pointeur pointe vers une chaine
			    initialisee a l'aide de la fonction vider_chaine.
*/
void ecrire_chaine_fichier(FILE * fichier_destination,
						   const t_chaine * ptr_chaine);




#endif