/**
 * Test: Fibonacci ITERATIVO (sin recursión)
 * 
 * Secuencia: 0, 1, 1, 2, 3, 5, 8, 13, 21...
 * 
 * fibonacci_iter(6) = 8
 */

int fibonacci_iter(int n) {
    int a;
    int b;
    int temp;
    int i;
    int uno;
    
    uno = 1;
    
    // Casos base
    if (n == 0) {
        return 0;
    }
    
    // fibonacci iterativo
    a = 0;
    b = 1;
    i = 1;
    
    while (i != n) {
        temp = a + b;
        a = b;
        b = temp;
        i = i + uno;
    }
    
    return b;
}

int main() {
    int n;
    int result;
    
    n = 6;
    result = fibonacci_iter(n);
    
    // result debería ser 8
    
    return 0;
}
