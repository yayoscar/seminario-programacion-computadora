# Simulador de CPU con Pipeline Completo

## 🚀 Inicio Rápido

### Linux / macOS
```bash
# 1. Clonar o descargar el proyecto
git clone <repo-url>
cd seminario-programacion-computadora

# 2. Compilar
make

# 3. Ejecutar un ejemplo
./bin/main -e asm/programa.asm
```

### Windows (WSL - Recomendado)
```bash
# En WSL Ubuntu
sudo apt-get install build-essential
make
./bin/main -e asm/programa.asm
```

### Windows (MinGW/MSYS2)
```cmd
REM En CMD o PowerShell
mingw32-make
bin\main.exe -e asm\programa.asm
```

---

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
- ✅ **Estructuras de control** - Bucles `while` con operadores `==` y `!=`
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

## 💻 Requisitos del Sistema

### Linux
- **Compilador**: GCC o Clang
- **Build tools**: Make
- **Sistema**: Cualquier distribución moderna

```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# Fedora/RHEL
sudo dnf install gcc make

# Arch
sudo pacman -S base-devel
```

### macOS
- **Xcode Command Line Tools**
```bash
xcode-select --install
```
- Alternativamente: Homebrew + GCC
```bash
brew install gcc make
```

### Windows
**Opción 1: WSL (Recomendado)**
```powershell
# En PowerShell como administrador
wsl --install
# Reiniciar, luego dentro de WSL:
sudo apt-get update && sudo apt-get install build-essential
```

**Opción 2: MinGW-w64**
- Descargar de: https://www.mingw-w64.org/
- Instalar y agregar `bin/` al PATH de Windows
- Usar `mingw32-make` en lugar de `make`

**Opción 3: MSYS2**
- Descargar de: https://www.msys2.org/
- Instalar paquetes:
```bash
pacman -S mingw-w64-x86_64-gcc make
```

---

## 🔧 Compilación

### Compilar todo el proyecto

**Linux / macOS / WSL:**
```bash
cd /ruta/al/proyecto
make
```

**Windows (PowerShell con MinGW):**
```powershell
cd C:\ruta\al\proyecto
mingw32-make
```

**Windows (MSYS2 bash):**
```bash
cd /c/ruta/al/proyecto
make
```

**Salida esperada:**
```
✓ Main program compiled 
✓ Assembler compiled 
✓ C to ASM compiler compiled 
✓ Build complete!
```

### Limpiar archivos generados

```bash
make clean
```

---

## 🚀 Pipeline Completo: C → ASM → Binario → CPU

Este proyecto implementa el **flujo completo** desde código de alto nivel hasta ejecución en CPU:

### Ejemplo 1: Función Simple (Suma)

#### Paso 1: Escribir código C

Archivo `tests/test_c_simple_func.c`:
```c
int suma(int a, int b) {
    return a + b;
}

int main() {
    int x = 5;
    int y = 3;
    int z = suma(x, y);
    return z;
}
```

#### Paso 2: Compilar C → Ensamblador

```bash
./bin/c_to_asm tests/test_c_simple_func.c tests/test_c_simple_func.asm
```

Genera `test_c_simple_func.asm` con código ensamblador:
```assembly
func_suma:
    CARGAR R0, 248        ; Cargar param a
    CARGAR R1, 249        ; Cargar param b
    SUMAR R0, R1          ; a + b
    GUARDAR R0, 250       ; Guardar retorno
    RETORNAR              ; Regresar

func_main:
    MOVI R4, 5            ; int x = 5
    MOVI R5, 3            ; int y = 3
    GUARDAR R4, 248       ; Pasar param 1
    GUARDAR R5, 249       ; Pasar param 2
    LLAMAR func_suma      ; Llamar función
    CARGAR R6, 250        ; z = retorno
    MOVER R0, R6          ; return z
    RETORNAR

inicio:
    SALTAR func_main      ; Punto de entrada
    ALTO
```

#### Paso 3: Ensamblar ASM → Binario

```bash
./bin/assembler tests/test_c_simple_func.asm tests/test_c_simple_func.mem
```

Genera `test_c_simple_func.mem` con código máquina:
```
A009    ; SALTAR func_main (expandido)
F000    ; ALTO
80F8    ; CARGAR R0, 248
91F9    ; CARGAR R1, 249
3001    ; SUMAR R0, R1
90FA    ; GUARDAR R0, 250
...     ; RETORNAR (expandido a 4 instrucciones)
```

#### Paso 4: Ejecutar en CPU Simulada

```bash
./bin/cpu_simulator tests/test_c_simple_func.mem
```

Resultado:
```
[CPU] Programa cargado: 30 instrucciones
[CPU] Iniciando ejecución...
[CPU] R6 = 0x0008  (z = suma(5,3) = 8)
[CPU] Ejecución completada en 161 ciclos
```

---

### Ejemplo 2: Bucle While Funcional ⭐

#### Código C con `while`

Archivo `ejemplos/02_numeros_pares_while.c`:
```c
int main() {
    int contador;
    int resultado;
    int dos;
    
    contador = 2;
    dos = 2;
    resultado = 0;
    
    // Bucle while con operador !=
    while (contador != 22) {
        resultado = contador;
        contador = contador + dos;
    }
    
    return resultado;  // Retorna 20
}
```

#### Compilar y Ejecutar

```bash
# Pipeline completo
./bin/c_to_asm ejemplos/02_numeros_pares_while.c ejemplos/02_numeros_pares_while.asm && \
./bin/main -e ejemplos/02_numeros_pares_while.asm
```

**Resultado**: R0 = 0x0014 (20 decimal) en 99 ciclos ✅

---

### Ejemplo 3: Función con Operaciones Aritméticas

#### Paso 1: Código C

Archivo `tests/test_c_multiply10.c`:
```c
// TEST: Multiplicar por 10 usando solo sumas
int test_if(int x) {
    int resultado;
    
    resultado = 0;
    
    // Calcular x * 10 mediante sumas sucesivas
    resultado = x;
    resultado = resultado + resultado;  // x * 2
    resultado = resultado + resultado;  // x * 4
    resultado = resultado + x;          // x * 5
    resultado = resultado + resultado;  // x * 10
    
    return resultado;
}

int main() {
    int n;
    int result;
    
    n = 5;
    result = test_if(n);  // Debería retornar 50
    
    return 0;
}
```

#### Paso 2: Compilar C → ASM

```bash
./bin/c_to_asm tests/test_c_multiply10.c tests/test_c_multiply10.asm
```

Genera código ensamblador con múltiples operaciones aritméticas:
```assembly
; Punto de entrada: saltar a main()
SALTAR func_main

; Función: test_if(int x)
func_test_if:
; Variable 'x' -> R0 (param)
; Variable 'resultado' -> R4
MOVI R4, 0  ; Inicializar resultado = 0

; resultado = x
MOVER R4, R0

; resultado = resultado + resultado  (x * 2)
SUMAR R4, R4

; resultado = resultado + resultado  (x * 4)
SUMAR R4, R4

; resultado = resultado + x  (x * 5)
SUMAR R4, R0

; resultado = resultado + resultado  (x * 10)
SUMAR R4, R4

; return resultado
MOVER R0, R4
RETORNAR

; Función: main()
func_main:
; Variable 'n' -> R4
MOVI R4, 0  ; Inicializar n = 0
; Variable 'result' -> R5
MOVI R5, 0  ; Inicializar result = 0
MOVI R4, 5  ; n = 5

; Llamar test_if(n)
MOVER R0, R4
LLAMAR func_test_if
MOVER R5, R0  ; Guardar resultado

; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR

ALTO  ; Fin del programa
```

#### Paso 3: Ensamblar ASM → Binario

```bash
./bin/assembler tests/test_c_multiply10.asm tests/test_c_multiply10.mem
```

Genera archivo `.mem` con instrucciones máquina. Las pseudo-instrucciones LLAMAR y RETORNAR se expanden:

- **LLAMAR func_test_if** → 5 instrucciones (guardar contexto + salto)
- **RETORNAR** → 4 instrucciones (restaurar contexto + salto de regreso)

#### Paso 4: Ejecutar en CPU

```bash
./bin/main -r tests/test_c_multiply10.mem
```

**Resultado esperado:**
```
[CPU] Programa cargado: ~35 instrucciones
[CPU] Iniciando ejecución...
[CPU] R5 = 0x0032  (50 en decimal: 5 * 10)
[CPU] Ejecución completada en ~167 ciclos
```

#### Pipeline Completo en Un Solo Paso

```bash
# Compilar + Ensamblar + Ejecutar
./bin/c_to_asm tests/test_c_multiply10.c tests/test_c_multiply10.asm && \
./bin/main -e tests/test_c_multiply10.asm
```

**Salida:**
```
[CPU] test_if(5) = 50 ✓
[CPU] Resultado: R5 = 0x0032 (50 decimal)
[CPU] Total de ciclos: 167
[CPU] Operaciones aritméticas validadas ✓
```

---

### Observaciones sobre Operaciones Aritméticas

**Características demostradas:**
- ✅ **Llamadas a funciones**: test_if(n) con paso de parámetros
- ✅ **Gestión de stack**: Guarda/restaura contexto automáticamente
- ✅ **Operaciones en secuencia**: Múltiples sumas para lograr multiplicación
- ✅ **Variables locales**: Uso de registros para variables temporales
- ✅ **Optimización manual**: x*10 mediante x*2→x*4→x*5→x*10

**Expansión de pseudo-instrucciones:**
- Cada `LLAMAR` se convierte en 5 instrucciones máquina
- Cada `RETORNAR` se convierte en 4 instrucciones máquina
- El código final tiene ~35 instrucciones expandidas

**Técnica de multiplicación:**
- `x * 2` = `x + x`
- `x * 4` = `(x * 2) + (x * 2)`
- `x * 5` = `(x * 4) + x`
- `x * 10` = `(x * 5) + (x * 5)`
- Total: 4 sumas para multiplicar por 10

### Pipeline Automático (Un Solo Comando)

**Linux / macOS / WSL:**
```bash
# Desde archivo C
./bin/c_to_asm tests/test_c_simple_func.c /tmp/temp.asm && \
./bin/main -e /tmp/temp.asm

# Desde archivo ASM
./bin/main -e tests/test_c_simple_func.asm
```

**Windows (CMD):**
```cmd
REM Desde archivo ASM
bin\main.exe -e tests\test_c_simple_func.asm
```

**Windows (PowerShell):**
```powershell
# Desde archivo C
.\bin\c_to_asm.exe tests\test_c_simple_func.c temp.asm; .\bin\main.exe -e temp.asm

# Desde archivo ASM
.\bin\main.exe -e tests\test_c_simple_func.asm
```

---

## 📖 Guía de Ejecución por Plataforma

### Linux

```bash
# 1. Compilar el proyecto
make

# 2. Ejecutar pipeline completo (ejemplo)
./bin/main -e asm/programa.asm

# 3. Solo ensamblar
./bin/assembler asm/programa.asm asm/programa.mem

# 4. Solo ejecutar
./bin/cpu_simulator asm/programa.mem

# 5. Compilar C a ASM
./bin/c_to_asm tests/test_c_simple_func.c tests/output.asm
```

### macOS

```bash
# Idéntico a Linux
make
./bin/main -e asm/programa.asm
```

### Windows (WSL) - Recomendado

```bash
# Dentro de WSL (Ubuntu), igual que Linux
cd /mnt/c/Users/TuUsuario/proyecto
make
./bin/main -e asm/programa.asm
```

### Windows (Nativo con MinGW)

```cmd
REM 1. Compilar
mingw32-make

REM 2. Ejecutar pipeline completo
bin\main.exe -e asm\programa.asm

REM 3. Solo ensamblar
bin\assembler.exe asm\programa.asm asm\programa.mem

REM 4. Solo ejecutar
bin\cpu_simulator.exe asm\programa.mem

REM 5. Compilar C a ASM
bin\c_to_asm.exe tests\test_c_simple_func.c tests\output.asm
```

### Windows (PowerShell)

```powershell
# 1. Compilar
mingw32-make

# 2. Ejecutar pipeline completo
.\bin\main.exe -e asm\programa.asm

# 3. Compilar C a ASM
.\bin\c_to_asm.exe tests\test_c_simple_func.c tests\output.asm
```

### Troubleshooting

**Linux/macOS:**
- Si `make` falla: verificar que GCC esté instalado con `gcc --version`
- Permisos: `chmod +x bin/*`

**Windows:**
- Si los .exe no se encuentran: verificar que MinGW esté en el PATH
- En PowerShell: usar `.\bin\` en lugar de `bin\`
- Error de compilación: verificar que `gcc` y `make` estén disponibles

---

## 🌟 PLUS: Compilador Bilingüe (C Español)

### Característica Especial

Nuestro compilador soporta **sintaxis C en ESPAÑOL**, permitiendo escribir código con palabras clave en nuestro idioma:

**Palabras clave soportadas:**

| Inglés | Español | Uso |
|--------|---------|-----|
| `int` | `entero` | Tipo de datos |
| `return` | `retornar` | Retorno de función |
| `if` | `si` | Condicional |
| `while` | `mientras` | Bucle |
| `for` | `para` | Bucle con contador |

### Ejemplo en C Español

Archivo `tests/test_ces_main_only.c`:
```c
// C Español (CES)
entero main() {
    entero resultado = 42;
    retornar resultado;
}
```

### Compilar C Español → ASM → CPU

```bash
# Paso 1: C Español → ASM
./bin/c_to_asm tests/test_ces_main_only.c tests/test_ces_main_only.asm

# Paso 2: Pipeline completo (ASM → Binario → CPU)
./bin/main -e tests/test_ces_main_only.asm
```

**Resultado:**
```
[CPU] R0 = 0x002A  (42 en decimal)
[CPU] Ejecución completada en 41 ciclos
```

### Ejemplos Disponibles

| Test en Español | Descripción | Características | Ciclos |
|-----------------|-------------|-----------------|--------|
| `test_ces_main_only.c` | Programa simple (solo main) | Variables, asignaciones | 77 |
| `test_ces_simple_func.c` | Función suma con parámetros | Funciones, llamadas | 161 |
| `test_ces_function.c` | Función duplicar valor | Parámetros | 137 |
| `test_ces_factorial.c` | Función factorial simplificada | Funciones | 137 |
| `test_ces_fibonacci.c` | Función fibonacci simplificada | Funciones | 137 |
| `test_ces_if.c` | Condicional con `si` | **if/si** | 65 |
| `test_ces_while.c` | Bucle con `mientras` | **while/mientras** | 53 |
| `test_ces_for.c` | Bucle con `para` | **for/para** | 53 |

**Total**: 8 tests completos

**Validación**: Todos los tests compilan y ejecutan correctamente en el pipeline completo ✓

### Notas sobre C Español

- ✅ **Soportado**: `entero`, `retornar`, `si`, `mientras`, `para`
- ✅ **Estructuras de control**: Condicionales y bucles completos
- ✅ **Validado**: 8 tests funcionales con todas las características
- ⚠️ **Limitación**: Expresiones simples (sin operadores complejos anidados)
- 🎯 **Objetivo**: Didáctico, para entender compiladores sin barrera del idioma

---

## 🔧 Uso de las Herramientas

### Ejecutar Tests

**Linux / macOS / WSL:**
```bash
make test
```

**Windows (CMD/PowerShell):**
```cmd
mingw32-make test
```

### Ejemplos Rápidos por Plataforma

**Linux / macOS:**
```bash
# Pipeline completo
./bin/main -e asm/programa.asm

# Solo ensamblar
./bin/main -a asm/programa.asm asm/programa.mem

# Solo ejecutar
./bin/main -r asm/programa.mem
```

**Windows:**
```cmd
REM Pipeline completo
bin\main.exe -e asm\programa.asm

REM Solo ensamblar
bin\main.exe -a asm\programa.asm asm\programa.mem

REM Solo ejecutar
bin\main.exe -r asm\programa.mem
```

---

## 📖 Opciones de Línea de Comandos

El programa principal (`main`) acepta las siguientes opciones:

### Opciones de Línea de Comandos

**Ayuda:**
```bash
# Linux/macOS
./bin/main -h

# Windows
bin\main.exe -h
```

**Opciones disponibles:**
```
-h, --ayuda       Mostrar ayuda
-a, --ensamblar   Solo ensamblar (genera .mem)
-r, --ejecutar    Solo ejecutar archivo .mem
-e, --completo    Pipeline completo (ensamblar + ejecutar)
```

### Ejemplos de Uso

**1. Pipeline Completo (Ensamblar + Ejecutar)**

Linux/macOS:
```bash
./bin/main -e asm/programa.asm
```

Windows:
```cmd
bin\main.exe -e asm\programa.asm
```

**2. Solo Ensamblar**

Linux/macOS:
```bash
./bin/main -a asm/programa.asm asm/programa.mem
```

Windows:
```cmd
bin\main.exe -a asm\programa.asm asm\programa.mem
```

**3. Solo Ejecutar (archivo .mem ya ensamblado)**

Linux/macOS:
```bash
./bin/main -r asm/programa.mem
```

Windows:
```cmd
bin\main.exe -r asm\programa.mem
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
