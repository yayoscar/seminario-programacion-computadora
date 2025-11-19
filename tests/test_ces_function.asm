; Compilado desde: tests/test_ces_function.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: duplicar(entero x)
func_duplicar:
; Variable 'x' -> R0 (param)
; Variable 'resultado' -> R4
MOVI R4, 0  ; Inicializar resultado = 0
MOVER R4, R0  ; resultado = x
; return resultado
MOVER R0, R4  ; Valor de retorno
RETORNAR
; Fin de función

; Función: main()
func_main:
; Variable 'valor' -> R4
MOVI R4, 0  ; Inicializar valor = 0
; Variable 'doble' -> R5
MOVI R5, 0  ; Inicializar doble = 0
MOVI R4, 10  ; valor = 10
; Llamar duplicar(valor)
MOVER R0, R4
LLAMAR func_duplicar
MOVER R5, R0  ; Guardar resultado
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR
; Fin de función

ALTO  ; Fin del programa
; Compilación completa: 2 variables, 2 etiquetas
