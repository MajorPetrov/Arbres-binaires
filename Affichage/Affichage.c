#ifndef ARBREBINAIRE
#include "ArbreBinaire.h"
#endif
#include <stdio.h>
#include <stdlib.h>

static unsigned int ParcoursRecursif(Noeud_t arbre, FILE *mfile)
{
    static unsigned int nodenumber;
    unsigned int fg, fd, node;

    node = ++nodenumber;

    if (EstVide(arbre))
    {
        fprintf(mfile, "N%d [style=invis]\n", nodenumber);

        return nodenumber;
    }

    fprintf(mfile, "N%d [label=\"%d\"]\n", nodenumber, (int)ValeurDuNoeud(arbre));
    fg = ParcoursRecursif(arbre->filsgauche, mfile);
    fd = ParcoursRecursif(arbre->filsdroit, mfile);

    if (!EstVide(arbre->filsgauche))
        fprintf(mfile, "N%d -> N%d\n", node, fg);
    else
        fprintf(mfile, "N%d -> N%d [style=invis]\n", node, fg);

    if (!EstVide(arbre->filsdroit))
        fprintf(mfile, "N%d -> N%d\n", node, fd);
    else
        fprintf(mfile, "N%d -> N%d [style=invis]\n", node, fd);

    return node;
}

void SauverArbreDansFichier(Noeud_t arbre, char *file)
{
    char tmp[100] = "";
    FILE *mfile;

    sprintf(tmp, "%s.gv", file);

    mfile = fopen(tmp, "w");

    fprintf(mfile, "digraph G{\n");
    ParcoursRecursif(arbre, mfile);
    fprintf(mfile, "}\n");
    fclose(mfile);

    return;
}
