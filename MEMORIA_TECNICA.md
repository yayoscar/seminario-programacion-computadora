# 📘 MEMORIA TÉCNICA DEL PROYECTO
## Simulador de CPU con Pipeline Completo C → Máquina

**Seminario de Programación de Computadora**  
**Fecha:** Noviembre 2025

---

## 📋 ÍNDICE

1. [Introducción](#introducción)
2. [Objetivos del Proyecto](#objetivos-del-proyecto)
3. [Desarrollo por Semanas](#desarrollo-por-semanas)
4. [Retos Técnicos y Soluciones](#retos-técnicos-y-soluciones)
5. [Arquitectura del Sistema](#arquitectura-del-sistema)
6. [Proceso de Desarrollo](#proceso-de-desarrollo)
7. [Reflexiones y Aprendizajes](#reflexiones-y-aprendizajes)
8. [Conclusiones](#conclusiones)

---

## 🎯 INTRODUCCIÓN

Este documento describe el proceso completo de desarrollo de un simulador educativo de computadora que implementa el flujo completo desde código de alto nivel (C) hasta la ejecución en una CPU simulada, pasando por todas las etapas intermedias: compilación, ensamblado y ejecución.

### Motivación

El proyecto nace de la necesidad de entender profundamente cómo funciona una computadora desde sus fundamentos, implementando cada componente del pipeline de ejecución de programas. A diferencia de simplemente estudiar teoría, este proyecto construye **desde cero** cada pieza del rompecabezas.

### Alcance

El simulador implementa:
- Una ISA (Instruction Set Architecture) de 16 bits con mnemónicos en español
- Un compilador simplificado de C a ensamblador
- Un ensamblador de dos pasadas con soporte de pseudo-instrucciones
- Un simulador de CPU con arquitectura de registros generales
- Gestión de stack para llamadas a funciones

---

## 🎯 OBJETIVOS DEL PROYECTO

### Objetivos Principales

1. **Comprender el flujo completo de ejecución**: Desde código fuente hasta instrucciones máquina
2. **Implementar cada etapa del pipeline**: Compilador, ensamblador, simulador
3. **Diseñar una ISA funcional**: Con instrucciones suficientes para programación real
4. **Soportar llamadas a funciones**: Con gestión de stack y convenciones de llamada
5. **Crear herramienta educativa**: Con mnemónicos en español para facilitar aprendizaje

### Objetivos Secundarios

- Documentar exhaustivamente el proceso de desarrollo
- Implementar herramientas integradas y fáciles de usar
- Validar funcionamiento con programas de prueba
- Mantener código limpio y bien estructurado

---

## 📅 DESARROLLO POR SEMANAS

### Semana 1: Fundamentos de la CPU Simulada

**Objetivo**: Implementar el núcleo del simulador de CPU.

**Actividades realizadas**:

1. **Diseño de la ISA** (16 bits):
   - Formato: `[4 bits opcode][4 bits Rd][8 bits operand]`
   - Definición de 16 instrucciones básicas
   - Elección de mnemónicos en español

2. **Estructura de datos**:
   ```c
   typedef struct {
       uint16_t R[16];        // Registros generales
       uint16_t PC;           // Program Counter
       uint16_t IR;           // Instruction Register
       uint16_t memory[256];  // Memoria Von Neumann
       bool halted;           // Estado de CPU
       uint64_t cycles;       // Contador de ciclos
   } CPU;
   ```

3. **Ciclo fetch-decode-execute**:
   - `cpu_fetch()`: Carga instrucción de memoria
   - `cpu_decode_execute()`: Decodifica y ejecuta
   - `cpu_step()`: Un ciclo completo
   - `cpu_run()`: Ejecución hasta ALTO

**Resultado**: CPU funcional capaz de ejecutar programas básicos cargados directamente en memoria.

---

### Semana 2: Ensamblador y Lenguaje ASM

**Objetivo**: Crear ensamblador para traducir código simbólico a binario.

**Actividades realizadas**:

1. **Ensamblador de dos pasadas**:
   - **Primera pasada**: Construir tabla de símbolos (etiquetas)
   - **Segunda pasada**: Generar código máquina

2. **Parser de lenguaje ensamblador**:
   - Soporte para comentarios (`;`)
   - Etiquetas (terminan en `:`)
   - Instrucciones con operandos
   - Números decimales y hexadecimales

3. **Tabla de instrucciones**:
   ```c
   static const InfoInstruccion TABLA_ISA[] = {
       {"MOVI",   OP_MOVI,   2},
       {"SUMAR",  OP_SUMAR,  2},
       {"CARGAR", OP_CARGAR, 2},
       // ... etc
   };
   ```

4. **Generación de código máquina**:
   - Codificación de instrucciones
   - Resolución de etiquetas
   - Formato de salida `.mem` (hexadecimal)

**Resultado**: Ensamblador funcional que traduce programas ASM a formato ejecutable.

**Ejemplo de programa**:
```assembly
; Suma de 1 a 10
        MOVI R0, 0      ; suma = 0
        MOVI R1, 1      ; i = 1
bucle:  SUMAR R0, R1    ; suma += i
        MOVI R2, 1
        SUMAR R1, R2    ; i++
        MOVI R2, 11
        RESTAR R2, R1   ; 11 - i
        SNZ R2, bucle   ; if (i != 11) goto bucle
        ESCRIBIR R0     ; mostrar suma
        ALTO
```

---

### Semana 3: Compilador C → ASM

**Objetivo**: Implementar compilador simplificado de C a ensamblador.

**Actividades realizadas**:

1. **Diseño del compilador** (`c_to_asm.c`):
   - Parser de líneas de código C
   - Tabla de variables con asignación de registros
   - Generación de código ASM

2. **Características implementadas**:
   - Declaraciones: `int x, y, z;`
   - Asignaciones: `x = 5;`
   - Expresiones aritméticas: `z = x + y;`
   - Definición de funciones: `int suma(int a, int b) { ... }`
   - Llamadas a funciones: `z = suma(x, y);`
   - Return statements: `return resultado;`
   - Bucles: `while`, `for`
   - Condicionales: `if`

3. **Convención de llamadas**:
   - Parámetros en R0-R3
   - Retorno en R0
   - Variables locales en R4-R13
   - SP en R14, temporal en R15

4. **Gestión de variables**:
   ```c
   typedef struct {
       char name[64];
       int reg;        // Registro asignado
       bool is_param;  // Es parámetro de función
   } Variable;
   ```

**Resultado**: Compilador que traduce funciones C simples a ensamblador funcional.

**Ejemplo de traducción**:
```c
// Código C
int suma(int a, int b) {
    int resultado = a + b;
    return resultado;
}
```

Genera:
```assembly
func_suma:
    ; Variable 'a' -> R0 (param)
    ; Variable 'b' -> R1 (param)
    ; Variable 'resultado' -> R4
    MOVI R4, 0
    MOVER R4, R0
    SUMAR R4, R1
    MOVER R0, R4
    RETORNAR
```

---

### Semana 4: Pseudo-instrucciones y Stack

**Objetivo**: Implementar llamadas a funciones con gestión de stack.

**Actividades realizadas**:

1. **Diseño de pseudo-instrucciones**:
   - **EMPUJAR Rd** (Push): Guardar registro en stack
   - **SACAR Rd** (Pop): Restaurar registro desde stack
   - **LLAMAR dir** (Call): Llamada a función
   - **RETORNAR** (Return): Retorno de función

2. **Expansión de pseudo-instrucciones** (`isa_extended.h`):

   **EMPUJAR Rd** → 3 instrucciones:
   ```
   MOVI R15, 1
   RESTAR R14, R15      ; SP--
   GUARDAR Rd, [R14]    ; stack[SP] = Rd
   ```

   **SACAR Rd** → 3 instrucciones:
   ```
   CARGAR Rd, [R14]     ; Rd = stack[SP]
   MOVI R15, 1
   SUMAR R14, R15       ; SP++
   ```

   **LLAMAR dir** → 5 instrucciones:
   ```
   MOVI R13, ret_addr   ; Dirección de retorno
   GUARDAR R13, [R14]   ; Push ret_addr
   MOVI R15, 1
   RESTAR R14, R15      ; SP--
   SALTAR target        ; Saltar a función
   ```

   **RETORNAR** → 4 instrucciones:
   ```
   MOVI R15, 1
   SUMAR R14, R15       ; SP++
   CARGAR R13, [R14]    ; Pop ret_addr
   SALTAR R13           ; Salto indirecto
   ```

3. **Modificaciones al ensamblador**:
   - Reconocer pseudo-instrucciones
   - Expandirlas durante segunda pasada
   - Ajustar direcciones de etiquetas

4. **Integración con compilador**:
   - Generar `LLAMAR func_name` en llamadas
   - Generar `RETORNAR` al final de funciones
   - Agregar `SALTAR func_main` como punto de entrada

**Resultado**: Sistema completo con soporte de llamadas a funciones y gestión automática de stack.

---

## 🔧 RETOS TÉCNICOS Y SOLUCIONES

### 1. Bug de strdup() - Segmentation Fault

**Problema**: El compilador crasheaba al procesar funciones con parámetros.

**Causa raíz**:
```c
// Código problemático
char *param_name = strdup(token);  // strdup() no disponible en -std=c99
```

**Solución implementada**:
```c
// Solución con strncpy()
char param_name[256];
strncpy(param_name, token, 255);
param_name[255] = '\0';
```

**Lección**: Revisar disponibilidad de funciones según estándar de C usado.

---

### 2. RETORNAR Duplicado - Stack Overflow

**Problema**: Cada función generaba 2 instrucciones RETORNAR, causando que el stack pointer se desbordara.

**Causa raíz**: Dos ubicaciones del compilador generaban RETORNAR:
- Al procesar `return` statement
- Al cerrar bloque de función `}`

**Solución implementada**:
```c
// Agregar flag a estructura Compiler
typedef struct {
    // ... otros campos
    bool function_has_explicit_return;
} Compiler;

// En compile_return()
void compile_return(Compiler *c, const char *line) {
    // ... generar RETORNAR
    c->function_has_explicit_return = true;  // Marcar flag
}

// En compile_closing_brace()
void compile_closing_brace(Compiler *c) {
    if (c->in_function && !c->function_has_explicit_return) {
        emit("MOVI R0, 0");
        emit("RETORNAR");  // Solo si no hay return explícito
    }
    c->function_has_explicit_return = false;  // Reset
}
```

**Lección**: Mantener estado del compilador para evitar generación duplicada de código.

---

### 3. LLAMAR no Implementado

**Problema**: El ensamblador tenía placeholder para LLAMAR pero no lo expandía.

**Causa raíz**: Case statement incompleto en `expand_pseudo_instruction()`.

**Solución implementada**:
```c
case PSEUDO_CALL: {
    uint16_t target_addr;
    
    // Intentar resolver como etiqueta
    if (find_label(asm_state, pseudo->operand_str, &target_addr)) {
        expand_call(expanded, current_addr, (uint8_t)target_addr);
    } else {
        // Fallback: interpretar como número
        target_addr = parse_number(pseudo->operand_str);
        expand_call(expanded, current_addr, (uint8_t)target_addr);
    }
    break;
}
```

**Cambios adicionales**:
- Modificar firma de `expand_pseudo_instruction()` para recibir `Assembler *asm_state`
- Aumentar `MAX_PSEUDO_EXPANSION` de 4 a 5

**Lección**: Completar todas las ramas de control antes de testing.

---

### 4. SALTAR - Loop Infinito

**Problema**: Instrucción SALTAR causaba loop infinito, PC permanecía en 0x0000.

**Causa raíz**: Confusión entre saltos directos e indirectos:
```c
// Código problemático
case OP_SALTAR:
    if (operand < NUM_REGISTERS) {  // ¡ERROR! 2 < 16 = true
        cpu->PC = cpu->R[operand];  // Salto indirecto: PC = R[2] = 0
    } else {
        cpu->PC = operand;          // Salto directo
    }
```

Para `SALTAR 2`, operand=2 < 16, entonces hacía `PC = R[2]` (salto indirecto), pero R[2]=0, creando loop infinito.

**Solución implementada**:
```c
case OP_SALTAR:
    // Usar campo Rd para distinguir tipo de salto
    if (rd != 0 && rd < NUM_REGISTERS) {
        // Salto indirecto: SALTAR Rs (donde Rs en campo Rd)
        cpu->PC = cpu->R[rd];
    } else {
        // Salto directo: SALTAR addr
        cpu->PC = operand;
    }
    break;
```

**Codificación**:
- `SALTAR 0x0009` → `0xA009` (Rd=0, salto directo)
- `SALTAR R13` → `0xAD00` (Rd=13, salto indirecto)

**Lección**: Diseñar encoding cuidadosamente para evitar ambigüedades.

---

### 5. Punto de Entrada - Ejecución Incorrecta

**Problema**: CPU empezaba ejecutando en PC=0, que era la primera función definida (no main).

**Causa raíz**: El compilador generaba funciones en orden de definición en el source C.

**Solución implementada**:
```c
// Al inicio de compile_c_to_asm()
emit("; Punto de entrada: saltar a main()");
emit("SALTAR func_main");
emit("");
```

Ahora el programa siempre empieza:
```assembly
SALTAR func_main   ; Dirección 0x0000 - primera instrucción

func_suma:         ; Funciones definidas primero
    ; ...

func_main:         ; Main definido último, pero se ejecuta primero
    ; ...
```

**Lección**: Considerar punto de entrada en diseño de compilador.

---

## 🏗️ ARQUITECTURA DEL SISTEMA

### Pipeline Completo

```
┌──────────────┐
│  Código C    │  test.c
└──────┬───────┘
       │ c_to_asm
       ▼
┌──────────────┐
│ Ensamblador  │  test.asm  (MOVI, SUMAR, LLAMAR, etc.)
└──────┬───────┘
       │ assembler (2 pasadas)
       ▼
┌──────────────┐
│   Binario    │  test.mem  (A009, 1400, 2400, etc.)
└──────┬───────┘
       │ cpu_simulator
       ▼
┌──────────────┐
│  Ejecución   │  Resultado en registros
└──────────────┘
```

### Estructura de Directorios

```
seminario-programacion-computadora/
├── src/
│   ├── main.c              # Programa principal integrado
│   ├── cpu_simulator.c     # Simulador de CPU (432 líneas)
│   ├── assembler.c         # Ensamblador (708 líneas)
│   └── c_to_asm.c          # Compilador C→ASM (754 líneas)
├── include/
│   ├── isa.h               # ISA en español
│   ├── isa_extended.h      # Pseudo-instrucciones
│   ├── cpu.h               # API simulador
│   └── assembler.h         # API ensamblador
├── tests/
│   ├── test_c_simple_func.c    # Demo con funciones
│   ├── test_c_main_only.c      # Test simple
│   └── *.asm                   # Tests en ASM
├── asm/
│   └── programa.asm        # Programa de ejemplo
├── docs/
│   └── presentacion_completa.html  # Presentación
├── bin/                    # Ejecutables generados
├── Makefile
├── README.md
└── MEMORIA_TECNICA.md      # Este documento
```

### Componentes Principales

#### 1. Compilador (c_to_asm.c)

**Responsabilidad**: Traducir subconjunto de C a ensamblador.

**Estructura**:
```c
typedef struct {
    Variable vars[MAX_VARS];
    int var_count;
    int label_counter;
    bool in_function;
    bool function_has_explicit_return;
    char current_function[64];
    int indent_level;
} Compiler;
```

**Funciones principales**:
- `compile_function_definition()` - Procesa definición de función
- `compile_declaration()` - Variables locales
- `compile_assignment()` - Asignaciones
- `compile_function_call()` - Llamadas a funciones
- `compile_return()` - Return statements
- `compile_if()`, `compile_while()`, `compile_for()` - Control de flujo

#### 2. Ensamblador (assembler.c)

**Responsabilidad**: Traducir ASM a binario.

**Estructura**:
```c
typedef struct {
    Label labels[MAX_LABELS];
    int label_count;
    uint16_t instructions[MEMORY_SIZE];
    int instruction_count;
} Assembler;
```

**Proceso**:
1. **Primera pasada**: Construir tabla de símbolos
2. **Segunda pasada**: Generar código máquina
3. **Expansión**: Convertir pseudo-instrucciones

#### 3. Simulador (cpu_simulator.c)

**Responsabilidad**: Ejecutar código máquina.

**Ciclo de ejecución**:
```c
void cpu_step(CPU *cpu) {
    cpu_fetch(cpu);           // Cargar instrucción
    cpu_decode_execute(cpu);  // Decodificar y ejecutar
    cpu->cycles++;
}
```

**Instrucciones implementadas**:
- Aritméticas: SUMAR, RESTAR
- Lógicas: Y, O, NO
- Memoria: CARGAR, GUARDAR
- Control: SALTAR, SZ, SNZ
- I/O: LEER, ESCRIBIR
- Sistema: ALTO

---

## 🔄 PROCESO DE DESARROLLO

### Metodología

1. **Diseño incremental**: Cada semana agrega funcionalidad
2. **Testing continuo**: Validar cada componente antes de integrar
3. **Documentación paralela**: Escribir mientras se desarrolla
4. **Refactoring iterativo**: Mejorar código conforme se entiende mejor

### Herramientas Utilizadas

- **Lenguaje**: C (ANSI C99)
- **Compilador**: GCC con flags `-Wall -Wextra -std=c99`
- **Build system**: Make
- **Control de versiones**: Git
- **Depuración**: gdb, prints de debug

### Proceso de Testing

**Niveles de prueba**:

1. **Unitario**: Cada función probada individualmente
2. **Integración**: Componentes juntos (compilador + ensamblador)
3. **Sistema**: Pipeline completo (C → ejecución)
4. **Aceptación**: Programas reales funcionando

**Ejemplos de tests**:
- `test_simple.asm` - Suma básica
- `test_memory.asm` - Load/store
- `test_c_main_only.c` - Programa C sin funciones
- `test_c_simple_func.c` - Llamada a función

### Validación Final

**Test principal**: `test_c_simple_func.c`

```c
int suma(int a, int b) {
    int resultado = a + b;
    return resultado;
}

int main() {
    int x = 5, y = 3, z = suma(x, y);
    return 0;
}
```

**Resultado esperado**: R6 = 0x0008 (z = 8)

**Ejecución**:
```bash
$ ./bin/c_to_asm tests/test_c_simple_func.c > test.asm
$ ./bin/main -e test.asm
```

**Salida**:
```
Total de ciclos ejecutados: 161
Halted: YES
R06:0008  ← ✅ Correcto: suma(5, 3) = 8
```

---

## 💡 REFLEXIONES Y APRENDIZAJES

### Sobre la Arquitectura de Computadoras

**Antes del proyecto**:
- Conocimiento teórico de fetch-decode-execute
- Comprensión superficial de ISAs
- Idea vaga de compiladores y ensambladores

**Después del proyecto**:
- Comprensión profunda de cada etapa del pipeline
- Apreciación de decisiones de diseño en ISAs reales
- Entendimiento visceral de trade-offs arquitectónicos

**Ejemplo concreto**: Al implementar SALTAR, se entendió por qué x86 tiene múltiples tipos de JMP (directo, indirecto, relativo) - cada uno optimiza casos de uso diferentes.

### Sobre el Diseño de Lenguajes

**Desafío**: ¿Cómo representar llamadas a funciones en una ISA simple?

**Aprendizaje**: Las pseudo-instrucciones son una abstracción poderosa:
- **A nivel de usuario**: `LLAMAR func` es simple y claro
- **A nivel de hardware**: Se expande a 5 instrucciones reales
- **Ventaja**: Simplicidad sin sacrificar funcionalidad

**Paralelo con lenguajes reales**: Similar a cómo Python esconde complejidad de manejo de memoria.

### Sobre Compilación

**Desafío inicial**: "¿Cómo traduzco `x = a + b` a ensamblador?"

**Aprendizaje**:
```c
// C
x = a + b;

// Se descompone en:
// 1. Cargar a en registro temporal
// 2. Sumarle b
// 3. Guardar resultado en x

// ASM generado:
MOVER R4, R0   // R4 = a (R0 contiene a)
SUMAR R4, R1   // R4 += b (R1 contiene b)
// R4 ahora contiene x
```

**Insight**: Compilación es descomposición sistemática de operaciones de alto nivel en operaciones primitivas.

### Sobre Gestión de Stack

**Concepto abstracto inicial**: "El stack guarda contexto de funciones"

**Comprensión concreta actual**:
```
Memoria antes de LLAMAR:
[250]: ???

Después de LLAMAR func (dirección 0x0015):
[249]: 0x0015  ← Dirección de retorno guardada
SP: 249

Después de RETORNAR:
SP: 250        ← Stack "vacío" de nuevo
PC: 0x0015     ← Continuamos después de LLAMAR
```

**Lección**: Abstracciones se entienden mejor implementándolas.

### Sobre Debugging

**Problema típico**: "El programa no funciona, ¿dónde está el bug?"

**Técnicas aprendidas**:
1. **Dividir y conquistar**: Probar componentes aisladamente
2. **Simplificar**: Crear test mínimo que reproduzca el bug
3. **Instrumentar**: Agregar prints en puntos críticos
4. **Verificar asunciones**: "¿Realmente funciona como creo?"

**Ejemplo real**: Bug de SALTAR se encontró probando:
```assembly
SALTAR end
MOVI R0, 99   ; No debería ejecutarse
end:
MOVI R1, 42
ALTO
```

Si R0 != 0 al final, hay bug. Simple pero efectivo.

---

## 🎓 CONCLUSIONES

### Sobre la Importancia del Flujo Completo

**Valor educativo de implementar el pipeline completo**:

1. **Desmitificación**: Los compiladores no son magia negra, son programas con lógica clara.

2. **Apreciación de abstracciones**: Cada capa del stack esconde complejidad:
   ```
   C:       z = suma(5, 3);
   ASM:     MOVER R0, R4
            MOVER R1, R5
            LLAMAR func_suma
            MOVER R6, R0
   Binario: 2004 2105 [5 instrucciones expandidas] 2600
   CPU:     [~40 ciclos de fetch-decode-execute]
   ```

3. **Entendimiento de trade-offs**: Cada decisión de diseño tiene consecuencias:
   - ISA compleja → hardware difícil, compiladores fáciles
   - ISA simple → hardware fácil, compiladores complejos
   - Nuestro proyecto: Balance entre ambos

4. **Debugging profundo**: Cuando un programa falla, podemos inspeccionar **cada nivel**:
   - ¿El C es correcto?
   - ¿El ASM generado es correcto?
   - ¿El binario es correcto?
   - ¿La ejecución es correcta?

### Sobre el Desarrollo Didáctico

**¿Por qué este proyecto es efectivo para aprendizaje?**

1. **Construcción incremental**: 
   - Semana 1: CPU básica (fundamento)
   - Semana 2: Ensamblador (capa de abstracción)
   - Semana 3: Compilador (alto nivel)
   - Semana 4: Integración (sistema completo)

2. **Mnemónicos en español**:
   - Reduce barrera de entrada
   - Facilita comprensión de conceptos
   - Hace código auto-documentado

3. **Escala manejable**:
   - 16 instrucciones (vs ~200 de x86)
   - 256 palabras de memoria (vs GBs)
   - Pipeline simple (vs superscalar out-of-order)
   
   Suficientemente simple para entender completamente, suficientemente complejo para ser realista.

4. **Visibilidad total**:
   - Todo el código es accesible
   - Cada decisión de diseño es explícita
   - Se puede modificar y experimentar libremente

### Retos Superados

Durante el desarrollo enfrentamos y resolvimos:

1. ✅ **Bugs de compilador** (strdup, RETORNAR duplicado)
2. ✅ **Diseño de ISA** (saltos directos vs indirectos)
3. ✅ **Expansión de pseudo-instrucciones** (LLAMAR requiere 5 instrucciones)
4. ✅ **Gestión de stack** (SP, dirección de retorno)
5. ✅ **Punto de entrada** (main no siempre está primero en memoria)

Cada reto enseñó algo valioso sobre cómo funcionan realmente las computadoras.

### Lecciones Principales

1. **Las abstracciones tienen costo**: Cada capa de abstracción (C → ASM → binario) agrega overhead pero mejora productividad.

2. **El diseño es iterativo**: La ISA, el compilador y el simulador evolucionaron juntos. No se puede diseñar uno en aislamiento.

3. **La simplicidad es difícil**: Hacer una ISA simple pero completa requirió muchas iteraciones.

4. **El debugging es fundamental**: Más del 50% del tiempo se invirtió en encontrar y corregir bugs. Herramientas de debugging son cruciales.

5. **La documentación importa**: Este documento existe porque documentar durante el desarrollo facilitó el progreso.

### Aplicaciones Futuras

Este proyecto sienta bases para extensiones:

- **Optimizaciones de compilador**: Eliminación de código muerto, propagación de constantes
- **Caché simulada**: Agregar jerarquía de memoria
- **Pipeline de CPU**: Implementar pipeline de 5 etapas
- **Multiprocesamiento**: Simular múltiples cores
- **Sistema operativo simple**: Scheduler, manejo de memoria

Cada extensión profundizaría comprensión de sistemas de computación.

---

## 🎯 REFLEXIÓN FINAL

**¿Qué aprendimos realmente?**

Más allá de conocimiento técnico, este proyecto enseñó que:

1. **Las computadoras son comprensibles**: No son cajas negras mágicas. Cada operación se puede descomponer y entender.

2. **El software y hardware están profundamente acoplados**: Decisiones de ISA afectan compiladores. Decisiones de compilador afectan performance de hardware.

3. **La abstracción es poderosa**: Poder escribir `z = suma(5, 3)` en vez de 40+ instrucciones máquina es la diferencia entre programar ser viable o no.

4. **El proceso importa tanto como el resultado**: Los bugs encontrados y corregidos enseñaron más que si todo hubiera funcionado a la primera.

5. **La educación efectiva requiere práctica**: Leer sobre compiladores ≠ implementar un compilador. La segunda experiencia es cualitativamente diferente.

### Valor Personal y Profesional

**Habilidades desarrolladas**:
- Pensamiento sistémico (ver cómo componentes interactúan)
- Debugging sistemático (aislar, simplificar, verificar)
- Diseño de software (estructuras de datos, APIs)
- Documentación técnica (explicar decisiones de diseño)
- Persistencia (seguir cuando algo no funciona)

**Conexión con industria**:
Este proyecto, aunque simplificado, modela problemas reales:
- Diseñadores de CPU enfrentan estos trade-offs a mayor escala
- Compiladores reales (GCC, LLVM) siguen estos principios
- Entender este flujo facilita usar herramientas profesionales

### Mensaje para Futuros Estudiantes

Si estás considerando un proyecto similar:

**Hazlo**. Será difícil. Habrá bugs frustrantes. Pero al final:
- Entenderás tu computadora a un nivel que pocos alcanzan
- Apreciarás abstracciones que antes dabas por sentado
- Tendrás una herramienta educativa que puedes compartir

**Empieza simple**: No intentes implementar x86 completo. Una ISA de 16 instrucciones es suficiente para aprender los conceptos.

**Documenta todo**: Tu yo del futuro (y otros) te lo agradecerán.

**Disfruta el proceso**: Los bugs son oportunidades de aprendizaje, no fracasos.

---

## 📚 REFERENCIAS

- **Libros consultados**:
  - "Computer Organization and Design" - Patterson & Hennessy
  - "Compilers: Principles, Techniques, and Tools" - Aho, Lam, Sethi, Ullman
  
- **Recursos en línea**:
  - Documentación de ISAs reales (ARM, RISC-V, MIPS)
  - Tutoriales de compiladores
  - Ejemplos de ensambladores simples

---

## 📝 APÉNDICE: MÉTRICAS DEL PROYECTO

**Líneas de código (sin comentarios)**:
- `cpu_simulator.c`: 432 líneas
- `assembler.c`: 708 líneas
- `c_to_asm.c`: 754 líneas
- **Total**: ~1,900 líneas de código C

**Tiempo invertido**:
- Semana 1 (CPU): ~15 horas
- Semana 2 (Ensamblador): ~20 horas
- Semana 3 (Compilador): ~25 horas
- Semana 4 (Integración + debugging): ~30 horas
- Documentación: ~10 horas
- **Total**: ~100 horas

**Bugs encontrados y corregidos**: 5 críticos, ~15 menores

**Tests creados**: 12 programas de prueba

**Commits**: ~50+ (desarrollo iterativo)

---

**Fin del documento**

---

**Autor**: Proyecto de Seminario de Programación de Computadora  
**Fecha**: Noviembre 2025  
**Versión**: 1.0 Final
