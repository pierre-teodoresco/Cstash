# Cstash

**Cstash** est une bibliothèque de structures de données génériques en C. Conçue pour être simple, robuste et efficace, elle offre des structures de données réutilisables avec une API claire et cohérente.

## 🎯 Objectifs

- **Vector** : Tableau dynamique  ✅
- **LinkedList** : Liste chaînée  ✅
- **HashMap** : Table de hachage  ✅
- **Stack** : Pile                ✅

## 🏗️ Structure du projet
```bash
├── Makefile
├── README.md
├── build
│   └── compilation results
├── benchmarks
│  └── bench_*.c
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

# Compiler les tests (à retrouver sous build/tests)
make test

# Exécuter tous les tests
make testr-run

# Compiler et exécuter les tests avec une validation mémoire
make test-sanitize

# Compiler les exemples (à retouver dans build/examples)
make examples

# Compiler les benchmarks (à retrouver dans build/benchmarks)
make bench

# Nettoyer les artefacts de build
make clean
```

## 🔜 Roadmap

+ [ ] *Documentation* des différentes API

## 👤 Auteur
Fait avec ❤️ par Pierre Teodoresco
