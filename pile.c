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
pile_t* initPile(int taille)
{
    if(taille !=0) //taille différent de 0 
    {
        pile_t* pile = malloc(sizeof(pile_t));

        //initialisation des valeurs
        pile->taille = taille;
        pile->sommet = -1;
        pile->base = malloc(sizeof(taille*sizeof(eltType))); //allocation de la base

        return pile;
    }
    else //taille egale a 0 donc retourner null
        return NULL;

    
}


/** TO DO
 * @brief Liberer les memoires occupees par la pile
 * @param [in, out] adrPtPile l'adresse du pointeur de la structure pile_t
 */
void libererPile(pile_t** adrPtPile)
{
    if(*adrPtPile != NULL)
    {
        free((*adrPtPile)->base); //libération des éléments dynamique
        free((*adrPtPile)); //libération des éléments statiques (sommet, taille)
        *adrPtPile = NULL; //ne pointe plus sur la liste libéré
    }
}


/** TO DO
 * @brief Verifier si la pile est vide (aucun element dans la "base")
 * @param [in] ptPile l'adresse de la structure pile_t
 * @return 1 - vide, ou 0 - non vide
 */
int estVidePile(pile_t * ptPile)
{
    if(ptPile->sommet == -1)
        return 1;
    else
        return 0;
}


/** TO DO
 * @brief Entrer un element dans la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [in] ptVal l'adresse de la valeur a empiler
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
void empiler(pile_t * ptPile, eltType * ptVal, int* code)
{
    if(ptPile->sommet < ptPile->taille-1)
    {
        ptPile->sommet +=1;
        *(ptPile->base + ptPile->sommet) = *ptVal;
        *code = 0;
    }
    else 
        *code = 1;

}


/** TO DO
 * @brief Sortir un element de la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [out] ptRes l'adresse de l'element sorti
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
void depiler(pile_t* ptPile, eltType* ptRes,int* code)
{
    if(estVidePile(ptPile)==0)
    {
        
        *ptRes = *(ptPile->base + ptPile->sommet);
        ptPile->sommet -=1;
        *code = 0;
        
    }
    else 
        *code = 1;

}
