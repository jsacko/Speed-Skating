#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable: 4996)

// Définition des constantes utiles au programme//
enum { LGMOT = 30 }; // Longueur max d'un mot
enum { NB_PATINEUR = 3 }; // Nombre de patineur par équipe
enum { NB_EQUIPE = 32 }; // Nombre d'équipe de patineurs
enum { NB_PARCOURSMAX = 10 }; // Nombre de parcours max
enum { NB_EPREUVEMAX = 32}; // Nombre d'épreuve max
enum { EQUIPE_PAR_POURSUITE = 2}; // Nombre d'équipe en jeu par poursuite



// Un patineur possède un nom, un dossard, ses temps effectués et le nombre de tours effectués.
typedef struct {
	char nom[LGMOT + 1];
	unsigned int dossard;
	double temps[NB_PARCOURSMAX];
	unsigned int tour;
}Patineur; 

// Une équipe possède le nombre de patineurs défini et appartient a un pays.
typedef struct {
	Patineur data[NB_PATINEUR];
	char pays[LGMOT + 1];
	double tempsMax;
}Equipe[NB_EQUIPE]; 


// Commande pour inscrire une équipe de patineurs.
void inscrire_equipe(unsigned int* numeroEquipe, unsigned int* dossard, Equipe e)
{
	scanf("%s", e[*numeroEquipe].pays); // Le premier mot est stocké dans la case pays de l'équipe
	for (int j = 0; j < NB_PATINEUR; j += 1) // On boucle pour le nombre de patineur
	{
		scanf("%s", e[*numeroEquipe].data[j].nom); // Le mot est stocké dans la case nom du patineur en cours
		e[*numeroEquipe].data[j].dossard = *dossard; // Le dossard est inscrit dans la case dossard du patineur en cours
		printf("inscription dossard %d\n", e[*numeroEquipe].data[j].dossard);
		*dossard += 1;
	}
	*numeroEquipe += 1;
}

// Commande pour afficher les équipes de patineurs dans l'ordre d'inscription
void afficher_equipes(Equipe e, unsigned int numEquipe)
{
	unsigned int dossard = 101;
	for (int iEquipe = 0; iEquipe < numEquipe; iEquipe += 1) 
	{
		printf("%s ", e[iEquipe].pays); 
		for (int iPatineur = 0; iPatineur < NB_PATINEUR; iPatineur += 1) 
		{
			printf("%s %d ", e[iEquipe].data[iPatineur].nom, dossard); 
			dossard += 1;
		}
		printf("\n");
	}
}

// Fonction qui trie dans l'ordre croissant un tableau.
// Le tableau et la taile doivent être donnés en paramètres.
void procedure_tri_croissant(double t[], unsigned int taille)
{
	double v;
	int j;
	for (int i = 1; i < taille; i += 1)
	{
		v = t[i];
		j = i;
		while (j > 0 && t[j - 1] > v)
		{
			t[j] = t[j - 1];
			j = j - 1;
		}
		t[j] = v;
	}
}

// Fonction qui permet de trouver l'équipe d'un patineur et sa position dans 
// data à partir du dossard.
void trouver_joueur(Equipe e, int dossard, int* iEquipe, int* iPatineur)
{
	while (e[*iEquipe].data[*iPatineur].dossard != dossard)  
	{
		*iPatineur += 1;
		if (*iPatineur == NB_PATINEUR) 
		{
			*iPatineur = 0;
			*iEquipe += 1;
		}
	}
}

// Fonction qui trouve l'indice d'une équipe à partir du temps donné en paramètre
void trouver_temps_equipe(Equipe e, double temps, int* iEquipe)
{
	while (e[*iEquipe].tempsMax != temps)
		*iEquipe += 1;
}

// Fonction qui réalise l'affichage final de la compétition et met fin au programme
void detection_fin_competition(Equipe e, unsigned int iPoursuite)
{
	unsigned int iEquipe = 0;
	double tempsFinaux[NB_EQUIPE];
	printf("detection_fin_competition\n");
	for (int i = 0; i < iPoursuite * 2; i += 1)
		tempsFinaux[i] = e[i].tempsMax;
	procedure_tri_croissant(tempsFinaux, iPoursuite * 2);
	for (int j = 0; j < iPoursuite * 2; j += 1)
	{
		trouver_temps_equipe(e, tempsFinaux[j], &iEquipe);
		printf("%s %.1lf\n", e[iEquipe].pays, e[iEquipe].tempsMax);
		iEquipe = 0;
	}
	exit(0);
}

// Fonction qui affiche les gagnants et perdant de la poursuite dans l'ordre
// Elle détecte également la fin de la compétition
void detection_fin_poursuite(Equipe e, unsigned int  nbEpreuve)
{
	unsigned int gagnant, perdant;
	printf("detection_fin_poursuite\n");
	static unsigned int iPoursuiteEquipeA = 0, iPoursuiteEquipeB = 1, iPoursuite = 0;
	// Ternaire pour désigner le gagnant de la poursuite
	gagnant = (e[iPoursuiteEquipeA].tempsMax < e[iPoursuiteEquipeB].tempsMax) ? 
	(perdant = iPoursuiteEquipeB, iPoursuiteEquipeA) : (perdant = iPoursuiteEquipeA, iPoursuiteEquipeB);
	printf("%s %.1lf\n", e[gagnant].pays, e[gagnant].tempsMax);
	printf("%s %.1lf\n", e[perdant].pays, e[perdant].tempsMax);
	iPoursuite += 1;
	iPoursuiteEquipeA += EQUIPE_PAR_POURSUITE;
	iPoursuiteEquipeB += EQUIPE_PAR_POURSUITE;
	if (iPoursuite == nbEpreuve)
	{
		detection_fin_competition(e, iPoursuite);
	}


}

// Commande pour enregistrer le temps d'un patineur et détecter la fin d'une poursuite
void enregistrer_temps(Equipe e, unsigned int* nbTourParcours, unsigned int nbParcours, unsigned int nbEpreuve)
{
	int dossard, iPatineur = 0, iEquipe = 0;
	scanf("%d", &dossard);
	trouver_joueur(e, dossard, &iEquipe, &iPatineur); 
	scanf("%d", &e[iEquipe].data[iPatineur].tour);
	scanf("%lf", &e[iEquipe].data[iPatineur].temps[e[iEquipe].data[iPatineur].tour - 1]);
	if (e[iEquipe].data[iPatineur].temps[e[iEquipe].data[iPatineur].tour - 1] > e[iEquipe].tempsMax)
		e[iEquipe].tempsMax = e[iEquipe].data[iPatineur].temps[e[iEquipe].data[iPatineur].tour - 1]; 
	*nbTourParcours += 1;
	if (*nbTourParcours == (NB_PATINEUR * 2) * nbParcours)
	{
		detection_fin_poursuite(e, nbEpreuve);
		*nbTourParcours = 0;
	}


}

// Commande pour afficher le(s) temps d'un patineur 
void afficher_temps(Equipe e)
{
	unsigned int dossard, iPatineur = 0, iEquipe = 0;
	scanf("%d", &dossard);
	trouver_joueur(e, dossard, &iEquipe, &iPatineur); 
	for (int iTour = 0; iTour < e[iEquipe].data[iPatineur].tour; iTour += 1)
	{
		printf("%s %d %s %.1lf\n", e[iEquipe].pays, iTour + 1,
			e[iEquipe].data[iPatineur].nom, e[iEquipe].data[iPatineur].temps[iTour]);
	}
}

// Commande pour afficher le temps des equipes ayant fait le nombre de tour donné
// Elle affiche indisponible si l'équipe n'a pas fini le tour
void afficher_temps_equipes(Equipe e)
{
	unsigned int tour;
	unsigned int nbTourEquipe = 0;
	double tempsMaxTour;
	scanf("%d", &tour);
	for (int iEquipe = 0; iEquipe < NB_EQUIPE; iEquipe += 1)
	{
		if (e[iEquipe].tempsMax > 0)
		{
			tempsMaxTour = 0;
			nbTourEquipe = 0;
			for (int iPatineur = 0; iPatineur < NB_PATINEUR; iPatineur += 1)
				if (e[iEquipe].data[iPatineur].tour >= tour)
				{
					nbTourEquipe += 1;
					if (e[iEquipe].data[iPatineur].temps[tour - 1] > tempsMaxTour)
						tempsMaxTour = e[iEquipe].data[iPatineur].temps[tour - 1];
				}
			printf("%s ", e[iEquipe].pays);
			if ((tour * NB_PATINEUR) == nbTourEquipe)
				printf("%.1lf\n", tempsMaxTour);
			else
				printf("indisponible\n");
		}
	}

}

// Commande qui définit le nombre de parcours par épreuve.
void definir_parcours(int* nbParcours)
{
	scanf("%d", nbParcours);
	assert(*nbParcours <= NB_PARCOURSMAX);
}

// Commande pour définit le nombre d'épreuve de la compétition
void definir_nombre_epreuve(int* nbEpreuve)
{
	scanf("%d", nbEpreuve);
	assert(*nbEpreuve <= NB_EPREUVEMAX);
}

int main()
{
	int nbParcours = -1;
	int nbEpreuve = -1;
	unsigned int nbTourParcours = 0;
	char mot[LGMOT + 1];
	unsigned int numEquipe = 0; 
	unsigned int numPatineur = 101; 
	Equipe e;
	// Initialisation du temps maximum des équipes a 0
	for (int i = 0; i < NB_EQUIPE; i += 1)
	{
		e[i].tempsMax = 0;
	}

	while (1)
	{
		scanf("%s", mot);
		if (strcmp(mot, "definir_parcours") == 0)
			definir_parcours(&nbParcours);
		else if (strcmp(mot, "definir_nombre_epreuves") == 0)
			definir_nombre_epreuve(&nbEpreuve);
		else if (strcmp(mot, "inscrire_equipe") == 0)
			inscrire_equipe(&numEquipe, &numPatineur, e);
		else if (strcmp(mot, "afficher_equipes") == 0)
			afficher_equipes(e, numEquipe);
		else if (strcmp(mot, "enregistrer_temps") == 0)
			enregistrer_temps(e, &nbTourParcours, nbParcours, nbEpreuve);
		else if (strcmp(mot, "afficher_temps") == 0)
			afficher_temps(e);
		else if (strcmp(mot, "afficher_temps_equipes") == 0)
			afficher_temps_equipes(e);
		else if (strcmp(mot, "exit") == 0)
			exit(0);
	}
	system("pause"); return 0;
}