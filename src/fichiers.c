#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../include/constantes.h"
#include "../include/fichiers.h"

int chargerNiveau(int rang[][NB_BLOCS_HAUTEUR], int niveau)
{
    FILE * fichier = NULL;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
    int i = 0, j = 0;

    if (niveau == 1) {
        fichier = fopen("./niveaux/niveau_1.niv", "r");
        if (fichier == NULL)
            return 0;

    fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);
    }

    if (niveau == 2) {
        fichier = fopen("./niveaux/niveau_2.niv", "r");
        if (fichier == NULL)
            return 0;

    fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);
    }

    if (niveau == 3) {
        fichier = fopen("./niveaux/niveau_3.niv", "r");
        if (fichier == NULL)
            return 0;

    fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);
    }

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)    //  On "décode le fchier" niveau
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
            {
                case '0':
                    rang[j][i] = 0;
                    break;
                case '#':
                    rang[j][i] = 1;
                    break;
                case 'C':
                    rang[j][i] = 2;
                    break;
                case 'I':
                    rang[j][i] = 3;
                    break;
                case 'P':
                    rang[j][i] = 4;
                    break;
            }
        }
    }

    fclose(fichier);
    return 1;
}

int sauvegarderNiveau(int rang[][NB_BLOCS_HAUTEUR])
{
    FILE* fichier = NULL;
    int i = 0, j = 0;

    fichier = fopen("./niveaux/niveau_4.niv", "a");
    if (fichier == NULL)
        return 0;

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            fprintf(fichier, "%d", rang[j][i]);
        }
    }

    fclose(fichier);
    return 1;
}


void regles(SDL_Surface* ecran) 
{
    SDL_Surface *regles = NULL;
    SDL_Rect positionRegles;
    SDL_Event event_regles;

    positionRegles.x = 0;
    positionRegles.y = 0;

    regles = IMG_Load("./res/images/regles.bmp");
    
    //SDL_Delay(4000); // 4 secondes
    
    int continuer = 1;

    while (continuer)
    {
        SDL_WaitEvent(&event_regles);
        switch (event_regles.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event_regles.key.keysym.sym)
            {
            case SDLK_ESCAPE: // Veut arrêter le jeu
                continuer = 0;
                break;
            default:
                break;
            }
        default:
            break;
        }

    SDL_BlitSurface(regles, NULL, ecran, &positionRegles);

    SDL_Flip(ecran);

    }

}