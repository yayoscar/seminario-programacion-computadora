/**
 * assembler.c
 * Ensamblador de dos pasadas para la ISA de 16 bits
 * 
 * PASADA 1: Construir tabla de símbolos (etiquetas)
 * PASADA 2: Generar código máquina
 * 
 * Formato de salida: archivo .mem con una palabra hexadecimal de 16 bits por línea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../include/assembler.h"
#include "../include/isa.h"

// ============================================================================
// FUNCIONES AUXILIARES
// ============================================================================

/**
 * Elimina espacios en blanco al inicio y final de una cadena
 */
static char *trim(char *str) {
    // Eliminar espacios al inicio
    while (isspace((unsigned char)*str)) {
        str++;
    }
    
    if (*str == 0) {
        return str;
    }
    
    // Eliminar espacios al final
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = 0;
    
    return str;
}

/**
 * Convierte una cadena a mayúsculas
 */
static void to_upper(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

int parse_number(const char *str) {
    if (!str) return 0;
    
    // Hexadecimal: 0x...
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        return (int)strtol(str, NULL, 16);
    }
    
    // Decimal
    return (int)strtol(str, NULL, 10);
}

int parse_register(const char *str) {
    if (!str) return -1;
    
    // Formato: R0, R1, ..., R15 (o r0, r1, etc.)
    if ((str[0] == 'r' || str[0] == 'R') && isdigit((unsigned char)str[1])) {
        int reg_num = atoi(str + 1);
        if (reg_num >= 0 && reg_num <= 15) {
            return reg_num;
        }
    }
    
    return -1;
}

int get_opcode(const char *mnemonic) {
    // Buscar primero en la tabla en ESPAÑOL
    for (int i = 0; TABLA_ISA[i].mnemonico != NULL; i++) {
        if (strcmp(mnemonic, TABLA_ISA[i].mnemonico) == 0) {
            return TABLA_ISA[i].codigo_op;
        }
    }
    
    // Si no se encuentra, buscar en la tabla en INGLÉS (compatibilidad)
    for (int i = 0; TABLA_ISA_EN[i].mnemonico != NULL; i++) {
        if (strcmp(mnemonic, TABLA_ISA_EN[i].mnemonico) == 0) {
            return TABLA_ISA_EN[i].codigo_op;
        }
    }
    
    return -1;
}

int find_label(Assembler *asm_state, const char *label_name) {
    for (int i = 0; i < asm_state->label_count; i++) {
        if (strcmp(asm_state->labels[i].name, label_name) == 0) {
            return asm_state->labels[i].address;
        }
    }
    return -1;
}

void add_label(Assembler *asm_state, const char *label_name, int address) {
    if (asm_state->label_count >= MAX_LABELS) {
        fprintf(stderr, "[ERROR ENSAMBLADOR] Demasiadas etiquetas (máx: %d)\n", MAX_LABELS);
        exit(1);
    }
    
    // Verificar si la etiqueta ya existe
    if (find_label(asm_state, label_name) >= 0) {
        fprintf(stderr, "[ERROR ENSAMBLADOR] Etiqueta duplicada: %s\n", label_name);
        exit(1);
    }
    
    strncpy(asm_state->labels[asm_state->label_count].name, label_name, 63);
    asm_state->labels[asm_state->label_count].name[63] = '\0';
    asm_state->labels[asm_state->label_count].address = address;
    asm_state->label_count++;
    
    printf("[ENSAMBLADOR] Etiqueta '%s' -> Dirección 0x%04X\n", label_name, address);
}

/**
 * Separa una línea de argumentos separados por comas
 * Retorna el número de argumentos encontrados
 */
static int split_arguments(char *str, char **args, int max_args) {
    int count = 0;
    char *p = str;
    
    while (*p && count < max_args) {
        // Saltar espacios
        while (*p && isspace((unsigned char)*p)) {
            p++;
        }
        
        if (!*p) break;
        
        // Marcar inicio del argumento
        char *start = p;
        
        // Buscar fin del argumento (coma o fin de cadena)
        while (*p && *p != ',') {
            p++;
        }
        
        // Terminar argumento
        if (*p == ',') {
            *p = '\0';
            p++;
        }
        
        args[count++] = trim(start);
    }
    
    return count;
}

// ============================================================================
// INICIALIZACIÓN Y LIMPIEZA
// ============================================================================

void assembler_init(Assembler *asm_state) {
    memset(asm_state, 0, sizeof(Assembler));
    asm_state->label_count = 0;
    asm_state->line_count = 0;
    asm_state->program_length = 0;
}

void assembler_free(Assembler *asm_state) {
    // Liberar líneas de código fuente
    for (int i = 0; i < asm_state->line_count; i++) {
        if (asm_state->source_lines[i]) {
            free(asm_state->source_lines[i]);
        }
    }
}

// ============================================================================
// PASADA 1: CONSTRUCCIÓN DE TABLA DE SÍMBOLOS
// ============================================================================

static void first_pass(Assembler *asm_state) {
    int address = 0;
    
    printf("\n[ENSAMBLADOR] === PRIMERA PASADA: Construyendo tabla de símbolos ===\n");
    
    for (int i = 0; i < asm_state->line_count; i++) {
        char line[MAX_LINE_LENGTH];
        strncpy(line, asm_state->source_lines[i], MAX_LINE_LENGTH - 1);
        line[MAX_LINE_LENGTH - 1] = '\0';
        
        // Eliminar comentarios
        char *comment = strchr(line, ';');
        if (comment) {
            *comment = '\0';
        }
        
        char *trimmed = trim(line);
        
        // Línea vacía
        if (trimmed[0] == '\0') {
            continue;
        }
        
        // Directivas (comenzando con '.')
        if (trimmed[0] == '.') {
            // Directivas futuras: .data, .text, .org, etc.
            continue;
        }
        
        // Etiqueta (termina con ':')
        if (strchr(trimmed, ':')) {
            char label_name[64];
            sscanf(trimmed, "%63[^:]", label_name);
            char *label = trim(label_name);
            
            add_label(asm_state, label, address);
            
            // Verificar si hay una instrucción en la misma línea
            char *after_colon = strchr(trimmed, ':') + 1;
            trimmed = trim(after_colon);
            
            if (trimmed[0] == '\0') {
                continue;  // Solo etiqueta, sin instrucción
            }
        }
        
        // Es una instrucción, incrementar dirección
        address++;
    }
    
    printf("[ENSAMBLADOR] Primera pasada completa. %d etiquetas encontradas.\n", asm_state->label_count);
}

// ============================================================================
// PASADA 2: GENERACIÓN DE CÓDIGO
// ============================================================================

static void second_pass(Assembler *asm_state) {
    int address = 0;
    
    printf("\n[ENSAMBLADOR] === SEGUNDA PASADA: Generando código máquina ===\n");
    
    for (int i = 0; i < asm_state->line_count; i++) {
        char line[MAX_LINE_LENGTH];
        strncpy(line, asm_state->source_lines[i], MAX_LINE_LENGTH - 1);
        line[MAX_LINE_LENGTH - 1] = '\0';
        
        // Eliminar comentarios
        char *comment = strchr(line, ';');
        if (comment) {
            *comment = '\0';
        }
        
        char *trimmed = trim(line);
        
        // Línea vacía
        if (trimmed[0] == '\0') {
            continue;
        }
        
        // Directivas
        if (trimmed[0] == '.') {
            continue;
        }
        
        // Saltar etiqueta si existe
        if (strchr(trimmed, ':')) {
            char *after_colon = strchr(trimmed, ':') + 1;
            trimmed = trim(after_colon);
            
            if (trimmed[0] == '\0') {
                continue;
            }
        }
        
        // Parsear instrucción
        char mnemonic[64];
        char arguments[MAX_LINE_LENGTH];
        arguments[0] = '\0';
        
        int fields = sscanf(trimmed, "%63s %[^\n]", mnemonic, arguments);
        
        if (fields < 1) {
            continue;
        }
        
        to_upper(mnemonic);
        
        // Obtener código de operación
        int opcode = get_opcode(mnemonic);
        if (opcode < 0) {
            fprintf(stderr, "[ERROR ENSAMBLADOR] Instrucción desconocida '%s' en línea %d\n", 
                    mnemonic, i + 1);
            exit(1);
        }
        
        // Decodificar argumentos
        uint8_t rd = 0;
        uint8_t operand = 0;
        
        if (fields > 1) {
            char *args[8];
            int arg_count = split_arguments(arguments, args, 8);
            
            // Procesar según el tipo de instrucción
            if (opcode == OP_NADA || opcode == OP_ALTO) {
                // Sin argumentos
                rd = 0;
                operand = 0;
                
            } else if (opcode == OP_MOVI) {
                // MOVI Rd, imm
                if (arg_count < 2) {
                    fprintf(stderr, "[ERROR ENSAMBLADOR] MOVI requiere 2 argumentos en línea %d\n", i + 1);
                    exit(1);
                }
                rd = parse_register(args[0]);
                operand = parse_number(args[1]) & 0xFF;
                
            } else if (opcode == OP_MOVER || opcode == OP_SUMAR || opcode == OP_RESTAR || 
                       opcode == OP_Y || opcode == OP_O) {
                // Rd, Rs
                if (arg_count < 2) {
                    fprintf(stderr, "[ERROR ENSAMBLADOR] %s requiere 2 registros en línea %d\n", 
                            mnemonic, i + 1);
                    exit(1);
                }
                rd = parse_register(args[0]);
                int rs = parse_register(args[1]);
                if (rs < 0) {
                    fprintf(stderr, "[ERROR ENSAMBLADOR] Registro fuente inválido in %s en línea %d\n", 
                            mnemonic, i + 1);
                    exit(1);
                }
                operand = rs & 0xFF;
                
            } else if (opcode == OP_NO || opcode == OP_ESCRIBIR || opcode == OP_LEER) {
                // Solo Rd
                if (arg_count < 1) {
                    fprintf(stderr, "[ERROR ENSAMBLADOR] %s requiere 1 registro en línea %d\n", 
                            mnemonic, i + 1);
                    exit(1);
                }
                rd = parse_register(args[0]);
                operand = 0;
                
            } else if (opcode == OP_CARGAR || opcode == OP_GUARDAR) {
                // Rd, [addr] o Rd, addr
                if (arg_count < 2) {
                    fprintf(stderr, "[ERROR ENSAMBLADOR] %s requiere 2 argumentos en línea %d\n", 
                            mnemonic, i + 1);
                    exit(1);
                }
                rd = parse_register(args[0]);
                
                // Eliminar corchetes si existen
                char *addr_str = args[1];
                if (addr_str[0] == '[') {
                    addr_str++;
                    char *end = strchr(addr_str, ']');
                    if (end) *end = '\0';
                }
                
                operand = parse_number(addr_str) & 0xFF;
                
            } else if (opcode == OP_SALTAR) {
                // JMP addr o JMP label
                if (arg_count < 1) {
                    fprintf(stderr, "[ERROR ENSAMBLADOR] JMP requiere 1 argumento en línea %d\n", i + 1);
                    exit(1);
                }
                
                // Intentar como número primero
                if (isdigit((unsigned char)args[0][0]) || args[0][0] == '0') {
                    operand = parse_number(args[0]) & 0xFF;
                } else {
                    // Es una etiqueta
                    int label_addr = find_label(asm_state, args[0]);
                    if (label_addr < 0) {
                        fprintf(stderr, "[ERROR ENSAMBLADOR] Etiqueta no definida '%s' en línea %d\n", 
                                args[0], i + 1);
                        exit(1);
                    }
                    operand = label_addr & 0xFF;
                }
                rd = 0;
                
            } else if (opcode == OP_SZ || opcode == OP_SNZ) {
                // JZ/JNZ Rd, addr o Rd, label
                if (arg_count < 2) {
                    fprintf(stderr, "[ERROR ENSAMBLADOR] %s requiere 2 argumentos en línea %d\n", 
                            mnemonic, i + 1);
                    exit(1);
                }
                rd = parse_register(args[0]);
                
                // Intentar como número primero
                if (isdigit((unsigned char)args[1][0]) || args[1][0] == '0') {
                    operand = parse_number(args[1]) & 0xFF;
                } else {
                    // Es una etiqueta
                    int label_addr = find_label(asm_state, args[1]);
                    if (label_addr < 0) {
                        fprintf(stderr, "[ERROR ENSAMBLADOR] Etiqueta no definida '%s' en línea %d\n", 
                                args[1], i + 1);
                        exit(1);
                    }
                    operand = label_addr & 0xFF;
                }
            }
        }
        
        // Validar registro destino
        if (rd < 0 || rd >= NUM_REGISTERS) {
            fprintf(stderr, "[ERROR ENSAMBLADOR] Registro destino inválido en línea %d\n", i + 1);
            exit(1);
        }
        
        // Codificar instrucción
        uint16_t instruction = ENCODE_INSTR(opcode, rd, operand);
        asm_state->program[address++] = instruction;
        
        printf("[ENSAMBLADOR] 0x%04X: %s -> 0x%04X\n", address - 1, mnemonic, instruction);
    }
    
    asm_state->program_length = address;
    printf("[ENSAMBLADOR] Segunda pasada completa. %d instrucciones generadas.\n", address);
}

// ============================================================================
// FUNCIÓN PRINCIPAL DE ENSAMBLADO
// ============================================================================

int assemble_file(const char *input_file, const char *output_file) {
    Assembler asm_state;
    assembler_init(&asm_state);
    
    asm_state.input_filename = (char *)input_file;
    asm_state.output_filename = (char *)output_file;
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║               ENSAMBLADOR v1.0 - ESPAÑOL MX                ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║ Entrada:  %-48s ║\n", input_file);
    printf("║ Salida:   %-48s ║\n", output_file);
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    // Leer archivo fuente
    FILE *f = fopen(input_file, "r");
    if (!f) {
        fprintf(stderr, "[ERROR ENSAMBLADOR] No se puede abrir el archivo: %s\n", input_file);
        return -1;
    }
    
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), f)) {
        if (asm_state.line_count >= MAX_LINES) {
            fprintf(stderr, "[ERROR ENSAMBLADOR] Demasiadas líneas (máx: %d)\n", MAX_LINES);
            fclose(f);
            return -1;
        }
        
        char *line = malloc(strlen(buffer) + 1);
        if (!line) {
            fprintf(stderr, "[ERROR ENSAMBLADOR] Error de asignación de memoria\n");
            fclose(f);
            return -1;
        }
        strcpy(line, buffer);
        asm_state.source_lines[asm_state.line_count++] = line;
    }
    fclose(f);
    
    printf("[ENSAMBLADOR] Leídas %d líneas del archivo fuente\n", asm_state.line_count);
    
    // Primera pasada: construir tabla de símbolos
    first_pass(&asm_state);
    
    // Segunda pasada: generar código
    second_pass(&asm_state);
    
    // Escribir archivo de salida
    FILE *out = fopen(output_file, "w");
    if (!out) {
        fprintf(stderr, "[ERROR ENSAMBLADOR] No se puede crear el archivo de salida: %s\n", output_file);
        assembler_free(&asm_state);
        return -1;
    }
    
    for (int i = 0; i < asm_state.program_length; i++) {
        fprintf(out, "%04X\n", asm_state.program[i]);
    }
    fclose(out);
    
    printf("\n[ENSAMBLADOR] ¡ÉXITO! Generadas %d instrucciones -> %s\n\n", 
           asm_state.program_length, output_file);
    
    assembler_free(&asm_state);
    return 0;
}

// ============================================================================
// MAIN (para uso standalone del ensamblador)
// Solo se compila si ASSEMBLER_STANDALONE está definido
// ============================================================================

#ifdef ASSEMBLER_STANDALONE
int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <entrada.asm> <salida.mem>\n", argv[0]);
        fprintf(stderr, "Ejemplo: %s programa.asm programa.mem\n", argv[0]);
        return 1;
    }
    
    int result = assemble_file(argv[1], argv[2]);
    return (result == 0) ? 0 : 1;
}
#endif
