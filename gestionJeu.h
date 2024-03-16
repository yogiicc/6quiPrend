#ifndef GESTIONJEU_H
#define GESTIONJEU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <stdbool.h>

#define NBCARTESMAX 104
#define NBRANGEESMAX 4
#define NBNOMBRECARTES_RANGEESMAX 6
#define NBJOUEURSMAX 10
#define NBTOURSMAX 10

typedef struct 
{
    int valeur;
    int teteDeBoeuf;
} Carte;

typedef struct
{
    int nbrCartes;
    Carte cartes[NBCARTESMAX];
} Paquet;

typedef struct 
{
    int nbrCartes_Rangees[4];
    int scoreTdB_Rangees[4];
    Carte rangees[NBRANGEESMAX][7];
} Plateau;

typedef struct 
{
    int id;
    int typeJoueur;
    Carte main[10];
    int nbrTdB;
} Joueur;

typedef struct
{
    int idJoueur;
    Carte carte;
} CartesJouees;

typedef struct {
    int joueurID;
    int score;
    int tour;
    int nbJoueurTotal;
} LogInfo;

void accueilJoueur(int *nbJoueursH, int * nbJoueurTotal);
void initialiserJoueurs(int nbJoueurTotal, int nbJoueursH, Joueur *listeJoueurs);
void afficherJoueur(Joueur *j);
void afficherJoueurs(int nbJoueurTotal, Joueur *listeJoueurs);

void afficherCarte(Carte c);
int calculerTdB(Carte c);
void initialiserPaquet(Paquet *paquet);
void affichePaquet(Paquet *paquet);
void initialiserAleatoire();
void melangerPaquet(Paquet *paquet);
void distribuerPaquet(Paquet *paquet, int nbJoueurTotal, Joueur *listeJoueurs);

void initaliserPlateau(Paquet *paquet, Plateau *plateau);
void afficherPlateau(Plateau *plateau);

void afficherMain(Joueur *joueur);
void tourJoueurH(Joueur *joueur, Plateau *plateau, CartesJouees *cartesJouees);
int choixCarteR(Carte *main, Plateau *plateau);
void tourJoueurR(Joueur *joueur, Plateau *plateau, CartesJouees *cartesJouees);
void trierCartesJouees(CartesJouees *cartesJouees, int nbJoueurTotal);
void choixRangeesH(Joueur *joueur, Plateau *plateau, int *indRange);
int choixRangeesR(Joueur *joueur, Plateau *plateau);
void finTour(Plateau *plateau, CartesJouees *cartesJouees, int nbJoueurTotal, Joueur *listeJoueurs, LogInfo logInfo);
void manche(Joueur *listeJoueurs, int nbJoueurTotal, Plateau *plateau);



#endif