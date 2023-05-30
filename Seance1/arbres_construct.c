/**
 * @file arbres_construct.c
 * @brief fichier d'implementation du programme pour la construction d'une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"

/**
 * @brief lire le fichier contenant la representation prefixee de l'arborescence
 * @param [in] fileName le nom du fichier contenant la representation prefixee
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref l'adresse memoire contenant le nombre des elements du tabEltPref
 * @return le nombre de racines
 */
int lirePref_fromFileName(char * fileName, eltPrefPostFixee_t* tabEltPref , int* nbEltsPref)
{
    int nbRacine = 0;
    char c ;
    
    if(tabEltPref && nbEltsPref){
        FILE * file = fopen(fileName, "r");
        *nbEltsPref = 0;

        if(file)
        {
            fscanf(file,"%d", &nbRacine);
            c = fgetc(file);
            while(c == ' ')
            {  
                fscanf(file, "%c %d", &tabEltPref[*nbEltsPref].val, &tabEltPref[*nbEltsPref].nbFils);
                *nbEltsPref +=1;
                c = fgetc(file);
            }
            fclose(file);
        }
    }
    return nbRacine;
}

/** TO DO
 * @brief afficher les elements de la representation prefixee sur un flux de sortie
 * @param file : le flux de sortie
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref le nombre des elements du tabEltPref
 */
void printTabEltPref(FILE *file, eltPrefPostFixee_t *tabEltPref, int nbEltsPref)
{
    int ind;
    for(ind=0; ind<nbEltsPref; ind++){
        fprintf(file, " (%c,%d)", tabEltPref[ind].val, tabEltPref[ind].nbFils);
    }
    fprintf(file,"\n");

}

/** TO DO
 * @brief creer et initialiser un nouveau point de l'arborescence
 * @param [in] val la valeur du point
 * @return l'adresse du nouveau point 
 */
cell_lvlh_t *allocPoint(char val)
{
    cell_lvlh_t *nouv = malloc(sizeof(cell_lvlh_t));
    if(nouv)
    {
        nouv->val = val;
        nouv->lv = NULL;
        nouv->lh = NULL;
        //test
    }
    return nouv;
}

/** TO DO
 * @brief construire un arbre avec lvlh a partir de representation prefixee
 * @param [in] tabEltPref tableau des elements de la representation prefixee
 * @param [in] nbRacines nombre de racines de l'arborescence
 * @return : 
 *     - NULL si l'arbre resultatnt est vide
 *     - l'adresse de la racine de l'arbre sinon
*/
int* pref2lvlh(int* a0)
{
     cell_lvlh* nouv = NULL;

    pile_t pile = initPile(PILE_SZ);
    cell_lvlh_t* adrTete=NULL;
    int* courLc=a0;
    cell_lvlh_t* pprec=adrTete;
    int NB_fils_ou_frere= *a0;
    courLc+=1;

    while (NB_fils_ou_frere>0 || !estVide(pile))
    {
        if(NB_fils_ou_frere>0){
            nouv = allocPoint(*courLc);
            pprec= nouv;
            empiler(pile, NB_fils_ou_frere-1);
            empiler(pile, nouv->lh);
            pprec=nouv->lh;
            NB_fils_ou_frere= *(courLc+2)
            courLc= courLc->lh;

        }else{
            if(!estVide(pile)){
                pprec=depiler(pile);
                NB_fils_ou_frere=depiler(pile);
            }
        }
    }

    libererPile(pile)
    return adrTete;
    

}

/** TO DO
 * @brief liberer les blocs memoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */
//  libererArbre()
// {
// // TO DO
// }