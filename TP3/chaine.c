#include "chaine.h"
#include <assert.h>

/*
	VIDER_CHAINE

	Cette fonction vide la chaine recue.

	PARAMETRE :
		- ptr_chaine : L'adresse de la chaine a vider (t_chaine *).

	RETOUR : Aucun. Cependant, la chaine a l'adresse recue ne contient plus
			 de caracteres.
*/
void vider_chaine(t_chaine * ptr_chaine)
{
	ptr_chaine -> caracteres[0] = '/0';
	ptr_chaine->nb_caracteres = 0;
}


/*
	AJOUTER_CARACTERE

	Cette fonction ajoute un caractere au bout de la chaine recue.

	PARAMETRES :
		- ptr_chaine : L'adresse de la chaine a modifier (t_chaine *).
		- ajout      : Le caractere a ajouter a la chaine.

	RETOUR : 1 en cas de succes et 0 si la chaine est pleine.

*/
int ajouter_caractere(t_chaine * ptr_chaine, unsigned char ajout)
{
	if(ptr_chaine->nb_caracteres != 0)
		return 0;
	else
	{
		ptr_chaine -> caracteres[0] = ajout;
		ptr_chaine -> caracteres[1] = '/0';

		return 1;
	}
}



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

	ATTENTION : La fonction suppose que le pointeur pointe vers une chaine
			    initialisee a l'aide de la fonction vider_chaine.
*/
unsigned char consulter_caractere(const t_chaine * ptr_chaine, int indice)
{
	assert(indice >= 0);
	assert(indice < TAILLE_MAXIMALE_CHAINE);

	unsigned char ptr_caractere_lu;
	ptr_caractere_lu = ptr_chaine->caracteres[indice];

	return ptr_caractere_lu;
}
//asaaaa

/*
	TAILLE_CHAINE

	Cette fonction retourne le nombre de caracteres dans une chaine.

	PARAMETRE :
		- ptr_chaine : L'adresse de la chaine a consulter (const t_chaine *).

	RETOUR : Le nombre de caracteres de la chaine. Cette valeur est toujours
			 dans l'intervalle [0, TAILLE_MAXIMALE_CHAINE].
*/
int taille_chaine(const t_chaine * ptr_chaine)
{
	return ptr_chaine -> nb_caracteres;
}


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

*/
int chaines_semblables(const t_chaine * ptr_chaine1,
					   const t_chaine * ptr_chaine2)
{
	int i;

	if(taille_chaine(ptr_chaine1) == taille_chaine(ptr_chaine2))
	{
		for(i = 0; i < taille_chaine(ptr_chaine1) ; i++)
		{
			if(ptr_chaine1->caracteres[i] != ptr_chaine2->caracteres[i])
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
}



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