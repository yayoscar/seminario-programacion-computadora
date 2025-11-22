// Ejemplo 3: Comparacion con IF
// 
// Descripcion: Verifica si un numero es igual a 2 usando IF
// Objetivo: Demostrar condicionales if funcionales

int main() {
    int numero;
    int resultado;
    
    numero = 2;
    resultado = 0;
    
    // Usar IF para comparar
    if (numero == 2) {
        resultado = 100;  // Si numero es 2, retorna 100
    }
    
    if (numero != 2) {
        resultado = 999;  // Si numero no es 2, retorna 999
    }
    
    // Si numero == 2, resultado sera 100
    // Si numero != 2, resultado sera 999
    return resultado;
}
