/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"
#include "../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_CONSTRUCT)

TEST(nouvCell) { //TEST création d'une cellule
	cell_lvlh_t *new; //initialisation de la cellule

	new = allocPoint('A'); //créer la cellule de valeur A
	//VERIFICATIONS :
	REQUIRE( NULL != new ); //new est bien créer ?
	CHECK( 'A' == new->val ); //valeur de new = A ?
	CHECK( NULL == new->lv ); //new n'a pas de fils ?
	CHECK( NULL == new->lh ); //new n'a pas de frère ?

	free(new);//libération de la place mémoire de new

	//LEXIQUE variable locale:
	// new -> nouvelle cellule 
}


TEST(lirePref_fromFileName_exTP) {//TEST récupération de donnée dans un fichier
	int nbRacines = 0; //nombre de racine
	int nbEltsPref = 0; //nombre d'élément totale du fichier
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX]; //tableau des éléments 

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref); //récupération des inforamations

	printf("\033[34m\nlirePref_fromFileName_exTP :");//affichage de la source
	printf("\033[0m\n");

	//VERIFICATIONS :
	CHECK( 2 == nbRacines ); //bon nombre de racine ?
	CHECK( 13 == nbEltsPref ); //bon nombre d'élément ?
	CHECK( 'A' == tabEltPref[0].val ); //la valeur du premier élément du tableau est bien A ?
	CHECK( 3 == tabEltPref[0].nbFils ); //le premier élément a bien 3 fils ?

	CHECK( 'B' == tabEltPref[1].val ); //la valeur du deuxieme élément du tableau est bien B ?
	CHECK( 2 == tabEltPref[1].nbFils ); //il a bien 2 fils ?

	CHECK( 'C' == tabEltPref[7].val ); //la valeur du huitième élément du tableau est bien C ?  
	CHECK( 2 == tabEltPref[7].nbFils ); //il a bien 2 fils ?
	
	CHECK( 'I' == tabEltPref[nbEltsPref-1].val ); //la valeur du dernier élément du tableau est bien I ?
	CHECK( 0 == tabEltPref[nbEltsPref-1].nbFils ); //il a bien 0 fils ?

	//LEXIQUE variables locales:
	//nbRacines -> nombre de racine (de neoud) de la base de donnée
	//nbEltsPref -> nombre d'élement totale du fichier (taille max du tableau de donnée)
	//tabEltPref -> tableau des élément contenue dans le fichier
}

TEST(printTabEltPref_exTP) {//TEST affichage des valeurs
	int nbRacines = 0; //nombre de racine
	int nbEltsPref = 0; //nombre d'élément totale du fichier
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX]; //tableau des éléments

	char buffer[1024]; //buffer de taille 1024 espace d'écriture
	FILE * file = fmemopen(buffer, 1024, "w"); //ouverture du fichier qui contiendra les données en mode écriture
	REQUIRE ( NULL != file); //vérification que le fichier est bien ouvert

	printf("\033[34m\nprintPref_exTP :");//affichage de la source
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref); //récupération des informations
	fprintf(file, "%d", nbRacines); //écriture du nombre de racine dans le fichier
	printTabEltPref(file, tabEltPref, nbEltsPref);//ecriture des couples d'element dans le fichier
	fclose(file);//fermeture du fichier
	CHECK( 0 == strcmp(buffer, "2 (A,3) (B,2) (E,0) (J,0) (D,0) (H,1) (G,0) (C,2) (F,3) (K,0) (M,0) (T,0) (I,0)\n") ); //vérification : écriture du fichier correct ?

	//LEXIQUE variables locales:
	//nbRacines -> nombre de racine (de neoud) de la base de donnée
	//nbEltsPref -> nombre d'élement totale du fichier (taille max du tableau de donnée)
	//tabEltPref -> tableau des élément contenue dans le fichier
	//buffer -> emplacement d'écriture
	//file -> buffer ouvert en mode écriture
}

TEST(pref2lvlh1_exTP) {//TEST création d'un arbre
	int nbRacines = 0; //nombre de racine
	int nbEltsPref = 0; //nombre d'élément totale du fichier
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX]; //tableau des éléments
	cell_lvlh_t *racine = NULL; //initialisation de l'arbre
	
	char buffer[1024]; //espace d'écriture
	FILE * file = fmemopen(buffer, 1024, "w");//ouverture de l'espace en mode écriture
	REQUIRE ( NULL != file); //vérification que le ficheir est bien ouvert

	printf("\033[35m\npref2lvlh1_exTP :");//affichage de la source
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, nbEltsPref);//récupération des donnée sous forme de tableau

	racine=pref2lvlh(tabEltPref,&nbRacines);//création de l'arbre

	//VERIFICATIONS :
	CHECK(racine->val == 'A'); //la racine a bien pour valeur A ?
	CHECK(racine->lv->val =='B'); //le fils de la racine a bien pour valeur B ?
	CHECK(racine->lv->lv->val == 'E'); //le fils du fils de la racine a bien pour valeur E ?
	CHECK(racine->lv->lv->lh->val == 'J'); //le frère du fils du fils de la racine a bien pour valeur J ?
	CHECK(racine->lv->lh->val == 'D'); //le frere du fils de la racine a bien pour valeur D ?
	CHECK(racine->lv->lh->lh->val == 'H'); //le frere du frere du fils de la racine a bien pour valeur H ?
	CHECK(racine->lv->lh->lh->lh == NULL); //le frere du frere du fils de la racine a pas de frere ?
	CHECK(racine->lv->lh->lh->lv->val == 'G'); //le fils du frere du frere du fils de la racine a bien pour valeur G ?
	CHECK(racine->lh->val == 'C'); // le frere de la racine a bien pour valeur C ?
	CHECK(racine->lh->lv->val == 'F'); //le fils du frère de la racine a bien pour valeur F ?
	CHECK(racine->lh->lv->lv->val == 'K'); //le fils du fils du frère de la racine a bien pour valeur K ?
	CHECK(racine->lh->lv->lv->lh->val == 'M'); //le frere du fils du fils du frere de la racine a bien pour valeur M ?
	CHECK(racine->lh->lv->lv->lh->lh->val == 'T');//le frere du frere du fils du fils du frere de la racine a bien pour valeur T ?
	CHECK(racine->lh->lv->lh->val == 'I'); //le frere du fils du frere de la racine a bien pour valeur I ?

	libererArbre(&racine);//liberartion de l'arbre
	fclose(file);//fermeture du fichier

	//LEXIQUE variables locales:
	//LEXIQUE variables locales:
	//nbRacines -> nombre de racine (de neoud) de la base de donnée
	//nbEltsPref -> nombre d'élement totale du fichier (taille max du tableau de donnée)
	//tabEltPref -> tableau des élément contenue dans le fichier
	//racine -> adresse premier element de l'arbre
	//buffer -> emplacement d'écriture
	//file -> buffer ouvert en mode écriture
}


END_TEST_GROUP(ARBRE_CONSTRUCT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_CONSTRUCT);
	return EXIT_SUCCESS;
}
