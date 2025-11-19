; ======================================
; Compilador C -> ASM
; Entrada: tests/test_c_simple.c
; Salida: tests/test_c_simple.asm
; ======================================

; Compilado desde: tests/test_c_simple.c
; ISA de 16 bits - Español/México

; Variable 'a' -> R4
MOVI R4, 0  ; Inicializar a = 0
; Variable 'b' -> R5
MOVI R5, 0  ; Inicializar b = 0
; Variable 'c' -> R6
MOVI R6, 0  ; Inicializar c = 0
MOVI R4, 5  ; a = 5
MOVI R5, 3  ; b = 3
MOVER R6, R4
SUMAR R6, R5  ; c = a + b

ALTO  ; Fin del programa
; Compilación completa: 3 variables, 0 etiquetas
