#include "chaine.h"
#include <assert.h>

/*
	VIDER_CHAINE

	Cette fonction vide la chaine recue.
*/
void vider_chaine(t_chaine * ptr_chaine)
{
	int i;

	for(i = 0; i<taille_chaine(ptr_chaine); i++)
	{
		ptr_chaine -> caracteres[i] = NULL;
	}
	
	ptr_chaine->nb_caracteres = 0;
}

/*
	AJOUTER_CARACTERE

	Cette fonction ajoute un caractere au bout de la chaine recue.
*/
int ajouter_caractere(t_chaine * ptr_chaine, unsigned char ajout)
{
	if(taille_chaine(ptr_chaine) < TAILLE_MAXIMALE_CHAINE)
	{
		ptr_chaine -> caracteres[taille_chaine(ptr_chaine)] = ajout;
		ptr_chaine->nb_caracteres++;

		return 1;
	}
	else
	{
		return 0;
	}
}

/*
	CONSULTER_CARACTERE

	Cette fonction consulte le caractere dans une chaine a l'indice demande.
*/
unsigned char consulter_caractere(const t_chaine * ptr_chaine, int indice)
{
	assert(indice >= 0);
	assert(indice < taille_chaine(ptr_chaine));

	return ptr_chaine->caracteres[indice];
}

/*
	TAILLE_CHAINE

	Cette fonction retourne le nombre de caracteres dans une chaine.
*/
int taille_chaine(const t_chaine * ptr_chaine)
{
	return ptr_chaine -> nb_caracteres;
}

/*
	CHAINES_SEMBLABLES

	Cette fonction verifie si deux chaines sont identiques.
*/
int chaines_semblables(const t_chaine * ptr_chaine1,
					   const t_chaine * ptr_chaine2)
{
	int i;

	if(taille_chaine(ptr_chaine1) == taille_chaine(ptr_chaine2))
	{
		for(i = 0; i < taille_chaine(ptr_chaine1) ; i++)
		{
			if(consulter_caractere(ptr_chaine1, i) != consulter_caractere(ptr_chaine2, i))
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}

	return 1;
}

/*
	ECRIRE_CHAINE_FICHIER

	Cette fonction ecrit la chaine pointee dans le fichier recu.
*/
void ecrire_chaine_fichier(FILE * fichier_destination,
						   const t_chaine * ptr_chaine)
{
	fwrite(ptr_chaine, sizeof(unsigned char), 1, fichier_destination);
}