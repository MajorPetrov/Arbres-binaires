#include <stdio.h>

#include "ArbreBinaire.h"
#include "Affichage.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

/* Manipulation d'arbres binaires */
static int nbcomp = 0;

Noeud_t arbre1(void)
{
    Noeud_t a1 = CreerNoeud(12);

    AjouterFilsGauche(a1, CreerNoeud(9));
    AjouterFilsDroit(a1, CreerNoeud(8));

    return a1;
}

Noeud_t arbre2(void)
{
    Noeud_t a2 = CreerNoeud(12), tmp = CreerNoeud(9);

    AjouterFilsGauche(a2, tmp);

    tmp = FilsGauche(a2);
    AjouterFilsDroit(tmp, CreerNoeud(5));

    tmp = FilsDroit(tmp);
    AjouterFilsGauche(tmp, CreerNoeud(7));

    return a2;
}

Noeud_t arbre3(void)
{
    Noeud_t a3 = arbre1(), tmp;

    tmp = FilsGauche(a3);

    AjouterFilsGauche(tmp, CreerNoeud(1));
    AjouterFilsDroit(tmp, CreerNoeud(5));

    tmp = FilsDroit(a3);

    AjouterFilsDroit(tmp, CreerNoeud(4));

    tmp = FilsDroit(tmp);

    AjouterFilsGauche(tmp, CreerNoeud(7));
    AjouterFilsDroit(tmp, CreerNoeud(6));

    return a3;
}

void imprimer(Noeud_t a)
{
    if (!EstVide(a))
    {
        imprimer(FilsGauche(a));
        printf("%d ", ValeurDuNoeud(a));
        imprimer(FilsDroit(a));
    }
}

int taille(Noeud_t a)
{
    if (EstVide(a))
        return 0;
    else
    {
        if (EstFeuille(a))
            return 1;
        else
            return taille(FilsGauche(a)) + taille(FilsDroit(a)) + 1;
    }
}

int hauteur(Noeud_t a)
{
    if (EstVide(a))
        return -1;
    else
    {
        if (EstFeuille(a))
            return 1;
        else
            return max(hauteur(FilsGauche(a)), hauteur(FilsDroit(a))) + 1;
    }
}

int nbFeuilles(Noeud_t a)
{
    if (EstVide(a))
        return 0;
    else
    {
        if (EstFeuille(a))
            return 1;
        else
            return nbFeuilles(FilsGauche(a)) + nbFeuilles(FilsDroit(a));
    }
}

/* Comptage d'arbres */
int nbArbres(int n)
{
    int i, res;

    if (n < 0)
        return 0;
    else
    {
        if (n <= 1)
            return 1;
        else
        {
            res = 0;

            for (i = 0; i < n - 1; i++)
                res += nbArbres(i) * nbArbres(n - i - 1);

            return nbArbres(n - 1) + res;
        }
    }
}

/* Comptage d'arbres */
int nbArbresEfficace(int n)
{
    int k, l;
    value_t res = 0;
    value_t tab[n];
    tab[0] = 1;

    if (n < 0)
        ;
    else
    {
        if (n <= 1)
            res = 1;
        else
        {
            res = 1;

            for (k = 1; k <= n; k++)
            {
                for (l = 1; l < k; l++)
                    res += tab[l] * tab[k - l - 1];

                tab[k] = res;
            }
        }
    }

    return res;
}

/* Manipulation d'arbres binaires de recherche */
Noeud_t abr1(void)
{
    Noeud_t a1 = CreerNoeud(6);
    Noeud_t temp = CreerNoeud(4);

    AjouterFilsGauche(a1, temp);
    AjouterFilsGauche(temp, CreerNoeud(2));
    AjouterFilsDroit(a1, CreerNoeud(7));
    AjouterFilsDroit(temp, CreerNoeud(5));

    temp = FilsGauche(temp);

    AjouterFilsGauche(temp, CreerNoeud(1));

    return a1;
}

Noeud_t ajouter(value_t v, Noeud_t a)
{
    if (EstVide(a))
        return CreerNoeud(v);
    else
    {
        Noeud_t fg = FilsGauche(a), fd = FilsDroit(a), ag, ad;

        if (v <= ValeurDuNoeud(a))
        {
            ag = ajouter(v, fg);

            RemplacerFilsGauche(a, ag);

            return a;
        }
        else
        {
            ad = ajouter(v, fd);

            RemplacerFilsDroit(a, ad);

            return a;
        }
    }
}

Noeud_t abr2(void)
{
    Noeud_t a2 = CreerNoeud(5);

    ajouter(4, a2);
    ajouter(2, a2);
    ajouter(7, a2);
    ajouter(6, a2);
    ajouter(1, a2);

    return a2;
}

Noeud_t abr3(void)
{
    Noeud_t a3 = CreerNoeud(7);

    ajouter(1, a3);
    ajouter(4, a3);
    ajouter(5, a3);
    ajouter(6, a3);
    ajouter(2, a3);

    return a3;
}

int appartient(value_t v, Noeud_t a)
{
    nbcomp++;

    if (EstVide(a))
        return 0;
    else
    {
        nbcomp++;

        if (v == ValeurDuNoeud(a))
            return 1;
        else
        {
            nbcomp++;

            if (v <= ValeurDuNoeud(a))
                return appartient(v, FilsGauche(a));
            else
                return appartient(v, FilsDroit(a));
        }
    }
}

int valeur_minimale(Noeud_t abr)
{
    if (EstVide(abr))
        return 0;
    else
    {
        Noeud_t temp = FilsGauche(abr), temp2;

        if (temp == NULL)
            return ValeurDuNoeud(abr);
        else
        {
            while (temp != NULL)
            {
                temp2 = temp;
                temp = FilsGauche(temp);
            }

            return ValeurDuNoeud(temp2);
        }
    }
}

int valeur_maximale(Noeud_t abr)
{
    if (EstVide(abr))
        return 0;
    else
    {
        Noeud_t temp = FilsDroit(abr), temp2;

        if (temp == NULL)
            return ValeurDuNoeud(abr);
        else
        {
            while (temp != NULL)
            {
                temp2 = temp;
                temp = FilsDroit(temp);
            }

            return ValeurDuNoeud(temp2);
        }
    }
}

/* Entier mysterieux */
Noeud_t construitArbreEntierMysterieux(value_t i, value_t j)
{
    if (i < j - 2)
    {
        value_t med = (i + j) / 2;
        Noeud_t a = CreerNoeud(med);

        AjouterFilsGauche(a, construitArbreEntierMysterieux(i, med - 1));
        AjouterFilsDroit(a, construitArbreEntierMysterieux(med + 1, j));

        return a;
    }
    else
    {
        if (i == j - 1)
        {
            Noeud_t a = CreerNoeud(j);

            AjouterFilsGauche(a, CreerNoeud(i));

            return a;
        }
        else
        {
            if (i == j - 2)
            {
                Noeud_t a = CreerNoeud(j - 1);

                AjouterFilsGauche(a, CreerNoeud(j - 2));
                AjouterFilsDroit(a, CreerNoeud(j));

                return a;
            }
        }
    }
}

/*int median=(i+j)/2,k;
	Noeud_t myst=CreerNoeud(median);
	if(i>j)
		return NULL;
	for(k=i;k<=j;k++){
		if(k!=median)
			ajouter(k,myst);
	}
   return myst;*/

void jouer(int n)
{
    Noeud_t myst = construitArbreEntierMysterieux(1, n), fiston = myst;
    char coup[100];

    printf("\n Ceci est un jeu de l'entier mystérieux. Choisissez un nombre entre 1 et %n et regardez moi le deviner.");
    printf("\nEst ce %d? Taper 'g' pour gagne, '+' pour plus grand, '-' pour moins grand: ", (ValeurDuNoeud(myst)));
    scanf("%s", coup);

    while (coup[0] != 'g')
    {
        while (coup[0] != '+' && coup[0] != '-' && coup[0] != 'g')
        {
            printf("\n Commande invalide: ");
            scanf("%s", coup);
        }

        if (coup[0] == '+')
        {
            fiston = FilsDroit(fiston);

            if (EstVide(fiston))
            {
                printf("Tu triches, c'est pas bien ça.");
                coup[0] = 'g';
            }
            else
            {
                printf("\nEst ce %d? Taper 'g' pour gagne, '+' pour plus grand, '-' pour moins grand: ", (ValeurDuNoeud(fiston)));
                scanf("%s", coup);
            }
        }
        else
        {
            fiston = FilsGauche(fiston);

            if (EstVide(fiston))
            {
                printf("Tu triches, c'est pas bien ça.");
                coup[0] = 'g';
            }
            else
            {
                printf("\nEst ce %d? Taper 'g' pour gagne, '+' pour plus grand, '-' pour moins grand: ", (ValeurDuNoeud(fiston)));
                scanf("%s", coup);
            }
        }
    }

    printf("\nCh'suis trop fort :P\n");

    return;
}

/* Tests sur les arbres binaires */
void testArbreBinaire(Noeud_t a)
{
    imprimer(a);
    printf("\n");
    printf("Taille     = %d\n", (taille(a)));
    printf("Hauteur    = %d\n", (hauteur(a)));
    printf("nbFeuilles = %d\n", (nbFeuilles(a)));
}

/* Tests sur les arbres binaires de recherche */
void testABR(Noeud_t a)
{
    int i;

    imprimer(a);
    printf("\n");
    printf("Taille     = %d\n", (taille(a)));
    printf("Hauteur    = %d\n", (hauteur(a)));
    printf("nbFeuilles = %d\n", (nbFeuilles(a)));
    printf("Valeurs présentes dans l'arbre : ");

    for (i = 0; i <= 10; i++)
    {
        nbcomp = 0;

        printf("\n");

        if (appartient(i, a))
            printf("%d appartient à l'arbre ", i);
        else
            printf("%d n'appartient pas à l'arbre ", i);

        printf("Valeur recherchée: %d; nb comp: %d", i, nbcomp);
    }

    printf("\nPlus petite valeur de l'arbre: %d", (valeur_minimale(a)));
    printf("\nPlus grande valeur de l'arbre: %d", (valeur_maximale(a)));
    printf("\n");
}

/* Programme principal */
int main(int argc, char **argv)
{
    int i;

    printf("Arbre1:");
    testArbreBinaire(arbre1());

    printf("Arbre2:");
    testArbreBinaire(arbre2());

    printf("Arbre3:");
    testArbreBinaire(arbre3());

    for (i = 0; i <= 19; i++)
        printf("Le nombre d'arbres à %d noeuds est %d\n", i, (nbArbres(i)));

    for (i = 0; i <= 19; i++)
        printf("Le nombre d'arbres à %d noeuds est %d\n", i, (nbArbresEfficace(i)));

    printf("\nABR1:");
    testABR(abr1());

    printf("\nABR2:");
    testABR(abr2());

    printf("\nABR3:");
    testABR(abr3());

    printf("Arbre mysterieux entre 12 et 24:\n");
    imprimer(construitArbreEntierMysterieux(12, 24));
    printf("\n");

    jouer(100);

    return 0;
}
