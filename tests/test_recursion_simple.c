// Test simple de recursión
// Cuenta desde n hasta 1

int count_down(int n) {
    int uno;
    int temp;
    int resultado;
    
    if (n == 0) {
        return 0;
    }
    uno = 1;
    temp = n;
    temp = temp - uno;
    resultado = count_down(temp);
    return n;
}

int main() {
    int resultado;
    
    resultado = 0;
    resultado = count_down(3);
    return resultado;
}
