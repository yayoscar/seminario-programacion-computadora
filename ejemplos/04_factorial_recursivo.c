
int multiplicar(int a, int b) {
    int resultado;
    int contador;
    
    resultado = 0;
    contador = 0;
    
    while (contador != b) {
        resultado = resultado + a;
        contador = contador + 1;
    }
    
    return resultado;
}

int factorial(int n) {
    int resultado;
    int n_menos_1;
    int uno;
    int temp;
    
    uno = 1;
    
    if (n == 1) {
        return 1;
    }
    
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
    
    n = 4;
    resultado = factorial(n);
    
    return resultado;
}
