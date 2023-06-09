/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "../Seance1/arbres_construct.h"
#include "arbres_insert.h"
#include "../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_INSERT)

TEST(nouvCell) {
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );

	free(new);
}


TEST(rechercher_v) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	cell_lvlh_t *pere = NULL;

	printf("\033[35m\nrechercher_v :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	pere = rechercher_v(racine, 'X');   // valeur inexistante
	CHECK( NULL == pere );

	pere = rechercher_v(racine, 'A');   // valeur a la racine
	REQUIRE( NULL != pere );
	CHECK( 'A' == pere->val );

	pere = rechercher_v(racine, 'Z');   // valeur qui n'existe pas
	CHECK( NULL == pere );

	pere = rechercher_v(racine, 'J');   // valeur du dernier fils de B
	REQUIRE( NULL != pere );
	CHECK( 'J' == pere->val );

	libererArbre(&racine);
}

TEST(rechercherPrecFilsTries) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	cell_lvlh_t *pere = NULL;
	cell_lvlh_t **pprec = NULL;

	printf("\033[34m\nrechercherPrecFilsTries :");
	printf("\033[0m\n");
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	pere = rechercher_v(racine, 'F');
	REQUIRE( NULL != pere );
	CHECK( 'F' == pere->val );

	pprec = rechercherPrecFilsTries(pere, 'L');
	REQUIRE( NULL != *pprec );
	CHECK( 'M' == (*pprec)->val );

	pprec = rechercherPrecFilsTries(pere, 'A');
	REQUIRE( NULL != *pprec );
	CHECK( 'K' == (*pprec)->val );

	pprec = rechercherPrecFilsTries(pere, 'Z');
	CHECK( NULL == (*pprec));

	pere = rechercher_v(racine, 'C');
	pprec = rechercherPrecFilsTries(pere, 'F');
	REQUIRE( NULL != *pprec );
	CHECK( 'I' == (*pprec)->val );

	libererArbre(&racine);
}

TEST(insererTrie) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;

	printf("\033[34m\ninsererTrie :");
	printf("\033[0m\n");
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	printf("\033[34mPremiere Insertion : B dans A");
	printf("\033[0m\n");
	insererTrie(racine,'A','B');
	CHECK('B' == racine->lv->val);
	CHECK('B' == racine->lv->lh->val);
	CHECK('D' == racine->lv->lh->lh->val);

	printf("\033[34mDeuxieme Insertion : A dans A");
	printf("\033[0m\n");
	insererTrie(racine, 'A', 'A');
	CHECK('A' == racine->lv->val);
	CHECK('B' == racine->lv->lh->val);
	CHECK('B' == racine->lv->lh->lh->val);
	CHECK('D' == racine->lv->lh->lh->lh->val);

	printf("\033[34mTroisieme Insertion : L dans F");
	printf("\033[0m\n");
	insererTrie(racine, 'F', 'L');
	CHECK('F' == racine->lh->lv->val);
	CHECK('K' == racine->lh->lv->lv->val);
	CHECK('L' == racine->lh->lv->lv->lh->val);
	CHECK('M' == racine->lh->lv->lv->lh->lh->val);
	CHECK('T' == racine->lh->lv->lv->lh->lh->lh->val);
	
	printf("\033[34mQuatrieme Insertion : Z dans F");
	printf("\033[0m\n");
	insererTrie(racine, 'F', 'Z');
	CHECK('F' == racine->lh->lv->val);
	CHECK('K' == racine->lh->lv->lv->val);
	CHECK('L' == racine->lh->lv->lv->lh->val);
	CHECK('M' == racine->lh->lv->lv->lh->lh->val);
	CHECK('T' == racine->lh->lv->lv->lh->lh->lh->val);
	CHECK('Z' == racine->lh->lv->lv->lh->lh->lh->lh->val);


	libererArbre(&racine);
}

END_TEST_GROUP(ARBRE_INSERT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_INSERT);
	return EXIT_SUCCESS;
}
