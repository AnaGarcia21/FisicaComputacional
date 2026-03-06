#include <iostream>

using namespace std;

int main() {
    // --- PARTE 1: OVERFLOW ---
    // Iniciamos cerca del limite de 10^308
    double num_alto = 1e306;
    cout << "--- Buscando el Overflow ---" << endl;

    for (int i = 0; i < 10; i++) {
        num_alto = num_alto * 10;
        cout << "Multiplicacion " << i + 1 << ": " << num_alto << endl;
    }

    cout << endl; // Espacio entre pruebas

    // --- PARTE 2: UNDERFLOW ---
    // Iniciamos cerca del limite inferior
    double num_bajo = 1e-320;
    int potencia = -320; 

    cout << "--- Buscando el Underflow ---" << endl;
    while (num_bajo > 0.0) {
        num_bajo = num_bajo / 10.0;
        potencia--;
        cout << "Potencia 10^" << potencia << " -> Valor: " << num_bajo << endl;
    }
    cout << "Colapso en 0.0 detectado." << endl;

    return 0;
}