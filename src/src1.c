/**   
* code sources qui comprend le code de la recherche sequentielle
* et de la recherche dichotomique
*/

#include <stdlib.h>
#include <stdio.h>

#define N 10 /** taille max des tableaux utiliser*/
#define TEST -1 /** nombre pour effectuer les test dans les recherches*/
typedef int tabEntiers[N];
int recherche_dicho_iteratif(int valeur,  tabEntiers tablo);
int recherche_sequentielle (int valeur,  tabEntiers tablo );
const tabEntiers leTablo = {23, 54, 65, 12, 43, 78, 68, 93, 18, 31} ; /**un tableau de valeur */
const tabEntiers leTabloTrie = {13, 24, 35, 42, 53, 68, 77, 83, 88, 91} ; /**un tableau de valeur triee */

typedef struct {
    char recherche;/** Caractere de recherche associe au test. */
    int num_test;/** Numero du test. */
    int nb_test;/** Nombre total de tests. */
} structure_test;/** Sturcture d'un test */

typedef struct {
    char prenom;/** Prenom de l'etudiant. */
    char nom;/** Nom de l'etudiant. */
    int grp_td;/** Numero du groupe de travaux diriges (TD). */
    int grp_tp;/** Numero du groupe de travaux pratiques (TP). */
} structure_etu ;/** Structure d'un etudiant */ 



/**
* \brief verifie que les fonctions de recherche fonctionnent,
* et ecrit a l'ecran l'indice de la valeurs recherche
* \return EXIT_SUCCESS
*/
int main(){
    //declaration des variables
    int test1 = 65 ; /** valeurs de test 1(sequentielle)*/
    int test2 = 43 ; /** valeur de test 2(dichotomique)*/
    char test3 = "test3"; /** pour test */
    float test4 = 3.14; /** Pi */

    // saisie des donnees
    printf("%d \n",recherche_sequentielle(65,leTablo));
    printf("%d \n",recherche_dicho_iteratif(43,leTabloTrie));


    // traitement des donnees



    // affichage des resultats



    return EXIT_SUCCESS;
}

/**
 * \brief Recherche sequentielle dans un tableau d'entiers.
 *
 * \detail Cette fonction effectue une recherche sequentielle pour trouver la position
 * d'une valeur donnee dans un tableau d'entiers. Si la valeur est presente dans le tableau,
 * la fonction retourne l'indice de la premiere occurrence de la valeur. Sinon, elle retourne -1.
 *
 * \param valeur La valeur a rechercher dans le tableau.
 * \param tablo Le tableau d'entiers dans lequel effectuer la recherche.
 * \return L'indice de la premiere occurrence de la valeur dans le tableau, ou -1 si la valeur n'est pas presente.
 */
int recherche_sequentielle (int valeur,  tabEntiers tablo ){
    int i = 0; /** indice permettant de parcourir le tableau*/
    int id=-1; /** indice de la valeur si trouve*/
    while (id == TEST && i < N){
        if (tablo[i]==valeur){
            id=i;
        }else{
            i=i+1;
        } 
    }
    return id ; 
}

/**
 * \brief Recherche iterative par dichotomie dans un tableau d'entiers.
 *
 * \detail Cette fonction effectue une recherche iterative par dichotomie pour trouver la position
 * d'une valeur donnee dans un tableau d'entiers trie. Si la valeur est presente dans le tableau,
 * la fonction retourne l'indice de la premiere occurrence de la valeur. Sinon, elle retourne -1.
 *
 * \param valeur La valeur a rechercher dans le tableau.
 * \param tablo Le tableau d'entiers trie dans lequel effectuer la recherche.
 * \return L'indice de la premiere occurrence de la valeur dans le tableau, ou -1 si la valeur n'est pas presente.
 */
int recherche_dicho_iteratif(int valeur,  tabEntiers tablo){
    int mid ; /** indice du millieu de la liste*/
    int id = -1 ; /** indice de la valeur si trouve*/
    int min = 0 ; /** indice du min de la liste*/
    int max = N-1 ; /** indice du max de la liste*/
    while (id==TEST && min <= max){
        mid = (max+min)/2;
        if (valeur < tablo[mid]){
            max=mid-1;
        }else if (valeur > tablo[mid]){
            min=mid+1;
        }else if (valeur == tablo[mid]){
            id = mid;
        }  
    }
    return id;
}
