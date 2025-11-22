; Compilado desde: tests/test_nested_calls.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: func_b()
func_func_b:
; return 42
MOVI R0, 42  ; Valor de retorno
RETORNAR
; Fin de función

; Función: func_a()
func_func_a:
; Variable 'resultado' -> R4
MOVI R4, 0  ; Inicializar resultado = 0
; return resultado
MOVER R0, R4  ; Valor de retorno
RETORNAR
; Fin de función

; Función: main()
func_main:
; Variable 'x' -> R4
MOVI R4, 0  ; Inicializar x = 0
; return x
MOVER R0, R4  ; Valor de retorno
; main cae al ALTO sin RETORNAR
; Fin de función
ALTO  ; Fin del programa
; Compilación completa: 1 variables, 3 etiquetas
