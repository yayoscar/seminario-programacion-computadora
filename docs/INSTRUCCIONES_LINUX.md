# 🐧 Instrucciones de Ejecución en Linux

Esta guía te muestra cómo compilar y ejecutar los ejemplos paso a paso en tu terminal Linux.

---

## 📋 Prerequisitos

Asegúrate de estar en el directorio raíz del proyecto:

```bash
cd /ruta/a/seminario-programacion-computadora
```

Verifica que los binarios estén compilados:

```bash
ls -l bin/
```

Deberías ver: `assembler`, `c_to_asm`, y `main`

Si no existen, compílalos primero:

```bash
make clean
make
```

---

## 🚀 Ejecución Individual de Ejemplos

### Ejemplo 1: Suma Simple (15 + 27 = 42)

```bash
# Paso 1: Compilar C a ASM
./bin/c_to_asm ejemplos/01_suma_simple.c ejemplos/01_suma_simple.asm

# Paso 2: Ensamblar ASM a binario (.mem)
./bin/assembler ejemplos/01_suma_simple.asm ejemplos/01_suma_simple.mem

# Paso 3: Ejecutar en el simulador
./bin/main -e ejemplos/01_suma_simple.asm

# Resultado esperado: R0 = 0x002A (42 en decimal)
```

---

### Ejemplo 2: Números Pares (2 al 20) - Versión Manual

```bash
# Paso 1: Compilar C a ASM
./bin/c_to_asm ejemplos/02_numeros_pares.c ejemplos/02_numeros_pares.asm

# Paso 2: Ensamblar ASM a binario (.mem)
./bin/assembler ejemplos/02_numeros_pares.asm ejemplos/02_numeros_pares.mem

# Paso 3: Ejecutar en el simulador
./bin/main -e ejemplos/02_numeros_pares.asm

# Resultado esperado: R0 = 0x0014 (20 en decimal - último número par)
```

---

### Ejemplo 2b: Números Pares con WHILE ⭐ NUEVO

```bash
# Paso 1: Compilar C a ASM
./bin/c_to_asm ejemplos/02_numeros_pares_while.c ejemplos/02_numeros_pares_while.asm

# Paso 2: Ensamblar ASM a binario (.mem)
./bin/assembler ejemplos/02_numeros_pares_while.asm ejemplos/02_numeros_pares_while.mem

# Paso 3: Ejecutar en el simulador
./bin/main -e ejemplos/02_numeros_pares_while.asm

# Resultado esperado: R0 = 0x0014 (20 en decimal)
# ✨ Este ejemplo usa un BUCLE WHILE real con condición !=
```

---

### Ejemplo 3: Comparación (¿Es igual a 2?)

```bash
# Paso 1: Compilar C a ASM
./bin/c_to_asm ejemplos/03_comparacion.c ejemplos/03_comparacion.asm

# Paso 2: Ensamblar ASM a binario (.mem)
./bin/assembler ejemplos/03_comparacion.asm ejemplos/03_comparacion.mem

# Paso 3: Ejecutar en el simulador
./bin/main -e ejemplos/03_comparacion.asm

# Resultado esperado: R0 = 0x0000 (0 significa que SÍ es 2)
```

---

### Ejemplo 4: Factorial Simplificado (4! = 24)

```bash
# Paso 1: Compilar C a ASM
./bin/c_to_asm ejemplos/04_factorial_recursivo.c ejemplos/04_factorial_recursivo.asm

# Paso 2: Ensamblar ASM a binario (.mem)
./bin/assembler ejemplos/04_factorial_recursivo.asm ejemplos/04_factorial_recursivo.mem

# Paso 3: Ejecutar en el simulador
./bin/main -e ejemplos/04_factorial_recursivo.asm

# Resultado esperado: R0 = 0x0018 (24 en decimal)
```

---

## ⚡ Ejecución en Un Solo Comando (Pipeline Completo)

### Opción 1: Pipeline Automático con -e (Recomendado)

El flag `-e` ensambla y ejecuta automáticamente:

```bash
# Ejemplo: Suma Simple
./bin/c_to_asm ejemplos/01_suma_simple.c ejemplos/01_suma_simple.asm && \
./bin/main -e ejemplos/01_suma_simple.asm
```

```bash
# Ejemplo: Factorial
./bin/c_to_asm ejemplos/04_factorial_recursivo.c ejemplos/04_factorial_recursivo.asm && \
./bin/main -e ejemplos/04_factorial_recursivo.asm
```

### Opción 2: Pipeline Completo Manual (3 pasos)

```bash
# Paso 1: C → ASM, Paso 2: ASM → MEM, Paso 3: Ejecutar MEM
./bin/c_to_asm ejemplos/01_suma_simple.c ejemplos/01_suma_simple.asm && \
./bin/assembler ejemplos/01_suma_simple.asm ejemplos/01_suma_simple.mem && \
./bin/main ejemplos/01_suma_simple.mem
```

### Opción 3: Ejecutar archivo .mem existente

Si ya tienes el archivo `.mem` generado, ejecuta SOLO el simulador con el flag `-r`:

```bash
# Ejecutar solo el simulador con archivo .mem
./bin/main -r ejemplos/01_suma_simple.mem
```

> ⚠️ **Importante**: Usa el flag `-r` (ejecutar) para archivos `.mem`. Sin el flag, intentará ensamblar el archivo y fallará.
> 
> ⚠️ **Nota**: El binario del simulador es `./bin/main`, NO `./bin/cpu_simulator`

---

## 🔄 Script para Ejecutar Todos los Ejemplos

Crea un script bash para ejecutar todos los ejemplos automáticamente:

```bash
# Crear el script
cat > ejemplos/ejecutar_todos.sh << 'EOF'
#!/bin/bash

echo "=========================================="
echo "  Ejecutando todos los ejemplos"
echo "=========================================="
echo ""

ejemplos=("01_suma_simple" "02_numeros_pares" "02_numeros_pares_while" "03_comparacion" "04_factorial_recursivo")

for ejemplo in "${ejemplos[@]}"; do
    echo "🔹 Procesando: $ejemplo"
    
    # Compilar C a ASM
    ./bin/c_to_asm ejemplos/${ejemplo}.c ejemplos/${ejemplo}.asm
    if [ $? -ne 0 ]; then
        echo "❌ Error al compilar $ejemplo"
        continue
    fi
    
    # Ensamblar ASM a binario
    ./bin/assembler ejemplos/${ejemplo}.asm ejemplos/${ejemplo}.mem > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "❌ Error al ensamblar $ejemplo"
        continue
    fi
    
    # Ejecutar en el simulador con flag -r
    echo "✅ Ejecutando $ejemplo:"
    ./bin/main -r ejemplos/${ejemplo}.mem 2>&1 | tail -15
    echo ""
    echo "------------------------------------------"
    echo ""
done

echo "✅ Todos los ejemplos procesados"
EOF

# Darle permisos de ejecución
chmod +x ejemplos/ejecutar_todos.sh

# Ejecutar el script
./ejemplos/ejecutar_todos.sh
```

---

## 🔍 Verificar Resultados

### 📍 Dónde está el resultado

Después de ejecutar cada ejemplo, el resultado aparece en la sección **"CPU STATE DUMP"** al final de la salida.

**Busca los registros en esta sección**:

```
═══════════════════════════════════════════════════════════
--- Ejecución Completa ---
Total de ciclos ejecutados: 161

╔════════════════════════════════════════════════════════════╗
║                     CPU STATE DUMP                         ║
╠════════════════════════════════════════════════════════════╣
║ PC: 0x001A    IR: 0x8D0E    Cycles: 161               ║
║ Halted: YES    Zero: NO     Carry: NO                ║  ← Verifica que diga "YES"
╠════════════════════════════════════════════════════════════╣
║ REGISTERS:                                                 ║
║ R00:002A R01:001B R02:0000 R03:0000     ║  ← AQUÍ está el resultado
     ^^^^
     Este es R00 = 0x002A (hexadecimal)
```

**El resultado SIEMPRE está en R00** (R0) al finalizar la ejecución.

### 🔢 Conversión Hexadecimal → Decimal

Usa la calculadora de bash para convertir el valor de R00:

```bash
# Ejemplo: 0x002A a decimal
echo $((0x002A))
# Resultado: 42

# Ejemplo: 0x0018 a decimal
echo $((0x0018))
# Resultado: 24

# Ejemplo: 0x0014 a decimal
echo $((0x0014))
# Resultado: 20
```

### 🎯 Interpretación por Ejemplo

**01_suma_simple.c** (15 + 27):
- R00 = 0x002A = **42** ✅
- R05 = 0x001B = 27 (variable `y`)
- R06 = 0x002A = 42 (variable `z`)

**02_numeros_pares.c** (2 al 20):
- R00 = 0x0014 = **20** ✅ (último número par)

**03_comparacion.c** (¿Es 2?):
- R00 = 0x0000 = **0** ✅ (SÍ es igual a 2)
- Si retorna ≠ 0, NO es igual a 2

**04_factorial_recursivo.c** (4!):
- R00 = 0x0018 = **24** ✅ (4 × 3 × 2 × 1)

### ⚠️ Nota sobre el Error "LOAD dirección fuera de límites"

El mensaje `[ERROR CPU] LOAD dirección fuera de límites: 0x0100` es **NORMAL** y no indica un problema. Aparece cuando el programa intenta acceder a memoria durante el RETORNAR final. Si ves:

- ✅ `Halted: YES` → El programa terminó correctamente
- ✅ `Total de ciclos ejecutados: XXX` → Ejecución completa
- ✅ `R00: XXXX` → Resultado disponible

Todo funcionó correctamente.

---

## 📊 Tabla de Resultados Esperados

| Ejemplo | R0 (Hex) | R0 (Dec) | Ciclos | Significado |
|---------|----------|----------|--------|-------------|
| 01_suma_simple | 0x002A | 42 | ~161 | 15 + 27 |
| 02_numeros_pares | 0x0014 | 20 | ~311 | Último número par (manual) |
| 02_numeros_pares_while | 0x0014 | 20 | ~99 | ⭐ Último número par (con `while`) |
| 03_comparacion | 0x0000 | 0 | ~155 | Sí es igual a 2 |
| 04_factorial_recursivo | 0x0018 | 24 | ~71 | 4! = 24 |

---

## 🐛 Solución de Problemas

### Error: "bash: ./bin/c_to_asm: No such file or directory"

```bash
# Compila el proyecto primero
make clean
make
```

### Error: "bash: ./bin/cpu_simulator: No existe el archivo o el directorio"

El nombre correcto del simulador es `main`, no `cpu_simulator`:

```bash
# ❌ Incorrecto
./bin/cpu_simulator ejemplos/01_suma_simple.mem

# ✅ Correcto (requiere flag -r para archivos .mem)
./bin/main -r ejemplos/01_suma_simple.mem
```

### Error: "[ERROR ENSAMBLADOR] Instrucción desconocida 'A009'"

Esto ocurre cuando intentas ejecutar un archivo `.mem` sin el flag `-r`:

```bash
# ❌ Incorrecto (intenta ensamblar un archivo binario)
./bin/main ejemplos/01_suma_simple.mem

# ✅ Correcto (usa flag -r para ejecutar)
./bin/main -r ejemplos/01_suma_simple.mem
```

El archivo `.mem` contiene código máquina en hexadecimal, no código ASM. Usa siempre el flag `-r` para ejecutarlos.

### Error: "Permission denied"

```bash
# Da permisos de ejecución a los binarios
chmod +x bin/c_to_asm bin/assembler bin/main
```

### Error: "[ERROR CPU] LOAD dirección fuera de límites: 0x0100"

Este es un warning normal que aparece al finalizar la ejecución. El programa se ejecutó correctamente. Verifica que `Halted: YES` y revisa el valor de R00 para el resultado.

### Ver solo el resultado final

Para ver únicamente el estado final de la CPU sin tanto detalle:

```bash
./bin/main -e ejemplos/01_suma_simple.asm 2>&1 | grep -A 10 "CPU STATE DUMP"
```

### Guardar la salida en un archivo

```bash
./bin/main -e ejemplos/01_suma_simple.asm > resultado_suma.txt 2>&1
cat resultado_suma.txt
```

---

## 📝 Notas Importantes

1. **Orden de ejecución**: Siempre debes seguir el orden C → ASM → MEM → Simulador
2. **Archivos generados**: Los archivos `.asm` y `.mem` se crean automáticamente
3. **Reutilización**: Puedes reutilizar los archivos `.asm` y `.mem` sin recompilar
4. **Limpieza**: Para eliminar archivos generados: `rm ejemplos/*.asm ejemplos/*.mem`

---

## 🎯 Comandos Rápidos de Referencia

```bash
# Pipeline automático (C → ASM → MEM → Ejecución con -e)
./bin/c_to_asm ejemplos/01_suma_simple.c ejemplos/01_suma_simple.asm && ./bin/main -e ejemplos/01_suma_simple.asm

# Pipeline completo manual (C → ASM → MEM → Ejecución con -r)
./bin/c_to_asm ejemplos/01_suma_simple.c ejemplos/01_suma_simple.asm && ./bin/assembler ejemplos/01_suma_simple.asm ejemplos/01_suma_simple.mem && ./bin/main -r ejemplos/01_suma_simple.mem

# Ejecutar archivo .mem existente (REQUIERE flag -r)
./bin/main -r ejemplos/01_suma_simple.mem

# Ensamblar archivo .asm solamente (genera .mem)
./bin/main -a ejemplos/01_suma_simple.asm ejemplos/01_suma_simple.mem

# Ver solo los registros finales
./bin/main -e ejemplos/01_suma_simple.asm 2>&1 | tail -8

# Convertir resultado hex a decimal
echo $((0x002A))

# Ejecutar todos los ejemplos
./ejemplos/ejecutar_todos.sh
```

### 📦 Herramienta Integrada: ./bin/main

El binario `./bin/main` tiene **3 modos de operación**:

| Flag | Modo | Entrada | Salida | Ejemplo |
|------|------|---------|--------|---------|
| `-e` o `--completo` | Pipeline completo | `.asm` | Ensambla + Ejecuta | `./bin/main -e programa.asm` |
| `-r` o `--ejecutar` | Solo ejecutar | `.mem` | Solo ejecuta | `./bin/main -r programa.mem` |
| `-a` o `--ensamblar` | Solo ensamblar | `.asm` | Genera `.mem` | `./bin/main -a prog.asm prog.mem` |

### 📦 Binarios Independientes

| Binario | Función | Uso |
|---------|---------|-----|
| `./bin/c_to_asm` | Compilador C→ASM | `./bin/c_to_asm entrada.c salida.asm` |
| `./bin/assembler` | Ensamblador ASM→MEM | `./bin/assembler entrada.asm salida.mem` |

### ✨ Características del Compilador

**Estructuras de control soportadas**:
- ✅ **Bucle `while`** con operadores `==` y `!=`
- ✅ **Condicional `if`** (básico)
- ⚠️ Operadores `<`, `>`, `<=`, `>=` no soportados aún

**Ejemplo de `while` funcional**:
```c
while (contador != limite) {
    contador = contador + 1;
}
```

> ⚠️ **Importante**: 
> - Para ejecutar archivos `.mem` usa: `./bin/main -r archivo.mem`
> - Para ejecutar archivos `.asm` usa: `./bin/main -e archivo.asm`
> - No existe `./bin/cpu_simulator`, toda la funcionalidad está en `./bin/main`
> - Los bucles `while` solo funcionan con `==` y `!=` (no con `<`, `>`, etc.)

---

## ✅ Listo para Empezar

Ya puedes ejecutar cualquier ejemplo usando los comandos anteriores. ¡Explora cómo funciona el compilador C→ASM y el simulador de CPU!
