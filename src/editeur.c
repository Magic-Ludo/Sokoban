#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../include/constantes.h"
#include "../include/editeur.h"
#include "../include/fichiers.h"

void editeur(SDL_Surface* ecran)
{
    SDL_Surface *mur = NULL, *fantome = NULL, *prison = NULL, *pac_man = NULL;
    SDL_Rect position;
    SDL_Event event;

    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    int objet_Nouveau = MUR, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    // Chargement des objets et du niveau
    mur = IMG_Load("./res/images/mur.bmp");
    fantome = IMG_Load("./res/images/pac_ghost.gif");
    prison = IMG_Load("./res/images/prison.gif");
    pac_man = IMG_Load("./res/images/pac_D.gif");

    if (!chargerNiveau(carte,1))
        exit(EXIT_FAILURE);

    //  Boucle sans fin de l'éditeur pour pourvoir éditer sans soucis
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:   // Gestion des boutons de la souris (enfoncé)
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objet_Nouveau;  //  L'objet est placé au niveau du pointeur de la souris
                    clicGaucheEnCours = 1; //   Permet de savoir quel est le bouton de la souris sur lequel on appuie
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)   //  Un clic droit permet d'effacer
                {
                    carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC] = VIDE;
                    clicDroitEnCours = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP: // Gestion des boutons de la souris (relevé)
                if (event.button.button == SDL_BUTTON_LEFT)
                    clicGaucheEnCours = 0;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    clicDroitEnCours = 0;
                break;
            case SDL_MOUSEMOTION:   // Gestion du mouvement de la souris (relevé)
                if (clicGaucheEnCours)
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objet_Nouveau;
                }
                else if (clicDroitEnCours)
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_s:
                        sauvegarderNiveau(carte);
                        break;
                    case SDLK_c:
                        chargerNiveau(carte, 1);    // On charge par defaut le niveau comme base de construction
                        break;
                    case SDLK_KP1:
                        objet_Nouveau = MUR;
                        break;
                    case SDLK_KP2:
                        objet_Nouveau = FANTOME;
                        break;
                    case SDLK_KP3:
                        objet_Nouveau = PRISON;
                        break;
                    case SDLK_KP4:
                        objet_Nouveau = PAC_MAN;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran -> format, 0, 0, 0));

        //  Positionnement des objets à l'écran
        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case FANTOME:
                        SDL_BlitSurface(fantome, NULL, ecran, &position);
                        break;
                    case PRISON:
                        SDL_BlitSurface(prison, NULL, ecran, &position);
                        break;
                    case PAC_MAN:
                        SDL_BlitSurface(pac_man, NULL, ecran, &position);
                        break;
                    default:
                        break;
                }
            }
        }

        // Comme d'habitude, on met à jour l'écran
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(mur);
    SDL_FreeSurface(fantome);
    SDL_FreeSurface(prison);
    SDL_FreeSurface(pac_man);
}
