#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "include/constantes.h"
#include "include/jeu.h"
#include "include/editeur.h"
#include "include/fichiers.h"

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    //  Chargement de l'icone du jeu
    SDL_WM_SetIcon(IMG_Load("res/images/pac_ghost.gif"), NULL); 

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    //  Titre de la fenetre du jeu
    SDL_WM_SetCaption("<|°_°|>   SOKO-PACMAN   <|°_°|>", NULL);

    menu = IMG_Load("res/images/menu.bmp");
    positionMenu.x = 0;
    positionMenu.y = 0;

    while (continuer)
    {#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "fusion.h"


/* The header file */
 /*2 Dimensional array a[TAILLE][TAILLE] For all 0*/
void Start()           /* Generate start Interface */
{
    printf("Welcome to 2048\n");
    printf("  1). A new game \n");
    printf("  2). help \n");
}
int Score(int **a) /* The scoring function */
{
    int i, j;
    int max = a[0][0];
    int sum = 0;
    for (i = 0; i < TAILLE; i++)
        for (j = 0; j < TAILLE; j++)
            if (a[i][j] > max)
                max = a[i][j];
    sum += max;
    return sum; /* Take the sum of the largest number as the score */
}
void Interface(int **a)
{
    int i, j;
    int b[2] = {2, TAILLE}, c[TAILLE] = {0, 1, 2, 3}, sum, n, m;
    do
    {
        srand((int)time(NULL)); /* Take time as a random number seed */
        m = c[rand() % TAILLE];
        n = c[rand() % TAILLE];
        /* Randomly generated coordinates */
        if (a[m][n] == 0) /* Determines whether it is a space */
        {
            a[m][n] = b[rand() % 2]; /* Randomly generated 2 or TAILLE*/
            break;                   /* Jump out of the loop */
        }
    } while (1);
    printf("%d %d %d\n", m, n, a[m][n]);
    for (i = 0; i < TAILLE; i++)
    {
        printf("-------------------------\n");
        for (j = 0; j < TAILLE; j++)
        {
            if ((m == i) && (n == j))
                printf("| %d ", a[m][n]); /* The output is randomly generated 2 or TAILLE*/
            else
            {
                if (a[i][j] > 0)
                    printf("| %d ", a[i][j]); /* if a[i][j] If there are Numbers, output them */
                else
                    printf("|   "); /* if a[i][j] No Numbers, output Spaces */
            }
        }
        printf("|\n");
    }
    printf("-------------------------\n");
    printf("      score :%d\n", sum = Score(a));
}


void Mouvement(char b, int **a)
{
    int x, m, i, j;
    switch (b)
    {
    case 'h':
        for (j = 0; j < TAILLE; j++)
            for (i = 1; i <= 3; i++)
                for (x = i, m = i; x > 0; x--, m--) /*x Is the number of cycles, m alternative i Keep the cycle going */
                {
                    if (a[m - 1][j] > 0)
                        break; /* If the 1 A non 0 And jump down 1 position */
                    else
                    {
                        a[m - 1][j] = a[m][j];
                        a[m][j] = 0;
                    }
                }
        Fusion_up(a);
        break;
    case 'b':
        for (j = 0; j < TAILLE; j++)
            for (i = 2; i >= 0; i--)
                for (x = 3 - i, m = i; x > 0; x--, m++)
                {
                    if (a[m + 1][j] > 0)
                        break;
                    else
                    {
                        a[m + 1][j] = a[m][j];
                        a[m][j] = 0;
                    }
                }
        Fusion_down(a);
        break;
    case 'g':
        for (i = 0; i < TAILLE; i++)
            for (j = 1; j <= 3; j++)
                for (x = j, m = j; x > 0; x--, m--)
                {
                    if (a[i][m - 1] > 0)
                        break;
                    else
                    {
                        a[i][m - 1] = a[i][m];
                        a[i][m] = 0;
                    }
                }
        Fusion_left(a);
        break;
    case 'd':
        for (i = 0; i < TAILLE; i++)
            for (j = 2; j >= 0; j--)
                for (x = 3 - j, m = j; x > 0; x--, m++)
                {
                    if (a[i][m + 1] > 0)
                        break;
                    else
                    {
                        a[i][m + 1] = a[i][m];
                        a[i][m] = 0;
                    }
                }
        Fusion_right(a);
        break;
    }
}

int ** allocation ()
{
	int **Tab;
	Tab = malloc(TAILLE * sizeof(int*));

    int i ;

    if ( Tab == NULL )
    {
    	exit( EXIT_FAILURE ) ;
    }

    for ( i = 0 ; i < TAILLE ; i++ )
    {
	Tab[i] = malloc(TAILLE * sizeof(int));
    }
    return Tab;
}

int main(int argc, char *argv[])
{
    system("clear");
    int i, j;


    int **plateau;
    plateau = allocation();


    for (i = 0; i < TAILLE; i++) {
        for (j= 0; j < TAILLE; j++) {
            plateau[i][j] = 0;
        }
    }

    for (i = 0; i < TAILLE; i++) {
        for (j= 0; j < TAILLE; j++) {
            printf("%d\t",plateau[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");

    int flag = 1;
    char c, k;
    system("stty -icanon");
outloop:;
    Start();
    k = getchar();
    printf("\n");
    if (k == '1')
    {
        while (flag == 1)
        {
            Interface(plateau);
            c = getchar();
            printf("\n");
            system("clear");
            Mouvement(c, plateau);
            for (i = 0; i < TAILLE; i++)
                for (j = 0; j < TAILLE; j++)
                {
                    if (plateau[i][j] == 0)
                    {
                        flag = 1;
                        goto end; /* If you have a checkerboard 1 Jump out of the judgment and continue to generate random Numbers */
                    }
                    else
                        flag = 0;
                }
        end:;
        }
    }
    if (k == '2')
    {
        do
        {
            printf(" Rules of the game: by clicking <w>,<s>,<a>,<d> Key to move the Numbers up, down, left and right. Add the same Numbers. The sum of the Numbers in each cell will be scored. \n");
            printf("  3). return \n");
            k = getchar();
        } while (k != 3);
        goto outloop; /* Jump to the start screen */
    }
    printf("      Game over \n");
    return 0;
}
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE: //    Demande l'arret du jeu
                continuer = 0;
                break;

            case SDLK_F1:   //  Touche F1
                regles(ecran);
                break;

            case SDLK_KP1: // Demande à jouer, niveau 1
                jouer(ecran, 1);
                break;

            case SDLK_KP2: // Demande à jouer, niveau 2
                jouer(ecran, 2);
                break;

            case SDLK_KP3: // Demande à jouer, niveau 3
                jouer(ecran, 3);
                break;

            case SDLK_KP4: // Demande l'éditeur de niveaux
                editeur(ecran);
                break;
                
            default:
                break;
            }
            break;
        default:
            break;
        }

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran -> format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }

    //printf("Nombre de déplacements : %d\n", deplacements);

    SDL_FreeSurface(menu);
    SDL_Quit();
    TTF_Quit();

    return EXIT_SUCCESS;
}
