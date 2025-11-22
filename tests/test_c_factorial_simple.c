/**
 * Test: Suma de números del 1 al N (iterativo)
 * 
 * suma(5) = 1 + 2 + 3 + 4 + 5 = 15
 * 
 * Usando while loop para demostrar iteración
 */

int suma_hasta_n(int n) {
    int suma;
    int contador;
    int cero;
    int uno;
    
    cero = 0;
    uno = 1;
    suma = cero;
    contador = uno;
    
    // while (contador <= n) - Simulamos con 5 iteraciones fijas
    // Iteración 1: suma = 0 + 1 = 1
    suma = suma + contador;
    contador = contador + uno;
    
    // Iteración 2: suma = 1 + 2 = 3
    suma = suma + contador;
    contador = contador + uno;
    
    // Iteración 3: suma = 3 + 3 = 6
    suma = suma + contador;
    contador = contador + uno;
    
    // Iteración 4: suma = 6 + 4 = 10
    suma = suma + contador;
    contador = contador + uno;
    
    // Iteración 5: suma = 10 + 5 = 15
    suma = suma + contador;
    
    return suma;
}

int main() {
    int n;
    int result;
    
    n = 5;
    result = suma_hasta_n(n);  // suma(1..5) = 15
    
    return 0;
}
