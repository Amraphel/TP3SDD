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
    int NB_fils_ou_frere = 0; //initialisation nombre de fils ou frère
    if (ptCell != NULL) //pointeur non null
    {
        NB_fils_ou_frere = 1; //car il existe
        cell_lvlh_t * cour = ptCell;//pointeur courant
        while (cour->lh != NULL)//possède un frère ?
        {
            NB_fils_ou_frere += 1;//incrémentation pour chaque frère
            cour = cour->lh;//déplacement dans l'arbre horizontalement
        }
    }
    return NB_fils_ou_frere;//retourne le nombre de frère

    //LEXIQUE variables locales :
    // NB_fils_ou_frere -> nombre de frère que possède la cellule
    // cour -> pointeur courant permettant de se déplacer dans l'arbre
}


/** TO DO
 * @brief parcours en profondeur postfixee
 * @param [in] file le flux de sortie
 * @param [in] racine la racine de l'arborescence
 */
void printPostfixee(FILE* file, cell_lvlh_t * racine)
{
    int code=0; //code pour l'empilement et le dépilement 
    cell_lvlh_t ** cour = &racine; //double pointeur couran
    pile_t* pile = initPile(NB_ELTPREF_MAX); //pile
    eltType eltPile; //element de la pile
    while( (*cour) != NULL || !estVidePile(pile)) //pointeur courant nonn null et la pile n'est pas vide
    {
        if((*cour)->lv!=NULL)//possède un fils 
        {   
            //initialisation des valeurs de l'element de la pile
            eltPile.adrCell = *cour;
            eltPile.adrPrec = NULL;
            eltPile.nbFils_ou_Freres = getNbFils_ou_Freres((*cour)->lv); //recuperation du nombre de frère
            empiler(pile, &eltPile, &code);//sauvegarde des données de cet element
            cour = &(*cour)->lv;//déplacement du pointeur courant verticalement
        } 
        else //ne possède pas de fils
        {
            if((*cour)->lh != NULL){//possède un frère
                fprintf(file, "(%c,%d) ", (*cour)->val, 0);//ecriture dans le fichier le couple
                cour=&(*cour)->lh; //déplacement horizontal de cour
            }
            else //ne possède pas de fils 
            {
                while(((*cour)->lh == NULL) && !estVidePile(pile) ) //pointeur courant non null et la pile non vide
                {
                    fprintf(file, "(%c,%d) ", (*cour)->val, getNbFils_ou_Freres((*cour)->lv));//écriture dans le fichier le couple
                    depiler(pile, &eltPile, &code);//supprime les données de l'élément de la pile
                    cour = &eltPile.adrCell;//cour devient pointe sur l'élement supprimer
                    
                }
                fprintf(file, "(%c,%d) ", (*cour)->val, eltPile.nbFils_ou_Freres);//écriture dans le fichier le couple
                cour = &(*cour)->lh;// deplacement horizontale de cour
            }
        }
    }
    fprintf(file,"%d\n", getNbFils_ou_Freres(racine));//écriture du nombre de fils de la racine 
    libererPile(&pile);//libération de l'espace mémoire de la pile

    //LEXIQUE variables locales :
    // code -> permet de savoir si l'empliement ou de dépilement c'est bien fait
    // cour -> pointeur courant permettant de se déplacer dans l'arbre
    // pile -> pile pour stocker les éléments pile et se déplacer correctemant dans l'arbre
    // eltPile -> élément de la pile 
}
