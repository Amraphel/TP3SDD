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
    int nbRacine = 0; // entier représentant le nombre de racine
    char c ;          // caractère indiquateur de fin de fichier et utilisé pour surpprimer les espaces entre les couples
    
    if(tabEltPref && nbEltsPref){ //tableau des éléments et adresses mémoires du nombre d'éléments non vide
        FILE * file = fopen(fileName, "r"); // ouverture du fichier
        *nbEltsPref = 0; //initialisation à 0 élément

        if(file) //vérification si le fichier est bien ouvert
        {
            fscanf(file,"%d", &nbRacine); //récupération le nombre d'arbres différents
            c = fgetc(file); // déplacement d'un dans le fichier
            // déplacement dans tout le fichier
            while(c == ' ') 
            {
                //récupération des informations du fichier sous forme de couples et suppression des espaces 
                //stockage des valeurs dans un tableau 
                fscanf(file, "%c %d", &tabEltPref[*nbEltsPref].val, &tabEltPref[*nbEltsPref].nbFils);
                *nbEltsPref +=1; //augmentation du nombre d'élements à chaque passage
                c = fgetc(file); //déplacement d'un espace dans le fichier
            }
            fclose(file); //fermeture du fichier
        }
    }
    return nbRacine; // retourne le nombre de racine


    //LEXIQUE variables locales:
    // nbRacine -> nombre de racines
    // c -> permet le déplacement dans le fichier (indicateur de fin de fichier)
}

/** TO DO
 * @brief afficher les elements de la representation prefixee sur un flux de sortie
 * @param file : le flux de sortie
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref le nombre des elements du tabEltPref
 */
void printTabEltPref(FILE *file, eltPrefPostFixee_t *tabEltPref, int nbEltsPref)
{
    int ind; //indice d'itération
    for(ind=0; ind<nbEltsPref; ind++){ //pour tous les élements
        fprintf(file, " (%c,%d)", tabEltPref[ind].val, tabEltPref[ind].nbFils); //écriture dans un fichier sous forme de couple
    }
    fprintf(file,"\n");//retour à la ligne

    //LEXIQUE variable locale:
    // ind -> entier qui représente le nombre d'itération pour pouvoir parcourir tous les éléments
}

/** TO DO
 * @brief creer et initialiser un nouveau point de l'arborescence
 * @param [in] val la valeur du point
 * @return l'adresse du nouveau point 
 */
cell_lvlh_t *allocPoint(char val)
{
    cell_lvlh_t *nouv = malloc(sizeof(cell_lvlh_t)); //allocation de mémoire
    if(nouv) //allocation réussie
    {
        //initiation des valeurs du cell_lvlh alloué
        nouv->val = val;
        nouv->lv = NULL;
        nouv->lh = NULL;
    }
    return nouv; //retourne adresse du nouveau point

    //LEXIQUE variable locale :
    // nouv -> nouvelle cellule allouée
}

/** TO DO
 * @brief construire un arbre avec lvlh a partir de representation prefixee
 * @param [in] tabEltPref tableau des elements de la representation prefixee
 * @param [in] nbRacines nombre de racines de l'arborescence
 * @return : 
 *     - NULL si l'arbre resultatnt est vide
 *     - l'adresse de la racine de l'arbre sinon
*/
cell_lvlh_t* pref2lvlh(eltPrefPostFixee_t * tabEltPref,int nbRacines)
{
    int code=0; // code pour la fonction empiler
    cell_lvlh_t* nouv = NULL; // nouvelle cellule
    eltType eltPile; // contenu d'un élément de la pile

    cell_lvlh_t* adrTete=NULL; // adresse du premier element
    cell_lvlh_t** pprec=&adrTete; // pointeur précédent

    pile_t * pile = initPile(PILE_SZ); // pile
    eltPrefPostFixee_t * courLc=tabEltPref; // pointeur courant liste continue (tableau) 
    int NB_fils_ou_frere= nbRacines; // nombre de fils et/ou de frère


    while (NB_fils_ou_frere>0 || !estVidePile(pile)) // tant que l'on n'a pas tout parcouru 
    {
        
        if(NB_fils_ou_frere>0){ //nombre de frère > 0
            nouv = allocPoint(courLc->val); //allocation de mémoire
            *pprec=nouv; 
            
            //initialisation des informations de l'élément de la pile
            eltPile.adrPrec=&(nouv->lh);
            eltPile.nbFils_ou_Freres=NB_fils_ou_frere-1;
            
            empiler(pile,&eltPile, &code); //sauvegarde de l'élément dans la pile
            pprec=&(nouv->lv); //avancement de pprec dans la liste
            NB_fils_ou_frere= (courLc->nbFils); //mise à jour du nombre de fils ou de frère
            courLc= courLc+1; //avancement du pointeur courant dans le tableau

        }else{ //nombre de frère <= 0
            if(!estVidePile(pile)){ //s'il reste des elements empiles
                depiler(pile,&eltPile,&code); //supprime l'element de la pile
                pprec=eltPile.adrPrec; // déplacement de pprec
                NB_fils_ou_frere=eltPile.nbFils_ou_Freres; //mise a jour du nombre de fils ou de frere
            }
        }
        
    }
    libererPile(&pile); // liberation de la pile
    return adrTete; // retourne l'adresse de l'arbre

    //LEXIQUE variable locale :
    // code -> permet de savoir si la fonction empiler/dépiler à bien marche
    // nouv -> nouvelle cellule
    // eltPile -> contenue d'un element de la pile
    // adrTete -> adresse du premier element
    // pprec -> pointeur precedant de l'element courant (pointeur courLc)
    // pile -> pile pour sauvegarder les deplacements dans l'arbre
    // courLc -> pointeur courant liste continue (tableau) 
    // NB_fils_ou_frere -> nombre de fils ou de frere total

}


/** TO DO
 * @brief liberer les blocs meDmoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */
void libererArbre(cell_lvlh_t** adrPtRacine)
{
    if((*adrPtRacine)){//racine non nulle
        if((*adrPtRacine)->lv){//possède un fils
            libererArbre(&(*adrPtRacine)->lv);//libère l'espace mémoire du fils
        }
        if((*adrPtRacine)->lh){//possède un frère
            libererArbre(&(*adrPtRacine)->lh);//libère l'espace mémoire du frere
        }
        free(*adrPtRacine);//libère l'espace mémoire de la racine

        *adrPtRacine=NULL;//mis à null car la mémoire de la racine est liberee 
    }

}