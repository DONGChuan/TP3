/****************************************************************************/
/* Par     : Frederick Henri.												*/
/* Date    : 05/11/2008														*/
/* Fichier : TP3.C															*/
/*																			*/
/* Ce programme permet de compresser/decompresser un fichier a l'aide d'un	*/
/* algorithme de compression LZW.											*/
/*																			*/
/* L'appel du programme doit se faire sur la ligne de commande. Il peut		*/
/* etre appele des facons suivantes :										*/
/*	lzw    fichier_a_compresser   fichier_resultant							*/
/*	lzw -d fichier_a_decompresser fichier_resultant							*/
/*	lzw /?																	*/
/****************************************************************************/




#include "dictionnaire.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>




/****************************************************************************/
/*						DEFINITIONS DE CONSTANTES							*/
/****************************************************************************/
/* Tableaux de messages d'erreur.											*/
const char * MESSAGES_ERREUR[] =
{
	"Aucune erreur",
	"Le nombre de parametres est invalide.",
	"Le fichier source specifie n'existe pas.",
	"Cette option n'est pas reconnue.",
	"La compression a echoue.",
	"La decompression a echoue.",
};

/* Identification des messages d'erreur.									*/
#define SUCCES						0
#define NOMBRE_PARAMETRES_INVALIDE	1
#define FICHIER_SOURCE_INEXISTANT	2
#define OPTION_NON_RECONNUE			3
#define ECHEC_COMPRESSION			4
#define ECHEC_DECOMPRESSION			5

/* Parametres de la ligne de commande.										*/
#define PARAMETRE_AIDE				"/?"
#define PARAMETRE_DECOMPRESSION		"-d"

/* Nombre de bits des codes compresses.										*/
#define NB_BITS_PAR_CODE		  12

/* Constantes pour faciliter la lecture.									*/
typedef enum {COMPRESSION, DECOMPRESSION} t_traitement;




/****************************************************************************/
/*						DECLARATIONS DE FONCTIONS							*/
/****************************************************************************/
/*
	VALIDER_PARAMETRES

	Cette fonction valide le nombre et la valeur des parametres passes lors
	de l'appel de l'application.

	PARAMETRES :
		- nb_arguments  : Le nombre d'arguments (int).
		- tab_arguments : Le tableau des arguments (const char * []).

	RETOUR : SUCCES si les arguments sont valides et un numero d'erreur
			 lorsque ce n'est pas le cas.
*/
int valider_parametres(int nb_arguments, const char * tab_arguments[]);



/*
	AFFICHER_AIDE

	Cette fonction affiche l'aide expliquant comment appeler le programme.

	PARAMETRE : Aucun.

	RETOUR : Aucun.
*/
void afficher_aide(void);



/*
	DEMARRER_TRAITEMENT

	Cette fonction ouvre le fichier source et le fichier destination.
	Elle choisit entre la compression et le decompression selon la valeur
	du parametre "action".

	PARAMETRES :
		- nom_fichier_source : Le nom du fichier source (const char *).
		- nom_fichier_destination : Le nom du fichier destination
									(const char *).
		- action : L'action a effectuer (COMPRESSION ou DECOMPRESSION).

	RETOUR : 1 en cas de succes et 0 dans el cas contraire.

	ATTENTION : On suppose que le fichier source existe et peut etre lu.
*/
int demarrer_traitement(const char * nom_fichier_source,
						const char * nom_fichier_destination,
						t_traitement action);



/*
	EFFECTUER_COMPRESSION

	Cette fonction recoit deux fichiers ouverts (le premier en lecture et le
	second en ecriture), compresse le fichier source et ecrit le resultat
	dans le fichier destination.

	PARAMETRES :
		- fichier_source : Le fichier contenant les donnees a compresser
						   (FILE *).
		- fichier_destination : Le fichier ou l'on doit ecrire les donnees
								compressees (FILE *).

	RETOUR : 1 en cas de succes et 0 dans le cas contraire.
*/
int effectuer_compression(FILE * fichier_source, FILE * fichier_destination);



/*
	ECRIRE_CODE_CHAINE

	Cette fonction ecrit dans un fichier binaire le code recu sur un total de
	taille_compression bits.
	
	A NOTER : Les ecritures se font toujours en multiples de 8 bits. Pour
			  s'assurer que tout a ete ecrit dans le fichier, il est important
			  de faire un appel a la toute fin avec le code 0 et une
			  taille_compression de 7.

	PARAMETRES :
		- fichier_destination : Le fichier ou l'on souhaite ecrire le code
								(FILE *).
		- code : Le code a ecrire (unsigned int).
		- taille_compression : Le nombre de bits de compression (int).
							   On suppose que la taille est > 0.

	RETOUR : Aucun.
*/
void ecrire_code_chaine(FILE * fichier_destination,
						unsigned int code, int taille_compression);



/*
	EFFECTUER_DECOMPRESSION

	Cette fonction recoit deux fichiers ouverts (le premier en lecture et le
	second en ecriture), de compresse le fichier source et ecrit le resultat
	dans le fichier destination.

	PARAMETRES :
		- fichier_source : Le fichier contenant les donnees a decompresser
						   (FILE *).
		- fichier_destination : Le fichier ou l'on doit ecrire les donnees
								decompressees (FILE *).

	RETOUR : 1 en cas de succes et 0 dans le cas contraire.
*/
int effectuer_decompression(FILE * fichier_source, FILE * fichier_destination);



/*
	LIRE_CODE_CHAINE
	
	Cette fonction permet de lire un code dans le fichier source.

	PARAMETRES :
		- fichier_source : Le fichier contenant le code a lire
						   (FILE *).
		- ptr_code : L'adresse ou l'on souhaite ecrire le code lu
					 (unsigned int *).

	RETOUR : 1 en cas de succes et 0 lorsque la fin du fichier est atteinte.
*/
int lire_code_chaine(FILE * fichier_source, unsigned int * code);




/****************************************************************************/
/*							PROGRAMME PRINCIPAL								*/
/****************************************************************************/
int main(int argc, const char * argv[])
{
	int resultat_validation = valider_parametres(argc, argv);

	/* On valide le nombre et la valeur des parametres.						*/
	if (resultat_validation != SUCCES)
	{
		printf("%s\n", MESSAGES_ERREUR[resultat_validation]);
	}
	else if (argc == 2 && strcmp(argv[1], PARAMETRE_AIDE) == 0)
	{
		afficher_aide();
	}
	else if (argc == 3)
	{
		if (!demarrer_traitement(argv[1], argv[2], COMPRESSION))
			printf("%s\n", MESSAGES_ERREUR[ECHEC_COMPRESSION]);
	}
	else
	{
		if (!demarrer_traitement(argv[2], argv[3], DECOMPRESSION))
			printf("%s\n", MESSAGES_ERREUR[ECHEC_DECOMPRESSION]);
	}

	return EXIT_SUCCESS;	
}




/****************************************************************************/
/*						DEFINITIONS DE FONCTIONS							*/
/****************************************************************************/
int valider_parametres(int argc, const char * argv[])
{
	int resultat_validation = SUCCES;

	/* On valide le cas ou le nombre de parametre est invalide.				*/
	if (argc <= 1 || (argc == 2 && strcmp(argv[1], PARAMETRE_AIDE) != 0) ||
		argc > 4)
		resultat_validation = NOMBRE_PARAMETRES_INVALIDE;
	else if (argc == 4 && strcmp(argv[1], PARAMETRE_DECOMPRESSION) != 0)
		resultat_validation = OPTION_NON_RECONNUE;
	else if (argc > 2)
	{
		/* On regle le cas ou le fichier source n'existe pas.				*/
		FILE * fichier = fopen(argv[(argc == 3) ? 1 : 2], "rt");
		if (fichier == NULL)
			resultat_validation = FICHIER_SOURCE_INEXISTANT;
		else
			fclose(fichier);
	}

	return resultat_validation;
}



void afficher_aide(void)
{
	printf("Compresse/decompresse un fichier.\n\n");
	printf("lzw ["PARAMETRE_DECOMPRESSION"] source destination\n");
}



int demarrer_traitement(const char * source, const char * destination,
						t_traitement action)
{
	FILE * fichier_source, * fichier_destination;
	int resultat;

	/* Ouverture des deux fichiers.											*/
	fichier_source = fopen(source, "rb");
	if ((fichier_destination = fopen(destination, "wb")) == NULL)
	{
		fclose(fichier_source);
		return 0;
	}

	/* Choix du traitement voulu.											*/
	if (action == COMPRESSION)
		resultat = effectuer_compression(fichier_source, fichier_destination);
	else
		resultat = effectuer_decompression(fichier_source, fichier_destination);

	/* Fermeture des fichiers et retour du resultat.						*/
	fclose(fichier_source);
	fclose(fichier_destination);

	return resultat;
}



int effectuer_compression(FILE * fichier_source, FILE * fichier_destination)
{
	printf("Compression a venir...\n");

	/*
		COMPLETER CETTE FONCTION.
		AU BESOIN, ECRIVEZ DES SOUS-FONCTIONS.
	*/

	return 1;
}



void ecrire_code_chaine(FILE * fichier_destination, unsigned int code,
						int taille_compression)
{
	/*	Le tampon conserve les donnees qui devaient etre ecrite mais ne l'ont
		pas encore ete parce que ce n'etait pas un multiple de 8 bits.		*/
	static unsigned long tampon_code = 0L;
	static int nb_bits_tampon = 0;
	unsigned long temp;						/* Pour decaleer  le tampon.	*/

	/*	On ajoute le code dans le tampon. Le code est colle juste a la droite
		de ce qui est dans le tampon. Ainsi, si le tampon contient "11011" et
		que le code est "000", alors on obtient "11011000".
	*/
	tampon_code |= (unsigned long) code <<
				   (32 - taille_compression - nb_bits_tampon);
	nb_bits_tampon += taille_compression;

	/* On ecrit le plus de paquets de 8 bits possibles dans le fichier.		*/
	while (nb_bits_tampon >= 8)
	{
		/* On ecrit les 8 bits les plus a gauche.							*/
		temp = tampon_code >> 24;
		fwrite(&temp, sizeof(char), 1, fichier_destination);

		/* On retire les 8 bits les plus a gauche.							*/
		tampon_code <<= 8;
		nb_bits_tampon -= 8;
	}
}



int effectuer_decompression(FILE * fichier_source, FILE * fichier_destination)
{
	printf("Decompression a venir...\n");

	/*
		chaîne : t_chaîne // Une chaîne pouvant contenir '\0'.
		caractère : t_caractère // Un caractère non signé.
		dictionnaire : t_dictionnaire // Un dictionnaire de chaînes.
		
		ajouter tous les codes ASCII au dictionnaire
		tant que (on peut lire un caractère dans le fichier source)
			caractère  lire_un_caractère(fichier_source)
			si (dictionnaire contient la chaîne chaîne+caractère) alors
				chaîne  chaîne+caractère // On concatène les deux.
			sinon
				si (le dictionnaire contient moins de 212 chaînes) alors
					ajouter chaîne+caractère dans le dictionnaire
				fin si
				écrire le code de chaîne dans le fichier destination
				chaîne  caractere;
			fin si
		fin tant que
		écrire le code de chaîne dans le fichier destination
	*/
	
	return 1;
}



int lire_code_chaine(FILE * fichier_source, unsigned int * code)
{
	static unsigned long tampon_code = 0;	/* Tampon de lecture.			*/
	static int nb_bits_tampon = 0;			/* Taille du contenu du tampon.	*/
	unsigned char lecteur;					/* Pour lire dans le fichier.	*/

	/*	Tant que le contenu du tampon n'atteint pas le nombre de bits d'un
		code, on lit un caractere de plus et on l'ajoute au tampon.			*/
	while (nb_bits_tampon < NB_BITS_PAR_CODE)
	{
		/* On tente de lire un caractere de plus.							*/
		if (fread(&lecteur, sizeof(char), 1, fichier_source) == 0)
			return 0;

		/* On ajoute le caractere dans le tampon.							*/
		tampon_code |= (unsigned long) lecteur << (24 - nb_bits_tampon);
		nb_bits_tampon += 8;
	}

	/* On extrait le code de NB_BITS_PAR_CODE du tampon.					*/
	*code = tampon_code >> (32 - NB_BITS_PAR_CODE);
	tampon_code <<= NB_BITS_PAR_CODE;
	nb_bits_tampon -= NB_BITS_PAR_CODE;

	return 1;
}