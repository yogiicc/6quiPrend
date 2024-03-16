#include "gestionJeu.h"

int main()
{
    int nbJoueurTotal = 0;
    int nbJoueursH = 0;
    int nbJoueursR = 0;

    Paquet paquet;
    Plateau plateau;

    accueilJoueur(&nbJoueursH, &nbJoueurTotal);
    printf("Création des joueurs...\n");
    Joueur *listeJoueurs = malloc(nbJoueurTotal * sizeof(Joueur));
    initialiserJoueurs(nbJoueurTotal, nbJoueursH, listeJoueurs);
    afficherJoueurs(nbJoueurTotal, listeJoueurs);
    int scoreMax = 0;
    while (scoreMax < 66)
    {
        printf("Initialisation du paquet...\n");
        initialiserPaquet(&paquet);
        printf("Mélange du paquet...\n");
        melangerPaquet(&paquet);
        printf("Distribution des cartes au joueur... \n");
        distribuerPaquet(&paquet, nbJoueurTotal, listeJoueurs);
        printf("Initialisation du plateau... \n\n");
        initaliserPlateau(&paquet, &plateau);
        afficherPlateau(&plateau);

        printf("\n ------------------------------------ \n \n");

        printf("Debut de la manche : \n");
        manche(listeJoueurs, nbJoueurTotal, &plateau);
        printf("Fin de la manche");

        for (int i = 0; i < nbJoueurTotal; i++)
        {
            if (listeJoueurs[i].nbrTdB > scoreMax)
            {
                scoreMax = listeJoueurs[i].nbrTdB;
            }
        }
    }

    free(listeJoueurs);
}