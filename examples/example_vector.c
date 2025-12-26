#include "cstash/result.h"
#include "cstash/vector.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Créer un vector d'entiers avec capacité initiale de 4
    CsVector* vec = cs_vector_create(sizeof(int), 4);

    printf("=== Push ===\n");
    // Ajouter des éléments (déclenchera une réallocation)
    for (int i = 0; i < 10; i++) {
        if (cs_vector_push(vec, &i) != CS_SUCCESS) {
            fprintf(stderr, "Erreur lors du push\n");
            return 1;
        }
    }

    printf("Taille: %zu, Capacité: %zu\n", vec->size, vec->capacity);
    printf("Éléments: ");
    for (size_t i = 0; i < vec->size; i++) {
        int* value = (int*)cs_vector_get(vec, i);
        printf("%d ", *value);
    }
    printf("\n");

    printf("\n=== Pop ===\n");
    int* popped = (int*)cs_vector_pop(vec);
    printf("Élément retiré: %d\n", *popped);
    printf("Nouvelle taille: %zu\n", vec->size);

    printf("\n=== Reserve ===\n");
    printf("Capacité avant reserve: %zu\n", vec->capacity);
    cs_vector_reserve(vec, 50);
    printf("Capacité après reserve(50): %zu\n", vec->capacity);

    printf("\n=== Shrink to Fit ===\n");
    cs_vector_shrink_to_fit(vec);
    printf("Capacité après shrink_to_fit: %zu (taille: %zu)\n", vec->capacity, vec->size);

    printf("\n=== Clone ===\n");
    CsVector* clone = cs_vector_clone(vec);
    printf("Clone créé avec %zu éléments\n", clone->size);

    // Modifier le clone
    int new_value = 999;
    cs_vector_push(clone, &new_value);
    printf("Clone après push(999): ");
    for (size_t i = 0; i < clone->size; i++) {
        int* value = (int*)cs_vector_get(clone, i);
        printf("%d ", *value);
    }
    printf("\n");

    printf("Original (inchangé): ");
    for (size_t i = 0; i < vec->size; i++) {
        int* value = (int*)cs_vector_get(vec, i);
        printf("%d ", *value);
    }
    printf("\n");

    printf("\n=== Clear ===\n");
    cs_vector_clear(vec);
    printf("Taille après clear: %zu\n", vec->size);
    printf("Capacité préservée: %zu\n", vec->capacity);
    printf("Est vide: %s\n", vec->size == 0 ? "oui" : "non");

    // Réutiliser après clear
    int val = 42;
    cs_vector_push(vec, &val);
    printf("Après nouveau push: taille = %zu, valeur = %d\n", vec->size, *(int*)cs_vector_get(vec, 0));

    // Nettoyer
    cs_vector_destroy(vec);
    cs_vector_destroy(clone);
    return 0;
}
