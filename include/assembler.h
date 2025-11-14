/**
 * assembler.h
 * API del ensamblador de dos pasadas
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>

// ============================================================================
// CONSTANTES DEL ENSAMBLADOR
// ============================================================================

#define MAX_LINES       8192    // Máximo número de líneas en un archivo .asm
#define MAX_LABELS      1024    // Máximo número de etiquetas
#define MAX_LINE_LENGTH 256     // Longitud máxima de una línea

// ============================================================================
// ESTRUCTURAS
// ============================================================================

// Tabla de símbolos (etiquetas)
typedef struct {
    char name[64];
    int address;
} Label;

// Estado del ensamblador
typedef struct {
    Label labels[MAX_LABELS];
    int label_count;
    
    char *source_lines[MAX_LINES];
    int line_count;
    
    uint16_t program[MAX_LINES];
    int program_length;
    
    char *input_filename;
    char *output_filename;
} Assembler;

// ============================================================================
// API DEL ENSAMBLADOR
// ============================================================================

/**
 * Inicializa el ensamblador
 */
void assembler_init(Assembler *asm_state);

/**
 * Libera recursos del ensamblador
 */
void assembler_free(Assembler *asm_state);

/**
 * Ensambla un archivo .asm a .mem
 * @param input_file Archivo fuente .asm
 * @param output_file Archivo de salida .mem
 * @return 0 en éxito, -1 en error
 */
int assemble_file(const char *input_file, const char *output_file);

/**
 * Busca una etiqueta en la tabla de símbolos
 * @return Dirección de la etiqueta, o -1 si no existe
 */
int find_label(Assembler *asm_state, const char *label_name);

/**
 * Añade una etiqueta a la tabla de símbolos
 */
void add_label(Assembler *asm_state, const char *label_name, int address);

/**
 * Parsea un número (decimal o hexadecimal con 0x)
 */
int parse_number(const char *str);

/**
 * Parsea un nombre de registro (R0-R15) y devuelve su número
 * @return Número de registro (0-15), o -1 si inválido
 */
int parse_register(const char *str);

/**
 * Obtiene el opcode para un mnemónico
 * @return Opcode (0x0-0xF), o -1 si no existe
 */
int get_opcode(const char *mnemonic);

#endif // ASSEMBLER_H
