; Compilado desde: tests/test_call_simple.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: add_one(int n)
func_add_one:
; Variable 'n' -> R0 (param)
; Variable 'uno' -> R4
MOVI R4, 0  ; Inicializar uno = 0
MOVI R4, 1  ; uno = 1
; return n
RETORNAR
; Fin de función

; Función: main()
func_main:
; Variable 'resultado' -> R4
MOVI R4, 0  ; Inicializar resultado = 0
; Llamar add_one(5)
MOVI R0, 5
LLAMAR func_add_one
MOVER R4, R0  ; Guardar resultado
; return resultado
MOVER R0, R4  ; Valor de retorno
; main cae al ALTO sin RETORNAR
; Fin de función
ALTO  ; Fin del programa
; Compilación completa: 1 variables, 2 etiquetas
