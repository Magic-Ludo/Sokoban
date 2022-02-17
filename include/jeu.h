/*
Header des fonctions du jeu
*/

#ifndef DEF_JEU
#define DEF_JEU

    void jouer(SDL_Surface* ecran, int niveau);
    void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
    void deplacerfantome(int *premiereCase, int *secondeCase);
    int gagner(SDL_Surface *ecran, int deplace, int minutes, int secondes);
    int format_temps(int *minutes, int *secondes, int temps_ms);

#endif
