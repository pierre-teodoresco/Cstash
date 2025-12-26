#include "cstash/hashmap.h"
#include "cstash/result.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // Créer une HashMap pour stocker des entiers
    CsHashMap* map = cs_hashmap_create(sizeof(int));
    if (!map) {
        fprintf(stderr, "Erreur lors de la création de la HashMap\n");
        return 1;
    }

    printf("=== Insert ===\n");
    // Insérer des éléments
    int age_alice = 25;
    int age_bob = 30;
    int age_charlie = 35;
    int age_diana = 28;

    if (cs_hashmap_insert(map, "Alice", &age_alice) != CS_SUCCESS) {
        fprintf(stderr, "Erreur lors de l'insertion\n");
        return 1;
    }
    cs_hashmap_insert(map, "Bob", &age_bob);
    cs_hashmap_insert(map, "Charlie", &age_charlie);
    cs_hashmap_insert(map, "Diana", &age_diana);

    printf("Taille: %zu, Capacité: %zu\n", map->size, map->capacity);

    printf("\n=== Get ===\n");
    // Récupérer des valeurs
    int* alice_age = (int*)cs_hashmap_get(map, "Alice");
    int* bob_age = (int*)cs_hashmap_get(map, "Bob");

    if (alice_age) {
        printf("Alice a %d ans\n", *alice_age);
    }
    if (bob_age) {
        printf("Bob a %d ans\n", *bob_age);
    }

    printf("\n=== Has ===\n");
    // Vérifier l'existence de clés
    printf("Charlie existe: %s\n", cs_hashmap_has(map, "Charlie") ? "oui" : "non");
    printf("Eve existe: %s\n", cs_hashmap_has(map, "Eve") ? "oui" : "non");

    printf("\n=== Insert Duplicate ===\n");
    // Tenter d'insérer une clé existante
    int new_age = 26;
    CsResult result = cs_hashmap_insert(map, "Alice", &new_age);
    if (result == CS_CONFLICT) {
        printf("Impossible d'insérer: la clé 'Alice' existe déjà\n");
        printf("Âge d'Alice (inchangé): %d\n", *(int*)cs_hashmap_get(map, "Alice"));
    }

    printf("\n=== Remove ===\n");
    // Supprimer un élément
    result = cs_hashmap_remove(map, "Bob");
    if (result == CS_SUCCESS) {
        printf("Bob a été supprimé\n");
        printf("Nouvelle taille: %zu\n", map->size);
    }

    // Vérifier que Bob n'existe plus
    printf("Bob existe: %s\n", cs_hashmap_has(map, "Bob") ? "oui" : "non");

    printf("\n=== Resize ===\n");
    // Redimensionner manuellement
    printf("Capacité avant resize: %zu\n", map->capacity);
    cs_hashmap_resize(map, 32);
    printf("Capacité après resize(32): %zu\n", map->capacity);
    printf("Taille (inchangée): %zu\n", map->size);

    // Vérifier que les données sont toujours accessibles
    int* charlie_age = (int*)cs_hashmap_get(map, "Charlie");
    if (charlie_age) {
        printf("Charlie a toujours %d ans après resize\n", *charlie_age);
    }

    printf("\n=== Utilisation avec Structures ===\n");
    // Créer une HashMap pour des structures
    typedef struct {
        int id;
        double salary;
        char department[32];
    } Employee;

    CsHashMap* employees = cs_hashmap_create(sizeof(Employee));

    Employee emp1 = {101, 50000.0, "Engineering"};
    Employee emp2 = {102, 55000.0, "Marketing"};
    Employee emp3 = {103, 60000.0, "Sales"};

    cs_hashmap_insert(employees, "EMP001", &emp1);
    cs_hashmap_insert(employees, "EMP002", &emp2);
    cs_hashmap_insert(employees, "EMP003", &emp3);

    Employee* retrieved = (Employee*)cs_hashmap_get(employees, "EMP002");
    if (retrieved) {
        printf("Employé EMP002:\n");
        printf("  ID: %d\n", retrieved->id);
        printf("  Salaire: %.2f\n", retrieved->salary);
        printf("  Département: %s\n", retrieved->department);
    }

    printf("\n=== Clear ===\n");
    // Vider la HashMap originale
    cs_hashmap_clear(map);
    printf("Taille après clear: %zu\n", map->size);
    printf("Capacité préservée: %zu\n", map->capacity);
    printf("Est vide: %s\n", map->size == 0 ? "oui" : "non");

    // Réutiliser après clear
    int new_value = 42;
    cs_hashmap_insert(map, "NewKey", &new_value);
    printf("Après nouvelle insertion: taille = %zu\n", map->size);
    printf("Valeur de NewKey: %d\n", *(int*)cs_hashmap_get(map, "NewKey"));

    printf("\n=== Itération sur les buckets ===\n");
    // Afficher tous les employés
    printf("Liste des employés:\n");
    for (size_t i = 0; i < employees->capacity; i++) {
        CsHashMapEntry* entry = employees->buckets[i];
        while (entry) {
            Employee* emp = (Employee*)entry->data;
            printf("  %s: %s (ID: %d)\n", entry->key, emp->department, emp->id);
            entry = entry->next;
        }
    }

    // Nettoyer
    cs_hashmap_destroy(map);
    cs_hashmap_destroy(employees);

    printf("\nHashMaps détruites avec succès\n");
    return 0;
}
