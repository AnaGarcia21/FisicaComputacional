#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <stdexcept>

using namespace std;

// --------------------------------------------------
// Pre-ámbulo
// --------------------------------------------------


// --- --- --- --- ---
// Funciones matemáticas-numéricas:

// Función gaussiana
double gaussiana(double x){

    double res = exp(-(x*x));

    return res;
}

// Segunda derivada
double f2(double x){

    double res =
        exp(-(x*x))*((4*(x*x))-2);

    return res;
}

// Integral exacta
double i_exacta(double a, double b){

    const double PI =
        3.14159265358979323846;

    double res =
        (sqrt(PI)/2.0)*(erf(b)-erf(a));

    return res;
}

// Integral por conteo de cajas
double i_cajas(double a, double b, int N){

    double h = (b-a)/N;

    vector<double> x_i;
    vector<double> f;

    for(int i = 1; i <= N; i++){

        double x = a + h*i;

        x_i.push_back(x);

        f.push_back(
            gaussiana(x)
        );
    }

    double suma = 0.0;

    for(double v : f){

        suma += v;
    }

    double res = suma*h;

    return res;
}

// Integral por regla del trapezoide
double i_trapez(double a, double b, int N){

    double h = (b-a)/N;

    vector<double> x_i;
    vector<double> f;

    for(int i = 0; i <= N; i++){

        double x = a + h*i;

        x_i.push_back(x);

        f.push_back(
            gaussiana(x)
        );
    }

    double suma = 0.0;

    for(int i = 1; i < N; i++){

        suma += f[i];
    }

    double res =
        (h/2.0)*(f[0] + 2.0*suma + f[N]);

    return res;
}

// Integral por regla de Simpson
double i_simpson(double a, double b, int N){

    if((N%2) != 0){

        throw invalid_argument(
            "Error: N debe ser par."
        );
    }

    double h = (b-a)/N;

    vector<double> x_i;
    vector<double> f;

    for(int i = 0; i <= N; i++){

        double x = a + h*i;

        x_i.push_back(x);

        f.push_back(
            gaussiana(x)
        );
    }

    double suma = f[0] + f[N];

    for(int i = 1; i < N; i++){

        if((i%2) != 0){

            suma += 4.0*f[i];
        }

        else{

            suma += 2.0*f[i];
        }
    }

    double res = (h/3.0)*suma;

    return res;
}

// Cuadratura gaussiana
double cuadr_gauss(double a, double b, int N){

    if(N < 1 || N > 5){

        throw invalid_argument(
            "Error: N debe ser de 1 a 5."
        );
    }

    // Definiendo valores de las variables
    vector<vector<double>> x_i = {

        {},

        {0.0},

        {
            1.0/sqrt(3.0),
            -1.0/sqrt(3.0)
        },

        {
            0.0,
            3.0/sqrt(5.0),
            -3.0/sqrt(5.0)
        },

        {
            sqrt((3.0/7.0) - (2.0/7.0)*sqrt(6.0/5.0)),
            -sqrt((3.0/7.0) - (2.0/7.0)*sqrt(6.0/5.0)),

            sqrt((3.0/7.0) + (2.0/7.0)*sqrt(6.0/5.0)),
            -sqrt((3.0/7.0) + (2.0/7.0)*sqrt(6.0/5.0))
        },

        {
            0.0,

            (1.0/3.0)*sqrt(5.0 - 2.0*sqrt(10.0/7.0)),
            -(1.0/3.0)*sqrt(5.0 - 2.0*sqrt(10.0/7.0)),

            (1.0/3.0)*sqrt(5.0 + 2.0*sqrt(10.0/7.0)),
            -(1.0/3.0)*sqrt(5.0 + 2.0*sqrt(10.0/7.0))
        }
    };

    vector<vector<double>> w_i = {

        {},

        {2.0},

        {1.0, 1.0},

        {
            8.0/9.0,
            5.0/9.0,
            5.0/9.0
        },

        {
            (18.0 + sqrt(30.0))/36.0,
            (18.0 + sqrt(30.0))/36.0,
            (18.0 - sqrt(30.0))/36.0,
            (18.0 - sqrt(30.0))/36.0
        },

        {
            128.0/225.0,

            (322.0 + 13.0*sqrt(70.0))/900.0,
            (322.0 + 13.0*sqrt(70.0))/900.0,

            (322.0 - 13.0*sqrt(70.0))/900.0,
            (322.0 - 13.0*sqrt(70.0))/900.0
        }
    };

    // Comportamiento según el intervalo [a, b]
    vector<double> x_inew;
    vector<double> w_inew;

    for(double x : x_i[N]){

        x_inew.push_back(
            ((b + a)/2.0) +
            ((b - a)/2.0)*x
        );
    }

    for(double w : w_i[N]){

        w_inew.push_back(
            ((b - a)/2.0)*w
        );
    }

    vector<double> f;

    for(double x : x_inew){

        f.push_back(
            gaussiana(x)
        );
    }

    double suma = 0.0;

    for(size_t j = 0; j < w_inew.size(); j++){

        suma += w_inew[j] * f[j];
    }


    return suma;
}

// Error relativo
double error_rel(
    double x_real,
    double x_calculado
){

    double e_rel =
        abs(x_real-x_calculado)/x_real;

    return e_rel;
}


// --- --- --- --- ---
// Funciones de utilidad:

// Función para procesar intervalos
void procesar_intervalo(

    double a,
    double b,

    string nombre_intervalo,
    string nombre_archivo
){

    vector<int> N;

    for(int n = 10; n <= 100; n += 10){

        N.push_back(n);
    }


    vector<double> h;

    for(int n : N){

        h.push_back(
            (b-a)/n
        );
    }


    double exacta =
        i_exacta(a, b);


    vector<double> cajas;
    vector<double> trapezoide;
    vector<double> simpson;

    vector<double> e_cajas;
    vector<double> e_trapezoide;
    vector<double> e_simpson;


    for(int n : N){

        // Cálculo de resultados
        double c =
            i_cajas(a, b, n);

        double t =
            i_trapez(a, b, n);

        double s =
            i_simpson(a, b, n);

        cajas.push_back(c);

        trapezoide.push_back(t);

        simpson.push_back(s);

        // Cálculo de errores
        double e_c =
            error_rel(exacta, c);

        double e_t =
            error_rel(exacta, t);

        double e_s =
            error_rel(exacta, s);

        e_cajas.push_back(e_c);

        e_trapezoide.push_back(e_t);

        e_simpson.push_back(e_s);
    }

    // Resultados
    cout << fixed
         << setprecision(15);

    cout << "--- --- ---" << endl;

    cout << nombre_intervalo
         << endl;

    for(size_t i = 0; i < N.size(); i++){

        cout << "N = "
             << N[i]
             << endl;

        cout << "Cajas       : "
             << cajas[i]
             << endl;

        cout << "Trapezoide  : "
             << trapezoide[i]
             << endl;

        cout << "Simpson     : "
             << simpson[i]
             << endl;

        cout << endl;
    }

    // Guardar CSV para posterior transferencia a Excel
    ofstream archivo(nombre_archivo);

    archivo << fixed
            << setprecision(15);

    archivo

        << "N,"
        << "h,"
        << "Cajas,"
        << "Trapezoide,"
        << "Simpson,"
        << "Error_Cajas,"
        << "Error_Trapezoide,"
        << "Error_Simpson"

        << "\n";


    for(size_t i = 0; i < N.size(); i++){

        archivo

            << N[i] << ","

            << h[i] << ","

            << cajas[i] << ","

            << trapezoide[i] << ","

            << simpson[i] << ","

            << e_cajas[i] << ","

            << e_trapezoide[i] << ","

            << e_simpson[i]

            << "\n";
    }


    archivo.close();

    cout << "Archivo CSV generado: "
         << nombre_archivo
         << endl;

    cout << endl;
}



// --------------------------------------------------
// Main
// --------------------------------------------------

int main(){

    // --- --- --- --- --- 
    // Parte 1

    // Intervalo A: [-1,1]
    procesar_intervalo(-1.0, 1.0,
        "Intervalo A: [-1,1]",
        "datos_A.csv");

    // Intervalo B: [-2,2]
    procesar_intervalo(-2.0, 2.0,
        "Intervalo B: [-2,2]",
        "datos_B.csv");

    // Intervalo C: [-3,3]
    procesar_intervalo(-3.0, 3.0,
        "Intervalo C: [-3,3]",
        "datos_C.csv");


    // --- --- --- --- --- 
    // Parte 2: Cuadratura Gaussiana para B: [−2,2]

        vector<int> N_cuad;

    for(int n = 1; n <= 5; n++){

        N_cuad.push_back(n);
    }


    double error_deseado = 0.01;

    vector<double> reg_e;

    double exacta_B =
        i_exacta(-2.0, 2.0);


    for(int n : N_cuad){

        double I_i =
            cuadr_gauss(-2.0, 2.0, n);

        double e_I_i =
            error_rel(exacta_B, I_i);

        reg_e.push_back(e_I_i);
    }


    cout << "--- --- ---" << endl;

    cout << "Precision obtenida: "
         << reg_e.back()
         << " con n = "
         << N_cuad.back()
         << endl;


    ofstream archivo("gauss_B.csv");

    archivo << "n,error\n";

    for(size_t i = 0; i < N_cuad.size(); i++){

        archivo << N_cuad[i]
                << ","
                << reg_e[i]
                << "\n";
    }

    archivo.close();


    // --- --- --- --- --- 
    // Comparación con método del punto medio

    double a = -2.0;
    double b = 2.0;

    int M = 10000;

    double max_2derivada = 0.0;

    // Máximo absoluto
    for(int i = 0; i <= M; i++){

        double x =
            a + (b-a)*i/M;

        double val =
            abs(f2(x));

        if(val > max_2derivada){

            max_2derivada = val;
        }
    }


    double error_final =
        reg_e.back();


    // Cálculo de h
    double h =
        sqrt(
            (error_final * 24.0) /
            (max_2derivada * (b - a))
        );

    // Cálculo de n
    double n =
        (b - a) / h;


    cout << "--- --- ---" << endl;

    cout << "Max |f''| = "
         << max_2derivada
         << endl;

    cout << "h = "
         << h
         << endl;

    cout << "n necesario = "
         << n
         << endl;


    return 0;
}
