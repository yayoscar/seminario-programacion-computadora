; Compilado desde: tests/test_ces_while.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: main()
func_main:
; Variable 'contador' -> R4
MOVI R4, 0  ; Inicializar contador = 0
MOVI R4, 0  ; contador = 0
MOVI R15, 1
SUMAR R4, R15  ; contador = contador + 1
; Fin de función
RETORNAR  ; Return implícito
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR

ALTO  ; Fin del programa
; Compilación completa: 1 variables, 1 etiquetas
