; test_factorial.asm
; Calcula el factorial de 5 de forma iterativa
; Resultado esperado: 120 (5! = 5*4*3*2*1)
; NOTA: Requiere instrucción MULTI (no implementada aún)
; Por ahora, calculamos 5+4+3+2+1 = 15 (suma)
;
; LENGUAJE: Español México
; (En semana 3-4 se implementará multiplicación y recursión)

        MOVI R0, 0      ; R0 = resultado = 0
        MOVI R1, 5      ; R1 = n = 5
        MOVI R2, 1      ; R2 = constante 1

bucle:   
        SUMAR R0, R1    ; resultado += n
        RESTAR R1, R2   ; n = n - 1
        SNZ R1, bucle   ; Si n != 0, continuar
        
        ESCRIBIR R0     ; Mostrar resultado (15 por ahora)
        ALTO

; PENDIENTE para Semana 3-4:
; - Implementar MULTI (multiplicación)
; - Implementar LLAMAR/RETORNAR para recursión
; - Calcular factorial real: fact(5) = 5 * fact(4)
