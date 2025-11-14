/**
 * cpu_simulator.c
 * Simulador de CPU con arquitectura de registros generales
 * 
 * Características:
 * - 16 registros de propósito general (R0-R15)
 * - Memoria de 256 palabras de 16 bits (Von Neumann)
 * - Instrucciones de 16 bits: [4 bits opcode][4 bits Rd][8 bits operand]
 * - Ciclo fetch-decode-execute
 * 
 * Diseñado para soportar:
 * - Semana 2: Operaciones básicas, saltos, I/O
 * - Semana 3-4: Llamadas a funciones, recursión, stack
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "../include/cpu.h"
#include "../include/isa.h"

// ============================================================================
// IMPLEMENTACIÓN DE LA API DE LA CPU
// ============================================================================

void cpu_reset(CPU *cpu) {
    // Inicializar todos los registros a 0
    for (int i = 0; i < NUM_REGISTERS; i++) {
        cpu->R[i] = 0;
    }
    
    // Inicializar registros especiales
    cpu->PC = 0;
    cpu->IR = 0;
    cpu->halted = false;
    cpu->cycles = 0;
    
    // Inicializar flags
    cpu->zero_flag = false;
    cpu->carry_flag = false;
    
    // Limpiar memoria
    memset(cpu->memory, 0, sizeof(cpu->memory));
    
    // Inicializar stack pointer (R14) al tope del stack
    cpu->R[REG_SP] = STACK_BASE;
    
    printf("[CPU] Reinicio completo. PC=0x%04X, SP=0x%04X\n", cpu->PC, cpu->R[REG_SP]);
}

void cpu_load_program(CPU *cpu, const uint16_t *program, size_t size) {
    if (size > MEMORY_SIZE) {
        fprintf(stderr, "[ERROR CPU] Tamaño del programa (%zu) excede el tamaño de memoria (%d)\n", 
                size, MEMORY_SIZE);
        return;
    }
    
    // Cargar programa en memoria comenzando en dirección 0
    for (size_t i = 0; i < size; i++) {
        cpu->memory[i] = program[i];
    }
    
    printf("[CPU] Cargadas %zu instrucciones en memoria\n", size);
}

int cpu_load_from_file(CPU *cpu, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "[ERROR CPU] No se puede abrir el archivo: %s\n", filename);
        return -1;
    }
    
    int addr = 0;
    char line[64];
    
    // Leer archivo línea por línea (formato: cada línea es una palabra en hex)
    while (fgets(line, sizeof(line), f) && addr < MEMORY_SIZE) {
        uint32_t word;
        if (sscanf(line, "%X", &word) == 1) {
            cpu->memory[addr++] = (uint16_t)word;
        }
    }
    
    fclose(f);
    printf("[CPU] Cargadas %d instrucciones desde %s\n", addr, filename);
    return 0;
}

void cpu_dump_state(const CPU *cpu) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                     CPU STATE DUMP                         ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║ PC: 0x%04X    IR: 0x%04X    Cycles: %-10llu        ║\n", 
           cpu->PC, cpu->IR, (unsigned long long)cpu->cycles);
    printf("║ Halted: %-5s  Zero: %-5s  Carry: %-5s             ║\n",
           cpu->halted ? "YES" : "NO",
           cpu->zero_flag ? "YES" : "NO",
           cpu->carry_flag ? "YES" : "NO");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║ REGISTERS:                                                 ║\n");
    
    for (int i = 0; i < NUM_REGISTERS; i += 4) {
        printf("║ ");
        for (int j = 0; j < 4 && (i+j) < NUM_REGISTERS; j++) {
            int reg = i + j;
            if (reg == REG_SP) {
                printf("R%02d(SP):%04X ", reg, cpu->R[reg]);
            } else {
                printf("R%02d:%04X ", reg, cpu->R[reg]);
            }
        }
        printf("    ║\n");
    }
    
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

void cpu_dump_memory(const CPU *cpu, uint16_t start, uint16_t count) {
    printf("\n--- Memory Dump (Start: 0x%04X, Count: %d) ---\n", start, count);
    
    for (uint16_t i = start; i < start + count && i < MEMORY_SIZE; i++) {
        if ((i - start) % 8 == 0) {
            printf("\n0x%04X: ", i);
        }
        printf("%04X ", cpu->memory[i]);
    }
    printf("\n\n");
}

// ============================================================================
// CICLO DE INSTRUCCIÓN: FETCH - DECODE - EXECUTE
// ============================================================================

void cpu_fetch(CPU *cpu) {
    // Verificar que PC está dentro de límites
    if (cpu->PC >= MEMORY_SIZE) {
        fprintf(stderr, "[ERROR CPU] PC fuera de límites: 0x%04X\n", cpu->PC);
        cpu->halted = true;
        return;
    }
    
    // Cargar instrucción de memoria al registro IR
    cpu->IR = cpu->memory[cpu->PC];
    
    // Incrementar PC para apuntar a la siguiente instrucción
    cpu->PC++;
}

void cpu_decode_execute(CPU *cpu) {
    // Decodificar campos de la instrucción
    uint8_t opcode = DECODE_OPCODE(cpu->IR);
    uint8_t rd = DECODE_RD(cpu->IR);
    uint8_t operand = DECODE_OPERAND(cpu->IR);
    uint8_t rs = DECODE_RS(cpu->IR);  // Para instrucciones que usan registro fuente
    
    // Validar registro destino
    if (rd >= NUM_REGISTERS) {
        fprintf(stderr, "[ERROR CPU] Registro inválido Rd=%d\n", rd);
        cpu->halted = true;
        return;
    }
    
    // Ejecutar instrucción según el opcode
    switch (opcode) {
        case OP_NADA:
            // No operation
            break;
            
        case OP_MOVI:
            // MOVI Rd, imm -> Rd = immediate value
            cpu->R[rd] = operand;
            break;
            
        case OP_MOVER:
            // MOV Rd, Rs -> Rd = Rs
            if (rs >= NUM_REGISTERS) {
                fprintf(stderr, "[ERROR CPU] Registro inválido Rs=%d\n", rs);
                cpu->halted = true;
                return;
            }
            cpu->R[rd] = cpu->R[rs];
            break;
            
        case OP_SUMAR:
            // ADD Rd, Rs -> Rd = Rd + Rs
            if (rs >= NUM_REGISTERS) {
                fprintf(stderr, "[ERROR CPU] Registro inválido Rs=%d\n", rs);
                cpu->halted = true;
                return;
            }
            {
                uint32_t result = cpu->R[rd] + cpu->R[rs];
                cpu->carry_flag = (result > 0xFFFF);  // Detectar overflow
                cpu->R[rd] = (uint16_t)result;
                cpu->zero_flag = (cpu->R[rd] == 0);
            }
            break;
            
        case OP_RESTAR:
            // SUB Rd, Rs -> Rd = Rd - Rs
            if (rs >= NUM_REGISTERS) {
                fprintf(stderr, "[ERROR CPU] Registro inválido Rs=%d\n", rs);
                cpu->halted = true;
                return;
            }
            {
                int32_t result = (int32_t)cpu->R[rd] - (int32_t)cpu->R[rs];
                cpu->carry_flag = (result < 0);  // Borrow
                cpu->R[rd] = (uint16_t)result;
                cpu->zero_flag = (cpu->R[rd] == 0);
            }
            break;
            
        case OP_Y:
            // AND Rd, Rs -> Rd = Rd & Rs
            if (rs >= NUM_REGISTERS) {
                fprintf(stderr, "[ERROR CPU] Registro inválido Rs=%d\n", rs);
                cpu->halted = true;
                return;
            }
            cpu->R[rd] = cpu->R[rd] & cpu->R[rs];
            cpu->zero_flag = (cpu->R[rd] == 0);
            break;
            
        case OP_O:
            // OR Rd, Rs -> Rd = Rd | Rs
            if (rs >= NUM_REGISTERS) {
                fprintf(stderr, "[ERROR CPU] Registro inválido Rs=%d\n", rs);
                cpu->halted = true;
                return;
            }
            cpu->R[rd] = cpu->R[rd] | cpu->R[rs];
            cpu->zero_flag = (cpu->R[rd] == 0);
            break;
            
        case OP_NO:
            // NOT Rd -> Rd = ~Rd
            cpu->R[rd] = ~cpu->R[rd];
            cpu->zero_flag = (cpu->R[rd] == 0);
            break;
            
        case OP_CARGAR:
            // LOAD Rd, [addr] -> Rd = MEM[addr]
            if (operand >= MEMORY_SIZE) {
                fprintf(stderr, "[ERROR CPU] LOAD dirección fuera de límites: 0x%02X\n", operand);
                cpu->halted = true;
                return;
            }
            cpu->R[rd] = cpu->memory[operand];
            break;
            
        case OP_GUARDAR:
            // STORE Rd, [addr] -> MEM[addr] = Rd
            if (operand >= MEMORY_SIZE) {
                fprintf(stderr, "[ERROR CPU] STORE dirección fuera de límites: 0x%02X\n", operand);
                cpu->halted = true;
                return;
            }
            cpu->memory[operand] = cpu->R[rd];
            break;
            
        case OP_SALTAR:
            // JMP addr -> PC = addr (salto incondicional)
            cpu->PC = operand;
            break;
            
        case OP_SZ:
            // JZ Rd, addr -> if (Rd == 0) PC = addr
            if (cpu->R[rd] == 0) {
                cpu->PC = operand;
            }
            break;
            
        case OP_SNZ:
            // JNZ Rd, addr -> if (Rd != 0) PC = addr
            if (cpu->R[rd] != 0) {
                cpu->PC = operand;
            }
            break;
            
        case OP_ESCRIBIR:
            // OUT Rd -> output value of Rd
            printf("[SALIDA] R%d = %d (0x%04X)\n", rd, cpu->R[rd], cpu->R[rd]);
            break;
            
        case OP_LEER:
            // IN Rd -> read input into Rd
            printf("[ENTRADA] Ingrese valor para R%d: ", rd);
            {
                int value;
                if (scanf("%d", &value) == 1) {
                    cpu->R[rd] = (uint16_t)value;
                } else {
                    fprintf(stderr, "[ERROR CPU] Entrada inválida\n");
                    cpu->R[rd] = 0;
                }
            }
            break;
            
        case OP_ALTO:
            // HALT -> detener ejecución
            cpu->halted = true;
            printf("[CPU] Instrucción ALTO ejecutada\n");
            break;
            
        default:
            fprintf(stderr, "[ERROR CPU] Código de operación desconocido: 0x%X at PC=0x%04X\n", 
                    opcode, cpu->PC - 1);
            cpu->halted = true;
            break;
    }
}

int cpu_step(CPU *cpu) {
    if (cpu->halted) {
        return -1;
    }
    
    // FETCH
    cpu_fetch(cpu);
    
    if (cpu->halted) {
        return -1;
    }
    
    // DECODE & EXECUTE
    cpu_decode_execute(cpu);
    
    // Incrementar contador de ciclos
    cpu->cycles++;
    
    return cpu->halted ? -1 : 0;
}

uint64_t cpu_run(CPU *cpu, uint64_t max_cycles) {
    uint64_t initial_cycles = cpu->cycles;
    
    printf("[CPU] Iniciando ejecución...\n");
    
    while (!cpu->halted) {
        if (max_cycles > 0 && (cpu->cycles - initial_cycles) >= max_cycles) {
            printf("[CPU] Alcanzado límite máximo de ciclos (%llu)\n", 
                   (unsigned long long)max_cycles);
            break;
        }
        
        if (cpu_step(cpu) < 0) {
            break;
        }
    }
    
    uint64_t executed = cpu->cycles - initial_cycles;
    printf("[CPU] Ejecución detenida después de %llu cycles\n", (unsigned long long)executed);
    
    return executed;
}

// ============================================================================
// NOTAS PARA SEMANAS 3 Y 4
// ============================================================================

/*
 * EXTENSIONES FUTURAS:
 * 
 * 1. LLAMADAS A FUNCIONES (CALL/RET):
 *    - CALL addr: 
 *        * PUSH(PC) -> memory[R[SP]--] = PC
 *        * PC = addr
 *    - RET:
 *        * PC = memory[++R[SP]]
 * 
 * 2. OPERACIONES DE STACK (PUSH/POP):
 *    - PUSH Rd: memory[R[SP]--] = R[rd]
 *    - POP Rd:  R[rd] = memory[++R[SP]]
 * 
 * 3. COMPARACIONES Y SALTOS CONDICIONALES:
 *    - CMP Rd, Rs: Establece flags basándose en Rd - Rs
 *    - JLT/JGT/JLE/JGE: Saltos basados en flags
 * 
 * 4. SOPORTE PARA COMPILADOR C->ASM:
 *    - Convenciones de llamada (argumentos en registros o stack)
 *    - Frame pointer para variables locales
 *    - Manejo de expresiones aritméticas complejas
 * 
 * 5. RECURSIÓN:
 *    - Asegurar que el stack funcione correctamente
 *    - Implementar factorial/fibonacci de manera recursiva
 * 
 * El diseño actual ya tiene:
 * - R14 como stack pointer
 * - Memoria unificada para código y datos
 * - Saltos condicionales básicos (JZ, JNZ)
 * - Operaciones aritméticas y lógicas
 * 
 * Solo falta añadir CALL/RET/PUSH/POP en las próximas semanas.
 */
