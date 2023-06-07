/**
 * @file arbres_insert.c
 * @brief fichier d'implementation du module pour l'insertion de valeur dans une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_insert.h"
#include "../Seance2/arbres_parcours.h"
#include "../Seance1/arbres_construct.h"


/**
 * @brief rechercher un point de valeur v
 * @param [in] racine pointeur vers la racine de l'arborescence 
 * @return 
 *   - l'adresse du point contenant v si v existe dans l'arborescence
 *   - NULL, sinon
 */
cell_lvlh_t * rechercher_v(cell_lvlh_t * racine, char v)
{
    cell_lvlh_t** cour = &racine;
    eltType eltPile;
    pile_t* pile = initPile(NB_ELTPREF_MAX);
    int code=0;
    while(((*cour) != NULL || !estVidePile(pile)) && (*cour)->val != v )
    {
        
        if((*cour)->lv!=NULL)
        {   
            eltPile.adrCell = *cour;
            eltPile.adrPrec = NULL;
            eltPile.nbFils_ou_Freres = getNbFils_ou_Freres((*cour)->lv);
            empiler(pile, &eltPile, &code);
            cour = &(*cour)->lv;
        } else {
            if((*cour)->lh != NULL){
                cour=&(*cour)->lh;
            }else {
                while(((*cour)->lh == NULL) && !estVidePile(pile) && (*cour)->val != v)
                {
                    depiler(pile, &eltPile, &code);
                    cour = &eltPile.adrCell;     
                }
                cour = &(*cour)->lh;
            }
        }
        
    }
    libererPile(&pile);
    return *cour;
}

/**
 * @brief rechercher le double prec de w dans une liste de fils
 * @param [in] adrPere l'adresse du pere
 * @param [in] w la valeur a inserer
 * @return l'adresse du pointeur prec apres lequel w doit etre inseree
 */
cell_lvlh_t ** rechercherPrecFilsTries(cell_lvlh_t * adrpere, char w)
{
    cell_lvlh_t** pprec = &adrpere->lv;
    while (*pprec != NULL && (*pprec)->val <= w)
    {
        pprec = &(*pprec)->lh;
    }
    return pprec;
}

/** TO DO
 * @brief inserer une valeur w dans les fils d'un point de valeur v
 * @param [in] racine la racine de l'arborescence
 * @param [in] v la valeur d'un point auquel on va inserer la valeur w en fils
 * @param [in] w la valeur a inserer
 * @return 1 - insertion realisee; 0 - insertion n'a pas ete realisee
 */
int insererTrie(cell_lvlh_t * racine, char v, char w)
{
    int code_retour = 0;
    cell_lvlh_t* adrpere = rechercher_v(racine, v);
    if(adrpere != NULL)
    {
        cell_lvlh_t** pprec = rechercherPrecFilsTries(adrpere, w);
        cell_lvlh_t* nouv = allocPoint(w);
        if(nouv != NULL)
        {
            nouv->lh = (*pprec);
            (*pprec)=nouv;
            code_retour = 1; 
        }
    }
    return code_retour;
}
