# Cstash

**Cstash** est une bibliothèque de structures de données génériques en C. Conçue pour être simple, robuste et efficace, elle offre des structures de données réutilisables avec une API claire et cohérente.

## 🎯 Objectifs

- **Vector** : Tableau dynamique ✅
- **LinkedList** : Liste chaînée ✅
- **HashMap** : Table de hachage ✅

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

- **Clang**
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

## 🧪 Tests

Le projet inclut une suite de tests complète avec un framework maison :

```bash
make test
```
## 🔜 Roadmap

+ [ ] *Documentation* étendue avec plus d'exemples
+ [ ] *Benchmarks* de performance

## 👤 Auteur
Fait avec ❤️ par Pierre Teodoresco
