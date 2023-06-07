/**
 * @file arbres_parcours.c
 * @brief fichier d'implementation du module pour le parcours d'arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_parcours.h"


/** TO DO
 * @brief calculer le nombre de fils ou freres d'un point a partir du pointeur du debut de la liste
 * @param [in] ptCell pointeur vers le 1er frere
 * @return le nombre de fils ou freres
 */
int getNbFils_ou_Freres( cell_lvlh_t * ptCell)
{
    int nbFils_ou_Freres = 0;
    if (ptCell != NULL)
    {
        nbFils_ou_Freres = 1;
        cell_lvlh_t * pprec1 = ptCell;
        while (pprec1->lh != NULL)
        {
            nbFils_ou_Freres += 1;
            pprec1 = pprec1->lh;
        }
    }

    return nbFils_ou_Freres;
}


/** TO DO
 * @brief parcours en profondeur postfixee
 * @param [in] file le flux de sortie
 * @param [in] racine la racine de l'arborescence
 */
void printPostfixee(FILE* file, cell_lvlh_t * racine)
{
    int code=0;
    cell_lvlh_t ** cour = &racine;
    pile_t* pile = initPile(NB_ELTPREF_MAX);
    eltType eltPile;
    while( (*cour) != NULL || !estVidePile(pile))
    {
        if((*cour)->lv!=NULL)
        {   
            eltPile.adrCell = NULL;
            eltPile.adrPrec = cour;
            eltPile.nbFils_ou_Freres = getNbFils_ou_Freres((*cour)->lv);
            empiler(pile, &eltPile, &code);
            cour = &(*cour)->lv;
        } else {
            if((*cour)->lh != NULL){
                fprintf(file, "(%c,%d) ", (*cour)->val, 0);
                cour=&(*cour)->lh;
            }else {
                while(((*cour)->lh == NULL) && !estVidePile(pile) )
                {
                    fprintf(file, "(%c,%d) ", (*cour)->val, getNbFils_ou_Freres((*cour)->lv));
                    depiler(pile, &eltPile, &code);
                    cour = eltPile.adrPrec;
                    
                }
                fprintf(file, "(%c,%d) ", (*cour)->val, eltPile.nbFils_ou_Freres);
                cour = &(*cour)->lh;
            }
        }
    }
    fprintf(file,"%d\n", getNbFils_ou_Freres(racine));
    libererPile(&pile);
}
