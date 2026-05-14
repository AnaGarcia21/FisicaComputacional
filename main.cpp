#include <iostream>

using namespace std;

int main() {
    // Parámetros definidos en el problema
    int r = 3;       // Semilla inicial (r1)
    int a = 4;       // Multiplicador 
    int c = 1;       // Incremento 
    int M = 9;       // Módulo 
    
    // Rango
    double A = 10.0; 
    double B = 20.0;

    cout << "Iteracion | r_i (Entero) | x_i (0 a 1) | Escalado (10 a 20)" << endl;
    cout << "------------------------------------------------------------" << endl;

    // El problema dice generar la secuencia M=9
    for (int i = 1; i <= M; i++) {
        
        // 1. Normalizar: de entero a decimal [0, 1]
        // Se usa (double) para que la división no de cero 
        double xi = (double)r / M; 

        // 2. Escalar: usar la fórmula xi = A + (B - A) * ri 
        double x_escalado = A + (B - A) * xi;

        // Mostrar resultados
        cout << i << "         | " << r << "           | " << xi << "       | " << x_escalado << endl;

        // 3. Calcular el siguiente número de la secuencia (la fórmula r_i+1)
        r = (a * r + c) % M;
    }

    return 0;
}