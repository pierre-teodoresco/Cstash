#include "cstash/result.h"
#include "cstash/vector.h"
#include <stdio.h>

int main(void) {
    // Créer un vector d'entiers avec capacité initiale de 10
    CsVector* vec = cs_vector_create(sizeof(int), 10);

    // Ajouter des éléments
    for (int i = 0; i < 10; i++) {
        if (cs_vector_push(vec, &i) != CS_SUCCESS) {
            fprintf(stderr, "Erreur lors du push\n");
            return 1;
        }
    }

    // Lire les éléments
    for (int i = 0; i < 10; i++) {
        int* value = (int*)cs_vector_get(vec, i);
        printf("%d ", *value);
    }
    printf("\n");

    // Nettoyer
    cs_vector_destroy(vec);
    return 0;
}
