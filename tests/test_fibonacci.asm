[ERROR COMPILADOR] Variable no declarada en resta
; ======================================
; Compilador C -> ASM
; Entrada: tests/test_c_fibonacci.c
; ======================================

; Compilado desde: tests/test_c_fibonacci.c
; ISA de 16 bits - Español/México


; Función: fibonacci(int n)
func_fibonacci:
; Variable 'n' -> R0 (param)
; Variable 'a' -> R4
MOVI R4, 0  ; Inicializar a = 0
; Variable 'b' -> R5
MOVI R5, 0  ; Inicializar b = 0
; Variable 'temp' -> R6
MOVI R6, 0  ; Inicializar temp = 0
MOVER R6, R0  ; temp = n
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR
; Fin de función
RETORNAR
