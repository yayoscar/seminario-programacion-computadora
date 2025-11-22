// Test: función A llama a función B (no recursión)

int func_b() {
    return 42;
}

int func_a() {
    int resultado;
    resultado = func_b();
    return resultado;
}

int main() {
    int x;
    x = func_a();
    return x;
}
