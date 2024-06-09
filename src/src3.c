/**
 * Ce programme simule un systeme de gestion de bibliotheque. Chaque livre est caracterise par un identifiant, 
 * un titre, un auteur et une annee de publication. Chaque membre de la bibliotheque est defini par un identifiant, 
 * un nom et la liste des livres qu'il a empruntes.
 * Les principales fonctionnalites du programme incluent l'affichage des details des livres et des membres, l'ajout 
 * de nouveaux livres et membres, le calcul de la somme des annees de publication des livres empruntes par un membre, 
 * et la recherche du livre le plus recent dans la bibliotheque. Le programme utilise des boucles pour iterer a travers 
 * les structures de donnees, assurant ainsi une gestion efficace de la bibliotheque. Les fonctions modulaires rendent le 
 * code extensible, permettant d'ajouter facilement de nouvelles fonctionnalites.
*/

#include <stdio.h>
#include <stdlib.h>  // Pour utiliser malloc et free
#include <string.h>

// Definition des Constantes
#define MAX_LIVRE 100 /** Nombre de livre MAX dans la bibliotheque*/
#define MAX_MEMBRE 100 /** Nombre de membre MAX dans la bibliotheque*/
#define TAILLE_MAX_TITRE 100 /** Longueur maximum d'un titre*/
#define TAILLE_MAX_AUTEUR 30 /** Longueur maximum du nom d'un auteur*/

int compteLivres(); /** Prototype fonction compteLivre*/
int compteMembres(); /** Prototype fonction compteMembre*/


struct livre { /** Structure d'un livre*/
    int IDLivre; /** ID du livre*/
    char titre[TAILLE_MAX_TITRE];/** Titre du livre*/
    char auteur[TAILLE_MAX_AUTEUR]; /** Auteur du livre*/
    int annee;/** Annee de parution du livre*/
};

// Structure pour representer un membre de la bibliotheque
struct membreBib { /** Structure d'un membre de la bibliotheque*/
    int IDMembre; /**ID du membre de la bibliotheque*/
    char nom[TAILLE_MAX_AUTEUR]; /** Nom du membre*/
    int livreEmprunte[MAX_LIVRE]; /** Nombre de livre emprunte*/
    int numLivreEmprunte; /** L'id du livre emprunte*/
};

/** Initialisation de quelques livres dans la bibliotheque*/
struct livre bibliotheque[MAX_LIVRE] = { 
    {1, "L'etranger", "Albert Camus", 1942},
    {2, "1984", "George Orwell", 1949},
    // ... Ajoutez d'autres livres ici
};

/** Initialisation de quelques membres de la bibliotheque*/
struct membreBib membres[MAX_MEMBRE] = {
    {101, "Alice", {1}, 1},  // Alice a emprunte le livre 1
    {102, "Bob", {2}, 1},    // Bob a emprunte le livre 2
};

/**
 * \brief Fonction pour afficher les details d'un livre
 * \detail La fonction afficheLivre prend en parametre une structure de type livre et affiche de 
 * maniere detaillee ses informations, offrant une presentation claire des details d'un livre dans 
 * un format lisible. Elle presente les elements suivants :
 * ID du livre : Affiche l'identifiant unique associe au livre.
 * Titre : Affiche le titre du livre, fournissant des informations sur son contenu.
 * Auteur : Affiche le nom de l'auteur du livre, identifiant la personne responsable de sa redaction.
 * Annee de publication : Affiche l'annee au cours de laquelle le livre a ete publie, donnant une indication temporelle de sa creation.
 * Ligne de separation : Ajoute une ligne de separation composee de caracteres specifiques, facilitant la distinction entre les details de differents livres.
 * 
 * \param struct livre b Structure du livre
 * */
void afficheLivre(struct livre b) {
    printf("ID du livre: %d\n", b.IDLivre);
    printf("Titre: %s\n", b.titre);
    printf("Auteur: %s\n", b.auteur);
    printf("Annee de publication: %d\n", b.annee);
    printf("\n");
}

/**
 * \brief Fonction pour afficher les details d'un membre de la bibliotheque
 * \detail La fonction afficheMembre prend en parametre une structure de type membreBib et affiche de maniere detaillee 
 * les informations liees a un membre de la bibliotheque. Elle offre une presentation claire des details d'un membre, 
 * notamment :
 * ID du membre : Affiche l'identifiant unique associe au membre.
 * Nom du membre : Affiche le nom du membre, permettant d'identifier de maniere unique l'utilisateur de la bibliotheque.
 * Livres empruntes : Affiche la liste des livres empruntes par le membre, en indiquant le nombre total de livres empruntes.
 * Ligne de separation : Ajoute une ligne de separation composee de caracteres specifiques, facilitant la distinction 
 * entre les details de differents membres.
 * 
 * \param struct membreBib m Structure des membre de la bibliotheque
 * \param struct livre l Structure des livres*/
void afficheMembre(struct membreBib m, struct livre l) {
    printf("ID du membre: %d\n", m.IDMembre);
    printf("Nom du membre: %s\n", m.nom);
    printf("Livres empruntes (%d) :\n", m.numLivreEmprunte);
    for (int i = 0; i < m.numLivreEmprunte; ++i) {
        printf("- Livre %d : %s de %s\n", m.livreEmprunte[i], l.titre, l.auteur);
    }
    printf("\n");
}

/** \brief Fonction pour calculer la somme des annees de publication des livres empruntes par un membre
 * \detail La fonction sommeAnneeLivreEmprunte prend en parametre une structure de type membreBib representant un membre 
 * de la bibliotheque. Elle calcule la somme des annees de publication des livres empruntes par ce membre.     
 * Si le membre n'a emprunte aucun livre, la fonction renvoie 0.
 * Les annees de publication des livres sont obtenues a partir de la bibliotheque globale.
 * 
 * \param struct membreBib m Structure des membre de la bibliotheque
 * \return sommeAnnee Retourne la somme des annee des livre emprunte
*/
int sommeAnneesLivresEmpruntes(struct membreBib m) {
    int sommeAnnees = 0;

    for (int i = 0; i < m.numLivreEmprunte; ++i) {
        int livreID = m.livreEmprunte[i];

        for (int j = 0; j < MAX_LIVRE; ++j) {
            if (bibliotheque[j].IDLivre == livreID) {
                sommeAnnees += bibliotheque[j].annee;
                break;
            }
        }
    }

    return sommeAnnees;
}

/**
 * \brief Fonction permettant de savoir le livre le plus recent
 * \detail La fonction livrePlusRecent recherche et retourne le livre le plus recent dans la bibliotheque. 
 * Elle parcourt l'ensemble des livres presents dans la bibliotheque et identifie celui ayant la date de publication 
 * la plus recente. Si la bibliotheque est vide, la fonction renvoie une structure de livre vide ou une valeur speciale
 * indiquant l'absence de livre.
 * 
 * \return plusRecent Retourne la structure du livre le plus recent
*/
struct livre livrePlusRecent() {
    struct livre plusRecent = bibliotheque[0];

    for (int i = 1; i < MAX_LIVRE; ++i) {
        if (bibliotheque[i].annee > plusRecent.annee) {
            plusRecent = bibliotheque[i];
        }
    }

    return plusRecent;
}

/**
 * \brief Fonction pour rajouter un livre dans la bibliotheque
 * \detail La fonction ajouteLivre permet d'ajouter un nouveau livre a la bibliotheque. Elle prend en parametre une structure 
 * de type livre representant les details du nouveau livre a ajouter l'id du livre, le nom, l'auteur et l'annee de parution, tels que l'ID du livre, le titre, l'auteur et l'annee de 
 * publication. La fonction verifie si la bibliotheque a encore de la place pour un nouveau livre. Si c'est le cas, le nouveau 
 * livre est ajoute a la bibliotheque ; sinon, un message indiquant que la bibliotheque est pleine est affiche.
 * 
 * \param struct livre *bibliotheque Structure comportant tout les livres
 * \param int id ID du livre a inserer dans la bibliotheque
 * \param char *nom Titre du livre a inserer dans la bibliotheque
 * \param char *auteur Auteur du livre a inserer dans la bibliotheque
 * \param int annee Annee de parution du livre a inserer dans la bibliotheque
 */
void ajouterLivre(struct livre *bibliotheque, int id, char *nom, char *auteur, int annee) {
    //Verifier si la bibliotheque est pleine
    if (compteLivres()>= MAX_LIVRE) {
        printf("La bibliotheque est pleine, impossible d'ajouter un nouveau livre.\n");
        return;
    }

    // Ajouter le livre
    bibliotheque[compteLivres()].IDLivre = id;
    strncpy(bibliotheque[compteLivres()].titre, nom, sizeof(bibliotheque[compteLivres()].titre) - 1);
    strncpy(bibliotheque[compteLivres()].auteur, auteur, sizeof(bibliotheque[compteLivres()].auteur) - 1);
    bibliotheque[compteLivres()].annee = annee;
    printf("Livre ajoute avec succes.\n");
}
/**
 * \brief Fonction pour rajouter un membre dans la bibliotheque
 * \detail La fonction ajouteMembre permet d'ajouter un nouveau membre a la bibliotheque. Elle prend en parametre une 
 * structure de type membreBib representant les details du nouveau membre a ajouter, tels que l'ID du membre, le nom, 
 * es livres empruntes et le nombre de livres empruntes. La fonction verifie si la bibliotheque a encore de la place pour 
 * un nouveau membre. Si c'est le cas, le nouveau membre est ajoute a la bibliotheque ; sinon, un message indiquant que la 
 * bibliotheque a atteint sa capacite maximale de membres est affiche.
 * 
 * \param struct membreBib nouveauMembre Structure pour ajouter le nouveau membre
 */
void ajouteMembre(struct membreBib nouveauMembre) {
    if (compteMembres() < MAX_MEMBRE) {
        membres[compteMembres()] = nouveauMembre;
        printf("Membre ajoute avec succes.\n");
    } else {
        printf("La bibliotheque a atteint sa capacite maximale de membres. Impossible d'ajouter un nouveau membre.\n");
    }
}

/**
 * \brief Fonction pour compter le nombre de livres dans la bibliotheque
 * \detail La fonction compteLivre permet de compter le nombre de livres presents dans la bibliotheque. Elle prend en 
 * parametre un tableau de structures de type livre representant la bibliotheque. La fonction utilise une boucle pour 
 * parcourir le tableau et compte le nombre de livres en incrementant un compteur a chaque iteration. Le resultat est 
 * renvoye en tant qu'entier, representant le nombre total de livres dans la bibliotheque.
 * 
 * \return nbLivre Nombre de livre contenu dans la bibliotheque
 */
int compteLivres() {
    int nbLivre = 0;
    for (int i = 0; i < MAX_LIVRE; ++i) {
        if(bibliotheque[i].IDLivre != 0) {
            nbLivre++;
        }
    }

    return nbLivre;
}

/**
 * \brief Fonction pour compter le nombre de membres dans la bibliotheque
 * \detail La fonction compteMembre permet de compter le nombre de membres inscrit dans la bibliotheque. Elle prend en 
 * parametre un tableau de structures de type membre representant la bibliotheque. La fonction utilise une boucle pour 
 * parcourir le tableau et compte le nombre de membre en incrementant un compteur a chaque iteration. Le resultat est 
 * renvoye en tant qu'entier, representant le nombre total de membre dans la bibliotheque.
 * 
 * \return compteur Retourne le nombre de membre inscrit dans la bibliotheque
 */
int compteMembres() {
    int compteur = 0;

    for (int i = 0; i < MAX_MEMBRE; ++i) {
        if (membres[i].IDMembre != 0) {
            compteur++;
        }
    }

    return compteur;
}

/**
 * \brief Fonction principale du programme pour gerer la bibliotheque
 * \detail La fonction main est la fonction principale du programme de gestion de bibliotheque. 
 * Elle initialise quelques livres et membres dans la bibliotheque, puis effectue des operations telles que 
 * l'affichage des details des livres et des membres, l'ajout d'un nouveau livre et d'un nouveau membre. 
 * Le but principal de la fonction main est de demontrer l'utilisation des differentes fonctions du programme.
 * 
 * \return EXIT_SUCCESS
*/
int main() {

    //Affichage des details des livres
    printf("| Details des livres |\n----------------------\n");
    for (int i = 0; i < compteLivres(bibliotheque); i++) {
        afficheLivre(bibliotheque[i]);
    }

    //Affichage des details des membres de la bibliotheque
    printf("\n| Details des membres de la bibliotheque |\n------------------------------------------\n");
    for (int i = 0; i < compteMembres(); i++) {
        afficheMembre(membres[i], bibliotheque[i]);
    }

    char reponse[4];
    printf("\nVoulez-vous ajouter des livre dans la bibliotheque (tapez oui ou non) : ");
    scanf("%s", reponse);
    while(strcmp(reponse, "oui") == 0){
        int id, annee;
        char titre[100], auteur[30];

        printf("Saisir ID du Livre : ");
        scanf("%d", &id);
        printf("Saisir le Titre du Livre (les espace remplacer par _): ");
        scanf("%s", titre);
        printf("Saisir l'auteur du Livre (les espace remplacer par _)non: ");
        scanf("%s", auteur);
        printf("Saisir l'annee de parution du Livre : ");
        scanf("%d", &annee);
        ajouterLivre(bibliotheque, id, titre, auteur, annee);
        for (int i = 0; i < compteLivres(bibliotheque); i++) {
            afficheLivre(bibliotheque[i]);
        }
        printf("\nVoulez-vous ajouter des livre dans la bibliotheque (tapez oui ou non) : ");
        scanf("%s", reponse);
    }
    for (int i = 0; i < compteLivres(bibliotheque); i++) {
            afficheLivre(bibliotheque[i]);
    }

    return 0;
}
