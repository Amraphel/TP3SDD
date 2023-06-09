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
    cell_lvlh_t** cour = &racine; //initialisation du pointeur courant
    eltType eltPile; //initialisation d'un element de la pile
    pile_t* pile = initPile(PILE_SZ); //initialisation de la pile
    int code=0; //code de retour des fonctions empiler et depiler
    while(((*cour) != NULL || !estVidePile(pile)) && (*cour)->val != v ) //tant que l'on a pas tout parcouru
    {
        
        if((*cour)->lv!=NULL)//possede un fils
        {   
            //initialisation des informations de l'élément de la pile
            eltPile.adrCell = *cour;
            eltPile.adrPrec = NULL;
            eltPile.nbFils_ou_Freres = getNbFils_ou_Freres((*cour)->lv); //recuperation du nombre de fils
            empiler(pile, &eltPile, &code); //sauvegarde de l'element dans la pile
            cour = &(*cour)->lv; //deplacement verticale du pointeur courant
        } 
        else //ne possede pas de fils
        {
            if((*cour)->lh != NULL)//possede un frere
            {
                cour=&(*cour)->lh;//deplacement horizontal du pointeur courant
            }
            else //ne possede pas de frere
            {
                while(((*cour)->lh == NULL) && !estVidePile(pile) && (*cour)->val != v) //tant que l'on a pas parcouru tout l'arbre ou pas trouvela valeur
                {
                    depiler(pile, &eltPile, &code); //suppression de l'element dans la pile
                    cour = &eltPile.adrCell; //recuperation de l'adresse de la cellule de l'element pile qui vient d'etre supprimer  
                }
                cour = &(*cour)->lh; //deplacement horizantal du pointeur courant
            }
        }
        
    }
    libererPile(&pile); //libération de la memoire de la pile
    return *cour;//retourne l'adresse du point contenant la valeur ou null

    // LEXIQUE variables locales :
    // cour -> pointeur courant permettant de se déplacer dans l'arbre
    // eltPile -> element de la pile
    // pile -> pile pour sauvegarder les déplacements dans l'arbre
    // code -> permet de vérifier si l'empilement ou le dépilement c'est bien passé
}

/**
 * @brief rechercher le double prec de w dans une liste de fils
 * @param [in] adrPere l'adresse du pere
 * @param [in] w la valeur a inserer
 * @return l'adresse du pointeur prec apres lequel w doit etre inseree
 */
cell_lvlh_t ** rechercherPrecFilsTries(cell_lvlh_t * adrpere, char w)
{
    cell_lvlh_t** pprec = &adrpere->lv; //initialisation du pointeur precedant
    while (*pprec != NULL && (*pprec)->val <= w) //tant qu'on ne trouve pas la valeur et que l'on a pas tout parcouru
    {
        pprec = &(*pprec)->lh; //deplacement horizontal du pointeur précédant
    }
    return pprec; //retourne l'adresse du pointeur precedant w

    //LEXIQUE varible locale:
    //pprec -> pointeur precedant la valeur a trouver 
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
    int code_retour = 0; //initialisation du code de retour
    cell_lvlh_t* adrpere = rechercher_v(racine, v); //recuperation de l'adresse de v
    if(adrpere != NULL) //pere existe
    {
        cell_lvlh_t** pprec = rechercherPrecFilsTries(adrpere, w); //pointeur precedant pointe sur l'adresse où il faut insérer w
        cell_lvlh_t* nouv = allocPoint(w); //allocation de la nouvelle cellule
        if(nouv != NULL)//allocation réussie
        {
            if(pprec){//pprec non null
                nouv->lh = (*pprec); //pprec devient le frere de nouv
            }
            (*pprec)=nouv;//insert nouv a l'ancinene place de pprec
            code_retour = 1; //isertion reussie
        }
    }
    return code_retour;

    //LEXIQUE variables locales :
    //code_retour -> code de retour 1 insertinon reussi 0 echec de l'insertion
    //adrpere -> adresse du pere de la valeur que nous allons inserer
    //pprec -> pointeur precedant de w
    //nouv -> cellule de w
}


