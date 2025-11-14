# Simulador de CPU & Ensamblador - Proyecto de Seminario

## 📋 Descripción del Proyecto

Este proyecto implementa una **computadora simulada completa** con:

1. **Simulador de CPU**: Simulador con arquitectura de registros generales
2. **Ensamblador**: Ensamblador de dos pasadas que traduce código ensamblador a código máquina
3. **ISA (Arquitectura del Conjunto de Instrucciones)**: Conjunto de instrucciones de 16 bits

### 🌟 Características Especiales

- **Lenguaje en Español (México)**: Todos los mnemónicos y comandos están en español
- **Sintaxis Natural**: Instrucciones como MOVER, SUMAR, CARGAR, SALTAR
- **Diseñado para Aprendizaje**: Ideal para estudiantes de habla hispana

### Cronograma de Desarrollo

- **✅ Semana 1**: CPU simulada básica en C
- **✅ Semana 2**: Lenguaje ensamblador en español + ensamblador
- **⏳ Semana 3**: Mini compilador C → Ensamblador
- **⏳ Semana 4**: Integración completa + programa recursivo

---

## 🏗️ Arquitectura

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

## 📚 Conjunto de Instrucciones (en Español)

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

### Instrucciones Futuras (Semanas 3-4)

```assembly
LLAMAR dir   ; Llamada a función
RETORNAR     ; Retorno de función
EMPUJAR Rd   ; Push a pila
SACAR Rd     ; Pop de pila
COMPARAR Rd, Rs  ; Comparación
MULTI Rd, Rs     ; Multiplicación
DIVIDIR Rd, Rs   ; División
```

---

## 📁 Estructura del Proyecto

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
│   └── test_factorial.asm # Factorial iterativo (preparado para recursión)
├── bin/                   # Ejecutables generados
│   ├── cpu_sim           # Programa principal
│   └── assembler         # Ensamblador standalone
├── Makefile
└── README.md
```

---

## 🚀 Compilación y Uso

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
./bin/main -a asm/programa.asm
# o usando el nombre largo:
./bin/main --ensamblar asm/programa.asm
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
./bin/main -a asm/programa.asm
./bin/main --ensamblar asm/programa.asm
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

### Suma 1 a 10 (resultado: 55)

```assembly
; Programa que suma los números del 1 al 10
        MOVI R0, 0      ; suma = 0
        MOVI R1, 1      ; i = 1
        MOVI R2, 10     ; limite = 10

bucle:  SUMAR R0, R1    ; suma += i
        MOVI R3, 1
        SUMAR R1, R3    ; i++
        MOVI R5, 11
        MOVER R6, R1
        RESTAR R6, R5
        SZ R6, fin      ; si i == 11, terminar
        SALTAR bucle

fin:    ESCRIBIR R0     ; Mostrar resultado (55)
        ALTO
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

## 🔮 Extensiones Futuras (Semanas 3-4)

### Semana 3: Compilador C → ASM

- Implementar `c_to_asm.c`
- Soportar:
  - Asignaciones: `int x = 10;`
  - Expresiones: `x = a + b * c;`
  - Condicionales: `if (x > 0) { ... }`
  - Bucles: `for`, `while`

### Semana 4: Funciones y Recursión

- Añadir instrucciones:
  - `CALL addr`: Llamada a función
  - `RET`: Retorno
  - `PUSH Rd`: Push a stack
  - `POP Rd`: Pop de stack
- Implementar:
  - Factorial recursivo
  - Fibonacci recursivo
  - Convenciones de llamada

### Diseño del Stack (ya preparado)

- **R14 (SP)**: Stack Pointer
- Stack crece hacia abajo desde 0xFF
- `CALL`: 
  ```
  MEM[SP] = PC
  SP = SP - 1
  PC = addr
  ```
- `RET`:
  ```
  SP = SP + 1
  PC = MEM[SP]
  ```

---

## 🐛 Debugging

### Ver estado de la CPU

El simulador muestra automáticamente:
- Valores de todos los registros
- PC, IR, ciclos ejecutados
- Flags (zero, carry)
- Memoria (primeras 32 palabras)

### Modo verbose (futuro)

```bash
./bin/cpu_sim -v -e programa.asm   # Modo detallado
```

---

## 📊 Estadísticas del Proyecto

- **Líneas de código**: ~1500+ líneas
- **Instrucciones soportadas**: 16 (con 10+ más planificadas)
- **Registros**: 16 de propósito general
- **Memoria**: 256 palabras de 16 bits
- **Tamaño de instrucción**: 16 bits fijos

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

## ✅ Checklist de Semana 2

- [x] Definir ISA de 16 bits
- [x] Implementar 16 instrucciones básicas
- [x] CPU con 16 registros generales
- [x] Ensamblador de dos pasadas
- [x] Soporte para etiquetas
- [x] Saltos condicionales e incondicionales
- [x] Operaciones aritméticas y lógicas
- [x] Operaciones de memoria (LOAD/STORE)
- [x] I/O básico (IN/OUT)
- [x] Programa de prueba funcional
- [x] Makefile para compilación automatizada
- [x] Suite de tests

**¡Semana 2 completada! 🎉**

Próximo objetivo: **Semana 3 - Compilador C → ASM**
