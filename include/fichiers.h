/*
Gestion des fichiers du jeu
*/

#ifndef DEF_FICHIERS
#define DEF_FICHIERS

    int chargerNiveau(int rang[][NB_BLOCS_HAUTEUR], int niveau);
    int sauvegarderNiveau(int rang[][NB_BLOCS_HAUTEUR]);
    void regles(SDL_Surface* ecran);

#endif

