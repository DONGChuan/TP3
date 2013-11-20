#include "liste.h"
#include <stdlib.h>

/*
	INITIALISER_LISTE

	Cette fonction initialise la liste recue. Au depart, la liste est vide.
*/
void initialiser_liste(t_liste_chainee * ptr_liste)
{
	ptr_liste -> tete = NULL;			
	ptr_liste -> queue = NULL;				
	ptr_liste -> nb_maillons = 0;	
}

/*
	TAILLE_LISTE

	Cette fonction retourne le nombre de maillons dans la liste.
*/
long int taille_liste(const t_liste_chainee * ptr_liste)
{
	return ptr_liste -> nb_maillons;
}

/*
	AJOUTER_DEBUT_LISTE

	Cette fonction ajoute une chaine et son code au debut d'une liste.
	On ne valide pas si la chaine est deja presente.
*/
int ajouter_debut_liste(t_liste_chainee * ptr_liste,
						const t_chaine * ptr_chaine,
						unsigned int code)
{
	if(!chercher_chaine_dans_liste(ptr_liste, ptr_chaine, &code))
	{
		t_maillon * maillon_ajoute;
		maillon_ajoute -> chaine = *ptr_chaine;
		maillon_ajoute -> code = code;
		maillon_ajoute -> suivant = NULL;

		maillon_ajoute -> suivant = ptr_liste -> tete;
		ptr_liste -> tete = maillon_ajoute;

		ptr_liste -> nb_maillons++;

		return 1;
	}
	else
	{
		return 0;
	}
}

/*
	AJOUTER_CHAINE_FIN_LISTE

	Cette fonction ajoute une chaine et son code a la fin d'une liste.
	On ne valide pas si la chaine est deja presente.
*/
int ajouter_fin_liste(t_liste_chainee * ptr_liste,
					  const t_chaine * ptr_chaine,
					  unsigned int code)
{
	if(!chercher_chaine_dans_liste(ptr_liste, ptr_chaine, &code))
	{
		t_maillon * maillon_ajoute;
		maillon_ajoute -> chaine = *ptr_chaine;
		maillon_ajoute -> code = code;
		maillon_ajoute -> suivant = NULL;

		ptr_liste -> queue -> suivant = maillon_ajoute;
		ptr_liste -> queue = maillon_ajoute;

		ptr_liste->nb_maillons++;

		return 1;
	}
	else
	{
		return 0;
	}
}

/*
	CHERCHER_CHAINE_DANS_LISTE

	Cette fonction recherche une chaine dans une liste et renvoie
	le code associe a cette chaine.
*/
int chercher_chaine_dans_liste(const t_liste_chainee * ptr_liste,
							   const t_chaine * ptr_chaine,
							   unsigned int * ptr_code)
{
	int i;
	const t_maillon * maillon_compare;

	maillon_compare = ptr_liste->tete;

	for(i=0; taille_liste(ptr_liste); i++)
	{
		if(chaines_semblables(&(maillon_compare->chaine), ptr_chaine))
		{
			*ptr_code = maillon_compare->code;
			return 1;
		}

		maillon_compare = maillon_compare->suivant;
	}

	return 0;
}

/*
	CHERCHER_CODE_DANS_LISTE

	Cette fonction recherche un code dans une liste et renvoie la
	chaine associee a ce code.
*/
int chercher_code_dans_liste(const t_liste_chainee * ptr_liste,
							 unsigned int code,
							 t_chaine * ptr_chaine)
{
	int i;
	const t_maillon * maillon_compare;

	maillon_compare = ptr_liste->tete;

	for(i=0; taille_liste(ptr_liste); i++)
	{
		if(maillon_compare->code == code)
		{
			*ptr_chaine = maillon_compare->chaine;
			return 1;
		}

		maillon_compare = maillon_compare->suivant;
	}

	return 0;
}

/*
	VIDER_LISTE

	Cette fonction vide la liste.
*/
void vider_liste(t_liste_chainee * ptr_liste)
{
	ptr_liste->nb_maillons = 0;

	t_maillon * tmp;

	while(ptr_liste->tete != NULL)
	{
		tmp = ptr_liste -> tete;
		free(ptr_liste -> tete);
		ptr_liste->tete = tmp -> suivant;
	}
}
