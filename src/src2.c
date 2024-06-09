/** 
 * programme permettant de faire des calcul simple entre 2 nombres
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#define MAX 10  /** Nombre Max */
#define MIN 0 /** Nombre Min*/

typedef struct {
    int x; /** Coordonnee x du poInt */
    int y; /** Coordonnee y du poInt */
}PoInt; /** Structure d'un poInt*/

typedef struct {
    char nom[50]; /** Nom de la personne */
    int age;     /** Age de la personne */
}Person; /** Structure d'une Person*/


/**
 * \brief Fonction principale du programme, fait une addition .
 * \return EXIT_SUCCESS si le programme s'est execute avec succes.
 */
int main() {
    int testadd = 4; /**1 chiffre pour tester les addition*/
    int test1add = 5; /**1 deuxieme chiffre pour tester les addition*/
    int total=Addition(testadd,test1add);
    printf("%d",total);

    return EXIT_SUCCESS;
}

/**
 * \brief Fonction pour calculer p1 plus p2.
 * \param p1 Le premier entier.
 * \param p2 Le deuxieme entier.
 * \return p1 + p2.
 */
int Addition(int p1, int p2){
    int total = p1 + p2 ;
    if (total>MAX){
        printf("nombre superieur a 10");
    }else if (total<MIN){
        printf("nombre inferieur a 0");
    }
    return total ;
}

/**
 * \brief Fonction pour calculer p1 moins p2.
 * \param p1 Le premier entier.
 * \param p2 Le deuxieme entier.
 * \return p1 - p2.
 */
int soustraction(int p1, int p2) {
    return p1-p2;
}

