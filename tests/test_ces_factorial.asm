; Compilado desde: tests/test_ces_factorial.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: factorial(entero n)
func_factorial:
; Variable 'n' -> R0 (param)
; Variable 'result' -> R4
MOVI R4, 0  ; Inicializar result = 0
MOVER R4, R0  ; result = n
; return result
MOVER R0, R4  ; Valor de retorno
RETORNAR
; Fin de función

; Función: main()
func_main:
; Variable 'n' -> R4
MOVI R4, 0  ; Inicializar n = 0
; Variable 'fact' -> R5
MOVI R5, 0  ; Inicializar fact = 0
MOVI R4, 3  ; n = 3
; Llamar factorial(n)
MOVER R0, R4
LLAMAR func_factorial
MOVER R5, R0  ; Guardar resultado
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR
; Fin de función

ALTO  ; Fin del programa
; Compilación completa: 2 variables, 2 etiquetas
