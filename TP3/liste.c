#include "liste.h"
#include <stdlib.h>

/*
	INITIALISER_LISTE

	Cette fonction initialise la liste recue. Au depart, la liste est vide.
*/
void initialiser_liste(t_liste_chainee * ptr_liste)
{
	/* On fait pointer la tête et la queue vers NULL */
	ptr_liste -> tete = NULL;			
	ptr_liste -> queue = NULL;	

	/* On initialise le nombre de maillons à 0 */
	ptr_liste -> nb_maillons = 0;	
}

/*
	TAILLE_LISTE

	Cette fonction retourne le nombre de maillons dans la liste.
*/
long int taille_liste(const t_liste_chainee * ptr_liste)
{
	/* 
		La taille de la liste est un champ du struct de la liste. 
		Il suffit de retourner le champ "nb_maillons" de la liste. 
	*/
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
	t_maillon * nouveau_maillon = (t_maillon *) malloc(sizeof(t_maillon));

	if(nouveau_maillon!=NULL)
	{
		nouveau_maillon -> chaine = *ptr_chaine;
		nouveau_maillon -> code = code;
		nouveau_maillon -> suivant = ptr_liste -> tete;

		ptr_liste -> tete = nouveau_maillon;

		if(nouveau_maillon -> suivant == NULL)
		{
			ptr_liste->queue = nouveau_maillon;
		}

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
	/* On tente de créer un nouveau maillon. */
	t_maillon * nouveau_maillon = (t_maillon *) malloc(sizeof(t_maillon));

	if (nouveau_maillon != NULL) 
	{
		nouveau_maillon -> chaine = *ptr_chaine;
		nouveau_maillon -> code = code;
		nouveau_maillon -> suivant = NULL;

		ptr_liste -> queue -> suivant = nouveau_maillon;
		ptr_liste -> queue = nouveau_maillon;

		if(ptr_liste->nb_maillons == 0)
		{
			ptr_liste->tete = nouveau_maillon;
		}

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
	const t_maillon * ptr_parcourir_liste;

	ptr_parcourir_liste = ptr_liste->tete;

	for(i=0; taille_liste(ptr_liste); i++)
	{
		if(chaines_semblables(&(ptr_parcourir_liste->chaine), ptr_chaine))
		{
			*ptr_code = ptr_parcourir_liste->code;
			return 1;
		}

		ptr_parcourir_liste = ptr_parcourir_liste->suivant;
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
	const t_maillon * ptr_parcourir_liste;

	ptr_parcourir_liste = ptr_liste->tete;

	for(i=0; taille_liste(ptr_liste); i++)
	{
		if(ptr_parcourir_liste->code == code)
		{
			*ptr_chaine = ptr_parcourir_liste->chaine;
			return 1;
		}

		ptr_parcourir_liste = ptr_parcourir_liste->suivant;
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

	t_maillon * ptr_maillon_a_detruire;

	while(ptr_liste->tete != NULL)
	{
		ptr_maillon_a_detruire = ptr_liste->tete;
		ptr_liste->tete = ptr_maillon_a_detruire->suivant;
		free(ptr_maillon_a_detruire);
	}

	ptr_liste->queue = NULL;
}
