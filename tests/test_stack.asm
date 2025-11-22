; Compilado desde: tests/test_stack.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: identity(int n)
func_identity:
; Variable 'n' -> R0 (param)
; return n
RETORNAR
; Fin de función

; Función: main()
func_main:
; Variable 'resultado' -> R4
MOVI R4, 0  ; Inicializar resultado = 0
; Llamar identity(42)
MOVI R0, 42
LLAMAR func_identity
MOVER R4, R0  ; Guardar resultado
; return resultado
MOVER R0, R4  ; Valor de retorno
; main cae al ALTO sin RETORNAR
; Fin de función
ALTO  ; Fin del programa
; Compilación completa: 1 variables, 2 etiquetas
