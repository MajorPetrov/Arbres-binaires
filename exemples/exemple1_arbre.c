#include "ArbreBinaire.h"
#include "Affichage.h"

int main(void)
{
	Noeud_t arbre, tmp;

	arbre = CreerNoeud(12);
	tmp = CreerNoeud(9);

	AjouterFilsGauche(arbre, tmp);

	tmp = CreerNoeud(8);

	AjouterFilsDroit(arbre, tmp);
	SauverArbreDansFichier(arbre, "exemple1");

	return 0;
}
