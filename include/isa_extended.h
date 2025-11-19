#ifndef ISA_EXTENDED_H
#define ISA_EXTENDED_H

#include "isa.h"

/* ============================================
   ISA EXTENDIDA - Instrucciones para Semana 3
   Mantiene compatibilidad con ISA base (16 bits)
   ============================================ */

// Constantes adicionales
#define REG_TMP 15  // R15 como registro temporal
#define MAX_PSEUDO_EXPANSION 5  // Máximo de instrucciones en una expansión (LLAMAR necesita 5)

/* Pseudo-instrucciones que el ensamblador expande a múltiples instrucciones reales
 * Estas no son códigos de operación reales, sino macros que el ensamblador traduce
 */

typedef enum {
    PSEUDO_PUSH = 0x100,  /* EMPUJAR Rs  → expande a 3 instrucciones */
    PSEUDO_POP  = 0x101,  /* SACAR Rd    → expande a 2 instrucciones */
    PSEUDO_CALL = 0x102,  /* LLAMAR addr → expande a múltiples instrucciones */
    PSEUDO_RET  = 0x103,  /* RETORNAR    → expande a múltiples instrucciones */
} PseudoOp;

/* Mnemónicos para pseudo-instrucciones */
#define MNEM_EMPUJAR  "EMPUJAR"
#define MNEM_SACAR    "SACAR"
#define MNEM_LLAMAR   "LLAMAR"
#define MNEM_RETORNAR "RETORNAR"

#define MNEM_PUSH     "PUSH"
#define MNEM_POP      "POP"
#define MNEM_CALL     "CALL"
#define MNEM_RET      "RET"

/* Información adicional de pseudo-instrucciones */
typedef struct {
    PseudoOp pseudo_op;
    const char *mnemonic_es;
    const char *mnemonic_en;
    const char *description;
    int expansion_size;  /* Número de instrucciones reales generadas */
} PseudoInstructionInfo;

static const PseudoInstructionInfo pseudo_table[] = {
    {PSEUDO_PUSH, MNEM_EMPUJAR,  MNEM_PUSH, "Empujar registro a pila",     3},
    {PSEUDO_POP,  MNEM_SACAR,    MNEM_POP,  "Sacar de pila a registro",    3},
    {PSEUDO_CALL, MNEM_LLAMAR,   MNEM_CALL, "Llamar a subrutina",          5},
    {PSEUDO_RET,  MNEM_RETORNAR, MNEM_RET,  "Retornar de subrutina",       4},
};

/* Funciones auxiliares para expansión de pseudo-instrucciones */

/* EMPUJAR Rs → 
 *   GUARDAR Rs, [R14]   ; Guardar en posición actual de SP
 *   MOVI R15, 1         ; Cargar 1 en temporal
 *   RESTAR R14, R15     ; SP = SP - 1 (decrementar)
 */
static inline int expand_push(uint16_t *output, uint8_t rs) {
    output[0] = ENCODE_INSTR(OP_GUARDAR, rs, REG_SP);     // GUARDAR Rs, [R14]
    output[1] = ENCODE_INSTR(OP_MOVI, REG_TMP, 1);        // MOVI R15, 1
    output[2] = ENCODE_INSTR(OP_RESTAR, REG_SP, REG_TMP); // RESTAR R14, R15
    return 3;
}

/* SACAR Rd →
 *   MOVI R15, 1         ; Cargar 1 en temporal
 *   SUMAR R14, R15      ; SP = SP + 1 (incrementar)
 *   CARGAR Rd, [R14]    ; Cargar desde nueva posición de SP
 */
static inline int expand_pop(uint16_t *output, uint8_t rd) {
    output[0] = ENCODE_INSTR(OP_MOVI, REG_TMP, 1);       // MOVI R15, 1
    output[1] = ENCODE_INSTR(OP_SUMAR, REG_SP, REG_TMP); // SUMAR R14, R15
    output[2] = ENCODE_INSTR(OP_CARGAR, rd, REG_SP);     // CARGAR Rd, [R14]
    return 3;
}

/* LLAMAR addr →
 *   MOVI R13, ret_addr_low    ; Parte baja de dirección de retorno
 *   GUARDAR R13, [R14]        ; Guardar en pila
 *   MOVI R15, 1
 *   RESTAR R14, R15           ; Decrementar SP
 *   SALTAR addr               ; Saltar a la función
 */
static inline int expand_call(uint16_t *output, uint16_t current_addr, uint8_t target_addr) {
    uint16_t ret_addr = current_addr + 5;  // Dirección después de la expansión de CALL
    
    output[0] = ENCODE_INSTR(OP_MOVI, 13, ret_addr & 0xFF);  // MOVI R13, ret_addr
    output[1] = ENCODE_INSTR(OP_GUARDAR, 13, REG_SP);        // GUARDAR R13, [R14]
    output[2] = ENCODE_INSTR(OP_MOVI, REG_TMP, 1);           // MOVI R15, 1
    output[3] = ENCODE_INSTR(OP_RESTAR, REG_SP, REG_TMP);    // RESTAR R14, R15
    output[4] = ENCODE_INSTR(OP_SALTAR, 0, target_addr);     // SALTAR addr
    return 5;
}

/* RETORNAR →
 *   MOVI R15, 1
 *   SUMAR R14, R15      ; Incrementar SP
 *   CARGAR R13, [R14]   ; Cargar dirección de retorno
 *   SALTAR R13          ; Saltar (usando R13 para indicar salto indirecto)
 */
static inline int expand_ret(uint16_t *output) {
    output[0] = ENCODE_INSTR(OP_MOVI, REG_TMP, 1);        // MOVI R15, 1
    output[1] = ENCODE_INSTR(OP_SUMAR, REG_SP, REG_TMP);  // SUMAR R14, R15
    output[2] = ENCODE_INSTR(OP_CARGAR, 13, REG_SP);      // CARGAR R13, [R14]
    output[3] = ENCODE_INSTR(OP_SALTAR, 13, 0);           // SALTAR indirecto vía R13
    return 4;
}

#endif /* ISA_EXTENDED_H */
