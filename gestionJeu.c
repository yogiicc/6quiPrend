#include "gestionJeu.h"

void accueilJoueur(int *nbJoueursH, int *nbJoueurTotal)
{
    while(*nbJoueursH >10 || *nbJoueursH <= 0)
    {
        printf("Combien de Joueur Humain etes-vous?");
        scanf("%d", nbJoueursH);
        if(*nbJoueursH >10 || *nbJoueursH <1)
        {
            printf("Il doit y avoir au moins 1 joueur Humain pour commencer une partie!\n");
        }
    }

    while(*nbJoueurTotal > NBJOUEURSMAX || *nbJoueurTotal < 2)
    {
        printf("Combien de joueurs voulez-vous dans la partie : ");
        scanf("%d", nbJoueurTotal);
        if(*nbJoueurTotal > NBJOUEURSMAX || *nbJoueurTotal < 2)
        {
            printf("Il doit y avoir entre 2 et 10 joueurs maximums dans une partie\n");
        }
    }

    int nbJoueursR = *nbJoueurTotal - *nbJoueursH;
    printf("Une partie avec %d joueurs Humains et %d joueurs Robots va etre créer ...\n\n", *nbJoueursH, nbJoueursR);
}

void initialiserJoueurs(int nbJoueurTotal, int nbJoueursH, Joueur *listeJoueurs)
{
    for( int i = 0; i < nbJoueurTotal; i++)
    {
        if(i < nbJoueursH)
        {
            listeJoueurs[i].id = i+1;
            listeJoueurs[i].typeJoueur = 0;
            listeJoueurs[i].nbrTdB = 0;
            for(int j = 0; j < 10; j++)
            {
                listeJoueurs[i].main[j].valeur = 0;
                listeJoueurs[i].main[j].teteDeBoeuf = 0;
            }

        }
        else
        {
            listeJoueurs[i].id = i+1;
            listeJoueurs[i].typeJoueur = 1;
            listeJoueurs[i].nbrTdB = 0;
            for(int j = 0; j < 10; j++)
            {
                listeJoueurs[i].main[j].valeur = 0;
                listeJoueurs[i].main[j].teteDeBoeuf = 0;
            }
        }
    }
}
void afficherJoueur(Joueur *j)
{
    if(j->typeJoueur == 0)
    {
        printf("Joueur Humain n°%d, tete de boeuf : %d \n", j->id, j->nbrTdB);
    }
    else
    {
        printf("Joueur Robot n°%d, tete de boeuf : %d \n", j->id, j->nbrTdB);
    }
}

void afficherJoueurs(int nbJoueurTotal, Joueur *listeJoueurs)
{
    printf("Nombre de Joueur : %d\n", nbJoueurTotal);
    for(int i = 0; i < nbJoueurTotal; i++)
    {
        afficherJoueur(&listeJoueurs[i]);
    }
}



//Initialisation des Têtes de Boeuf pour chaque carte
int calculerTdB(Carte carte)
{
    int dernierChiffre = carte.valeur % 10;

    if (dernierChiffre == 5 && carte.valeur != 55 ) 
    {
        return 2;
    }
    else if (dernierChiffre == 0)
    {
        return 3;
    }
    else if (carte.valeur % 11 == 0 && carte.valeur != 55)
    {
        return 5;
    }
    else if (carte.valeur == 55)
    {
        return 7;
    }
    else 
    {
        return 1;
    }
}

//Initialisation du paquet avec la valeur et les têtes de boeufs pour chaque carte
void initialiserPaquet(Paquet *paquet)
{
    paquet->nbrCartes= NBCARTESMAX;
    for(int i = 0; i < NBCARTESMAX; i++)
    {
        paquet->cartes[i].valeur = i + 1;
        paquet->cartes[i].teteDeBoeuf = calculerTdB(paquet->cartes[i]);
    }
}
//Affichage d'un carte
void afficherCarte(Carte c)
{
    if(c.valeur == 0)
    {
        printf(" [ , ]");
    }
    else
    {
        printf(" [ %d ,TdB: %d ]", c.valeur, c.teteDeBoeuf);
    }
}

//Affichage d'un paquet
void affichePaquet(Paquet *paquet)
{
    for(int i = 0; i < paquet->nbrCartes; i++)
    {
        afficherCarte(paquet->cartes[i]);
        printf("\n");
    }
}

// Fonction pour initialiser la graine du générateur de nombres aléatoires
void initialiserAleatoire() {
    srand(time(NULL));
}

// Melange du paquet
void melangerPaquet(Paquet *paquet)
{
    // Appel de la fonction pour initialiser la graine
    initialiserAleatoire();

    for(int i = 0; i < NBCARTESMAX - 1; i++)
    {
        int j = i + rand() % (NBCARTESMAX - i);
        Carte c = paquet->cartes[i];
        paquet->cartes[i] = paquet->cartes[j];
        paquet->cartes[j] = c;
    }
}

void distribuerPaquet(Paquet *paquet, int nbJoueurs, Joueur *listeJoueurs)
{
    for (int i = 0; i < nbJoueurs; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(paquet->nbrCartes > 0)
            {
                paquet->nbrCartes --;
                listeJoueurs[i].main[j] = paquet->cartes[paquet->nbrCartes];
            }
        }
    }
}

void initaliserPlateau(Paquet *paquet, Plateau *plateau)
{
    for(int i = 0; i < 4;i++)
    {
        plateau->nbrCartes_Rangees[i] = 0;
        plateau->scoreTdB_Rangees[i] = 0;
    }

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(j == 0)
            {
                if(paquet->nbrCartes > 0)
                {
                    paquet->nbrCartes --;
                    plateau->rangees[i][j] = paquet->cartes[paquet->nbrCartes];
                    plateau->nbrCartes_Rangees[i]  += 1;
                    plateau->scoreTdB_Rangees[i] += plateau->rangees[i][j].teteDeBoeuf;
                }
            }
            else
            {
                plateau->rangees[i][j].valeur = 0;
                plateau->rangees[i][j].teteDeBoeuf = 0;
            }
        }
        
    }
}

void afficherPlateau(Plateau *plateau)
{
    printf("======================== \n");
    printf("======================== \n");
    for(int i = 0; i < 4; i++)
    {
        printf("Rangée %d : ", i+1);
        for( int j = 0; j < plateau->nbrCartes_Rangees[i]; j++)
        {
            afficherCarte(plateau->rangees[i][j]);
        }
        printf("\n");
    }
    printf("======================== \n");
    printf("======================== \n");
}


void afficherMain(Joueur *joueur)
{
    printf("Main du joueur %d : \n", joueur->id);
    for(int i = 0; i < 10; i++)
    {
        if(joueur->main[i].valeur !=0)
        {
            afficherCarte(joueur->main[i]);
            printf("\n");
        }
    }
    printf("\n");
}



void tourJoueurH(Joueur *joueur, Plateau *plateau, CartesJouees *cartesJouees)
{
    printf("C'est au tour du : ");
    afficherJoueur(joueur);
    printf("\n");

    bool trouve = false;
    int carteJouer;
    while(!trouve)
    {
        afficherPlateau(plateau);
        afficherMain(joueur);
        int i = 0;
        printf("Quel carte voulez-vous jouer? \n Entrez la valeur de la carte  :");
        scanf("%d", &carteJouer);
        while(i <10)
        {
            if(joueur->main[i].valeur == carteJouer)
            {
            // Ajouter la carte au tableau des cartes jouées
            cartesJouees[joueur->id -1].carte = joueur->main[i];
            cartesJouees[joueur->id -1].idJoueur = joueur->id;
            // Retirer la carte de la main du joueur
            joueur->main[i].valeur = 0;
            joueur->main[i].teteDeBoeuf = 0;
            trouve = true;
            i = 10;
            printf("Vous avez jouer la carte : ");
            afficherCarte(cartesJouees[joueur->id-1].carte);
            printf("\n");
            }
            else
            {
                i++;
            }
        }
        if(!trouve)
        {
            printf("Vous ne possedez pas cette carte en main. Veuillez donner une carte qui est dans votre main. \n");
        } 
    }
    afficherMain(joueur);
    printf("\nFin du tour du ");
    afficherJoueur(joueur);
    printf("\n\n");
}

int choixCarteR(Carte *main, Plateau *plateau)
{
    int ecartFaible = 200;
    int ecart = 105;
    int valeur = 0;
    bool inf = true;
    int valeurMin = 105;
    for(int i=0; i < 10; i++)
    {
        for(int j = 0; j < NBRANGEESMAX; j++)
        {
            if(main[i].valeur > 0)
            {
                int nbCarteRangees = plateau->nbrCartes_Rangees[j];
                ecart = main[i].valeur - plateau->rangees[j][nbCarteRangees -1].valeur;

                if(ecart < ecartFaible && ecart >= 0)
                {
                    ecartFaible = ecart;
                    valeur = main[i].valeur;
                    inf = false;
                }

                else if(main[i].valeur < valeurMin && main[i].valeur > 0)
                {
                    valeurMin = main[i].valeur;
                }
            }
            
        }
    }
    if(inf)
    {
        valeur = valeurMin;
    }
    return valeur;
}

void tourJoueurR(Joueur *joueur, Plateau *plateau, CartesJouees *cartesJouees)
{
    printf("C'est au tour du : ");
    afficherJoueur(joueur);
    printf("\n");
    afficherMain(joueur);

    printf("Le robot choisit une carte...\n");
    int carteJouer = choixCarteR(joueur->main, plateau);
    
    int i = 0;
    while(i <10)
    {
        if(joueur->main[i].valeur == carteJouer)
        {
            // Ajouter la carte au tableau des cartes jouées
            cartesJouees[joueur->id -1].carte = joueur->main[i];
            cartesJouees[joueur->id -1].idJoueur = joueur->id;
            // Retirer la carte de la main du joueur
            joueur->main[i].valeur = 0;
            joueur->main[i].teteDeBoeuf = 0;
            i = 10;
            //afficherCarte(cartesJouees[joueur->id -1].carte);
            printf("\n");
        }
        else
        {
            i++;
        }
    }
    printf("\nFin du tour du ");
    afficherJoueur(joueur);
    printf("\n\n");
}


void trierCartesJouees(CartesJouees *cartesJouees, int nbJoueurTotal)
{
    CartesJouees temp;

    for (int i = 0; i <  nbJoueurTotal; ++i) {
        for (int j = i + 1; j < nbJoueurTotal; ++j) {
            if (cartesJouees[i].carte.valeur < cartesJouees[j].carte.valeur) 
            {
                // Échange des éléments si nécessaire pour obtenir un ordre décroissant.
                temp = cartesJouees[i];
                cartesJouees[i] = cartesJouees[j];
                cartesJouees[j] = temp;
            }
        }
    }
}

void choixRangeesH(Joueur *joueur, Plateau *plateau, int *indRangee)
{
    printf("Joueur n°%d. \nQuelle rangée voulez-vous récupérer? Entrez son indice : ", joueur->id);
    scanf("%d", indRangee);  // Met à jour la valeur pointée par indRangee

    // On récupère le score de Tête de Bœuf de la rangée et on le donne au joueur qui a posé la carte inférieure
    joueur->nbrTdB += plateau->scoreTdB_Rangees[*indRangee - 1];
}


int choixRangeesR(Joueur *joueur, Plateau *plateau)
{
    int RangeeMin = 200;
    int valeurRangee = 0;
    int indRangeeR = 0;
    for(int i = 0; i < NBRANGEESMAX; i++)
    {
        valeurRangee = plateau->scoreTdB_Rangees[i];
        if(valeurRangee < RangeeMin)
        {
            RangeeMin = valeurRangee;
            indRangeeR = i+1;
        }
    }
    
    // On récupère le score de Tête de Bœuf de la rangée et on le donne au joueur qui a posé la carte inférieure
    joueur->nbrTdB += plateau->scoreTdB_Rangees[indRangeeR - 1];
    return  indRangeeR;
}

void finTour(Plateau *plateau, CartesJouees *cartesJouees, int nbJoueurTotal, Joueur *listeJoueurs, LogInfo logInfo)
{   
    
    //On trie les cartes jouées dans l'ordre decroissant
    trierCartesJouees(cartesJouees, nbJoueurTotal);
    //On affiche les cartes jouées
    for(int i = nbJoueurTotal - 1; i >= 0; i--)
    {
        afficherCarte(cartesJouees[i].carte);
        printf("\n");
    }
    //on affiche le plateau
    afficherPlateau(plateau);

    
    int ecartFaible = 200;
    int ecart = 104;
    int positionI;
    int positionJ;
    bool inf = true;

    for(int i = nbJoueurTotal - 1; i >=0; i--)
    {
        for(int j = 0; j < NBRANGEESMAX; j++)
        {
            //On prend la derniere carte et on la compare avec la derniere carte de chaque rangée
            int nbCarteRangees = plateau->nbrCartes_Rangees[j];
            ecart = cartesJouees[i].carte.valeur - plateau->rangees[j][nbCarteRangees -1].valeur;

            if(ecart < ecartFaible && ecart >= 0)
            {
                inf = false;
                ecartFaible = ecart;
                //On recupere la position de la carte avec laquelle elle a l'ecart de plus faible en valeur
                positionI = j;
                positionJ = nbCarteRangees;
            }
        }
        //SI un joueur a mis une carte inferieur à la valeur de toute les cartes du tableaux
        if(inf)
        {
            // On demande au joueur qui a posé la carte quelle rangée il veut récupérer
            for (int k = 0; k < nbJoueurTotal; k++)
            {
                if (listeJoueurs[k].id == cartesJouees[i].idJoueur)
                {
                    //Si le joueur est humain
                    if(listeJoueurs[k].typeJoueur == 0)
                    {
                        //choix de la rangee h
                        int indRangee;
                        choixRangeesH(&(listeJoueurs[k]), plateau, &indRangee);
                        int indRangee1 = indRangee - 1;
                        // On vide la rangée
                        for (int l = 0; l < 6; l++)
                        {
                            if (l == 0)
                            {
                                plateau->rangees[indRangee1][l].valeur = cartesJouees[i].carte.valeur;
                                plateau->rangees[indRangee1][l].teteDeBoeuf = cartesJouees[i].carte.teteDeBoeuf;
                                plateau->scoreTdB_Rangees[indRangee1] = cartesJouees[i].carte.teteDeBoeuf; 
                                plateau->nbrCartes_Rangees[indRangee1] = 1;
                            }
                            else
                            {
                                plateau->rangees[indRangee1][l].valeur = 0;
                                plateau->rangees[indRangee1][l].teteDeBoeuf = 0;
                            }
                        }
                    }
                    //c'est un robot
                    else
                    {
                        //choix de la rangée robot
                        int indRangee = choixRangeesR(&listeJoueurs[k], plateau);
                        int indRangee1 = indRangee-1;
                        // On vide la rangée
                        for (int l = 0; l < 6; l++)
                        {
                            if (l == 0)
                            {
                                plateau->rangees[indRangee1][l].valeur = cartesJouees[i].carte.valeur;
                                plateau->rangees[indRangee1][l].teteDeBoeuf = cartesJouees[i].carte.teteDeBoeuf;
                                plateau->scoreTdB_Rangees[indRangee1] = cartesJouees[i].carte.teteDeBoeuf; 
                                plateau->nbrCartes_Rangees[indRangee1] = 1;
                            }
                            else
                            {
                                plateau->rangees[indRangee1][l].valeur = 0;
                                plateau->rangees[indRangee1][l].teteDeBoeuf = 0;
                            }
                        }
                    }
                    
                }
            }
        }
        else if(positionJ >= 5)
        {
            //on recupere le score de Tete de Boeuf de la rangée et on le donne au joueur qui a pose la carte en 6eme
            for(int k = 0; k < nbJoueurTotal; k++)
            {
                if(listeJoueurs[k].id == cartesJouees[i].idJoueur)
                {
                    listeJoueurs[k].nbrTdB += plateau->scoreTdB_Rangees[positionI];
                }
            }
            //on vide la rangée
            for(int l = 0; l < 6; l++)
            {
                if(l == 0)
                {
                    plateau->rangees[positionI][l].valeur = cartesJouees[i].carte.valeur;
                    plateau->rangees[positionI][l].teteDeBoeuf = cartesJouees[i].carte.teteDeBoeuf;
                    plateau->scoreTdB_Rangees[positionI] = plateau->rangees[positionI][l].teteDeBoeuf;
                    plateau->nbrCartes_Rangees[positionI] = 1;
                }
                else
                {
                    plateau->rangees[positionI][l].valeur = 0;
                    plateau->rangees[positionI][l].teteDeBoeuf = 0;
                }
            }
        }
        else
        {
            //On place la carte jouée à la position recupere sur le plateau
            plateau->rangees[positionI][positionJ] = cartesJouees[i].carte;
            //on increment le nombre de carte dans cette rangée du plateau
            plateau->nbrCartes_Rangees[positionI] += 1;
            //on incremente le score de tete de boeuf de la rangée
            plateau->scoreTdB_Rangees[positionI] += cartesJouees[i].carte.teteDeBoeuf;
        }
        logInfo.joueurID = listeJoueurs[i].id;
        logInfo.score = listeJoueurs[i].nbrTdB;
        //on retire la carte des cartes jouées
        cartesJouees[i].carte.valeur = 0;
        cartesJouees[i].carte.teteDeBoeuf = 0;
        ecartFaible = 200;
        inf = true;
    }
    //On affiche le plateau Modifier
    afficherPlateau(plateau);
}
/*
void trierScore(int *score, int nbJoueurs)
{
    int temp;

    for (int i = 0; i <  nbJoueurs; ++i) {
        for (int j = i + 1; j < nbJoueurs; ++j) {
            if (score[i] < score[j]) 
            {
                // Échange des éléments si nécessaire pour obtenir un ordre décroissant.
                temp = score[i];
                score[i] = score[j];
                score[j] = temp;
            }
        }
    }
}
*/
void enregistrerInfo(LogInfo logInfo)
{
    FILE *file = fopen("game.log", "a");
    if (file != NULL)
    {
        fprintf(file, "Dans cette partie, il y a %d Joueurs.\nAu tour %d : \nJoueurID: %d, Score: %d\n",logInfo.nbJoueurTotal, logInfo.tour, logInfo.joueurID, logInfo.score);
        fclose(file);
    }
}

void manche(Joueur *listeJoueurs, int nbJoueurTotal, Plateau *plateau)
{
    CartesJouees cartesJouees[nbJoueurTotal]; // Tableau pour stocker les cartes jouées
    int nbTours = 0;
    int score[nbJoueurTotal];
    for(int i = 0; i < nbJoueurTotal; i++)
    {
        score[i] = listeJoueurs[i].nbrTdB;
    }
    int max = 0;
    for(int i =0; i < nbJoueurTotal; i++)
    {
        if(score[i]>max)
        {
            max = score[i];
        }
    }


    LogInfo logInfo;
    logInfo.nbJoueurTotal = nbJoueurTotal;
    while(nbTours < NBTOURSMAX && max <=66)
    {
        printf("Tour %d : \n", nbTours+1);
        logInfo.tour = nbTours;
        for(int j = 0; j < nbJoueurTotal; j++)
        {
            if(listeJoueurs[j].typeJoueur == 0)
            {
                tourJoueurH(&listeJoueurs[j], plateau, cartesJouees);
            }
            else
            {
                tourJoueurR(&listeJoueurs[j], plateau, cartesJouees);
            }
        }
        printf("Fin du tour %d \n", nbTours+1);
        nbTours++;
        finTour(plateau, cartesJouees, nbJoueurTotal, listeJoueurs, logInfo);
        afficherJoueurs(nbJoueurTotal, listeJoueurs);
        enregistrerInfo(logInfo);
    }

}
