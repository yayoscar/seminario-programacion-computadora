#include <stdio.h>
#include <stdlib.h> // Para exit()

// --- Definición de Componentes ---

#define MEMORY_SIZE 256 // Nuestra computadora tendrá 256 bytes de memoria

// 1. Memoria Principal
unsigned char memory[MEMORY_SIZE];

// 2. CPU (Registros)
typedef struct {
    unsigned char pc;  // Program Counter (Contador de Programa)
    unsigned char ir;  // Instruction Register (Registro de Instrucción)
    unsigned char acc; // Accumulator (Acumulador)
} CPU;

// --- Definición del Set de Instrucciones (Opcodes) ---
// La UC y la ALU "entienden" estas operaciones
#define OP_LOAD 0x01 // Cargar un valor de memoria al Acumulador
#define OP_ADD  0x02 // Sumar un valor de memoria al Acumulador
#define OP_STORE 0x03 // Guardar el Acumulador en una dirección de memoria
#define OP_HALT 0xFF // Detener la ejecución

// --- Prototipos de Funciones del Ciclo ---
void fetch(CPU* cpu);
void decode_execute(CPU* cpu, int* running);
void load_program_example(void);
void dump_memory(void);

/**
 * Función principal: Inicializa la CPU y corre el ciclo de ejecución
 */
int main() {
    CPU cpu = {0, 0, 0}; // Inicializa todos los registros a 0
    int running = 1;     // Flag para mantener la CPU en ejecución

    // Cargar un programa de ejemplo en la memoria
    load_program_example();

    printf("--- Estado Inicial de la Memoria ---\n");
    dump_memory();
    printf("\n--- Iniciando Ciclo de Ejecución ---\n");

    // Este es el ciclo principal de la Unidad de Control
    while (running) {
        // 1. FETCH (Búsqueda)
        fetch(&cpu);

        // 2. DECODE & EXECUTE (Decodificación y Ejecución)
        decode_execute(&cpu, &running);

        // Opcional: Imprimir estado para depuración
        printf("PC: %02X  IR: %02X  ACC: %02X\n", cpu.pc, cpu.ir, cpu.acc);
    }

    printf("--- Ejecución Detenida (HALT) ---\n");
    printf("\n--- Estado Final de la Memoria ---\n");
    dump_memory();
    
    return 0;
}

/**
 * 1. Ciclo de Búsqueda (Fetch)
 * La UC obtiene la instrucción de la memoria apuntada por el PC.
 */
void fetch(CPU* cpu) {
    // La instrucción se carga en el IR
    cpu->ir = memory[cpu->pc];
    // Se incrementa el PC para apuntar a la siguiente posición
    // (que podría ser un operando o la siguiente instrucción)
    cpu->pc++;
}

/**
 * 2. Ciclo de Decodificación y Ejecución (Decode-Execute)
 * La UC interpreta la instrucción en el IR y la ALU/Memoria la ejecutan.
 */
void decode_execute(CPU* cpu, int* running) {
    // Este 'switch' actúa como el decodificador de la UC
    switch (cpu->ir) {
        
        case OP_LOAD: {
            // Instrucción de 2 bytes: [LOAD] [DIRECCIÓN]
            // 1. Obtener el operando (la dirección de memoria)
            unsigned char addr = memory[cpu->pc];
            cpu->pc++; // Incrementar PC para saltar el operando
            // 2. Ejecutar: Cargar dato de memoria al acumulador
            cpu->acc = memory[addr];
            printf("EJECUTADO: LOAD desde la dirección 0x%02X (Valor: %d)\n", addr, cpu->acc);
            break;
        }

        case OP_ADD: {
            // Instrucción de 2 bytes: [ADD] [DIRECCIÓN]
            // 1. Obtener el operando (la dirección de memoria)
            unsigned char addr = memory[cpu->pc];
            cpu->pc++; // Incrementar PC
            // 2. Ejecutar (ALU): Sumar valor de memoria al acumulador
            cpu->acc += memory[addr];
            printf("EJECUTADO: ADD desde la dirección 0x%02X (Nuevo ACC: %d)\n", addr, cpu->acc);
            break;
        }

        case OP_STORE: {
            // Instrucción de 2 bytes: [STORE] [DIRECCIÓN]
            // 1. Obtener el operando (la dirección de memoria)
            unsigned char addr = memory[cpu->pc];
            cpu->pc++; // Incrementar PC
            // 2. Ejecutar: Guardar el acumulador en la memoria
            memory[addr] = cpu->acc;
            printf("EJECUTADO: STORE en la dirección 0x%02X (Valor: %d)\n", addr, cpu->acc);
            break;
        }

        case OP_HALT: {
            // Instrucción de 1 byte: [HALT]
            // 1. Ejecutar: Detener el ciclo principal
            *running = 0;
            printf("EJECUTADO: HALT\n");
            break;
        }

        default:
            // Error: Instrucción desconocida
            printf("Error: Opcode desconocido 0x%02X en PC 0x%02X\n", cpu->ir, cpu->pc - 1);
            *running = 0;
            break;
    }
}

/**
 * Carga un programa simple en la memoria para probar el simulador.
 *
 * Este programa suma dos números (10 y 20) y guarda el resultado (30).
 * Los datos están en las direcciones 0x10 y 0x11.
 * El resultado se guardará en 0x12.
 */
void load_program_example() {
    // --- Sección de Datos ---
    // (En Von Neumann, datos y código comparten memoria)
    memory[0x10] = 10; // Dato A
    memory[0x11] = 20; // Dato B
    memory[0x12] = 0;  // Espacio para el resultado

    // --- Sección de Código (Programa) ---
    // El PC comenzará en 0x00
    
    // 0x00: LOAD 0x10   (Carga el valor 10 en ACC)
    memory[0x00] = OP_LOAD;
    memory[0x01] = 0x10;
    
    // 0x02: ADD 0x11    (Suma el valor 20 al ACC. ACC = 30)
    memory[0x02] = OP_ADD;
    memory[0x03] = 0x11;

    // 0x04: STORE 0x12  (Guarda el valor de ACC (30) en la memoria)
    memory[0x04] = OP_STORE;
    memory[0x05] = 0x12;

    // 0x06: HALT        (Termina el programa)
    memory[0x06] = OP_HALT;
}

/**
 * Muestra el contenido de la memoria (solo las primeras 32 celdas).
 */
void dump_memory() {
    for (int i = 0; i < 32; i++) {
        if (i % 8 == 0) printf("\n%02X: ", i);
        printf("%02X ", memory[i]);
    }
    printf("\n");
}