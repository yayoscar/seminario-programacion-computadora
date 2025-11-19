// Test de recursión: Factorial
// factorial(5) = 5 * 4 * 3 * 2 * 1 = 120

int factorial(int n) {
    int result;
    
    if (n == 0) {
        return 1;
    }
    
    result = n - 1;
    result = factorial(result);
    result = n * result;
    
    return result;
}

int main() {
    int n;
    int fact;
    
    n = 5;
    fact = factorial(n);
    
    return 0;
}
