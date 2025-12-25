#include "cstash/linkedlist.h"
#include "cstash/result.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Créer une linked list d'entiers
    CsLinkedList* list = cs_linkedlist_create(sizeof(int));

    printf("=== Push Back ===\n");
    // Ajouter des éléments à la fin
    for (int i = 0; i < 5; i++) {
        if (cs_linkedlist_push_back(list, &i) != CS_SUCCESS) {
            fprintf(stderr, "Erreur lors du push_back\n");
            return 1;
        }
    }

    // Afficher les éléments
    printf("Liste: ");
    for (size_t i = 0; i < cs_linkedlist_size(list); i++) {
        int* value = (int*)cs_linkedlist_get(list, i);
        printf("%d ", *value);
    }
    printf("\n");

    printf("\n=== Push Front ===\n");
    // Ajouter des éléments au début
    int values[] = {-1, -2, -3};
    for (int i = 0; i < 3; i++) {
        cs_linkedlist_push_front(list, &values[i]);
    }

    // Afficher la liste complète
    printf("Liste: ");
    for (size_t i = 0; i < cs_linkedlist_size(list); i++) {
        int* value = (int*)cs_linkedlist_get(list, i);
        printf("%d ", *value);
    }
    printf("\n");

    printf("\n=== Front et Back ===\n");
    int* front = (int*)cs_linkedlist_front(list);
    int* back = (int*)cs_linkedlist_back(list);
    printf("Premier élément: %d\n", *front);
    printf("Dernier élément: %d\n", *back);
    printf("Taille: %zu\n", cs_linkedlist_size(list));

    printf("\n=== Pop Front ===\n");
    int* popped = (int*)cs_linkedlist_pop_front(list);
    printf("Élément retiré du début: %d\n", *popped);
    free(popped);

    printf("\n=== Pop Back ===\n");
    popped = (int*)cs_linkedlist_pop_back(list);
    printf("Élément retiré de la fin: %d\n", *popped);
    free(popped);

    // Afficher la liste finale
    printf("\nListe finale: ");
    for (size_t i = 0; i < cs_linkedlist_size(list); i++) {
        int* value = (int*)cs_linkedlist_get(list, i);
        printf("%d ", *value);
    }
    printf("\n");

    // Nettoyer
    cs_linkedlist_destroy(list);
    return 0;
}
