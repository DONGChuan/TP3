#include <stdio.h>

struct noeud
{
	int donnee;
	struct noeud * suivant;
}

typedef struct noeud * ptr_noeud;

struct liste
{
	ptr_noeud tete;
}

ptr_liste creer_liste(void)
{
	struct liste * ptr = (struct liste *)malloc(sizeof(struct liste);
	if(ptr != NULL)
	{
		ptr->tete = NULL;
	}

	return ptr;
}

static ptr_noeud creer_noeud(const int element, ptr_noeud suivant)
{
	ptr_noeud new_noeud = (ptr_noeud)malloc(sizeof(struct noeud));
	if(new_noeud != NULL)
	{
		new_noeud -> donnee = element;
		new_noeud -> suivant = suivant;
	}

	return new_noeud;
}

int ajouter_debut(ptr_liste ptr, int element)
{
	ptr_noeud new_noeud = creer_noeud(element, ptr -> tete)

	if(new_noeud != NULL)
	{
		ptr -> tete = new_noeud;

		return 1;
	}
	else
	{
		return 0;
	}
}

int longueur_liste(const ptr_liste ptr)
{
	ptr_noeud tmp= ptr -> tete;
	int longueur = 0;

	while(tmp != NULL)
	{
		longueur++;
		tmp= tmp -> suivant;
	}

	return long
}

int retirer_debut(ptr_liste liste)
{
	if(liste->tete != NULL)
	{
		if(liste->tete->suivant != NULL)
		{
			ptr_noeud tmp;
			tmp = liste->tete->suivant;
			free(liste->tete);
			liste->tete = tmp;
		}
		else
		{
			liste->tete = NULL;
		}

		return 1;
	}
	else
	{
		return 0;
	}
}