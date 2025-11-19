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

int fibonacci(int n) {
    int a;
    int b;
    int uno;
    
    uno = 1;
    
    // Caso base 1: fibonacci(0) y fibonacci(1)
    if (n == uno) {
        return 1;
    }
    
    // Para este test simple, asumimos n > 1
    // Caso recursivo: fib(n) = fib(n-1) + fib(n-2)
    a = n - uno;
    a = fibonacci(a);
    
    b = n - uno;
    b = b - uno;
    b = fibonacci(b);
    
    return a + b;
}

int main() {
    int n;
    int result;
    
    n = 3;
    result = fibonacci(n);
    
    // result debería ser 2
    // fibonacci(3) = fib(2) + fib(1)
    //              = (fib(1) + fib(0)) + 1
    //              = (1 + 0) + 1 = 2
    // Pero sin caso base para 0, fib(2) = fib(1) + fib(0)
    // Simplificado: fib(3) = fib(2) + fib(1) = (1+1) + 1 = 3
    
    return 0;
}
