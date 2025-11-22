// Ejemplo 5: Factorial con IF funcional y WHILE
// Calcula factorial(5) = 120 = 5 x 4 x 3 x 2 x 1

// Funcion auxiliar para multiplicar usando sumas con while
int multiplicar(int a, int b) {
    int resultado;
    int contador;
    
    resultado = 0;
    contador = 0;
    
    // Sumar a un total de b veces
    while (contador != b) {
        resultado = resultado + a;
        contador = contador + 1;
    }
    
    return resultado;
}

// Funcion factorial RECURSIVA con IF
int factorial(int n) {
    int resultado;
    int n_menos_1;
    int uno;
    int temp;
    
    uno = 1;
    
    // Caso base: if (n == 1) return 1
    if (n == 1) {
        return 1;
    }
    
    // Caso recursivo: return n * factorial(n-1)
    temp = n;
    temp = temp - uno;
    n_menos_1 = temp;
    
    resultado = factorial(n_menos_1);
    resultado = multiplicar(n, resultado);
    
    return resultado;
}

int main() {
    int n;
    int resultado;
    
    // Calcular factorial(4) = 4 x 3 x 2 x 1 = 24
    n = 4;
    resultado = factorial(n);
    
    // resultado deberia ser 24
    return resultado;
}
