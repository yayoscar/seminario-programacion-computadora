/**
 * isa.h
 * Definición de la ISA (Arquitectura del Conjunto de Instrucciones)
 * Proyecto de Seminario - Programación de Computadora
 * 
 * FORMATO DE INSTRUCCIÓN: 16 bits
 * [4 bits CODIGO_OP][4 bits Rd][8 bits OPERANDO/Rs]
 * 
 * - CODIGO_OP: Código de operación (0x0 - 0xF)
 * - Rd: Registro destino (R0-R15)
 * - OPERANDO: Operando inmediato de 8 bits O registro fuente (Rs) en bits bajos
 * 
 * LENGUAJE: Español (México)
 * MNEMÓNICOS: En español para facilitar el aprendizaje
 */

#ifndef ISA_H
#define ISA_H

#include <stdint.h>

// ============================================================================
// DEFINICIÓN DE CÓDIGOS DE OPERACIÓN
// ============================================================================

// Operaciones básicas
#define OP_NADA     0x0  // NADA              -> Sin operación
#define OP_MOVI     0x1  // MOVI Rd, inm      -> Rd = inmediato (cargar inmediato)
#define OP_MOVER    0x2  // MOVER Rd, Rs      -> Rd = Rs (copiar registro)

// Operaciones aritméticas (ALU)
#define OP_SUMAR    0x3  // SUMAR Rd, Rs      -> Rd = Rd + Rs
#define OP_RESTAR   0x4  // RESTAR Rd, Rs     -> Rd = Rd - Rs

// Operaciones lógicas (ALU)
#define OP_Y        0x5  // Y Rd, Rs          -> Rd = Rd & Rs (AND lógico)
#define OP_O        0x6  // O Rd, Rs          -> Rd = Rd | Rs (OR lógico)
#define OP_NO       0x7  // NO Rd             -> Rd = ~Rd (NOT lógico)

// Operaciones de memoria
#define OP_CARGAR   0x8  // CARGAR Rd, [dir]  -> Rd = MEM[dir]
#define OP_GUARDAR  0x9  // GUARDAR Rd, [dir] -> MEM[dir] = Rd

// Saltos e instrucciones de control
#define OP_SALTAR   0xA  // SALTAR dir        -> PC = dir (salto incondicional)
#define OP_SZ       0xB  // SZ Rd, dir        -> si (Rd == 0) PC = dir (saltar si cero)
#define OP_SNZ      0xC  // SNZ Rd, dir       -> si (Rd != 0) PC = dir (saltar si no cero)

// Entrada/Salida
#define OP_ESCRIBIR 0xD  // ESCRIBIR Rd       -> mostrar valor de Rd
#define OP_LEER     0xE  // LEER Rd           -> Rd = valor de entrada

// Control del sistema
#define OP_ALTO     0xF  // ALTO              -> detener ejecución

// ============================================================================
// INSTRUCCIONES FUTURAS (Semana 3-4)
// Reservadas para soportar funciones y recursión
// ============================================================================
/*
#define OP_LLAMAR   0x10  // LLAMAR dir        -> EMPUJAR(PC+1); PC = dir
#define OP_RETORNAR 0x11  // RETORNAR          -> PC = SACAR()
#define OP_EMPUJAR  0x12  // EMPUJAR Rd        -> MEM[SP--] = Rd (PUSH)
#define OP_SACAR    0x13  // SACAR Rd          -> Rd = MEM[++SP] (POP)
#define OP_COMPARAR 0x14  // COMPARAR Rd, Rs   -> establecer banderas según Rd - Rs
#define OP_SMENOR   0x15  // SMENOR dir        -> saltar si menor que
#define OP_SMAYOR   0x16  // SMAYOR dir        -> saltar si mayor que
#define OP_SMENIG   0x17  // SMENIG dir        -> saltar si menor o igual
#define OP_SMAYIG   0x18  // SMAYIG dir        -> saltar si mayor o igual
#define OP_MULTI    0x19  // MULTI Rd, Rs      -> Rd = Rd * Rs (multiplicación)
#define OP_DIVIDIR  0x1A  // DIVIDIR Rd, Rs    -> Rd = Rd / Rs (división)
*/

// ============================================================================
// REGISTROS ESPECIALES
// ============================================================================

#define REG_SP      14   // R14: Puntero de Pila (Stack Pointer - para semanas 3-4)
#define REG_BAND    15   // R15: Registro de banderas (para comparaciones futuras)

// ============================================================================
// MACROS DE CODIFICACIÓN/DECODIFICACIÓN
// ============================================================================

// Codificar una instrucción de 16 bits
#define CODIFICAR_INSTR(codigo_op, rd, operando) \
    ((uint16_t)(((codigo_op) & 0xF) << 12) | (((rd) & 0xF) << 8) | ((operando) & 0xFF))

// Decodificar campos de una instrucción
#define DECODIF_CODIGO_OP(instr)   (((instr) >> 12) & 0xF)
#define DECODIF_RD(instr)          (((instr) >> 8) & 0xF)
#define DECODIF_OPERANDO(instr)    ((instr) & 0xFF)
#define DECODIF_RS(instr)          ((instr) & 0xF)  // Rs está en los 4 bits bajos del operando

// Compatibilidad con nombres anteriores (para transición)
#define ENCODE_INSTR    CODIFICAR_INSTR
#define DECODE_OPCODE   DECODIF_CODIGO_OP
#define DECODE_RD       DECODIF_RD
#define DECODE_OPERAND  DECODIF_OPERANDO
#define DECODE_RS       DECODIF_RS

// ============================================================================
// CONSTANTES DEL SISTEMA
// ============================================================================

#define MEMORY_SIZE     256    // Tamaño de memoria en palabras de 16 bits
#define TAM_MEMORIA     256    // Alias en español
#define NUM_REGISTERS   16     // Número de registros generales (R0-R15)
#define NUM_REGISTROS   16     // Alias en español
#define STACK_BASE      250    // Dirección base de la pila (crece hacia abajo, con margen)
#define BASE_PILA       250    // Alias en español

// ============================================================================
// MNEMÓNICOS (para referencia del ensamblador)
// ============================================================================

typedef struct {
    const char *mnemonico;
    uint8_t codigo_op;
    int num_operandos;  // Número de operandos esperados
} InfoInstruccion;

// Tabla de instrucciones en ESPAÑOL (usada por el ensamblador)
static const InfoInstruccion TABLA_ISA[] = {
    {"NADA",     OP_NADA,     0},
    {"MOVI",     OP_MOVI,     2},  // MOVI Rd, inm
    {"MOVER",    OP_MOVER,    2},  // MOVER Rd, Rs
    {"SUMAR",    OP_SUMAR,    2},  // SUMAR Rd, Rs
    {"RESTAR",   OP_RESTAR,   2},  // RESTAR Rd, Rs
    {"Y",        OP_Y,        2},  // Y Rd, Rs (AND)
    {"O",        OP_O,        2},  // O Rd, Rs (OR)
    {"NO",       OP_NO,       1},  // NO Rd (NOT)
    {"CARGAR",   OP_CARGAR,   2},  // CARGAR Rd, [dir]
    {"GUARDAR",  OP_GUARDAR,  2},  // GUARDAR Rd, [dir]
    {"SALTAR",   OP_SALTAR,   1},  // SALTAR dir
    {"SZ",       OP_SZ,       2},  // SZ Rd, dir (Saltar si Zero)
    {"SNZ",      OP_SNZ,      2},  // SNZ Rd, dir (Saltar si No Zero)
    {"ESCRIBIR", OP_ESCRIBIR, 1},  // ESCRIBIR Rd (salida)
    {"LEER",     OP_LEER,     1},  // LEER Rd (entrada)
    {"ALTO",     OP_ALTO,     0},  // ALTO (halt/detener)
    {NULL, 0, 0}  // Terminador
};

// Tabla de instrucciones en INGLÉS (compatibilidad/transición)
static const InfoInstruccion TABLA_ISA_EN[] = {
    {"NOP",   OP_NADA,     0},
    {"MOVI",  OP_MOVI,     2},
    {"MOV",   OP_MOVER,    2},
    {"ADD",   OP_SUMAR,    2},
    {"SUB",   OP_RESTAR,   2},
    {"AND",   OP_Y,        2},
    {"OR",    OP_O,        2},
    {"NOT",   OP_NO,       1},
    {"LOAD",  OP_CARGAR,   2},
    {"STORE", OP_GUARDAR,  2},
    {"JMP",   OP_SALTAR,   1},
    {"JZ",    OP_SZ,       2},
    {"JNZ",   OP_SNZ,      2},
    {"OUT",   OP_ESCRIBIR, 1},
    {"IN",    OP_LEER,     1},
    {"HALT",  OP_ALTO,     0},
    {NULL, 0, 0}
};

// Alias para compatibilidad
#define InstructionInfo InfoInstruccion
#define ISA_TABLE TABLA_ISA

#endif // ISA_H
