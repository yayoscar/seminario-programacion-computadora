; test_simple.asm
; Prueba muy simple: suma dos números y muestra el resultado
; Resultado esperado: 30 (10 + 20)
; LENGUAJE: Español México

        MOVI R0, 10     ; R0 = 10
        MOVI R1, 20     ; R1 = 20
        SUMAR R0, R1    ; R0 = R0 + R1 = 30
        ESCRIBIR R0     ; Mostrar resultado
        ALTO            ; Terminar
