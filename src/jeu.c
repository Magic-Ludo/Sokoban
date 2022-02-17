#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

//#include "../include/fichiers.h"  //  Tentative de réolution du Warning... Sans succès
#include "../include/constantes.h"
#include "../include/jeu.h"


void jouer(SDL_Surface *ecran, int niveau)
{
    //  Initialisation des paramètres
    SDL_Surface *pac_man[4] = {NULL};   //  4 surfaces car il y a 4 positions possibles pour Pacman
    SDL_Surface *mur = NULL, *fantome = NULL, *fantomeOK = NULL, *prison = NULL, *pac_man_Nouveau = NULL, *texte = NULL;
    SDL_Rect position, positionJoueur, position_texte;
    SDL_Event event;

    int nb_prisons = 1, nb_deplacements = 0;
    int continuer = 1, prisonsRestants = 0, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    //  Gestion du temps et du texte

    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
    int temps_Nouveau = 0, tempsPrecedent = 0, compteur = 0;
    char temps[40] = "";    // Tableau de char suffisamment grand pour afficher le texte du chrono
    int min = 0, sec = 0;

    //  Chargement de la police
    police = TTF_OpenFont("./res/police/CubicCoreMono.ttf", 45);
    if(!police) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    /* Initialisation du temps et du texte */
    temps_Nouveau = SDL_GetTicks();
    sprintf(temps, "Temps : %d", compteur);
    texte = TTF_RenderText_Shaded(police, temps, couleurNoire, couleurBlanche);

    //  Chargement des sprites du jeu
    mur = IMG_Load(".//res/images/mur.bmp");
    fantome = IMG_Load(".//res/images/pac_ghost.gif");   
    fantomeOK = IMG_Load(".//res/images/prison_ok.gif");
    prison = IMG_Load(".//res/images/prison.gif");
    pac_man[BAS] = IMG_Load(".//res/images/pac_B.gif");
    pac_man[GAUCHE] = IMG_Load(".//res/images/pac_G.gif");
    pac_man[HAUT] = IMG_Load(".//res/images/pac_H.gif");
    pac_man[DROITE] = IMG_Load(".//res/images/pac_D.gif");   

    pac_man_Nouveau = pac_man[DROITE];    // Lors de l'initialisation du jeu, 

    //  Chargement du niveau
    if (!chargerNiveau(carte, niveau))
        exit(EXIT_FAILURE); //  Vérification si le niveau peut s'ouvrir ou pas

    //  On trouve la position de départ de Pacman
    for (i = 0; i < NB_BLOCS_LARGEUR; i++)
    {
        for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
        {
            if (carte[i][j] == PAC_MAN) //  S'effectue si Pacman se trouve à la position [i][j]
            {
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
        }
    }

    //  Répétition des touches, déativé car utilisation de SDL_PollEvent
    //SDL_EnableKeyRepeat(100, 100);    

    while (continuer)
    {   
        temps_Nouveau = SDL_GetTicks();

        SDL_PollEvent(&event);
        
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            SDL_Delay(100); //  100 ms d'attente car on utilise SDL_PollEvent
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_UP:
                pac_man_Nouveau = pac_man[HAUT];
                deplacerJoueur(carte, &positionJoueur, HAUT);
                nb_deplacements ++;
                break;
            case SDLK_DOWN:
                pac_man_Nouveau = pac_man[BAS];
                deplacerJoueur(carte, &positionJoueur, BAS);
                nb_deplacements ++;
                break;
            case SDLK_RIGHT:
                pac_man_Nouveau = pac_man[DROITE];
                deplacerJoueur(carte, &positionJoueur, DROITE);
                nb_deplacements ++;
                break;
            case SDLK_LEFT:
                pac_man_Nouveau = pac_man[GAUCHE];
                deplacerJoueur(carte, &positionJoueur, GAUCHE);
                nb_deplacements ++;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }

        //  On efface l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran -> format, 0, 0, 0));

        //  On place les objets
        prisonsRestants = 0;

        for (i = 0; i < NB_BLOCS_LARGEUR; i++)
        {
            for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch (carte[i][j])
                {
                case MUR:
                    SDL_BlitSurface(mur, NULL, ecran, &position);
                    break;
                case FANTOME:
                    SDL_BlitSurface(fantome, NULL, ecran, &position);
                    break;
                case FANTOME_OK:
                    SDL_BlitSurface(fantomeOK, NULL, ecran, &position);
                    break;
                case PRISON:
                    SDL_BlitSurface(prison, NULL, ecran, &position);
                    nb_prisons ++;
                    prisonsRestants = 1;
                    break;
                }
            }
        }
        
        //  La partie est gagné si toute les prisons sont remplis, il n'y a plus de prisons libres
        if (!prisonsRestants) {
            SDL_Delay(500); // 0,5 seconde
            continuer = gagner(ecran, nb_deplacements, min, sec);
            //printf("nb_deplacements : %d\n", nb_deplacements);
            //printf("Temps m : %d\n", min);
            //printf("Temps s : %d\n", sec);
        }

        if (temps_Nouveau - tempsPrecedent >= 100) // Si 100 ms se sont au moins écoulées 
        {
            compteur += 100; // On rajoute 100 ms au compteur 

            format_temps(&min, &sec, compteur);
            //printf("Minutes : %d et secondes : %d\n", min, sec); 

            sprintf(temps, " Temps : %d min %d sec ", min, sec); // On écrit dans la chaîne "temps" le nouveau temps 

            SDL_FreeSurface(texte); //  On supprime la surface précédente 

            texte = TTF_RenderText_Shaded(police, temps, couleurBlanche, couleurNoire); //  On écrit la chaîne temps dans la SDL_Surface 
            
            tempsPrecedent = temps_Nouveau; //  On met à jour le "tempsPrecedent"
        }

        // Placement du joueur à la bonne position
        position.x = positionJoueur.x * TAILLE_BLOC;
        position.y = positionJoueur.y * TAILLE_BLOC;

        position_texte.x = 0;
        position_texte.y = 0;

        SDL_BlitSurface(texte, NULL, ecran, &position_texte); //    Blit du texte
        SDL_BlitSurface(pac_man_Nouveau, NULL, ecran, &position); //    Blit de Pacman

        SDL_Flip(ecran);
    }

    // Désactivation de la répétition des touches
    //SDL_EnableKeyRepeat(0, 0);

    // On libère les surfaces précédement utilisées
    SDL_FreeSurface(mur);
    SDL_FreeSurface(fantome);
    SDL_FreeSurface(fantomeOK);
    SDL_FreeSurface(prison);

    TTF_CloseFont(police);
    SDL_FreeSurface(texte);
    
    for (i = 0; i < 4; i++)
        SDL_FreeSurface(pac_man[i]);

    //return nb_deplacement;
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction)
{
    switch (direction)
    {
    case HAUT:
        if (pos -> y - 1 < 0) //    Vérification par rapport aux bors de l'écran pour ne pas dépasser
            break;
        if (carte[pos -> x][pos -> y - 1] == MUR) //    On arrete Pacman s'il y a un mur en face de lui
            break;
        //  Vérification des autres mouvements
        if ((carte[pos -> x][pos -> y - 1] == FANTOME || carte[pos -> x][pos -> y - 1] == FANTOME_OK) &&
            (pos -> y - 2 < 0 || carte[pos -> x][pos -> y - 2] == MUR ||
             carte[pos -> x][pos -> y - 2] == FANTOME || carte[pos -> x][pos -> y - 2] == FANTOME_OK))
            break;

        //    On vérifie si on a un fantaome à déplacer
        deplacerfantome(&carte[pos -> x][pos -> y - 1], &carte[pos -> x][pos -> y - 2]);

        pos -> y--;
        break;

    case BAS:
        if (pos -> y + 1 >= NB_BLOCS_HAUTEUR)
            break;
        if (carte[pos -> x][pos -> y + 1] == MUR)
            break;

        if ((carte[pos -> x][pos -> y + 1] == FANTOME || carte[pos -> x][pos -> y + 1] == FANTOME_OK) &&
            (pos -> y + 2 >= NB_BLOCS_HAUTEUR || carte[pos -> x][pos -> y + 2] == MUR ||
             carte[pos -> x][pos -> y + 2] == FANTOME || carte[pos -> x][pos -> y + 2] == FANTOME_OK))
            break;

        deplacerfantome(&carte[pos -> x][pos -> y + 1], &carte[pos -> x][pos -> y + 2]);

        pos -> y++;
        break;

    case GAUCHE:
        if (pos -> x - 1 < 0)
            break;
        if (carte[pos -> x - 1][pos -> y] == MUR)
            break;

        if ((carte[pos -> x - 1][pos -> y] == FANTOME || carte[pos -> x - 1][pos -> y] == FANTOME_OK) &&
            (pos -> x - 2 < 0 || carte[pos -> x - 2][pos -> y] == MUR ||
             carte[pos -> x - 2][pos -> y] == FANTOME || carte[pos -> x - 2][pos -> y] == FANTOME_OK))
            break;

        deplacerfantome(&carte[pos -> x - 1][pos -> y], &carte[pos -> x - 2][pos -> y]);

        pos -> x--;
        break;

    case DROITE:
        if (pos -> x + 1 >= NB_BLOCS_LARGEUR)
            break;
        if (carte[pos -> x + 1][pos -> y] == MUR)
            break;

        if ((carte[pos -> x + 1][pos -> y] == FANTOME || carte[pos -> x + 1][pos -> y] == FANTOME_OK) &&
            (pos -> x + 2 >= NB_BLOCS_LARGEUR || carte[pos -> x + 2][pos -> y] == MUR ||
             carte[pos -> x + 2][pos -> y] == FANTOME || carte[pos -> x + 2][pos -> y] == FANTOME_OK))
            break;

        deplacerfantome(&carte[pos -> x + 1][pos -> y], &carte[pos -> x + 2][pos -> y]);

        pos -> x++;
        break;
    }
}

void deplacerfantome(int *premiereCase, int *secondeCase)
{
    if (*premiereCase == FANTOME || *premiereCase == FANTOME_OK)
    {
        if (*secondeCase == PRISON)
            *secondeCase = FANTOME_OK;
        else
            *secondeCase = FANTOME;

        if (*premiereCase == FANTOME_OK)
            *premiereCase = PRISON;
        else
            *premiereCase = VIDE;
    }
}


int gagner(SDL_Surface *ecran, int deplace, int minutes, int secondes){

    SDL_Surface *gagne = NULL, *texte = NULL;
    TTF_Font *police = NULL;
    SDL_Rect position_gagne, position_texte;
    SDL_Color couleurNoire = {0, 0, 0}, couleurJaune = {255, 255, 0};

    char texte_score[1000] = "";
    int score = 0;

    // Chargement de la police
    police = TTF_OpenFont("./res/police/CubicCoreMono.ttf", 90);
    if(!police) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    if (minutes > 1){
        score = deplace * secondes * minutes;
    }
    else {
        score = deplace * secondes;
    }

    sprintf(texte_score, "%d", score);

    texte = TTF_RenderText_Shaded(police, texte_score, couleurJaune, couleurNoire);

    //printf("score : %d\n", score);

    position_gagne.x = 0;
    position_gagne.y = 0;
    //printf("Deplacements : %d\n", nb_deplacements);
    
    position_texte.x = 330;
    position_texte.y = 485;

    gagne = IMG_Load("./res/images/gagner_2.bmp");
    SDL_BlitSurface(gagne, NULL, ecran, &position_gagne); //    Blit de l'image
    SDL_BlitSurface(texte, NULL, ecran, &position_texte); //    Blit du texte

    SDL_Flip(ecran);
    SDL_Delay(4000); // 4 secondes

    SDL_FreeSurface(gagne);
    SDL_FreeSurface(texte);
    return EXIT_SUCCESS;
}


int format_temps(int *minutes, int *secondes, int temps_ms){
    //int *minutes = 0;
    //int *secondes = 0;

    *minutes = (temps_ms / 60000) % 60;
    *secondes = (temps_ms / 1000) % 60;

    return EXIT_SUCCESS;
}