/**
 * Test de recursión: Fibonacci recursivo
 * 
 * Fibonacci(n):
 *   si n == 0, retornar 0
 *   si n == 1, retornar 1
 *   sino retornar Fibonacci(n-1) + Fibonacci(n-2)
 * 
 * Secuencia: 0, 1, 1, 2, 3, 5, 8, 13, 21...
 * 
 * Test: fibonacci(5) = 5
 */

// TEST SIMPLE: Multiplicar por 10
int test_if(int x) {
    int resultado;
    
    resultado = 0;
    
    // Retornar x * 10
    resultado = x;
    resultado = resultado + resultado;  // x * 2
    resultado = resultado + resultado;  // x * 4
    resultado = resultado + x;          // x * 5
    resultado = resultado + resultado;  // x * 10
    
    return resultado;
}

int main() {
    int n;
    int result;
    
    n = 5;
    result = test_if(n);  // Debería retornar 50
    
    return 0;
}
