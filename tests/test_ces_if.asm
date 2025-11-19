; Compilado desde: tests/test_ces_if.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: main()
func_main:
; Variable 'a' -> R4
MOVI R4, 0  ; Inicializar a = 0
; Variable 'b' -> R5
MOVI R5, 0  ; Inicializar b = 0
MOVI R4, 5  ; a = 5
MOVI R5, 3  ; b = 3
MOVI R15, 1
SUMAR R4, R15  ; a = a + 1
; Fin de función
RETORNAR  ; Return implícito
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR

ALTO  ; Fin del programa
; Compilación completa: 2 variables, 1 etiquetas
