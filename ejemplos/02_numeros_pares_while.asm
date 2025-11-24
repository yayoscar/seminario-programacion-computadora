; Compilado desde: ejemplos/02_numeros_pares_while.c
; ISA de 16 bits - Español/México

; Punto de entrada: saltar a main()
SALTAR func_main


; Función: main()
func_main:
; Variable 'contador' -> R4
MOVI R4, 0  ; Inicializar contador = 0
; Variable 'resultado' -> R5
MOVI R5, 0  ; Inicializar resultado = 0
; Variable 'dos' -> R6
MOVI R6, 0  ; Inicializar dos = 0
; Variable 'veinte' -> R7
MOVI R7, 0  ; Inicializar veinte = 0
MOVI R4, 2  ; contador = 2
MOVI R6, 2  ; dos = 2
MOVI R7, 20  ; veinte = 20
MOVI R5, 0  ; resultado = 0
while_1:  ; while (contador != 22)
MOVER R15, R4  ; R15 = contador
MOVI R12, 22  ; temp = 22 (literal)
RESTAR R15, R12  ; R15 = contador - 22
SZ R15, endwhile_1  ; Saltar si contador == 22
MOVER R5, R4  ; resultado = contador
SUMAR R4, R6  ; contador = contador + dos
SALTAR while_1
endwhile_1:
; return resultado
MOVER R0, R5  ; Valor de retorno
; main cae al ALTO sin RETORNAR
; Fin de función
ALTO  ; Fin del programa
; Compilación completa: 4 variables, 2 etiquetas
