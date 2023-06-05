/**
 * @file pile.c
 * @brief fichier d'implementation pour la gestion de pile
 */
 
#include <stdlib.h>
#include "pile.h"

/** TO DO
 * @brief Initialiser une pile du type pile_t
 *   - allocation de memoire pour une structure pile_t et un tableau de taille elements
 * @param [in] taille taille de la pile
 * @return l'adresse de la structure
 */
pile_t * initPile(int taille)
{
    pile_t * p = (pile_t *)malloc(sizeof(pile_t));//allocation mémoire 
    if(p){
        if (taille>0)//si la taille est non nulle
        {
            p->taille = taille;
            p->sommet = -1;
            p->base = (eltType *)malloc(taille*sizeof(eltType));
        }else //Si la taille est nulle
            p = NULL;
    }else { //Si l'allocation échoue
        p = NULL;   
    }
        
    return p;
}



/** TO DO
 * @brief Liberer les memoires occupees par la pile
 * @param [in, out] adrPtPile l'adresse du pointeur de la structure pile_t
 */
void libererPile(pile_t ** adrPtPile)
{
    if (*adrPtPile) //si la pile est non nulle, on libère la base puis la pile
    {
        free((*adrPtPile)->base);
        free(*adrPtPile);
        *adrPtPile = NULL;
    }
}


/** TO DO
 * @brief Verifier si la pile est vide (aucun element dans la "base")
 * @param [in] ptPile l'adresse de la structure pile_t
 * @return 1 - vide, ou 0 - non vide
 */
 int estVidePile(pile_t * ptPile)
{
    return  (ptPile->sommet == -1);

}


/** TO DO
 * @brief Entrer un element dans la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [in] ptVal l'adresse de la valeur a empiler
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
void empiler(pile_t * ptPile, eltType * ptVal, int * code)
{
    if (ptPile->taille-1 > ptPile->sommet) //si la pile est assez grande pour accueillir un nouvel élément
    {
        ptPile->sommet++; //On augment le sommet
        copyElt(ptVal, &(ptPile->base[ptPile->sommet])); // On insere l'élément
        *code = 0;
    }
    else
    {
        *code = 1;
    }
}



/** TO DO
 * @brief Sortir un element de la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [out] ptRes l'adresse de l'element sorti
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
void depiler(pile_t * ptPile, eltType * ptRes, int * code)
{
    if (!estVidePile(ptPile))//si la pile est non vide
    {
        copyElt(&(ptPile->base[ptPile->sommet]), ptRes); //On récupère l'élément
        ptPile->sommet--;//On réduit le sommet
        *code = 0;
    }
    else 
    {
        *code = 1;
    }
}