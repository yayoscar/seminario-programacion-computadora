; Compilado desde: tests/test_recursion_simple.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: count_down(int n)
func_count_down:
; Variable 'n' -> R0 (param)
; Variable 'uno' -> R4
MOVI R4, 0  ; Inicializar uno = 0
; Variable 'temp' -> R5
MOVI R5, 0  ; Inicializar temp = 0
; Variable 'resultado' -> R6
MOVI R6, 0  ; Inicializar resultado = 0
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
MOVI R4, 1  ; uno = 1
MOVER R5, R0  ; temp = n
RESTAR R5, R4  ; temp = temp - uno
; Llamar count_down(temp)
; Guardar registros para recursión
EMPUJAR R0
EMPUJAR R1
EMPUJAR R2
EMPUJAR R3
MOVER R0, R5
LLAMAR func_count_down
; Restaurar registros después de recursión
MOVER R11, R0  ; Guardar resultado temporalmente
SACAR R3
SACAR R2
SACAR R1
SACAR R0
MOVER R12, R11  ; Mover resultado a R12
MOVER R6, R12  ; Guardar resultado
; return n
RETORNAR
; Fin de función

; Función: main()
func_main:
; Variable 'resultado' -> R4
MOVI R4, 0  ; Inicializar resultado = 0
MOVI R4, 0  ; resultado = 0
; Llamar count_down(3)
MOVI R0, 3
LLAMAR func_count_down
MOVER R4, R0  ; Guardar resultado
; return resultado
MOVER R0, R4  ; Valor de retorno
; main cae al ALTO sin RETORNAR
; Fin de función
ALTO  ; Fin del programa
; Compilación completa: 1 variables, 3 etiquetas
