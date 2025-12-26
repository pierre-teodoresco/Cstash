# Compilateur et flags
CC := clang
CFLAGS := -Wall -Wextra -Werror -std=c11 -pedantic -O2
CFLAGS_DEBUG := -Wall -Wextra -Werror -std=c11 -pedantic -g -O0 -fsanitize=address,undefined
INCLUDES := -Iinclude

# Répertoires
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
TEST_DIR := tests
EXAMPLE_DIR := examples

# Fichiers
SOURCES := $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
LIBRARY := $(BUILD_DIR)/libcstash.a

# Tests
TEST_SOURCES := $(wildcard $(TEST_DIR)/test_*.c)
TEST_RUNNER := $(TEST_DIR)/run_all_tests.c
TEST_EXEC := $(BUILD_DIR)/run_tests

# Exemples
EXAMPLE_SOURCES := $(wildcard $(EXAMPLE_DIR)/*.c)
EXAMPLE_EXECS := $(patsubst $(EXAMPLE_DIR)/%.c,$(BUILD_DIR)/examples/%,$(EXAMPLE_SOURCES))

# Couleurs pour l'affichage
GREEN := \033[0;32m
BLUE := \033[0;34m
YELLOW := \033[0;33m
RED := \033[0;31m
NC := \033[0m # No Color

# Règle par défaut
.PHONY: all
all: $(LIBRARY) compile_commands.json
	@echo "$(GREEN)✓ Build completed successfully$(NC)"

# Création du répertoire build
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/examples

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
$(TEST_EXEC): $(LIBRARY) $(TEST_SOURCES) $(TEST_RUNNER)
	@echo "$(BLUE)Compiling tests$(NC)"
	@$(CC) $(CFLAGS_DEBUG) $(INCLUDES) $(TEST_RUNNER) $(TEST_SOURCES) -L$(BUILD_DIR) -lcstash -o $@
	@echo "$(GREEN)✓ Tests compiled$(NC)"

# Compilation des exemples
$(BUILD_DIR)/examples/%: $(EXAMPLE_DIR)/%.c $(LIBRARY) | $(BUILD_DIR)
	@echo "$(BLUE)Compiling example$(NC) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) $< -L$(BUILD_DIR) -lcstash -o $@

# Exécution des tests
.PHONY: test
test: $(TEST_EXEC)
	@echo "$(YELLOW)Running tests...$(NC)"
	@./$(TEST_EXEC)

# Compilation et exécution des tests avec un seul make test
.PHONY: check
check: test

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
test-sanitize: library-sanitize
	@echo "$(BLUE)Compiling tests with sanitizers$(NC)"
	@$(CC) $(CFLAGS_DEBUG) $(INCLUDES) $(TEST_RUNNER) $(TEST_SOURCES) -L$(BUILD_DIR) -lcstash -o $(TEST_EXEC)
	@echo "$(YELLOW)Running tests with AddressSanitizer...$(NC)"
	@MallocNanoZone=0 \
		ASAN_OPTIONS=detect_leaks=1:print_suppressions=0 \
		LSAN_OPTIONS=suppressions=lsan_suppressions.txt:print_suppressions=0 \
		./$(TEST_EXEC)
	@echo "$(GREEN)✓ No memory leaks detected$(NC)"

# Compilation des exemples
.PHONY: examples
examples: $(EXAMPLE_EXECS)
	@echo "$(GREEN)✓ Examples compiled$(NC)"

# Génération de compile_commands.json pour les IDE
compile_commands.json: $(SOURCES)
	@echo "$(BLUE)Generating compile_commands.json$(NC)"
	@echo "[" > compile_commands.json
	@first=1; \
	for src in $(SOURCES); do \
		if [ $$first -eq 0 ]; then echo "," >> compile_commands.json; fi; \
		echo "  {" >> compile_commands.json; \
		echo "    \"directory\": \"$$(pwd)\"," >> compile_commands.json; \
		echo "    \"command\": \"$(CC) $(CFLAGS) $(INCLUDES) -c $$src\"," >> compile_commands.json; \
		echo "    \"file\": \"$$src\"" >> compile_commands.json; \
		echo -n "  }" >> compile_commands.json; \
		first=0; \
	done; \
	echo "" >> compile_commands.json; \
	echo "]" >> compile_commands.json
	@echo "$(GREEN)✓ compile_commands.json generated$(NC)"

# Nettoyage
.PHONY: clean
clean:
	@echo "$(YELLOW)Cleaning build artifacts$(NC)"
	@rm -rf $(BUILD_DIR)
	@echo "$(GREEN)✓ Clean completed$(NC)"

.PHONY: fclean
fclean: clean
	@rm -f compile_commands.json

# Re-compilation complète
.PHONY: re
re: fclean all

# Affichage de l'aide
.PHONY: help
help:
	@echo "$(BLUE)Cstash Makefile$(NC)"
	@echo ""
	@echo "Targets:"
	@echo "  $(GREEN)all$(NC)              - Build the library (default)"
	@echo "  $(GREEN)test$(NC)             - Build and run tests"
	@echo "  $(GREEN)test-sanitize         - Build library with AddressSanitizer and run test"
	@echo "  $(GREEN)examples$(NC)         - Build example programs"
	@echo "  $(GREEN)clean$(NC)            - Remove build artifacts"
	@echo "  $(GREEN)fclean$(NC)           - Remove all generated files"
	@echo "  $(GREEN)re$(NC)               - Clean and rebuild"
	@echo "  $(GREEN)help$(NC)             - Show this help message"

# Dépendances automatiques
-include $(OBJECTS:.o=.d)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "$(BLUE)Compiling$(NC) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
