; Compilado desde: tests/test_while_simple.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: main()
func_main:
; Variable 'contador' -> R4
MOVI R4, 0  ; Inicializar contador = 0
; Variable 'limite' -> R5
MOVI R5, 0  ; Inicializar limite = 0
MOVI R4, 0  ; contador = 0
MOVI R5, 5  ; limite = 5
MOVI R15, 1
SUMAR R4, R15  ; contador = contador + 1
; Fin de función
RETORNAR  ; Return implícito
; return contador
MOVER R0, R4  ; Valor de retorno
RETORNAR

ALTO  ; Fin del programa
; Compilación completa: 2 variables, 1 etiquetas
