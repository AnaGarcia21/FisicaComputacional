#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// --- --- --- --- ---
// Creación de la función
vector<unsigned long long> lineal_congruente(
    unsigned long long r, // semilla
    unsigned long long a, // multiplicador
    unsigned long long c, // incremento
    unsigned long long M, // módulo
    int n) // cantidad límite de rgn
{
    unsigned long long r_0 = r;
    vector<unsigned long long> r_n;
    r_n.push_back(r_0);

    while (true)
    {
        unsigned long long r_nuevo =
            (a * r_n.back() + c) % M;

        if (r_nuevo == r_0 || r_n.size() > (n - 1))
        {
            break;
        }

        r_n.push_back(r_nuevo);
    }

    return r_n;
}

// --- --- --- --- ---
// Código principal
int main()
{
    // --- --- ---
    // Registro de resultados para los parámetros solicitados (A)
    auto resultados_A = lineal_congruente(10, 57, 1, 256, 256);

    cout << "Antes de que la secuencia se repita, se generan "
         << resultados_A.size()
         << " numeros." << endl;

    // Creación de arreglos x_i_A, y_i_A
    vector<unsigned long long> x_i_A;
    vector<unsigned long long> y_i_A;

    for (size_t i = 0; i < resultados_A.size(); i++)
    {
        if (i % 2 == 0)
        {
            y_i_A.push_back(resultados_A[i]);
        }
        else
        {
            x_i_A.push_back(resultados_A[i]);
        }
    }

    // Guardado de datos
    ofstream file_A("lin_congr_A.csv");

    file_A << "x,y\n";  // Encabezados de Excel

    // Escritura en CSV
    for (size_t i = 0; i < x_i_A.size(); i++)
    {
        file_A << x_i_A[i]
            << ","
            << y_i_A[i]
            << "\n";
    }

    file_A.close();


    // --- --- ---
    // Registro de resultados utilizando 'random'
    vector<int> resultados_random;
    
    srand(time(0));
    
    for (int i = 0; i < 256; i++)
    {
        int rgn = rand() % 256;
        resultados_random.push_back(rgn);
    }

    // Creación de arreglos x_r, y_r
    vector<int> x_r;
    vector<int> y_r;

    for (size_t i = 0; i < resultados_random.size(); i++)
    {
        if (i % 2 == 0)
            y_r.push_back(resultados_random[i]);
        else
            x_r.push_back(resultados_random[i]);
    }

    // Guardado de datos
    ofstream file_random("random.csv");

    file_random << "x,y\n";

    for (size_t i = 0; i < x_r.size(); i++)
    {
        file_random << x_r[i]
                    << "," 
                    << y_r[i] 
                    << "\n";
    }

    file_random.close();


    // --- --- --- --- ---
    // Registro de resultados para los parámetros solicitados (B)
    vector<unsigned long long> resultados_B =
        lineal_congruente(
            10,
            0x5DEECE66D,
            11,
            (1ULL << 48),
            256
        );

    // Creación de arreglos x_i_B, y_i_B
    vector<unsigned long long> x_i_B;
    vector<unsigned long long> y_i_B;

    for (size_t i = 0; i < resultados_B.size(); i++)
    {
        if (i % 2 == 0)
            y_i_B.push_back(resultados_B[i]);
        else
            x_i_B.push_back(resultados_B[i]);
    }

    // Guardado de datos
    ofstream file_B("lin_congr_B.csv");

    file_B << "x,y\n";

    for (size_t i = 0; i < x_i_B.size(); i++)
    {
        file_B << x_i_B[i]
            << "," 
            << y_i_B[i] 
            << "\n";
    }

    file_B.close();

    return 0;
}
