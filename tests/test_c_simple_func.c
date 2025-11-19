/**
 * Test simple de función sin recursión
 */

int suma(int a, int b) {
    int resultado;
    resultado = a + b;
    return resultado;
}

int main() {
    int x;
    int y;
    int z;
    
    x = 5;
    y = 3;
    z = suma(x, y);
    
    return 0;
}
