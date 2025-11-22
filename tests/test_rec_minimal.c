// Test más simple: suma recursiva sin variables locales

// Guardar n en variable local antes de llamada recursiva
int suma_recursiva(int n) {
    int temp;
    int resultado;
    int n_guardado;
    if (n == 0) {
        return 0;
    }
    n_guardado = n;  // Guardar n porque se pierde en la llamada
    temp = n - 1;
    temp = suma_recursiva(temp);
    resultado = temp + n_guardado;  // Usar n_guardado
    return resultado;
}

int main() {
    int resultado;
    resultado = suma_recursiva(5);
    return resultado;
}
