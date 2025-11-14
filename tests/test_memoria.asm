; test_memoria.asm
; Prueba de operaciones de memoria: CARGAR y GUARDAR
; Carga valores de memoria, los suma, y guarda el resultado
; LENGUAJE: Español México

        MOVI R0, 100    ; Dirección donde guardaremos datos
        MOVI R1, 101    ; Dirección del segundo dato
        MOVI R2, 102    ; Dirección del resultado
        
        ; Guardar valores iniciales en memoria
        MOVI R3, 15     ; Primer número
        GUARDAR R3, 100 ; MEM[100] = 15
        
        MOVI R4, 25     ; Segundo número
        GUARDAR R4, 101 ; MEM[101] = 25
        
        ; Cargar y sumar
        CARGAR R5, 100  ; R5 = MEM[100] = 15
        CARGAR R6, 101  ; R6 = MEM[101] = 25
        SUMAR R5, R6    ; R5 = 15 + 25 = 40
        
        ; Guardar resultado
        GUARDAR R5, 102 ; MEM[102] = 40
        
        ; Mostrar resultado
        CARGAR R0, 102  ; R0 = MEM[102] = 40
        ESCRIBIR R0     ; Mostrar 40
        ALTO
