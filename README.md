# Cstash

**Cstash** est une bibliothèque de structures de données génériques en C, inspirée des conteneurs de la STL C++. Conçue pour être simple, robuste et efficace, elle offre des structures de données réutilisables avec une API claire et cohérente.

## 🎯 Objectifs

- **Vector** : Tableau dynamique (équivalent du `std::vector` en C++) ✅
- **LinkedList** : Liste chaînée (en développement)
- **HashMap** : Table de hachage (en développement)

## 📦 État actuel

**Version actuelle** : v0.1.0-alpha

**Fonctionnalités disponibles** :
- ✅ **CsVector** : Implémentation complète avec tests unitaires

## 🏗️ Structure du projet
```bash
├── Makefile
├── README.md
├── build
│   ├── compilation results
├── examples
│   └── example_*.c
├── include
│   └── cstash
│       ├── *.h
├── src
│   └── *.c
└── tests
    ├── run_all_tests.c
    ├── test_framework.h
    └── test_*.c
```

## 🚀 Compilation

### Prérequis

- **Clang** (ou GCC compatible)
- **Make**

### Commandes

```bash
# Compiler la bibliothèque
make

# Compiler et exécuter les tests
make test

# Compiler les exemples
make examples

# Nettoyer les artefacts de build
make clean

# Nettoyer complètement (y compris compile_commands.json)
make fclean

# Recompiler entièrement
make re
```

## 📚 API - CsVector

### Structure

```c
typedef struct {
    size_t capacity;        // Capacité allouée
    size_t size;            // Nombre d'éléments
    size_t element_size;    // Taille d'un élément en bytes
    void* data;             // Données
} CsVector;
```

### Fonctions

#### Création et destruction

```c
CsVector* vector_create(size_t element_size, size_t capacity);
void vector_destroy(CsVector* vector);
```

- `vector_create` : Crée un nouveau vector avec la taille d'élément et la capacité spécifiées
Si `capacity == 0`, utilise `VECTOR_DEFAULT_CAPACITY` (8)
Retourne `NULL` en cas d'échec d'allocation
- `vector_destroy` : Libère la mémoire du vector (safe avec `NULL`)

#### Manipulation des éléments

```c
CsResult vector_push(CsVector* vector, const void* element);
void* vector_pop(CsVector* vector);
void* vector_get(const CsVector* vector, size_t index);
```

- `vector_push` : Ajoute un élément à la fin (réallocation automatique si nécessaire)
- `vector_pop` : Retire et retourne le dernier élément (pointeur volatile)
- `vector_get` : Accède à l'élément à l'index donné (retourne `NULL` si hors limites)

#### Gestion de la capacité

```c
CsResult vector_reserve(CsVector* vector, size_t capacity);
void vector_clear(CsVector* vector);
CsResult vector_shrink_to_fit(CsVector* vector);
```

- `vector_reserve` : Réserve une capacité spécifique
⚠️ Si `capacity < size`, les données excédentaires sont perdues
- `vector_clear` : Vide le vector (conserve la capacité)
- `vector_shrink_to_fit` : Réduit la capacité pour correspondre à la taille

#### Clonage

```c
CsVector* vector_clone(const CsVector* vector);
```

- `vector_clone` : Crée une copie profonde du vector

### Codes de retour

```c
typedef enum {
    CS_SUCCESS = 0,              // Opération réussie
    CS_NULL_POINTER = 1,         // Pointeur NULL fourni
    CS_ALLOCATION_FAILED = 2,    // Échec d'allocation mémoire
} CsResult;
```

## 💡 Exemples d'utilisation

### Exemple basique

```c
#include "cstash/vector.h"
#include "cstash/result.h"
#include <stdio.h>

int main(void) {
    // Créer un vector d'entiers avec capacité initiale de 10
    CsVector* vec = vector_create(sizeof(int), 10);
    
    // Ajouter des éléments
    for (int i = 0; i < 10; i++) {
        if (vector_push(vec, &i) != CS_SUCCESS) {
            fprintf(stderr, "Erreur lors du push\n");
            return 1;
        }
    }
    
    // Lire les éléments
    for (int i = 0; i < 10; i++) {
        int* value = (int*)vector_get(vec, i);
        printf("%d ", *value);
    }
    printf("\n");
    
    // Nettoyer
    vector_destroy(vec);
    return 0;
}
```

### Avec des structures personnalisées

```c
typedef struct {
    int id;
    char name[32];
    double value;
} Record;

int main(void) {
    CsVector* records = vector_create(sizeof(Record), 0);
    
    Record r1 = {1, "Alice", 3.14};
    Record r2 = {2, "Bob", 2.71};
    
    vector_push(records, &r1);
    vector_push(records, &r2);
    
    // Accéder aux données
    Record* first = (Record*)vector_get(records, 0);
    printf("ID: %d, Name: %s\n", first->id, first->name);
    
    vector_destroy(records);
    return 0;
}
```

## 🧪 Tests

Le projet inclut une suite de tests complète avec un framework maison :

```bash
make test
```

### Couverture des tests

- ✅ Création et destruction
- ✅ Push, pop et get (avec réallocation)
- ✅ Reserve, clear et shrink_to_fit
- ✅ Clonage et indépendance
- ✅ Types complexes (structures)
- ✅ Tests de stress (1000+ éléments)
- ✅ Gestion des cas limites (NULL, out of bounds, etc.)

## 🎨 Philosophie de conception

- **Sécurité** : Gestion robuste des pointeurs `NULL` et des cas limites
- **Généricité** : Fonctionne avec n'importe quel type via `void*` et `element_size`
- **Performance** : Croissance exponentielle de la capacité (×2) pour minimiser les réallocations
- **Prévisibilité** : Codes de retour explicites (`CsResult`), pas d'erreurs silencieuses
- **Testabilité** : Suite de tests complète avec framework intégré

## 🔜 Roadmap

+ [x] *CsLinkedList* : Liste doublement chaînée
+ [ ] *CsHashMap* : Table de hachage avec résolution de collisions
+ [ ] *Documentation* étendue avec plus d'exemples
+ [ ] *Benchmarks* de performance

## 👤 Auteur
Fait avec ❤️ par Pierre Teodoresco
