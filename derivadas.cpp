#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstdlib>

double funcion_gaussiana(double x) {
    return std::exp(-x * x);
}

double derivada_exacta(double x) {
    return -2.0 * x * std::exp(-x * x);
}

double metodo_forward(double x, double h) {
    return (funcion_gaussiana(x + h) - funcion_gaussiana(x)) / h;
}

double metodo_backward(double x, double h) {
    return (funcion_gaussiana(x) - funcion_gaussiana(x - h)) / h;
}

double metodo_central(double x, double h) {
    return (funcion_gaussiana(x + h) - funcion_gaussiana(x - h)) / (2.0 * h);
}

int main() {
    double x0 = 0.5;
    double valor_real = derivada_exacta(x0);

    std::ofstream mi_archivo("datos_gaussiana.txt");

    double h = 0.1;
    for (int i = 0; i < 16; i++) {
        double error_forward  = std::abs(metodo_forward(x0, h) - valor_real);
        double error_backward = std::abs(metodo_backward(x0, h) - valor_real);
        double error_central  = std::abs(metodo_central(x0, h) - valor_real);

        mi_archivo << h << " " << error_forward << " " << error_backward << " " << error_central << "\n";
        h /= 10.0;
    }
    mi_archivo.close();

std::string instrucciones = "gnuplot -e \""
        "set title 'Error de Derivacion Numerica vs Paso h (Gaussiana)';"
        "set xlabel 'Tamaño del paso (h)';"
        "set ylabel 'Error Absoluto';"
        "set logscale xy;"
        "set xrange [1e-16:1e-1];"
        "set grid;"
      
        "set terminal png size 800,600;"      
        "set output 'grafica_derivadas.png';"  
        
        
        "plot 'datos_gaussiana.txt' u 1:2 w lp title 'Forward O(h)', "
        "     'datos_gaussiana.txt' u 1:3 w lp title 'Backward O(h)', "
        "     'datos_gaussiana.txt' u 1:4 w lp title 'Central O(h^2)'\"";
    std::system(instrucciones.c_str());

    return 0;
}