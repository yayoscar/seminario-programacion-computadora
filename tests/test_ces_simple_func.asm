; ======================================
; Compilador C -> ASM
; Entrada: tests/test_ces_simple_func.c
; Salida: tests/test_ces_simple_func.asm
; ======================================

; Compilado desde: tests/test_ces_simple_func.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: suma(entero a, entero b)
func_suma:
; Variable 'a' -> R0 (param)
; Variable 'b' -> R1 (param)
; Variable 'resultado' -> R4
MOVI R4, 0  ; Inicializar resultado = 0
MOVER R4, R0  ; resultado = a
MOVER R4, R1  ; resultado = b
; return resultado
MOVER R0, R4  ; Valor de retorno
RETORNAR
; Fin de función

; Función: main()
func_main:
; Variable 'x' -> R4
MOVI R4, 0  ; Inicializar x = 0
; Variable 'y' -> R5
MOVI R5, 0  ; Inicializar y = 0
; Variable 'z' -> R6
MOVI R6, 0  ; Inicializar z = 0
MOVI R4, 5  ; x = 5
MOVI R5, 3  ; y = 3
; Llamar suma(x, y)
MOVER R0, R4
MOVER R1, R5
LLAMAR func_suma
MOVER R6, R0  ; Guardar resultado
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR
; Fin de función

ALTO  ; Fin del programa
; Compilación completa: 3 variables, 2 etiquetas
