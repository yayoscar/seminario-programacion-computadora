; test_logico.asm
; Prueba de operaciones lógicas: Y (AND), O (OR), NO (NOT)
; LENGUAJE: Español México

        MOVI R0, 0x0F   ; R0 = 00001111
        MOVI R1, 0xF0   ; R1 = 11110000
        
        ; Y (AND lógico)
        MOVER R2, R0    ; R2 = R0
        Y R2, R1        ; R2 = R0 & R1 = 0x00
        ESCRIBIR R2     ; Salida: 0
        
        ; O (OR lógico)
        MOVER R3, R0    ; R3 = R0
        O R3, R1        ; R3 = R0 | R1 = 0xFF
        ESCRIBIR R3     ; Salida: 255
        
        ; NO (NOT lógico)
        MOVER R4, R0    ; R4 = R0 = 0x0F
        NO R4           ; R4 = ~R4 = 0xFFF0
        ESCRIBIR R4     ; Salida: 65520
        
        ALTO
