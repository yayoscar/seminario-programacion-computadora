; Compilado desde: tests/test_c_fibonacci.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: test_if(int x)
func_test_if:
; Variable 'x' -> R0 (param)
; Variable 'resultado' -> R4
MOVI R4, 0  ; Inicializar resultado = 0
MOVI R4, 0  ; resultado = 0
MOVER R4, R0  ; resultado = x
SUMAR R4, R4  ; resultado = resultado + resultado
SUMAR R4, R4  ; resultado = resultado + resultado
SUMAR R4, R0  ; resultado = resultado + x
SUMAR R4, R4  ; resultado = resultado + resultado
; return resultado
MOVER R0, R4  ; Valor de retorno
RETORNAR
; Fin de función

; Función: main()
func_main:
; Variable 'n' -> R4
MOVI R4, 0  ; Inicializar n = 0
; Variable 'result' -> R5
MOVI R5, 0  ; Inicializar result = 0
MOVI R4, 5  ; n = 5
; Llamar test_if(n)
MOVER R0, R4
LLAMAR func_test_if
MOVER R5, R0  ; Guardar resultado
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR
; Fin de función

ALTO  ; Fin del programa
; Compilación completa: 2 variables, 2 etiquetas
