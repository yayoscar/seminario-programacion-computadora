; Compilado desde: tests/test_rec_minimal.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: suma_recursiva(int n)
func_suma_recursiva:
; Variable 'n' -> R0 (param)
; Variable 'temp' -> R4
MOVI R4, 0  ; Inicializar temp = 0
; Variable 'resultado' -> R5
MOVI R5, 0  ; Inicializar resultado = 0
; Variable 'n_guardado' -> R6
MOVI R6, 0  ; Inicializar n_guardado = 0
; if (n == 0)
MOVI R15, 0  ; R15 = 0
MOVER R14, R0  ; R14 = n
RESTAR R14, R15  ; R14 = n - 0
MOVER R15, R14  ; R15 = resultado
SNZ R15, endif_1  ; Saltar si n != 0
; return 0
MOVI R0, 0  ; Valor de retorno
RETORNAR
endif_1:
MOVER R6, R0  ; n_guardado = n
MOVER R4, R0
MOVI R15, 1
RESTAR R4, R15  ; temp = n - 1
; Llamar suma_recursiva(temp)
MOVER R0, R4
LLAMAR func_suma_recursiva
MOVER R4, R0  ; Guardar resultado
MOVER R5, R4
SUMAR R5, R6  ; resultado = temp + n_guardado
; return resultado
MOVER R0, R5  ; Valor de retorno
RETORNAR
; Fin de función

; Función: main()
func_main:
; Variable 'resultado' -> R4
MOVI R4, 0  ; Inicializar resultado = 0
; Llamar suma_recursiva(5)
MOVI R0, 5
LLAMAR func_suma_recursiva
MOVER R4, R0  ; Guardar resultado
; return resultado
MOVER R0, R4  ; Valor de retorno
; main cae al ALTO sin RETORNAR
; Fin de función
ALTO  ; Fin del programa
; Compilación completa: 1 variables, 3 etiquetas
