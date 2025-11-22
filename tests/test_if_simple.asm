; Compilado desde: tests/test_if_simple.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: main()
func_main:
; Variable 'x' -> R4
MOVI R4, 0  ; Inicializar x = 0
; Variable 'resultado' -> R5
MOVI R5, 0  ; Inicializar resultado = 0
MOVI R4, 2  ; x = 2
MOVI R5, 0  ; resultado = 0
; if (x == 2)
MOVI R15, 2  ; R15 = 2
MOVER R14, R4  ; R14 = x
RESTAR R14, R15  ; R14 = x - 2
MOVER R15, R14  ; R15 = resultado
SNZ R15, endif_1  ; Saltar si x != 2
MOVI R5, 42  ; resultado = 42
endif_1:
; return resultado
MOVER R0, R5  ; Valor de retorno
RETORNAR
; Fin de función

ALTO  ; Fin del programa
; Compilación completa: 2 variables, 2 etiquetas
