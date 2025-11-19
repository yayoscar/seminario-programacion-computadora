# Makefile para el proyecto de CPU Simulator + Assembler
# Seminario de Programación de Computadora

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -g
INCLUDES = -Iinclude

# Directorios
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
ASM_DIR = asm
TEST_DIR = tests

# Archivos fuente
CPU_SRC = $(SRC_DIR)/cpu_simulator.c
ASM_SRC = $(SRC_DIR)/assembler.c
MAIN_SRC = $(SRC_DIR)/main.c
C_TO_ASM_SRC = $(SRC_DIR)/c_to_asm.c

# Ejecutables
MAIN_BIN = $(BIN_DIR)/main
ASM_BIN = $(BIN_DIR)/assembler
C_TO_ASM_BIN = $(BIN_DIR)/c_to_asm

# Archivos de prueba
TEST_ASM_FILES = $(wildcard $(TEST_DIR)/*.asm)
TEST_MEM_FILES = $(TEST_ASM_FILES:.asm=.mem)

# Color codes para output bonito
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m # No Color

# Regla por defecto
.PHONY: all
all: directories $(MAIN_BIN) $(ASM_BIN) $(C_TO_ASM_BIN)
	@echo "$(GREEN)✓ Build complete!$(NC)"
	@echo "  - Main executable: $(MAIN_BIN)"
	@echo "  - Assembler: $(ASM_BIN)"
	@echo "  - C to ASM Compiler: $(C_TO_ASM_BIN)"

# Crear directorios necesarios
.PHONY: directories
directories:
	@mkdir -p $(BIN_DIR)

# Compilar el programa principal (integrado)
$(MAIN_BIN): $(MAIN_SRC) $(CPU_SRC) $(ASM_SRC)
	@echo "$(YELLOW)Compiling main program...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
	@echo "$(GREEN)✓ Main program compiled$(NC)"

# Compilar el ensamblador standalone
$(ASM_BIN): $(ASM_SRC)
	@echo "$(YELLOW)Compiling assembler...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -DASSEMBLER_STANDALONE -o $@ $^
	@echo "$(GREEN)✓ Assembler compiled$(NC)"

# Compilar el compilador C -> ASM
$(C_TO_ASM_BIN): $(C_TO_ASM_SRC)
	@echo "$(YELLOW)Compiling C to ASM compiler...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
	@echo "$(GREEN)✓ C to ASM compiler compiled$(NC)"

# Limpiar archivos generados
.PHONY: clean
clean:
	@echo "$(YELLOW)Cleaning...$(NC)"
	rm -f $(BIN_DIR)/* $(ASM_DIR)/*.mem $(TEST_DIR)/*.mem
	@echo "$(GREEN)✓ Clean complete$(NC)"

# Limpiar todo (incluyendo directorios)
.PHONY: distclean
distclean: clean
	rm -rf $(BIN_DIR)

# Ejecutar pruebas
.PHONY: test
test: all test-simple test-memory test-logical test-programa

# Ejecutar pruebas de C
.PHONY: test-c
test-c: all test-c-simple test-c-if test-c-while test-c-for test-c-function

# Prueba C simple
.PHONY: test-c-simple
test-c-simple: $(C_TO_ASM_BIN) $(MAIN_BIN)
	@echo "\n$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)  Test C: Simple Sum (a+b)$(NC)"
	@echo "$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)Compiling C to ASM...$(NC)"
	$(C_TO_ASM_BIN) $(TEST_DIR)/test_c_simple.c $(TEST_DIR)/test_c_simple.asm
	@echo "$(YELLOW)Assembling and executing...$(NC)"
	$(MAIN_BIN) -e $(TEST_DIR)/test_c_simple.asm

# Prueba C con if
.PHONY: test-c-if
test-c-if: $(C_TO_ASM_BIN) $(MAIN_BIN)
	@echo "\n$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)  Test C: Conditional (if)$(NC)"
	@echo "$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)Compiling C to ASM...$(NC)"
	$(C_TO_ASM_BIN) $(TEST_DIR)/test_c_if.c $(TEST_DIR)/test_c_if.asm
	@echo "$(YELLOW)Assembling and executing...$(NC)"
	$(MAIN_BIN) -e $(TEST_DIR)/test_c_if.asm

# Prueba C con while
.PHONY: test-c-while
test-c-while: $(C_TO_ASM_BIN) $(MAIN_BIN)
	@echo "\n$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)  Test C: While Loop$(NC)"
	@echo "$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)Compiling C to ASM...$(NC)"
	$(C_TO_ASM_BIN) $(TEST_DIR)/test_c_while.c $(TEST_DIR)/test_c_while.asm
	@echo "$(YELLOW)Assembling and executing...$(NC)"
	$(MAIN_BIN) -e $(TEST_DIR)/test_c_while.asm

# Prueba C con for
.PHONY: test-c-for
test-c-for: $(C_TO_ASM_BIN) $(MAIN_BIN)
	@echo "\n$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)  Test C: For Loop$(NC)"
	@echo "$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)Compiling C to ASM...$(NC)"
	$(C_TO_ASM_BIN) $(TEST_DIR)/test_c_for.c $(TEST_DIR)/test_c_for.asm
	@echo "$(YELLOW)Assembling and executing...$(NC)"
	$(MAIN_BIN) -e $(TEST_DIR)/test_c_for.asm

# Prueba C con funciones
.PHONY: test-c-function
test-c-function: $(C_TO_ASM_BIN) $(MAIN_BIN)
	@echo "\n$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)  Test C: Functions$(NC)"
	@echo "$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)Compiling C to ASM...$(NC)"
	$(C_TO_ASM_BIN) $(TEST_DIR)/test_c_function.c $(TEST_DIR)/test_c_function.asm
	@echo "$(YELLOW)Assembling and executing...$(NC)"
	$(MAIN_BIN) -e $(TEST_DIR)/test_c_function.asm

# Prueba simple
.PHONY: test-simple
test-simple: $(MAIN_BIN)
	@echo "\n$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)  Running test: Simple Addition$(NC)"
	@echo "$(YELLOW)========================================$(NC)"
	$(MAIN_BIN) -e $(TEST_DIR)/test_simple.asm

# Prueba de memoria
.PHONY: test-memory
test-memory: $(MAIN_BIN)
	@echo "\n$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)  Running test: Memory Operations$(NC)"
	@echo "$(YELLOW)========================================$(NC)"
	$(MAIN_BIN) -e $(TEST_DIR)/test_memory.asm

# Prueba lógica
.PHONY: test-logical
test-logical: $(MAIN_BIN)
	@echo "\n$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)  Running test: Logical Operations$(NC)"
	@echo "$(YELLOW)========================================$(NC)"
	$(MAIN_BIN) -e $(TEST_DIR)/test_logical.asm

# Prueba del programa principal
.PHONY: test-programa
test-programa: $(MAIN_BIN)
	@echo "\n$(YELLOW)========================================$(NC)"
	@echo "$(YELLOW)  Running test: Sum 1 to 10$(NC)"
	@echo "$(YELLOW)========================================$(NC)"
	$(MAIN_BIN) -e $(ASM_DIR)/programa.asm

# Ejecutar el programa principal
.PHONY: run
run: $(MAIN_BIN)
	$(MAIN_BIN) $(ASM_DIR)/programa.asm

# Ensamblar todos los archivos de prueba
.PHONY: assemble-tests
assemble-tests: $(ASM_BIN) $(TEST_MEM_FILES)

%.mem: %.asm $(ASM_BIN)
	$(ASM_BIN) $< $@

# Ayuda
.PHONY: help
help:
	@echo "Makefile para CPU Simulator + Assembler"
	@echo ""
	@echo "Targets disponibles:"
	@echo "  make              - Compilar todo"
	@echo "  make clean        - Limpiar archivos generados"
	@echo "  make test         - Ejecutar todas las pruebas"
	@echo "  make test-simple  - Ejecutar prueba simple"
	@echo "  make test-memory  - Ejecutar prueba de memoria"
	@echo "  make test-logical - Ejecutar prueba lógica"
	@echo "  make test-programa- Ejecutar programa principal"
	@echo "  make test-c       - Ejecutar TODAS las pruebas de C"
	@echo "  make test-c-simple- Ejecutar prueba C simple"
	@echo "  make test-c-if    - Ejecutar prueba C condicional"
	@echo "  make test-c-while - Ejecutar prueba C while loop"
	@echo "  make run          - Ejecutar programa principal"
	@echo "  make help         - Mostrar esta ayuda"
	@echo ""
	@echo "Uso directo:"
	@echo "  $(MAIN_BIN) -a <input.asm> <output.mem>  # Ensamblar"
	@echo "  $(MAIN_BIN) -r <input.mem>               # Ejecutar"
	@echo "  $(MAIN_BIN) -e <input.asm>               # Ensamblar y ejecutar"

# Información del proyecto
.PHONY: info
info:
	@echo "$(GREEN)CPU Simulator & Assembler Project$(NC)"
	@echo "├── Source files:"
	@echo "│   ├── $(CPU_SRC)"
	@echo "│   ├── $(ASM_SRC)"
	@echo "│   └── $(MAIN_SRC)"
	@echo "├── Headers:"
	@echo "│   ├── $(INC_DIR)/isa.h"
	@echo "│   ├── $(INC_DIR)/cpu.h"
	@echo "│   └── $(INC_DIR)/assembler.h"
	@echo "├── Binaries:"
	@echo "│   ├── $(MAIN_BIN)"
	@echo "│   └── $(ASM_BIN)"
	@echo "└── Tests:"
	@echo "    └── $(TEST_DIR)/*.asm"
