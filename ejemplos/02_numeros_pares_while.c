// Ejemplo 2: Numeros Pares con WHILE
int main() {
    int contador;
    int resultado;
    int dos;
    int veinte;
    
    contador = 2;
    dos = 2;
    veinte = 20;
    resultado = 0;
    
    // while (contador != 22) → contar hasta que llegue a 22
    while (contador != 22) {
        resultado = contador;
        contador = contador + dos;
    }
    
    // resultado = 20 (ultimo numero par)
    return resultado;
}
