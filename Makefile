# Compilateur et flags
CC := clang
CFLAGS := -Wall -Wextra -Werror -std=c99 -pedantic -O2
CFLAGS_DEBUG := -Wall -Wextra -Werror -std=c99 -pedantic -g -O0 -fsanitize=address,undefined
INCLUDES := -Iinclude

# Répertoires
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
TEST_DIR := tests
EXAMPLE_DIR := examples
BENCHMARK_DIR := benchmarks

# Fichiers
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
LIBRARY := $(BUILD_DIR)/libcstash.a

# Tests
TEST_SOURCES := $(wildcard $(TEST_DIR)/test_*.c)
TEST_EXECS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/$(TEST_DIR)/%,$(TEST_SOURCES))

# Exemples
EXAMPLE_SOURCES := $(wildcard $(EXAMPLE_DIR)/*.c)
EXAMPLE_EXECS := $(patsubst $(EXAMPLE_DIR)/%.c,$(BUILD_DIR)/$(EXAMPLE_DIR)/%,$(EXAMPLE_SOURCES))

# Benchmarks
BENCHMARK_SOURCES := $(wildcard $(BENCHMARK_DIR)/*.c)
BENCHMARK_EXECS := $(patsubst $(BENCHMARK_DIR)/%.c,$(BUILD_DIR)/$(BENCHMARK_DIR)/%,$(BENCHMARK_SOURCES))

# Couleurs pour l'affichage
GREEN := \033[0;32m
BLUE := \033[0;34m
YELLOW := \033[0;33m
RED := \033[0;31m
NC := \033[0m # No Color

# Règle par défaut
.PHONY: all
all: $(LIBRARY)
	@echo "$(GREEN)✓ Build completed successfully$(NC)"

# Création du répertoire build
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compilation des fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "$(BLUE)Compiling$(NC) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Création de la bibliothèque statique
$(LIBRARY): $(OBJECTS)
	@echo "$(YELLOW)Creating library$(NC) $@"
	@ar rcs $@ $^
	@echo "$(GREEN)✓ Library created$(NC)"

# Compilation des tests
$(BUILD_DIR)/tests/%: $(TEST_DIR)/%.c $(LIBRARY)
	@mkdir -p $(BUILD_DIR)/tests
	@echo "$(BLUE)Compiling test$(NC) $<"
	@$(CC) $(CFLAGS_DEBUG) $(INCLUDES) $< -L$(BUILD_DIR) -lcstash -o $@

# Compilation des exemples
$(BUILD_DIR)/examples/%: $(EXAMPLE_DIR)/%.c $(LIBRARY)
	@mkdir -p $(BUILD_DIR)/examples
	@echo "$(BLUE)Compiling example$(NC) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) $< -L$(BUILD_DIR) -lcstash -o $@

# Compilation des benchmarks
$(BUILD_DIR)/benchmarks/%: $(BENCHMARK_DIR)/%.c $(LIBRARY) | $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/benchmarks
	@echo "$(BLUE)Compiling benchmark$(NC) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) $< -L$(BUILD_DIR) -lcstash -o $@

# Compilation des tests
.PHONY: test
test: $(TEST_EXECS)
	@echo "$(GREEN)✓ Tests compiled$(NC)"

# Exécution des tests
.PHONY: test-run
test-run: test
	@echo "$(YELLOW)Running tests...$(NC)"
	@for test in $(TEST_EXECS); do \
		echo "$(BLUE)Running$$NC $$test"; \
		./$$test; \
		echo ""; \
	done

# Bibliothèque avec sanitizers
.PHONY: library-sanitize
library-sanitize: clean
	@echo "$(BLUE)Compiling library with sanitizers$(NC)"
	@mkdir -p $(BUILD_DIR)
	@for src in $(SOURCES); do \
		obj=$(BUILD_DIR)/$$(basename $$src .c).o; \
		$(CC) $(CFLAGS_DEBUG) $(INCLUDES) -c $$src -o $$obj; \
	done
	@ar rcs $(LIBRARY) $(OBJECTS)
	@echo "$(GREEN)✓ Library with sanitizers created$(NC)"

# Tests avec sanitizers
.PHONY: test-sanitize
test-sanitize: library-sanitize $(TEST_EXECS)
	@echo "$(YELLOW)Running tests with AddressSanitizer...$(NC)"
	@for test in $(TEST_EXECS); do \
		echo "$(BLUE)Running sanitized test:$(NC) $$test"; \
		MallocNanoZone=0 \
		ASAN_OPTIONS=detect_leaks=1:print_suppressions=0 \
		LSAN_OPTIONS=suppressions=lsan_suppressions.txt:print_suppressions=0 \
		./$$test; \
	done
	@echo "$(GREEN)✓ No memory leaks detected$(NC)"

# Compilation des exemples
.PHONY: examples
examples: $(EXAMPLE_EXECS)
	@echo "$(GREEN)✓ Examples compiled$(NC)"

# Compilation des benchmarks
.PHONY: bench
bench: $(BENCHMARK_EXECS)
	@echo "$(GREEN)✓ Benchmarks compiled$(NC)"

# Nettoyage
.PHONY: clean
clean:
	@echo "$(YELLOW)Cleaning build artifacts$(NC)"
	@rm -rf $(BUILD_DIR)
	@echo "$(GREEN)✓ Clean completed$(NC)"

# Affichage de l'aide
.PHONY: help
help:
	@echo "$(BLUE)Cstash Makefile$(NC)"
	@echo ""
	@echo "Targets:"
	@echo "  $(GREEN)all$(NC)              - Build the library (default)"
	@echo "  $(GREEN)test$(NC)             - Build tests"
	@echo "  $(GREEN)test-run$(NC)         - Run all tests"
	@echo "  $(GREEN)test-sanitize         - Build library with AddressSanitizer and run test"
	@echo "  $(GREEN)examples$(NC)         - Build example programs"
	@echo "  $(GREEN)bench$(NC)            - Build benchmarks"
	@echo "  $(GREEN)clean$(NC)            - Remove build artifacts"
	@echo "  $(GREEN)help$(NC)             - Show this help message"

# Dépendances automatiques
-include $(OBJECTS:.o=.d)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "$(BLUE)Compiling$(NC) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
