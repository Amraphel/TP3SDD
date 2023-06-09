/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "../Seance1/arbres_construct.h"
#include "arbres_parcours.h"
#include "../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_PARCOURS)

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


TEST(getNbFils_ou_Freres) {//TEST recuperation du nombre de frere
	int nbRacines = 0; //nombre de racine
	int nbEltsPref = 0; //nombre des éléments de la table 
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX]; //tableau des éléments 
	cell_lvlh_t *racine = NULL; //racine de l'arbre
	
	char buffer[1024]; //espace d'écriture
	FILE * file = fmemopen(buffer, 1024, "w"); //ouverture du buffer en écriture
	REQUIRE ( NULL != file);

	printf("\033[35m\ngetNbFils_ou_Freres :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref); //récuperation du nombre de racine
	racine = pref2lvlh(tabEltPref, nbRacines); //récupération de l'adresse de la racine de l'arbre

	//VERIFICATIONS : 
	REQUIRE( NULL != racine ); // la racine n'est pas null ?
	CHECK( 2 == getNbFils_ou_Freres(racine) ); // la racine à 2 freres y compris lui-meme ?
	CHECK( 3 == getNbFils_ou_Freres(racine->lv) ); // la racine à 3 fils ?

	REQUIRE( NULL != racine->lv ); //le fils de la racine n'est pas null
	CHECK( 3 == getNbFils_ou_Freres(racine->lv) );     // le fils de la racine à 3 freres y compris lui-meme ?
	CHECK( 2 == getNbFils_ou_Freres(racine->lv->lv) ); // le fils de la racine à 2 fils ?

	REQUIRE( NULL != racine->lv->lh ); //le frere du fils de la racine existe ?
	CHECK( 0 == getNbFils_ou_Freres(racine->lv->lh->lv) ); //le frere du fils de la racine à 0 fils ?

	REQUIRE( NULL != racine->lv->lh->lh );//le frere du frere du fils de la racinne n'est pas null ?
	CHECK( 1 == getNbFils_ou_Freres(racine->lv->lh->lh->lv) ); // le frère du frère du fils de la racine à 1 fils ?

	fclose(file);//fermeture du fichier
	libererArbre(&racine);// libération de la place mémoire de l'arbre

	// LEXIQUE variables locales:
	// nbRacines -> nombre de racine (de noeud) de la base de donnée
	// nbEltsPref -> nombre d'élement totale du fichier (taille max du tableau de donnée)
	// tabEltPref -> tableau des éléments contenus dans le fichier
	// buffer -> emplacement d'écriture
	// file -> buffer ouvert en mode écriture
	// racine -> racine de l'arbre
}

TEST(printPostfixee) {//TEST de l'affichage sous forme postifixee
	int nbRacines = 0; //nombre de racines
	int nbEltsPref = 0; //nombre des éléments de la table 
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX]; //tableau des éléments
	cell_lvlh_t *racine = NULL; //initialisation de la racine
	
	char buffer[1024]; //espace d'écriture
	FILE * file = fmemopen(buffer, 1024, "w"); //ouverture du buffer en mode écriture
	REQUIRE ( NULL != file);// vérification que le fichier est bien ouvert 

	printf("\033[35m\nprintPostFixee :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref); //recuperation du nombre de racines
	racine = pref2lvlh(tabEltPref, nbRacines); //récupération de l'adresse de la racine de l'arbre
	printPostfixee(file, racine); //écriture sur le buffer les données de l'arbre
	fclose(file); //fermeture du fichier
	CHECK( 0 == strcmp(buffer,"(E,0) (J,0) (B,2) (D,0) (G,0) (H,1) (A,3) (K,0) (M,0) (T,0) (F,3) (I,0) (C,2) 2\n") ); //comparaison des résultats
	
	libererArbre(&racine); //liberation de l'espace mémoire de l'arbre

	//LEXIQUE varibles locales :
	// nbRacines -> nombre de racine (de neoud) de la base de donnée
	// nbEltsPref -> nombre d'élement totale du fichier (taille max du tableau de donnée)
	// tabEltPref -> tableau des élément contenue dans le fichier
	// buffer -> emplacement d'écriture
	// file -> buffer ouvert en mode écriture
	// racine -> racine de l'arbre
}


END_TEST_GROUP(ARBRE_PARCOURS)

int main(void) {
	RUN_TEST_GROUP(ARBRE_PARCOURS);
	return EXIT_SUCCESS;
}
