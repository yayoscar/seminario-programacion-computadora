/**
 * cpu.h
 * Definición de la estructura de la CPU y API del simulador
 */

#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include "isa.h"

// ============================================================================
// ESTRUCTURA DE LA CPU
// ============================================================================

typedef struct {
    // Registros de propósito general (R0-R15)
    uint16_t R[NUM_REGISTERS];
    
    // Registros especiales
    uint16_t PC;    // Program Counter (contador de programa)
    uint16_t IR;    // Instruction Register (registro de instrucción)
    
    // Memoria principal (Von Neumann: código y datos comparten memoria)
    uint16_t memory[MEMORY_SIZE];
    
    // Estado de la CPU
    bool halted;        // true si se ejecutó HALT
    uint64_t cycles;    // Contador de ciclos de reloj
    
    // Flags de estado (para futuras extensiones)
    bool zero_flag;     // Se activa cuando el resultado es 0
    bool carry_flag;    // Se activa en overflow/carry
} CPU;

// ============================================================================
// API DEL SIMULADOR
// ============================================================================

/**
 * Inicializa la CPU a su estado inicial
 * - Todos los registros en 0
 * - PC = 0
 * - Memoria limpia
 * - halted = false
 */
void cpu_reset(CPU *cpu);

/**
 * Carga un programa en la memoria de la CPU
 * @param cpu Puntero a la estructura CPU
 * @param program Array de instrucciones de 16 bits
 * @param size Número de instrucciones a cargar
 */
void cpu_load_program(CPU *cpu, const uint16_t *program, size_t size);

/**
 * Carga un programa desde archivo .mem (formato hexadecimal)
 * @param cpu Puntero a la estructura CPU
 * @param filename Nombre del archivo .mem
 * @return 0 en éxito, -1 en error
 */
int cpu_load_from_file(CPU *cpu, const char *filename);

/**
 * Ejecuta un ciclo de instrucción: fetch -> decode -> execute
 * @param cpu Puntero a la estructura CPU
 * @return 0 si continúa, -1 si debe detenerse (HALT o error)
 */
int cpu_step(CPU *cpu);

/**
 * Ejecuta el programa hasta encontrar HALT o alcanzar max_cycles
 * @param cpu Puntero a la estructura CPU
 * @param max_cycles Número máximo de ciclos a ejecutar (0 = sin límite)
 * @return Número de ciclos ejecutados
 */
uint64_t cpu_run(CPU *cpu, uint64_t max_cycles);

/**
 * Muestra el estado actual de la CPU (registros y PC)
 * @param cpu Puntero a la estructura CPU
 */
void cpu_dump_state(const CPU *cpu);

/**
 * Muestra el contenido de la memoria
 * @param cpu Puntero a la estructura CPU
 * @param start Dirección inicial
 * @param count Número de palabras a mostrar
 */
void cpu_dump_memory(const CPU *cpu, uint16_t start, uint16_t count);

// ============================================================================
// FUNCIONES INTERNAS (para cpu_simulator.c)
// ============================================================================

/**
 * Fase FETCH: Obtiene la siguiente instrucción de memoria
 */
void cpu_fetch(CPU *cpu);

/**
 * Fase DECODE & EXECUTE: Decodifica y ejecuta la instrucción en IR
 */
void cpu_decode_execute(CPU *cpu);

#endif // CPU_H
