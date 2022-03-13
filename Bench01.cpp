// Fecha: 03-02-2022
// Autor: Miguel Ángel Guerrero Medina
// Materia: Computación Paralela y Distribuida
// Tema: Construcción del Primer Benchmark
// Benchmark: Aplicación de juguete que permite evaluar rendimiento de un aspecto en específico de la computadora

#include <iostream>
#include <vector>
#include <random>
using namespace std;

struct timespec inicio, fin;

/* Inicio: medida de tiempo */
void sampleStart()
{
    clock_gettime(CLOCK_MONOTONIC, &inicio);
}

/* Fin: medida de tiempo */
void sampleEnd()
{
    clock_gettime(CLOCK_MONOTONIC, &fin);
    // Se imprime el tiempo
    double tiempoTotal;
    tiempoTotal = (fin.tv_sec - inicio.tv_sec) * 1e9;
    tiempoTotal = (tiempoTotal + (fin.tv_nsec - inicio.tv_nsec)) * 1e-9;
    cout << tiempoTotal << endl;
}

// Función que inicializa las matrices

vector<vector<double>> inicializacionMatriz(vector<vector<double>> M)
{

    float limInf = 0.001, limSup = 9.999;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(limInf, limSup);
    vector<vector<double>> Minicializada(M.size(), vector<double>(M.size(), 0));

    for (double i = 0; i < M.size(); i++)
    {
        for (double j = 0; j < M.size(); j++)
        {
            Minicializada[i][j] = dis(gen);
        }
        // cout << endl;
    }
    return Minicializada;
}
// Se crea la función para imprimir matrices

void imprimirMatriz(vector<vector<double>> M)
{
    for (double i = 0; i < M.size(); i++)
    {
        for (double j = 0; j < M.size(); j++)
        {
            cout << M[i][j] << "\t\t";
        }
        cout << endl;
    }
}
// Se requiere multiplicar las dos matrices: Adicionalmente
// los ingenieros deben verificar y validar que realmente se cumpla el algoritmo de multiplicación

vector<vector<double>> productoMatrices(vector<vector<double>> Ma, vector<vector<double>> Mb)
{
    vector<vector<double>> Mresultado(Ma.size(), vector<double>(Ma.size(), 0));

    for (double i = 0; i < Ma.size(); i++)
        for (double j = 0; j < Mb.size(); j++)
            for (double k = 0; k < Mresultado.size(); k++)
                Mresultado[i][j] += Ma[i][k] * Mb[k][j];

    return Mresultado;
}

// Se requiere implementar una aplicación que multiplique dos matrices.
// El algoritmo a usar será el clásico (filas por columanas)

int main(int argc, char **argv)
{
    int N = atoi(argv[1]);

    // Se usa la clase vector para crear las matrices

    vector<vector<double>> M1(N, vector<double>(N, 0));
    vector<vector<double>> M2(N, vector<double>(N, 0));
    vector<vector<double>> MR(N, vector<double>(N, 0));

    M1 = inicializacionMatriz(M1);
    M2 = inicializacionMatriz(M2);

    sampleStart();
    MR = productoMatrices(M1, M2);
    sampleEnd();

    // Se imprime la matriz M1
    // imprimirMatriz(M1);
    // cout << endl << endl << endl;

    // Se imprime la matriz M2
    // imprimirMatriz(M2);
    // cout << endl << endl << endl;

    // Se imprime la matriz MR
    // imprimirMatriz(MR);
    // cout << endl << endl << endl;

    return 0;
}