#include "cstash/result.h"
#include "cstash/stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Créer une stack
    CsStack* stack = cs_stack_create(sizeof(int));

    printf("=== Push ===\n");
    // Ajouter des éléments
    for (int i = 0; i < 10; i++) {
        if (cs_stack_push(stack, &i) != CS_SUCCESS) {
            fprintf(stderr, "Erreur lors du push\n");
            return 1;
        }
    }

    printf("Taille: %zu\n", stack->size);
    printf("\n=== Pop ===\n");
    // Résultats attendu: 9 8 7 6 5 4 3 2 1 0
    while (!cs_stack_is_empty(stack)) {
        int* value = (int*)cs_stack_pop(stack);
        printf("%d ", *value);
    }
    printf("\n");

    // Nettoyer
    cs_stack_destroy(stack);
    return 0;
}
