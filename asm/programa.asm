; ========================================
; Programa: Suma Simple
; Descripción: Suma dos números (5 + 3)
; Resultado esperado: 8
; ========================================
; LENGUAJE: Español (México)
; Mnemónicos en español para facilitar el aprendizaje

inicio:
    MOVI R0, 5          ; R0 = 5 (primer número)
    MOVI R1, 3          ; R1 = 3 (segundo número)
    RESTAR R0, R1        ; R0 = R0 - R1 = 5 - 3 = 2
    ESCRIBIR R0         ; Mostrar resultado
    ALTO                ; Terminar programa
