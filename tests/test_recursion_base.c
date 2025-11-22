// Test recursión con n=0 (caso base)

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
    
    resultado = count_down(0);  // Caso base directamente
    return resultado;
}
