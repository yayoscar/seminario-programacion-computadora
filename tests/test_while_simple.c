// Test simple de while con !=
int main() {
    int contador;
    int limite;
    
    contador = 0;
    limite = 5;
    
    // Contar de 0 a 4 (mientras contador != 5)
    while (contador != limite) {
        contador = contador + 1;
    }
    
    return contador;  // Debería retornar 5
}
