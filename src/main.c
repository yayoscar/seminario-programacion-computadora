/**
 * main.c
 * Programa principal integrado: ensambla y ejecuta programas
 * 
 * Opciones:
 * 1. Ensamblar un archivo .asm
 * 2. Ejecutar un archivo .mem en el simulador
 * 3. Ensamblar y ejecutar (pipeline completo)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../include/cpu.h"
#include "../include/isa.h"
#include "../include/assembler.h"

// ============================================================================
// PROTOTIPOS
// ============================================================================

void print_usage(const char *program_name);
void run_assembler_only(const char *input_file, const char *output_file);
void run_simulator_only(const char *mem_file);
void run_full_pipeline(const char *asm_file);

// ============================================================================
// MAIN
// ============================================================================

int main(int argc, char **argv) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    // Modo 1: Ensamblar solamente
    if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--ensamblar") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Error: -a requiere archivos de entrada y salida\n");
            print_usage(argv[0]);
            return 1;
        }
        run_assembler_only(argv[2], argv[3]);
        return 0;
    }
    
    // Modo 2: Ejecutar solamente
    if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "--ejecutar") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: -r requiere un archivo .mem\n");
            print_usage(argv[0]);
            return 1;
        }
        run_simulator_only(argv[2]);
        return 0;
    }
    
    // Modo 3: Pipeline completo (por defecto)
    if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--completo") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: -e requiere un archivo .asm\n");
            print_usage(argv[0]);
            return 1;
        }
        run_full_pipeline(argv[2]);
        return 0;
    }
    
    // Si no hay flag, asumir pipeline completo
    run_full_pipeline(argv[1]);
    
    return 0;
}

// ============================================================================
// FUNCIONES
// ============================================================================

void print_usage(const char *program_name) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║      SIMULADOR CPU & ENSAMBLADOR - Herramienta Integrada   ║\n");
    printf("║            Seminario Programacion de Computadora           ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("USO:\n");
    printf("  %s [OPCIONES] <archivo>\n", program_name);
    printf("\n");
    printf("OPCIONES:\n");
    printf("  -a, --ensamblar <entrada.asm> <salida.mem>\n");
    printf("      Solo ensamblar: convertir .asm a .mem\n");
    printf("\n");
    printf("  -r, --ejecutar <entrada.mem>\n");
    printf("      Solo ejecutar: ejecutar un archivo .mem en el simulador\n");
    printf("\n");
    printf("  -e, --completo <entrada.asm>\n");
    printf("      Pipeline completo: ensamblar y ejecutar archivo .asm\n");
    printf("      (Esta es la opción por defecto)\n");
    printf("\n");
    printf("EJEMPLOS:\n");
    printf("  %s -a programa.asm programa.mem\n", program_name);
    printf("  %s -r programa.mem\n", program_name);
    printf("  %s -e programa.asm\n", program_name);
    printf("  %s programa.asm                    # Igual que -e\n", program_name);
    printf("\n");
}

void run_assembler_only(const char *input_file, const char *output_file) {
    printf("\n=== MODO ENSAMBLADOR ===\n");
    
    if (assemble_file(input_file, output_file) != 0) {
        fprintf(stderr, "\n[ERROR] ¡Ensamblado falló!\n");
        exit(1);
    }
    
    printf("\n[ÉXITO] ¡Ensamblado completo!\n");
}

void run_simulator_only(const char *mem_file) {
    printf("\n=== MODO SIMULADOR ===\n");
    
    // Crear y resetear CPU
    CPU cpu;
    cpu_reset(&cpu);
    
    // Cargar programa desde archivo
    if (cpu_load_from_file(&cpu, mem_file) != 0) {
        fprintf(stderr, "\n[ERROR] ¡Fallo al cargar programa!\n");
        exit(1);
    }
    
    printf("\n--- Memoria Inicial (primeras 32 palabras) ---\n");
    cpu_dump_memory(&cpu, 0, 32);
    
    printf("\n--- Estado Inicial de CPU ---\n");
    cpu_dump_state(&cpu);
    
    printf("\n--- Iniciando Ejecución ---\n");
    printf("═══════════════════════════════════════════════════════════\n\n");
    
    // Ejecutar programa
    uint64_t cycles = cpu_run(&cpu, 10000);  // Límite de 10000 ciclos
    
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("--- Ejecución Completa ---\n");
    printf("Total de ciclos ejecutados: %llu\n", (unsigned long long)cycles);
    
    // Mostrar estado final
    cpu_dump_state(&cpu);
    
    printf("\n--- Memoria Final (primeras 32 palabras) ---\n");
    cpu_dump_memory(&cpu, 0, 32);
}

void run_full_pipeline(const char *asm_file) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║           PIPELINE COMPLETO: ENSAMBLAR + EJECUTAR         ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    // Generar nombre del archivo .mem
    char mem_file[256];
    strncpy(mem_file, asm_file, sizeof(mem_file) - 5);
    mem_file[sizeof(mem_file) - 5] = '\0';
    
    // Reemplazar extensión .asm con .mem
    char *dot = strrchr(mem_file, '.');
    if (dot && strcmp(dot, ".asm") == 0) {
        strcpy(dot, ".mem");
    } else {
        strcat(mem_file, ".mem");
    }
    
    // Paso 1: Ensamblar
    printf("\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("  PASO 1: ENSAMBLANDO\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    if (assemble_file(asm_file, mem_file) != 0) {
        fprintf(stderr, "\n[ERROR] ¡Ensamblado falló!\n");
        exit(1);
    }
    
    // Paso 2: Ejecutar
    printf("\n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("  PASO 2: EJECUTANDO\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    // Crear y resetear CPU
    CPU cpu;
    cpu_reset(&cpu);
    
    // Cargar programa
    if (cpu_load_from_file(&cpu, mem_file) != 0) {
        fprintf(stderr, "\n[ERROR] Fallo al cargar programa!\n");
        exit(1);
    }
    
    printf("\n--- Estado Inicial de CPU ---\n");
    cpu_dump_state(&cpu);
    
    printf("\n--- Starting Execution ---\n");
    printf("═══════════════════════════════════════════════════════════\n\n");
    
    // Ejecutar programa
    uint64_t cycles = cpu_run(&cpu, 10000);
    
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("--- Ejecución Completa ---\n");
    printf("Total de ciclos ejecutados: %llu\n", (unsigned long long)cycles);
    
    // Mostrar estado final
    cpu_dump_state(&cpu);
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                   PIPELINE COMPLETE!                       ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}
