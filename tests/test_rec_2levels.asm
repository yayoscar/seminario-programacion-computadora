; Compilado desde: tests/test_rec_2levels.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: cuenta(int n)
func_cuenta:
; Variable 'n' -> R0 (param)
; if (n == 0)
MOVER R15, R0  ; R15 = n
MOVI R12, 0  ; temp = 0 (literal)
RESTAR R15, R12  ; R15 = n - 0
SNZ R15, endif_1  ; Saltar si n != 0
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR
endif_1:
MOVI R15, 1
RESTAR R0, R15  ; n = n - 1
; Llamar cuenta(n)
LLAMAR func_cuenta
; return n
RETORNAR
; Fin de función

; Función: main()
func_main:
; Variable 'x' -> R4
MOVI R4, 0  ; Inicializar x = 0
; Llamar cuenta(1)
MOVI R0, 1
LLAMAR func_cuenta
MOVER R4, R0  ; Guardar resultado
; return x
MOVER R0, R4  ; Valor de retorno
; main cae al ALTO sin RETORNAR
; Fin de función
ALTO  ; Fin del programa
; Compilación completa: 1 variables, 3 etiquetas
