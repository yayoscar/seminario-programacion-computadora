// Test recursion with only 2 levels

int cuenta(int n) {
    if (n == 0) {
        return 0;
    }
    n = n - 1;
    n = cuenta(n);
    return n;
}

int main() {
    int x;
    x = cuenta(1);  // Solo 2 niveles: cuenta(1) → cuenta(0) → return
    return x;
}
