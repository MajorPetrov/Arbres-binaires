#ifndef ARBREBINAIRE
#include "ArbreBinaire.h"
#endif
#include <stdio.h>
#include <stdlib.h>

static Noeud_t AllocationNoeudBinaire(value_t val)
{
    Noeud_t tmp;
    tmp = malloc(sizeof(struct NoeudBinaire_m));
    tmp->filsgauche = NULL;
    tmp->filsdroit = NULL;
    tmp->val = val;
    return tmp;
}

Noeud_t CreerArbreVide(void)
{
    return NULL;
}

Noeud_t CreerNoeud(value_t val)
{
    return AllocationNoeudBinaire(val);
}

int EstVide(Noeud_t n)
{
    return n == NULL;
}

value_t ValeurDuNoeud(Noeud_t n)
{
    return n->val;
}

/* ajouter au noeud permier argument, le noeud second argument à gauche si char=='g' et à droite si char =='d' */
void AjouterAuNoeud(Noeud_t pere, Noeud_t fils, char goud)
{
    switch (goud)
    {
    case 'g':
    {
        pere->filsgauche = fils;

        return;
    }
    case 'd':
    {
        pere->filsdroit = fils;

        return;
    }
    default:
    {
        printf("Error last argument should be d or g\n");
        exit(1);
    }
    }

    return;
}

/* ajoute en fils gauche au noeud premier argument le noeud second
   argument.

   CU: le fils gauche doit être vide
   Si il existe deja un noeud non vide a gauche, produit une erreur
*/
void AjouterFilsGauche(Noeud_t pere, Noeud_t fils)
{
    if (!EstVide(pere->filsgauche))
    {
        printf("Error: Il y a un fils gauche\n");
        exit(FILSEXISTANT);
    }

    AjouterAuNoeud(pere, fils, 'g');
}

/* ajoute en fils droit au noeud premier argumentle noeud second
   argument.

   CU: le fils droit doit être vide
   Si il existe deja un noeud non vide a droite, produit une erreur.
*/
void AjouterFilsDroit(Noeud_t pere, Noeud_t fils)
{
    if (!EstVide(pere->filsdroit))
    {
        printf("Error: Il y a un fils droit\n");
        exit(FILSEXISTANT);
    }

    AjouterAuNoeud(pere, fils, 'd');
}

/* remplace le fils gauche du noeud premier argument par le noeud
   second argument.
*/
void RemplacerFilsGauche(Noeud_t pere, Noeud_t fils)
{
    AjouterAuNoeud(pere, fils, 'g');
}

/* remplace le fils droit du noeud premier argument par le noeud
   second argument.
*/
void RemplacerFilsDroit(Noeud_t pere, Noeud_t fils)
{
    AjouterAuNoeud(pere, fils, 'd');
}

/* retourne le fils gauche (resp. droit) du premier argument 
   si char =='g' (resp. 'd') */
Noeud_t Descendre(Noeud_t n, char goud)
{
    switch (goud)
    {
    case 'd':
        return n->filsdroit;
    case 'g':
        return n->filsgauche;
    default:
    {
        printf("Error last argument should be d or g\n");
        exit(BADARGUMENT);

        return NULL;
    }
    }

    return NULL;
}

/* retourne le fils gauche du noeud premier argument 
 * CU: n ne doit pas être vide
 */
Noeud_t FilsGauche(Noeud_t n)
{
    return Descendre(n, 'g');
}

/* retourne le fils droit du noeud premier argument 
 * CU: n ne doit pas être vide
 */
Noeud_t FilsDroit(Noeud_t n)
{
    return Descendre(n, 'd');
}

int EstFeuille(Noeud_t a)
{
    if (EstVide(a))
    {
        printf("Error: Le noeud est vide\n");
        exit(ARBREVIDE);
    }

    return (EstVide(Descendre(a, 'g')) && EstVide(Descendre(a, 'd')));
}
