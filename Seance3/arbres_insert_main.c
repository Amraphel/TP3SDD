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

TEST(nouvCell) {//TEST création d'une cellule
	cell_lvlh_t *new; //initialisation de la cellule

	new = allocPoint('A'); //créer la cellule de valeur A
	//VERIFICATIONS :
	REQUIRE( NULL != new );  //new est bien créee ?
	CHECK( 'A' == new->val ); //valeur de new = A ?
	CHECK( NULL == new->lv ); //new n'a pas de fils ?
	CHECK( NULL == new->lh ); //new n'a pas de frère ?

	free(new);//libération de la place mémoire de new

	//LEXIQUE variable locale:
	// new -> nouvelle cellule
}


TEST(rechercher_v) {//TEST recherche valeur 
	int nbRacines = 0; // initialisation nombre de racine
	int nbEltsPref = 0; //initialisation nombre totale d'élément dans le fichier
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];//initialisation du tableau des éléments
	cell_lvlh_t *racine = NULL;//initialisation du pointeur de la racine de l'arbre
	cell_lvlh_t *pere = NULL; //initialisation pointeur du pere

	printf("\033[35m\nrechercher_v :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref); //récuperation du nombre de racine
	racine = pref2lvlh(tabEltPref, nbRacines);//création de l'arbre et récupération de l'adresse de la première racine

	pere = rechercher_v(racine, 'X'); //chercher un noeud de valeur X
	CHECK( NULL == pere );// pere de valeur X n'existe pas

	pere = rechercher_v(racine, 'A'); //chercher un noeud de valeur A
	REQUIRE( NULL != pere );
	CHECK( 'A' == pere->val ); // le pere est de valeur A

	pere = rechercher_v(racine, 'Z'); //chercher un noeud de valeur Z
	CHECK( NULL == pere ); // valeur qui n'existe pas

	pere = rechercher_v(racine, 'J'); //chercher un noeud de valeur J
	REQUIRE( NULL != pere );
	CHECK( 'J' == pere->val );//le pere est de valeur J

	libererArbre(&racine); //liberartion de l'espace memoire de l'arbre

	//LEXIQUE variables locales:
	//nbRacines -> nombre de racine au début du fichier
	//nbEltsPref -> nombre d'élement totale du fichier (taille max du tableau de donnée)
	//tabEltPref -> tableau des éléments contenus dans le fichier
	//pere -> l'adresse du noeud de valeur v
}

TEST(rechercherPrecFilsTries) {
	int nbRacines = 0; // initialisation nombre de racine
	int nbEltsPref = 0; //initialisation nombre totale d'élément dans le fichier
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX]; //initialisation tableau des éléments
	cell_lvlh_t *racine = NULL; //initialisation du pointeur de l'arbre
	cell_lvlh_t *pere = NULL; //initialisation pointeur du pere
	cell_lvlh_t **pprec = NULL; //initialisatin pointeur precedant 

	printf("\033[34m\nrechercherPrecFilsTries :");
	printf("\033[0m\n");
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);//récuperation du nombre de racine
	racine = pref2lvlh(tabEltPref, nbRacines); //création de l'arbre et récupération de l'adresse de la première racine

	//Recherche F dans l'arbre
	pere = rechercher_v(racine, 'F'); 
	REQUIRE( NULL != pere );
	CHECK( 'F' == pere->val );

	//Recherche ou inserer L dans les fils de F
	pprec = rechercherPrecFilsTries(pere, 'L');
	REQUIRE( NULL != *pprec );
	CHECK( 'M' == (*pprec)->val ); //placer au milieu avant M

	//Recherche ou inserer A dans les fils de F
	pprec = rechercherPrecFilsTries(pere, 'A');
	REQUIRE( NULL != *pprec );
	CHECK( 'K' == (*pprec)->val ); //placer au debut avant K

	//Recherche ou inserer Z dans les fils de F
	pprec = rechercherPrecFilsTries(pere, 'Z');
	CHECK( NULL == (*pprec)); //placer a la fin

	//Recherche C dans l'arbre
	pere = rechercher_v(racine, 'C');
	//Recherche ou inserer F dans les fils de C
	pprec = rechercherPrecFilsTries(pere, 'F');
	REQUIRE( NULL != *pprec );
	CHECK( 'I' == (*pprec)->val ); //placer avant I

	libererArbre(&racine);//liberartion de l'espace memoire de l'arbre

	//LEXIQUE variables locales:
	//nbRacines -> nombre de racine au début du fichier
	//nbEltsPref -> nombre d'élement totale du fichier (taille max du tableau de donnée)
	//tabEltPref -> tableau des éléments contenus dans le fichier
	//racine -> adresse premier element de l'arbre
	//pere -> l'adresse du noeud de valeur v
	//pprec -> pointeur précédant pointe sur la cellule avant laquelle la cellule sera inserée
}

TEST(insererTrie) {
	int nbRacines = 0; // initialisation nombre de racine
	int nbEltsPref = 0; //initialisation nombre totale d'élément dans le fichier
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];//initialisation tableau des éléments
	cell_lvlh_t *racine = NULL; //initialisation du pointeur de l'arbre

	printf("\033[34m\ninsererTrie :");
	printf("\033[0m\n");
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);//récuperation du nombre de racine
	racine = pref2lvlh(tabEltPref, nbRacines); //création de l'arbre et récupération de l'adresse de la première racine

	printf("\033[34mPremiere Insertion : B dans A");
	printf("\033[0m\n");
	insererTrie(racine,'A','B');
	//VERIFICATIONS: B devient le fils de A
	CHECK('B' == racine->lv->val);
	CHECK('B' == racine->lv->lh->val);
	CHECK('D' == racine->lv->lh->lh->val);

	printf("\033[34mDeuxieme Insertion : A dans A");
	printf("\033[0m\n");
	insererTrie(racine, 'A', 'A');
	//VERIFICATIONS: A devient le fils de A
	CHECK('A' == racine->lv->val);
	CHECK('B' == racine->lv->lh->val);
	CHECK('B' == racine->lv->lh->lh->val);
	CHECK('D' == racine->lv->lh->lh->lh->val);

	printf("\033[34mTroisieme Insertion : L dans F");
	printf("\033[0m\n");
	insererTrie(racine, 'F', 'L');
	//VERIFICATIONS: L devient le fils de F
	CHECK('F' == racine->lh->lv->val);
	CHECK('K' == racine->lh->lv->lv->val);
	CHECK('L' == racine->lh->lv->lv->lh->val);
	CHECK('M' == racine->lh->lv->lv->lh->lh->val);
	CHECK('T' == racine->lh->lv->lv->lh->lh->lh->val);
	
	printf("\033[34mQuatrieme Insertion : Z dans F");
	printf("\033[0m\n");
	insererTrie(racine, 'F', 'Z');
	//VERIFICATIONS: Z devient le fils de F
	CHECK('F' == racine->lh->lv->val);
	CHECK('K' == racine->lh->lv->lv->val);
	CHECK('L' == racine->lh->lv->lv->lh->val);
	CHECK('M' == racine->lh->lv->lv->lh->lh->val);
	CHECK('T' == racine->lh->lv->lv->lh->lh->lh->val);
	CHECK('Z' == racine->lh->lv->lv->lh->lh->lh->lh->val);


	libererArbre(&racine);//liberartion de l'espace memoire de l'arbre

	//LEXIQUE variables locales:
	//nbRacines -> nombre de racine au début du fichier
	//nbEltsPref -> nombre d'élement totale du fichier (taille max du tableau de donnée)
	//tabEltPref -> tableau des éléments contenus dans le fichier
	//racine -> adresse premier element de l'arbre
}

END_TEST_GROUP(ARBRE_INSERT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_INSERT);
	return EXIT_SUCCESS;
}
