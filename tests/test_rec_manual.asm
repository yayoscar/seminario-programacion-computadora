; Test manual: cuenta(1) -> cuenta(0) -> return
; Código equivalente a test_rec_2levels.c pero escrito a mano

SALTAR func_main

; int cuenta(int n) { if (n==0) return 0; else return cuenta(n-1); }
func_cuenta:
    ; if (n == 0)
    MOVI R15, 0
    MOVER R14, R0
    RESTAR R14, R15
    MOVER R15, R14
    SNZ R15, else_1
    ; return 0
    MOVI R0, 0
    RETORNAR
else_1:
    ; n = n - 1
    MOVI R15, 1
    RESTAR R0, R15
    ; cuenta(n)
    LLAMAR func_cuenta
    ; return (resultado ya está en R0)
    RETORNAR

func_main:
    MOVI R0, 1
    LLAMAR func_cuenta
    ; R0 tiene el resultado
    ALTO
