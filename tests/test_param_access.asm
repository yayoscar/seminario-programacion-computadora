; Compilado desde: tests/test_param_access.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: doble(int n)
func_doble:
; Variable 'n' -> R0 (param)
; Variable 'resultado' -> R4
MOVI R4, 0  ; Inicializar resultado = 0
MOVI R15, 1
RESTAR R4, R15  ; resultado = n - 1
; return resultado
MOVER R0, R4  ; Valor de retorno
RETORNAR
; Fin de función

; Función: main()
func_main:
; Variable 'x' -> R4
MOVI R4, 0  ; Inicializar x = 0
; Llamar doble(5)
MOVI R0, 5
LLAMAR func_doble
MOVER R4, R0  ; Guardar resultado
; return x
MOVER R0, R4  ; Valor de retorno
; main cae al ALTO sin RETORNAR
; Fin de función
ALTO  ; Fin del programa
; Compilación completa: 1 variables, 2 etiquetas
