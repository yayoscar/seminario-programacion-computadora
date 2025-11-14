; programa.asm
; Programa de ejemplo: Calcula la suma de 1 a 10
; Resultado esperado: 55 (1+2+3+4+5+6+7+8+9+10)
; Algoritmo: suma = 0; para (i=1; i<=10; i++) suma += i;
;
; LENGUAJE: Español México
; Mnemónicos en español para facilitar el aprendizaje

        MOVI R0, 0      ; R0 = suma (acumulador) = 0
        MOVI R1, 1      ; R1 = i (contador) = 1
        MOVI R2, 10     ; R2 = limite = 10

; Bucle principal: suma += i, i++, si (i <= limite) ir a bucle
bucle:   
        SUMAR R0, R1    ; suma = suma + i
        MOVI R3, 1      ; R3 = 1 (constante)
        SUMAR R1, R3    ; i = i + 1
        
        ; Verificar si i <= limite (equivalente: i == 11?)
        MOVI R5, 11     ; R5 = 11
        MOVER R6, R1    ; R6 = i
        RESTAR R6, R5   ; R6 = i - 11
        SZ R6, fin      ; Si i == 11, terminar
        SALTAR bucle    ; Sino, continuar

; Fin del programa
fin:    
        ESCRIBIR R0     ; Mostrar resultado (suma = 55)
        ALTO            ; Terminar ejecución
