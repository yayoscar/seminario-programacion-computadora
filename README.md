# Simulador de CPU con Pipeline Completo

## Descripción del Proyecto

Simulador educativo completo de una computadora con ISA de 16 bits y mnemónicos en español. Implementa el flujo completo desde código C hasta ejecución en CPU simulada.

### Componentes Principales

1. **Compilador C → ASM** (`c_to_asm.c`) - Traduce subconjunto de C a ensamblador
2. **Ensamblador** (`assembler.c`) - Ensamblador de dos pasadas con pseudo-instrucciones
3. **Simulador CPU** (`cpu_simulator.c`) - Simulador con arquitectura de registros generales
4. **ISA de 16 bits** - Conjunto de instrucciones en español (MOVI, SUMAR, LLAMAR, etc.)

### Características

- ✅ **Mnemónicos en español** - MOVER, SUMAR, CARGAR, LLAMAR, RETORNAR
- ✅ **Pipeline completo** - C → ASM → Binario → Ejecución
- ✅ **Llamadas a funciones** - Pseudo-instrucciones LLAMAR/RETORNAR
- ✅ **Gestión de stack** - EMPUJAR/SACAR con R14 como SP
- ✅ **16 instrucciones básicas** - Aritméticas, lógicas, memoria, saltos, I/O

---

## Arquitectura

### ISA (Arquitectura del Conjunto de Instrucciones)

**Formato de Instrucción**: 16 bits

```
[4 bits CÓDIGO_OP][4 bits Rd][8 bits OPERANDO/Rs]
```

- **CÓDIGO_OP** (4 bits): Código de operación (0x0 - 0xF)
- **Rd** (4 bits): Registro destino (R0-R15)
- **OPERANDO** (8 bits): Operando inmediato O registro fuente (Rs)

### Registros

- **R0-R13**: Registros de propósito general (16 bits cada uno)
- **R14 (SP)**: Stack Pointer (para futuras llamadas a funciones)
- **R15**: Registro de flags
- **PC**: Program Counter
- **IR**: Instruction Register

### Memoria

- **256 palabras** de 16 bits cada una
- Arquitectura **Von Neumann**: código y datos comparten memoria
- Stack crece hacia abajo desde la dirección 255

---

## Conjunto de Instrucciones

| Código | Mnemónico | Descripción | Ejemplo |
|--------|-----------|-------------|---------|
| 0x0 | NADA | Sin operación | `NADA` |
| 0x1 | MOVI | Mover inmediato | `MOVI R0, 10` |
| 0x2 | MOVER | Mover registro | `MOVER R0, R1` |
| 0x3 | SUMAR | Sumar registros | `SUMAR R0, R1` |
| 0x4 | RESTAR | Restar registros | `RESTAR R0, R1` |
| 0x5 | Y | AND lógico | `Y R0, R1` |
| 0x6 | O | OR lógico | `O R0, R1` |
| 0x7 | NO | NOT lógico | `NO R0` |
| 0x8 | CARGAR | Cargar desde memoria | `CARGAR R0, 100` |
| 0x9 | GUARDAR | Guardar en memoria | `GUARDAR R0, 100` |
| 0xA | SALTAR | Salto incondicional | `SALTAR bucle` |
| 0xB | SZ | Saltar si cero | `SZ R0, etiqueta` |
| 0xC | SNZ | Saltar si no cero | `SNZ R0, etiqueta` |
| 0xD | ESCRIBIR | Mostrar registro | `ESCRIBIR R0` |
| 0xE | LEER | Leer a registro | `LEER R0` |
| 0xF | ALTO | Detener ejecución | `ALTO` |

### 🔄 Compatibilidad con Inglés

El ensamblador también acepta los mnemónicos en inglés (NOP, MOV, ADD, etc.) para compatibilidad con código existente.

### ✅ Pseudo-Instrucciones Implementadas (Semanas 3-4)

```assembly
LLAMAR dir   ; ✅ Llamada a función (expandida a 5 instrucciones)
RETORNAR     ; ✅ Retorno de función (expandida a 4 instrucciones)
EMPUJAR Rd   ; ✅ Push a pila (expandida a 3 instrucciones)
SACAR Rd     ; ✅ Pop de pila (expandida a 3 instrucciones)
```

**Nota:** Estas pseudo-instrucciones son expandidas automáticamente por el ensamblador a instrucciones máquina nativas.

---

## Estructura del Proyecto

```
seminario-programacion-computadora/
├── src/
│   ├── cpu_simulator.c    # Simulador de CPU
│   ├── assembler.c        # Ensamblador de dos pasadas
│   └── main.c             # Programa principal integrado
├── include/
│   ├── isa.h              # Definición de la ISA
│   ├── cpu.h              # API del simulador
│   └── assembler.h        # API del ensamblador
├── asm/
│   └── programa.asm       # Programa principal (suma 1..10)
├── tests/
│   ├── test_simple.asm    # Prueba simple: suma 10+20
│   ├── test_memory.asm    # Prueba de LOAD/STORE
│   ├── test_logical.asm   # Pruebas de AND/OR/NOT
├── bin/                   # Ejecutables generados
│   ├── cpu_sim           # Programa principal
│   └── assembler         # Ensamblador standalone
├── Makefile
└── README.md
```

---

## Compilación y Uso

### Requisitos

- GCC (o Clang)
- Make
## 🔧 Compilación y Uso

### Compilar todo el proyecto

```bash
make
```

### Ejecutar el pipeline completo (ensamblar + simular)

```bash
./bin/main -e asm/programa.asm
# o usando el nombre largo:
./bin/main --completo asm/programa.asm
```

Salida:
```
[Ensamblador] Ensamblando 'asm/programa.asm' → 'asm/programa.mem'...
[Ensamblador] ¡Ensamblado exitoso!
[Simulador] Cargando programa desde 'asm/programa.mem'...
[Simulador] Programa cargado. 12 palabras.
[Simulador] === Inicio de Ejecución ===
[OUT] R0 = 55
[Simulador] === CPU Detenida (ALTO) ===
[Simulador] Ciclos ejecutados: 86
```

### Solo ensamblar (sin ejecutar)

```bash
./bin/main -a asm/programa.asm asm/programa.mem
# o usando el nombre largo:
./bin/main --ensamblar asm/programa.asm asm/programa.mem
```

Genera el archivo `asm/programa.mem` con el código máquina en hexadecimal.

### Solo simular (programa ya ensamblado)

```bash
./bin/main -r asm/programa.mem
# o usando el nombre largo:
./bin/main --ejecutar asm/programa.mem
```

### Ejecutar pruebas

```bash
make test
```

Esto ejecuta todos los programas de prueba en la carpeta `tests/`.

### Limpiar binarios y archivos generados

```bash
make clean
```

---

## 📖 Opciones de Línea de Comandos

El programa principal (`main`) acepta las siguientes opciones:

### Ayuda

```bash
./bin/main -h
./bin/main --ayuda
```

Muestra:
```
Uso: ./bin/main [opciones] <archivo>

Opciones:
  -h, --ayuda       Mostrar esta ayuda
  -a, --ensamblar   Solo ensamblar (genera .mem)
  -r, --ejecutar    Solo ejecutar archivo .mem
  -e, --completo    Pipeline completo (ensamblar + ejecutar)

Ejemplos:
  ./bin/main -e programa.asm        # Ensamblar y ejecutar
  ./bin/main -a programa.asm        # Solo ensamblar
  ./bin/main -r programa.mem        # Solo ejecutar
```

### 1. Pipeline Completo (Ensamblar + Ejecutar)

```bash
./bin/main -e asm/programa.asm
./bin/main --completo asm/programa.asm
```

### 2. Solo Ensamblar

```bash
./bin/main -a asm/programa.asm asm/programa.mem
./bin/main --ensamblar asm/programa.asm asm/programa.mem
```

Genera el archivo `asm/programa.mem` con el código máquina.

### 3. Solo Ejecutar (archivo .mem ya ensamblado)

```bash
./bin/main -r asm/programa.mem
./bin/main --ejecutar asm/programa.mem
```

---

## 🧪 Ejecutar Pruebas

### Todas las pruebas

```bash
make test
```

Salida esperada:
```
=== Ejecutando prueba: tests/test_simple.asm ===
[OUT] R0 = 30
✓ test_simple.asm: CORRECTO

=== Ejecutando prueba: tests/test_memoria.asm ===
[OUT] R2 = 40
✓ test_memoria.asm: CORRECTO

=== Ejecutando prueba: asm/programa.asm ===
[OUT] R0 = 55
✓ programa.asm: CORRECTO
```

### Pruebas individuales

```bash
make test-simple    # Suma simple: 10 + 20 = 30
make test-memoria   # CARGAR/GUARDAR: 15 + 25 = 40
make test-logico    # Y, O, NO (operaciones lógicas)
make test-programa  # Suma 1..10 = 55
```

---

## 📝 Sintaxis del Ensamblador

### Formato de Instrucción

```
MNEMONICO Rd, OPERANDO
```

- **MNEMONICO**: Instrucción en español (p.ej. `SUMAR`, `MOVI`, `SALTAR`) o inglés (p.ej. `ADD`, `MOVI`, `JMP`)
- **Rd**: Registro destino (R0-R15)
- **OPERANDO**: Inmediato (0-255), dirección de memoria, o etiqueta

**Nota**: El ensamblador acepta tanto mnemónicos en español como en inglés para compatibilidad.

### Ejemplo Básico en Español

```assembly
; Comentario: suma simple
        MOVI R0, 10     ; R0 = 10
        MOVI R1, 20     ; R1 = 20
        SUMAR R0, R1    ; R0 = R0 + R1
        ESCRIBIR R0     ; Mostrar R0
        ALTO            ; Terminar
```

### Ejemplo Básico en Inglés (compatible)

```assembly
; Comment: simple addition
        MOVI R0, 10     ; R0 = 10
        MOVI R1, 20     ; R1 = 20
        ADD R0, R1      ; R0 = R0 + R1
        OUT R0          ; Display R0
        HALT            ; Stop
```

### Uso de Etiquetas

Las etiquetas permiten saltos y bucles:

```assembly
bucle:  SUMAR R0, R1    ; Etiqueta 'bucle'
        RESTAR R2, R3
        SNZ R2, bucle   ; Saltar a 'bucle' si R2 != 0
```

Equivalente en inglés:
```assembly
loop:   ADD R0, R1      ; Label 'loop'
        SUB R2, R3
        JNZ R2, loop    ; Jump to 'loop' if R2 != 0
```

### Formato General

- **Comentarios**: Comienzan con `;`
- **Etiquetas**: Terminan con `:`
- **Directivas**: Comienzan con `.` (reservadas para futuro)
- **Números**: Decimal (`10`) o hexadecimal (`0x0A`)
- **Registros**: `R0` a `R15` (no distingue mayúsculas/minúsculas)

---

## 🎯 Ejemplos de Programas en Español

### Ejemplo Básico: Suma de Dos Números (5 + 3 = 8)

```assembly
; Programa: Suma Simple
; Descripción: Suma dos números (5 + 3)
; Resultado esperado: 8

inicio:
    MOVI R0, 5          ; R0 = 5 (primer número)
    MOVI R1, 3          ; R1 = 3 (segundo número)
    SUMAR R0, R1        ; R0 = R0 + R1 = 5 + 3 = 8
    ESCRIBIR R0         ; Mostrar resultado
    ALTO                ; Terminar programa
```

**Código máquina generado** (archivo `.mem`):
```
1005    ; MOVI R0, 5
1103    ; MOVI R1, 3
3001    ; SUMAR R0, R1
D000    ; ESCRIBIR R0
F000    ; ALTO
```

**Ejecutar:**
```bash
./bin/main -e asm/programa.asm
```

**Resultado:**
```
[SALIDA] R0 = 8 (0x0008)
[CPU] Ejecución detenida después de 5 cycles
```

### Operaciones de Memoria

```assembly
; Guardar y cargar valores de la memoria
        MOVI R0, 15
        GUARDAR R0, 100   ; MEM[100] = 15
        MOVI R1, 25
        GUARDAR R1, 101   ; MEM[101] = 25
        
        CARGAR R2, 100    ; R2 = MEM[100]
        CARGAR R3, 101    ; R3 = MEM[101]
        SUMAR R2, R3      ; R2 = 15 + 25 = 40
        ESCRIBIR R2
        ALTO
```

### Ejemplo Simple (10 + 20)

```assembly
; Suma simple
        MOVI R0, 10     ; R0 = 10
        MOVI R1, 20     ; R1 = 20
        SUMAR R0, R1    ; R0 = R0 + R1 = 30
        ESCRIBIR R0     ; Mostrar 30
        ALTO
```

---

## 📊 Estadísticas del Proyecto

- **Líneas de código**: ~2,000+ líneas (fuente + headers)
- **Instrucciones básicas**: 16 (OP_NADA a OP_ALTO)
- **Pseudo-instrucciones**: 4 (LLAMAR, RETORNAR, EMPUJAR, SACAR)
- **Registros**: 16 de propósito general (R0-R15)
- **Memoria**: 256 palabras de 16 bits (Von Neumann)
- **Stack**: Base en dirección 250, crece hacia abajo

---

## 🎓 Uso Educativo

Este simulador permite entender el flujo completo de ejecución de programas:

```
Código C → Compilador → ASM → Ensamblador → Binario → CPU → Resultado
```

Cada etapa es visible y puede ser inspeccionada, facilitando el aprendizaje de:
- Compilación y traducción de lenguajes
- Arquitectura de computadoras
- Gestión de memoria y stack
- Llamadas a funciones y convenciones
- Ciclo fetch-decode-execute

---

## 👥 Autor

**Proyecto de Seminario - Programación de Computadora**

---

## 📄 Licencia

Este proyecto es parte de un seminario educativo.

---

## 🔗 Referencias

- **Arquitectura Von Neumann**: Memoria unificada para código y datos
- **Arquitectura de registros**: RISC-like con 16 registros
- **Ensamblador de dos pasadas**: Primera pasada construye tabla de símbolos, segunda genera código
- **Ciclo Fetch-Decode-Execute**: Simulación del ciclo de instrucción de una CPU real

---

## 📚 Documentación

- **README.md** - Este archivo (guía de uso)
- **MEMORIA_TECNICA.md** - Proceso completo de desarrollo, retos y reflexiones
- **ISA_REFERENCE.md** - Referencia completa de la ISA
- **docs/presentacion_completa.html** - Presentación del proyecto

---

## 👥 Autores

Proyecto de Seminario de Programación de Computadora

---

## 🎓 Valor Educativo

Este simulador demuestra el flujo completo de ejecución de programas, desde código de alto nivel hasta instrucciones máquina. Es una herramienta didáctica que permite entender:

- Cómo los compiladores traducen código
- Cómo funcionan los ensambladores
- Cómo ejecuta instrucciones una CPU
- La importancia de las abstracciones en computación

Para detalles del proceso de desarrollo, desafíos superados y reflexiones sobre el aprendizaje, consultar **MEMORIA_TECNICA.md**.
