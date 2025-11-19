; ======================================
; Compilador C -> ASM
; Entrada: tests/test_ces_main_only.c
; Salida: tests/test_ces_main_only.asm
; ======================================

; Compilado desde: tests/test_ces_main_only.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


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
MOVER R6, R4  ; z = x
MOVER R6, R5  ; z = y
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR
; Fin de función

ALTO  ; Fin del programa
; Compilación completa: 3 variables, 1 etiquetas
