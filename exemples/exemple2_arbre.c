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

	tmp = FilsGauche(arbre);

	AjouterFilsGauche(tmp, CreerNoeud(1));
	AjouterFilsDroit(tmp, CreerNoeud(5));

	tmp = FilsDroit(arbre);

	AjouterFilsDroit(tmp, CreerNoeud(4));

	tmp = FilsDroit(tmp);

	AjouterFilsDroit(tmp, CreerNoeud(6));
	AjouterFilsGauche(tmp, CreerNoeud(7));

	SauverArbreDansFichier(arbre, "exemple2");

	return 0;
}
