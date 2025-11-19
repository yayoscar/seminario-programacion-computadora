#include <stdio.h>
#include <stdint.h>
#include "../include/cpu.h"
#include "../include/isa.h"

int main() {
    CPU cpu;
    cpu_reset(&cpu);
    
    // Cargar programa simple: SALTAR 0x0005, luego ALTO en 0x0005
    cpu.memory[0] = 0xA005;  // SALTAR 5
    cpu.memory[5] = 0xF000;  // ALTO
    
    printf("Memoria cargada:\n");
    printf("  [0x0000] = 0x%04X (SALTAR 5)\n", cpu.memory[0]);
    printf("  [0x0005] = 0x%04X (ALTO)\n", cpu.memory[5]);
    printf("\n");
    
    printf("Estado inicial:\n");
    printf("  PC=%04X IR=%04X Halted=%d\n", cpu.PC, cpu.IR, cpu.halted);
    
    for (int i = 0; i < 10 && !cpu.halted; i++) {
        printf("\n--- Ciclo %d ---\n", i);
        printf("ANTES: PC=%04X IR=%04X\n", cpu.PC, cpu.IR);
        
        cpu_step(&cpu);
        
        printf("DESPUES: PC=%04X IR=%04X Halted=%d\n", 
               cpu.PC, cpu.IR, cpu.halted);
    }
    
    return 0;
}
