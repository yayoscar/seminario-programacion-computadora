# 📚 Ejemplos de Programas en C

Esta carpeta contiene **5 ejemplos progresivos** que demuestran las capacidades del compilador C→ASM, incluyendo **estructuras de control funcionales** (`while`).

## 📋 Lista de Ejemplos

### 01_suma_simple.c
**Concepto**: Operaciones básicas y llamadas a funciones

**Descripción**: Suma dos números (15 + 27 = 42)

**Características demostradas**:
- ✅ Declaración de variables
- ✅ Asignaciones simples
- ✅ Definición de funciones
- ✅ Llamadas a funciones con parámetros
- ✅ Retorno de valores

**Cómo ejecutar**:
```bash
# Compilar C → ASM
./bin/c_to_asm ejemplos/01_suma_simple.c ejemplos/01_suma_simple.asm

# Ensamblar + Ejecutar
./bin/main -e ejemplos/01_suma_simple.asm
```

**Resultado esperado**:
```
R5 = 0x002A (42 en decimal)
```

---

### 02_numeros_pares.c
**Concepto**: Iteraciones y contadores

**Descripción**: Genera números pares del 2 al 20

**Características demostradas**:
- ✅ Bucles desenrollados (sin while/for por limitación)
- ✅ Contadores e incrementos
- ✅ Operaciones repetitivas
- ✅ Variables temporales

**Cómo ejecutar**:
```bash
./bin/c_to_asm ejemplos/02_numeros_pares.c ejemplos/02_numeros_pares.asm
./bin/main -e ejemplos/02_numeros_pares.asm
```

**Resultado esperado**:
```
R4 = 0x0014 (20 en decimal - último número par)
```

**Nota**: Este ejemplo desenrolla el bucle manualmente. Ver `02_numeros_pares_while.c` para la versión con bucle `while` funcional.

---

### 02_numeros_pares_while.c ⭐ NUEVO
**Concepto**: Estructuras de control - Bucle `while`

**Descripción**: Genera números pares del 2 al 20 usando un **bucle `while` real**

**Características demostradas**:
- ✅ **Bucle `while`** con condición `!=`
- ✅ **Saltos condicionales** (`SZ` - saltar si cero)
- ✅ **Etiquetas** (`while_1`, `endwhile_1`)
- ✅ **Comparación funcional** con operador `!=`
- ✅ **Iteración automática** sin desenrollar

**Cómo ejecutar**:
```bash
./bin/c_to_asm ejemplos/02_numeros_pares_while.c ejemplos/02_numeros_pares_while.asm
./bin/main -e ejemplos/02_numeros_pares_while.asm
```

**Resultado esperado**:
```
R0 = 0x0014 (20 en decimal)
Total de ciclos: 99
```

**Código del bucle**:
```c
while (contador != 22) {
    resultado = contador;
    contador = contador + dos;
}
```

**ASM generado**:
```asm
while_1:  ; while (contador != 22)
MOVI R15, 22
MOVER R14, R4
RESTAR R14, R15
MOVER R15, R14
SZ R15, endwhile_1  ; Saltar si contador == 22
MOVER R5, R4  ; resultado = contador
SUMAR R4, R6  ; contador = contador + dos
SALTAR while_1
endwhile_1:
```

---

### 03_comparacion.c
**Concepto**: Comparaciones usando aritmética

**Descripción**: Verifica si un número es igual a 2

**Características demostradas**:
- ✅ Comparaciones mediante restas
- ✅ Lógica condicional implícita
- ✅ Funciones de verificación

**Cómo ejecutar**:
```bash
./bin/c_to_asm ejemplos/03_comparacion.c ejemplos/03_comparacion.asm
./bin/main -e ejemplos/03_comparacion.asm
```

**Resultado esperado**:
```
R5 = 0x0000 (0 significa que el número era 2)
```

**Lógica**:
- Si `x == 2`, entonces `(x - 2) == 0`
- Resultado 0 → número es 2
- Resultado ≠ 0 → número no es 2

---

### 02_numeros_pares_while.c
**Concepto**: Estructuras de control - Bucle `while`

**Descripción**: Genera números pares del 2 al 20 usando un bucle `while`

**Características demostradas**:
- ✅ **Bucle while**: Iteración con condición `!=`
- ✅ **Comparación**: Operador `!=` funcional
- ✅ **Contador automático**: Incremento dentro del bucle
- ✅ **Saltos condicionales**: `SZ` (saltar si cero)
- ✅ **Etiquetas**: `while_X` y `endwhile_X`

**Cómo ejecutar**:
```bash
./bin/c_to_asm ejemplos/02_numeros_pares_while.c ejemplos/02_numeros_pares_while.asm
./bin/main -e ejemplos/02_numeros_pares_while.asm
```

**Resultado esperado**:
```
R0 = 0x0014 (20 en decimal)
Último número par generado
Total de ciclos: ~99
```

**Código del bucle**:
```c
while (contador != 22) {
    resultado = contador;
    contador = contador + dos;
}
```

---

### 04_factorial_recursivo.c
**Concepto**: Cálculo matemático paso a paso

**Descripción**: Calcula factorial(4) = 24 usando únicamente sumas

**Características demostradas**:
- ✅ **Aritmética básica**: Multiplicación mediante sumas repetidas
- ✅ **Optimización manual**: Duplicación con `resultado + resultado`
- ✅ **Cálculo paso a paso**: 4 → 12 → 24
- ✅ **Sin funciones auxiliares**: Todo en `main()`
- ✅ **Sin recursión**: Evita llamadas anidadas

**Cómo ejecutar**:
```bash
./bin/c_to_asm ejemplos/04_factorial_recursivo.c ejemplos/04_factorial_recursivo.asm
./bin/main -e ejemplos/04_factorial_recursivo.asm
```

**Resultado esperado**:
```
R0 = 0x0018 (24 en decimal)
factorial(4) = 4! = 4 × 3 × 2 × 1 = 24
```

**Cálculo paso a paso**:
- Inicio: resultado = 4
- 4 × 3: resultado + resultado + 4 = 12
- 12 × 2: resultado + resultado = 24
- Total: 71 ciclos de ejecución

---

## 🚀 Ejecución Rápida de Todos los Ejemplos

### Linux / macOS / WSL:
```bash
# Ejecutar todos los ejemplos
for ejemplo in ejemplos/*.c; do
    nombre=$(basename "$ejemplo" .c)
    echo "=== Ejecutando $nombre ==="
    ./bin/c_to_asm "$ejemplo" "ejemplos/${nombre}.asm"
    ./bin/main -e "ejemplos/${nombre}.asm"
    echo ""
done
```

### Windows (PowerShell):
```powershell
Get-ChildItem ejemplos\*.c | ForEach-Object {
    $nombre = $_.BaseName
    Write-Host "=== Ejecutando $nombre ==="
    .\bin\c_to_asm.exe "ejemplos\$($_.Name)" "ejemplos\${nombre}.asm"
    .\bin\main.exe -e "ejemplos\${nombre}.asm"
    Write-Host ""
}
```

---

## 📊 Tabla Comparativa

| Archivo | LOC | Funciones | Bucles | Recursión | Complejidad | Ciclos |
|---------|-----|-----------|--------|-----------|-------------|--------|
| 01_suma_simple | 18 | 2 | No | No | Baja | ~161 |
| 02_numeros_pares | 56 | 1 | No (desenrollado) | No | Media | ~311 |
| 02_numeros_pares_while | 25 | 1 | **Sí (while)** | No | Media | ~99 |
| 03_comparacion | 22 | 2 | No | No | Baja | ~155 |
| 04_factorial_recursivo | 26 | 1 | No | No | Baja | ~71 |

---

## 🎯 Progresión Didáctica

Los ejemplos están ordenados pedagógicamente:

1. **Suma Simple** → Fundamentos: variables, funciones, retornos
2. **Números Pares** → Repetición manual: bucles desenrollados, contadores
3. **Números Pares (While)** → ⭐ **Bucle `while` funcional con `!=`**
4. **Comparación** → Lógica: verificación mediante aritmética
5. **Factorial** → Cálculo: multiplicación con sumas

---

## ✨ Estructuras de Control Soportadas

### ✅ Bucle `while` FUNCIONAL

El compilador **SÍ soporta** bucles `while` con operadores `==` y `!=`:

```c
// ✅ FUNCIONA - Operador !=
while (contador != limite) {
    contador = contador + 1;
}

// ✅ FUNCIONA - Operador ==
while (x == 0) {
    x = funcion();
}

// ⚠️ NO SOPORTADO - Operadores <, >, <=, >=
while (contador < limite) {  // Requiere instrucciones SMENOR/SMAYOR
    contador = contador + 1;
}
```

**Código ASM generado por `while`**:
```asm
while_1:  ; Etiqueta de inicio del bucle
MOVI R15, 22  ; Cargar valor de comparación
MOVER R14, R4  ; Copiar variable a comparar
RESTAR R14, R15  ; Realizar resta
MOVER R15, R14  ; Resultado en R15
SZ R15, endwhile_1  ; Saltar si resultado == 0 (condición falsa)
; ... cuerpo del bucle ...
SALTAR while_1  ; Volver al inicio
endwhile_1:  ; Etiqueta de salida
```

### ⚠️ Condicional `if` (Básico)

El `if` está detectado pero con funcionalidad limitada. Usar aritmética para comparaciones simples.

---

## 💡 Notas sobre Otras Limitaciones

### Multiplicación
No hay instrucción de multiplicación en el ISA, por eso:
- Se implementa mediante sumas repetidas
- Ejemplo: `3 * 4 = 4 + 4 + 4 = 12`

### Limitación 3: Arrays e I/O
- No hay soporte para arrays
- I/O limitado a registro final
- Los "prints" se ven en el dump de registros

---

## 🔍 Cómo Verificar Resultados

Después de ejecutar, revisa el **CPU STATE DUMP**:

```
╔════════════════════════════════════════════════════════════╗
║                     CPU STATE DUMP                         ║
╠════════════════════════════════════════════════════════════╣
║ REGISTERS:                                                 ║
║ R00:0000 R01:0000 R02:0000 R03:0000     ║
║ R04:0018 R05:0018 R06:0000 R07:0000     ← Aquí está el resultado
║ ...
╚════════════════════════════════════════════════════════════╝
```

- **R5** generalmente contiene el resultado de `main()`
- Valor en **hexadecimal** (0x0018 = 24 decimal)
- Verificar que coincide con el esperado

---

## 📖 Documentación Adicional

Para más información sobre el proyecto completo, consulta:
- **README.md** (raíz del proyecto) - Guía completa
- **MEMORIA_TECNICA.md** - Proceso de desarrollo
- **ISA_REFERENCE.md** - Conjunto de instrucciones

---

## 🎓 Valor Educativo

Estos ejemplos demuestran:

✅ **Progresión gradual** de conceptos (simple → complejo)  
✅ **Recursión funcional** sin necesidad de if explícito  
✅ **Transformación C → ASM** visible en cada paso  
✅ **Stack management** en acción  
✅ **Limitaciones reales** de compiladores simples  

Ideal para entender cómo funciona un compilador desde dentro.
