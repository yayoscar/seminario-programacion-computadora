# Tarjeta de Referencia ISA - Guía Rápida

## Formato de Instrucción (16 bits)

```
┌──────────┬────────┬────────────────┐
│ CÓDIGO_OP│   Rd   │    OPERANDO    │
│  4 bits  │ 4 bits │    8 bits      │
└──────────┴────────┴────────────────┘
```

---

## Conjunto Completo de Instrucciones

### Movimiento de Datos (0x0-0x2)

| Hex | Español | Inglés | Formato | Descripción | Ejemplo |
|-----|---------|--------|---------|-------------|---------|
| 0x0 | NADA | NOP | `NADA` | Sin operación | `NADA` |
| 0x1 | MOVI | MOVI | `MOVI Rd, inm` | Rd = valor inmediato | `MOVI R0, 10` |
| 0x2 | MOVER | MOV | `MOVER Rd, Rs` | Rd = Rs | `MOVER R1, R0` |

### Operaciones Aritméticas (0x3-0x4)

| Hex | Español | Inglés | Formato | Descripción | Ejemplo |
|-----|---------|--------|---------|-------------|---------|
| 0x3 | SUMAR | ADD | `SUMAR Rd, Rs` | Rd = Rd + Rs | `SUMAR R0, R1` |
| 0x4 | RESTAR | SUB | `RESTAR Rd, Rs` | Rd = Rd - Rs | `RESTAR R2, R3` |

### Operaciones Lógicas (0x5-0x7)

| Hex | Español | Inglés | Formato | Descripción | Ejemplo |
|-----|---------|--------|---------|-------------|---------|
| 0x5 | Y | AND | `Y Rd, Rs` | Rd = Rd & Rs | `Y R0, R1` |
| 0x6 | O | OR | `O Rd, Rs` | Rd = Rd \| Rs | `O R2, R3` |
| 0x7 | NO | NOT | `NO Rd` | Rd = ~Rd | `NO R0` |

### Acceso a Memoria (0x8-0x9)

| Hex | Español | Inglés | Formato | Descripción | Ejemplo |
|-----|---------|--------|---------|-------------|---------|
| 0x8 | CARGAR | LOAD | `CARGAR Rd, [dir]` | Rd = MEM[dir] | `CARGAR R0, 100` |
| 0x9 | GUARDAR | STORE | `GUARDAR Rd, [dir]` | MEM[dir] = Rd | `GUARDAR R0, 100` |

### Flujo de Control (0xA-0xC)

| Hex | Español | Inglés | Formato | Descripción | Ejemplo |
|-----|---------|--------|---------|-------------|---------|
| 0xA | SALTAR | JMP | `SALTAR dir` | PC = dir | `SALTAR bucle` |
| 0xB | SZ | JZ | `SZ Rd, dir` | si (Rd == 0) PC = dir | `SZ R0, fin` |
| 0xC | SNZ | JNZ | `SNZ Rd, dir` | si (Rd != 0) PC = dir | `SNZ R1, bucle` |

### Operaciones de E/S (0xD-0xE)

| Hex | Español | Inglés | Formato | Descripción | Ejemplo |
|-----|---------|--------|---------|-------------|---------|
| 0xD | ESCRIBIR | OUT | `ESCRIBIR Rd` | Mostrar Rd | `ESCRIBIR R0` |
| 0xE | LEER | IN | `LEER Rd` | Rd = entrada | `LEER R1` |

### Sistema (0xF)

| Hex | Español | Inglés | Formato | Descripción | Ejemplo |
|-----|---------|--------|---------|-------------|---------|
| 0xF | ALTO | HALT | `ALTO` | Detener ejecución | `ALTO` |

**Nota**: El ensamblador acepta tanto los mnemónicos en español como en inglés.

---

## Registros

| Registro | Número | Propósito |
|----------|--------|-----------|
| R0-R13 | 0-13 | Propósito general |
| R14 (SP) | 14 | Puntero de pila (futuro) |
| R15 | 15 | Registro de banderas (futuro) |
| PC | - | Contador de programa |
| IR | - | Registro de instrucción |

---

## Banderas (Flags)

| Bandera | Condición |
|---------|-----------|
| Zero | Se activa cuando el resultado es 0 |
| Carry | Se activa con desbordamiento aritmético |

---

## Mapa de Memoria

```
0x00-0xEF : Programa y datos (240 palabras)
0xF0-0xFF : Espacio de pila (16 palabras)
```

---

## Ejemplos de Codificación

### MOVI R0, 10
```
Código_Op: 0x1 (MOVI)
Rd: 0x0 (R0)
Operando: 0x0A (10 decimal)

Binario:  0001 0000 0000 1010
Hex:      0x100A
```

### SUMAR R2, R3
```
Código_Op: 0x3 (SUMAR/ADD)
Rd: 0x2 (R2)
Rs: 0x3 (R3 en campo de operando)

Binario:  0011 0010 0000 0011
Hex:      0x3203
```

### SNZ R1, bucle (bucle en dirección 5)
```
Código_Op: 0xC (SNZ/JNZ)
Rd: 0x1 (R1)
Dirección: 0x05 (5 decimal)

Binario:  1100 0001 0000 0101
Hex:      0xC105
```

---

## Sintaxis del Ensamblador

### Comentarios
```assembly
; Esto es un comentario
```

### Etiquetas
```assembly
bucle:              ; Definición de etiqueta
    SUMAR R0, R1
    SNZ R2, bucle   ; Referencia a etiqueta
```

### Números
```assembly
MOVI R0, 10     ; Decimal
MOVI R1, 0x0A   ; Hexadecimal
```

### Instrucciones
```assembly
; No distingue mayúsculas/minúsculas
MOVI R0, 10
movi r0, 10     ; Es lo mismo

; Español e inglés funcionan
SUMAR R0, R1    ; Español
ADD R0, R1      ; Inglés (equivalente)
```

---

## Patrones Comunes

### Bucle (contar hacia abajo)
```assembly
        MOVI R0, 10      ; contador = 10
bucle:   
        ; ... cuerpo del bucle ...
        MOVI R1, 1
        RESTAR R0, R1    ; contador--
        SNZ R0, bucle    ; si (contador != 0) ir a bucle
```

### Bucle (contar hacia arriba)
```assembly
        MOVI R0, 0       ; i = 0
        MOVI R1, 10      ; limite = 10
bucle:   
        ; ... cuerpo del bucle ...
        MOVI R2, 1
        SUMAR R0, R2     ; i++
        MOVI R3, 11
        MOVER R4, R0
        RESTAR R4, R3    ; temp = i - 11
        SNZ R4, bucle    ; si (i != 11) ir a bucle
```

### Condicional (si Rd == 0)
```assembly
        SNZ Rd, sino     ; si (Rd != 0) ir a sino
        ; ... bloque entonces ...
        SALTAR finde
sino:
        ; ... bloque sino ...
finde:
```

### Asignación de Variable
```assembly
        MOVI R0, 42      ; x = 42
        GUARDAR R0, 100  ; guardar x en dirección 100
```

### Cargar Variable
```assembly
        CARGAR R0, 100   ; x = MEM[100]
```

---

## Instrucciones Futuras (Actividades 3-4)

Estas se añadirán para llamadas a funciones y recursión:

| Hex | Español | Inglés | Formato | Descripción |
|-----|---------|--------|---------|-------------|
| POR DEFINIR | LLAMAR | CALL | `LLAMAR dir` | Llamar función |
| POR DEFINIR | RETORNAR | RET | `RETORNAR` | Retornar de función |
| POR DEFINIR | EMPUJAR | PUSH | `EMPUJAR Rd` | Empujar a pila |
| POR DEFINIR | SACAR | POP | `SACAR Rd` | Sacar de pila |
| POR DEFINIR | COMPARAR | CMP | `COMPARAR Rd, Rs` | Comparar (activar banderas) |
| POR DEFINIR | MULTI | MUL | `MULTI Rd, Rs` | Rd = Rd * Rs |
| POR DEFINIR | DIVIDIR | DIV | `DIVIDIR Rd, Rs` | Rd = Rd / Rs |
| POR DEFINIR | SMENOR | JLT | `SMENOR dir` | Saltar si menor que |
| POR DEFINIR | SMAYOR | JGT | `SMAYOR dir` | Saltar si mayor que |

---

## Modos de Direccionamiento

### Actuales (Semana 2)

| Modo | Descripción | Ejemplo |
|------|-------------|---------|
| Inmediato | Operando es el valor | `MOVI R0, 10` |
| Registro | Operando es número de registro | `SUMAR R0, R1` |
| Directo | Operando es dirección de memoria | `CARGAR R0, 100` |
| Indirecto (vía etiqueta) | Etiqueta se resuelve a dirección | `SALTAR bucle` |

### Futuros (Semanas 3-4)

| Modo | Descripción | Ejemplo |
|------|-------------|---------|
| Registro Indirecto | Dirección en registro | `CARGAR R0, [R1]` |
| Indexado | Base + desplazamiento | `CARGAR R0, [R1+10]` |

---

## Pseudo-instrucciones (Futuro)

Estas podrían añadirse al ensamblador como macros:

```assembly
; Limpiar registro
LIMPIAR R0       ; Se expande a: MOVI R0, 0

; Incrementar
INCREMENTAR R0   ; Se expande a: MOVI R1, 1; SUMAR R0, R1

; Decrementar
DECREMENTAR R0   ; Se expande a: MOVI R1, 1; RESTAR R0, R1

; Comparar
COMPARAR R0, R1  ; Se expande a: MOVER R2, R0; RESTAR R2, R1
```

---

## Códigos de Error

| Código | Significado |
|--------|-------------|
| -1 | Error general |
| PC fuera de límites | PC >= 256 |
| Registro inválido | Rd >= 16 |
| Código de operación inválido | Instrucción desconocida |
| Memoria fuera de límites | Dirección >= 256 |

---

## Notas de Rendimiento

- Todas las instrucciones se ejecutan en 1 ciclo
- Acceso a memoria: 1 ciclo (sin caché)
- Sin pipeline (simple fetch-decode-execute)
- Tamaño máximo de programa: 256 instrucciones
- Tamaño de pila: 16 palabras (configurable)

---

## Referencia Rápida: Estructura de Programa

```assembly
; Variables (opcional, guardadas en direcciones altas)
; ...

; Sección de código
inicio:
        MOVI R0, 0       ; Inicializar
        
bucle_principal:
        ; Lógica principal del programa
        SNZ R0, bucle_principal
        
        ESCRIBIR R0      ; Mostrar resultado
        ALTO             ; Terminar programa
```

---

**Versión ISA**: 1.0  
**Última Actualización**: 14 de noviembre de 2025  
**Estado**: Semana 2 Completada
