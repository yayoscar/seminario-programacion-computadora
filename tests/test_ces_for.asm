; Compilado desde: tests/test_ces_for.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: main()
func_main:
; Variable 'i' -> R4
MOVI R4, 0  ; Inicializar i = 0
; Variable 'suma' -> R5
MOVI R5, 0  ; Inicializar suma = 0
MOVI R5, 0  ; suma = 0
SUMAR R5, R4  ; suma = suma + i
; Fin de función
RETORNAR  ; Return implícito
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR

ALTO  ; Fin del programa
; Compilación completa: 2 variables, 1 etiquetas
