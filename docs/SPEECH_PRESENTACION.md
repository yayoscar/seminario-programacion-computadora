# Speech de Presentación - Simulador de CPU
## Pipeline Completo: C → Ensamblador → Máquina

**Duración: 5 minutos**  
**Presentador: [Nombre]**  
**Fecha: 22 de noviembre de 2025**

---

## INTRODUCCIÓN (20 segundos)

Buenos días a todos. Hoy les presento nuestro proyecto del Seminario de Programación de Computadoras: un **simulador de CPU completo** con pipeline C→ASM→Máquina.

En las semanas 1 y 2 construimos la arquitectura Von Neumann y el ISA en español. Ahora me enfocaré en las semanas 3 y 4 donde todo se integra.

---

## SEMANA 3: LENGUAJES DE ALTO NIVEL (2 minutos)

Esta es la parte más ambiciosa: crear un **compilador de C a ensamblador**.

Este compilador traduce código C real a nuestro lenguaje ensamblador. Las capacidades implementadas son:

**Características del lenguaje:**
- Declaraciones de tipo `int`
- Operaciones aritméticas: suma y resta
- Estructuras de control: `if/else`, `while`, `for`
- Funciones con parámetros y retorno de valores
- Gestión automática del stack para llamadas anidadas

**El pipeline de compilación tiene 4 etapas:**
1. **Parsing**: Análisis léxico y sintáctico del código C
2. **Generación de ASM**: Traducción a nuestro ensamblador
3. **Ensamblado**: Conversión a código máquina binario
4. **Ejecución**: Simulación en la CPU virtual

**Gestión de registros inteligente:**
- R0-R3: parámetros de función
- R4-R11: variables locales (máximo 8)
- R12: registro temporal para operaciones
- R13: usado por LLAMAR para direcciones de retorno
- R14: stack pointer
- R15: registro de flags para comparaciones

**Y aquí está nuestra innovación principal**: soporte **bilingüe único**.

El compilador acepta sintaxis en **inglés** y en **español** simultáneamente:
- `int` ↔ `entero`
- `if` ↔ `si`
- `while` ↔ `mientras`
- `for` ↔ `para`
- `return` ↔ `retornar`

Esto elimina la barrera del idioma. Los estudiantes pueden escribir:
```c
entero factorial(entero n) {
    si (n <= 1) retornar 1;
    retornar n * factorial(n - 1);
}
```

O en inglés tradicional. **El compilador entiende ambos**.

Esto permite que los estudiantes se enfoquen en **aprender conceptos de programación**, no en memorizar vocabulario en inglés.

---

## SEMANA 4: INTEGRACIÓN Y VALIDACIÓN (1 minuto 30 segundos)

En la semana final integramos todo el sistema y creamos una **suite de pruebas exhaustiva**.

Tenemos **18 tests** que validan el pipeline completo:
- 10 tests en sintaxis de C tradicional (inglés)
- 8 tests en sintaxis bilingüe (español)

Cada test pasa por todas las etapas:
```
programa.c → c_to_asm → programa.asm → assembler → programa.mem → CPU → resultado
```

**Los tests validan:**
- Programas simples con múltiples variables
- Funciones con parámetros y valores de retorno
- Estructuras `if/else` con comparaciones
- Bucles `while` y `for` con condiciones
- Factorial iterativo (funciona perfectamente)
- Fibonacci iterativo (funciona perfectamente)
- Llamadas a funciones anidadas (operativas)

**Resultado: 18 de 18 tests pasando** en funcionalidad no recursiva.

**Estado de la recursión:**

Implementamos todas las pseudo-instrucciones necesarias (LLAMAR, RETORNAR, EMPUJAR, SACAR) y las **llamadas simples a función funcionan perfectamente**. Por ejemplo, main() puede llamar a suma(a,b) y recibir el resultado correctamente.

Sin embargo, la **recursión completa** - donde una función se llama a sí misma - aún presenta desafíos técnicos. El problema está en la preservación correcta de registros durante llamadas recursivas múltiples. El stack pointer se mantiene balanceado, pero la gestión del stack frame necesita refinamiento.

**Este es nuestro principal reto pendiente**: completar el soporte de recursión requiere una estrategia más sofisticada para guardar y restaurar el contexto completo de cada llamada.

---

## RETOS TÉCNICOS SUPERADOS (45 segundos)

Durante el desarrollo enfrentamos y resolvimos varios bugs críticos:

**Bug crítico #1: Corrupción del Stack Pointer**
Las comparaciones en `if` y `while` estaban usando R14 (el stack pointer) como registro temporal. Esto corría el stack durante cada comparación. Lo detectamos cuando las funciones funcionaban individualmente pero fallaban al encadenarse. Solución: usar R12 como registro temporal dedicado.

**Bug #2: RETORNAR duplicado**
El compilador generaba dos instrucciones RETORNAR al final de cada función. Implementamos flags de control para evitar generación doble.

**Bug #3: Pseudo-instrucciones no expandidas**
LLAMAR y RETORNAR no se expandían en el ensamblador. Corregimos el case statement para procesarlas correctamente.

**Bug #4: Loops infinitos**
No distinguíamos entre saltos directos (a etiquetas) vs indirectos (a contenido de registros). Ahora el simulador los maneja correctamente.

Cada bug reveló algo profundo sobre cómo interactúan las capas de abstracción en un sistema computacional.

---

## CONCLUSIÓN (25 segundos)

Construimos un **sistema computacional completo y funcional**:

✅ Pipeline integrado C→ASM→BIN→CPU operativo  
✅ Compilador C bilingüe único en su tipo  
✅ Llamadas a función funcionando perfectamente  
✅ 18 tests validados en ambos idiomas  
✅ Estructuras de control completas (if, while, for)  
⚠️ Recursión: reto técnico pendiente

**Este proyecto demuestra que las computadoras son sistemas comprensibles** que podemos construir, entender y programar desde sus fundamentos.

---

## TRANSICIÓN A LA DEMOSTRACIÓN

Ahora les mostraré el sistema en acción. Voy a compilar y ejecutar programas en tiempo real para que vean todo el pipeline funcionando.

**[INICIAR DEMOSTRACIÓN EN VIVO]**

---

## NOTAS PARA LA DEMOSTRACIÓN

### Opción 1: Factorial en Español
```bash
./bin/c_to_asm tests/test_ces_factorial.c tests/test_ces_factorial.asm
cat tests/test_ces_factorial.asm | head -30
./bin/assembler tests/test_ces_factorial.asm tests/test_ces_factorial.mem
./bin/main tests/test_ces_factorial.mem
```

### Opción 2: Pipeline completo
```bash
# Mostrar el código C original
cat tests/test_ces_function.c

# Compilar a ASM
./bin/c_to_asm tests/test_ces_function.c tests/test_ces_function.asm

# Mostrar el ASM generado
cat tests/test_ces_function.asm

# Ensamblar
./bin/assembler tests/test_ces_function.asm tests/test_ces_function.mem

# Ejecutar
./bin/main tests/test_ces_function.mem
```

### Opción 3: Comparación Bilingüe
```bash
# Inglés
cat tests/test_c_function.c
./bin/main -e tests/test_c_function.c

# Español
cat tests/test_ces_function.c
./bin/main -e tests/test_ces_function.c
```

---

## TIEMPO TOTAL: 5 minutos

**Distribución:**
- Introducción: 20s
- Semana 3 (Compilador): 2min
- Semana 4 (Integración): 1min 30s
- Retos técnicos: 45s
- Conclusión: 25s

**Total: 5 minutos exactos**
