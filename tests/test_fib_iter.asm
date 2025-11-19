; ======================================
; Compilador C -> ASM
; Entrada: tests/test_c_fibonacci_iter.c
; ======================================

; Compilado desde: tests/test_c_fibonacci_iter.c
; ISA de 16 bits - Español/México


; Función: fibonacci_iter(int n)
func_fibonacci_iter:
; Variable 'n' -> R0 (param)
; Variable 'a' -> R4
MOVI R4, 0  ; Inicializar a = 0
; Variable 'b' -> R5
MOVI R5, 0  ; Inicializar b = 0
; Variable 'temp' -> R6
MOVI R6, 0  ; Inicializar temp = 0
; Variable 'i' -> R7
MOVI R7, 0  ; Inicializar i = 0
; Variable 'uno' -> R8
MOVI R8, 0  ; Inicializar uno = 0
MOVI R8, 1  ; uno = 1
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR
; Fin de función
RETORNAR
MOVI R4, 0  ; a = 0
MOVI R5, 1  ; b = 1
MOVI R7, 1  ; i = 1
MOVER R6, R4
SUMAR R6, R5  ; temp = a + b
MOVER R4, R5  ; a = b
MOVER R5, R6  ; b = temp
SUMAR R7, R8  ; i = i + uno
; return b
MOVER R0, R5  ; Valor de retorno
RETORNAR

; Función: main()
func_main:
; Variable 'n' -> R4
MOVI R4, 0  ; Inicializar n = 0
; Variable 'result' -> R5
MOVI R5, 0  ; Inicializar result = 0
MOVI R4, 6  ; n = 6
; Llamar fibonacci_iter(n)
MOVER R0, R4
LLAMAR func_fibonacci_iter
MOVER R5, R0  ; Guardar resultado
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR
; Fin de función
RETORNAR

ALTO  ; Fin del programa
; Compilación completa: 2 variables, 2 etiquetas
