#ifndef _TEMA_H
#define _TEMA_H
#include <stdlib.h>
#include <string.h>
#include "tema.h"

int main()
{
	/// PAS 1
	// Read from "Pas_1/candidati.csv"
	// Write to "Pas_1/test_1.csv"
	coada *c = creare_coada();
	citire_fisier(c);

	printf("=== PARTICIPANȚI ÎNREGISTRAȚI ===\n");

	scriere_fisier_test1(c);
	// liberare_mem(c);
	//  PAS 2
	node *root_lorzi = NULL;
	node *root_cavaleri = NULL;
	construire_bsturi(c, &root_lorzi, &root_cavaleri);

	scriere_fis2_lorzi(root_lorzi);
	scriere_fis2_cav_av(root_cavaleri); //
	citire_fisier_3(c);
	sterg_part(&root_lorzi, c);
	scriere_fisier_3(root_lorzi);

	//  pas 4
	int nr_trasee = 0;

	traseu trasee[10];
	heap *h = create(10);

	citeste_traseu(trasee, &nr_trasee);
	printf("nr_trasee = %d\n", nr_trasee);

	bst_to_vector_simplu(root_lorzi);
	scriere_vect();
	printf("\n-----------------\n");
	bst_to_vector_cav(root_cavaleri);
	scriere_vect_cav();
	filtrare_part(vector_lorzi, vector_cavaleri, index1, index2, trasee, nr_trasee, h);
	scriere_fisier4(h);
	recalc_experienta(h);

	scriere_fisier5(h);
	scriere_fisier6(h);
	printf(" ------\n");
	graf *g = creare_graf();
	int surse[11], nr_surse;
	int destinatii[11], nr_destinatii;

	sursa_dest(g, surse, &nr_surse, destinatii, &nr_destinatii);

	char **rez;
	int k;
	generat_trasee(g, surse, nr_surse, destinatii, nr_destinatii, &rez, &k);
	mergeSort(rez, 0, k - 1);
	scrie_trasee_cu_prefix(rez, k, "Pas_7/test_7.csv");
	for (int i = 0; i < k; i++)
		free(rez[i]);
	free(rez);

	eliberare_mem_bst(root_lorzi);
	eliberare_mem_bst(root_cavaleri);
	eliberare_mem(c);
	eliberare_heap(h);
	eliberare_vectl(vector_lorzi, index1);
	eliberare_mem_vector_cavaleri(vector_cavaleri, index2);
	eliberare_graf(g);

	return 0;
}

#endif
