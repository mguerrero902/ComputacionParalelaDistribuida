/***********************************************************
 * Fecha: 22022022
 * Autor: Miguel Ángel Guerrero Medina
 * Tema: Benchmark en serie. Implementación en C++
 * $>./ejecutable <MatrizSize>
 ***********************************************************/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>
#include <unistd.h>
#include <cstring>
#include <math.h>
#include <chrono>
#include <ctime>

using namespace std;

struct timespec inicio, fin;

/***** Lugar de funciones ****/

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

/* Aleatorio */

float randMM()
{
    float min = 0.001, max = 9.999;
    static int first = -1;
    if (first == (first < 0))
    {
        srand(time(NULL) + getpid());
    }
    if (min >= max)
    {
        return errno = EDOM, NAN;
    }
    return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

// Función Creación Matriz Doble Puntero

double **crearMatriz(int sizeN)
{
    double **matriz = new double *[sizeN];

    for (int i = 0; i < sizeN; ++i)
    {
        matriz[i] = new double[sizeN];
    }
    return matriz;
}

// Función Inicializar matriz

void inicializacionMatrices(int sizeN, double **&matriz1, double **&matriz2, double **&matriz3)
{
    for (int i = 0; i < sizeN; ++i)
    {
        for (int j = 0; j < sizeN; ++j)
        {
            matriz1[i][j] = randMM();
            matriz2[i][j] = randMM();
            matriz3[i][j] = 0;
        }
    }
}

// Función para imprimir las matrices

void imprimirMatriz(double **&matriz, int sizeN)
{
    for (int i = 0; i < sizeN; ++i)
    {
        for (int j = 0; j < sizeN; ++j)
        {
            printf(" %f ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

// Retornamos la memoria al sistema (Destruir las matrices)
void destruirMatriz(int sizeN, double **&matriz)
{
    if (matriz)
    {
        for (int i = 0; i < sizeN; ++i)
        {
            delete[] matriz[i];
        }
        delete[] matriz;
        matriz = nullptr;
    }
}

// Función Multiplicación de Matrices
// Algoritmo clásico (FilasXColumnas)
double **productoMatrices(int sizeN, double **&matriz1, double **&matriz2)
{
    double **matriz = crearMatriz(sizeN);
    for (int i = 0; i < sizeN; ++i) // Filas
    {
        for (int j = 0; j < sizeN; ++j) // Columnas
        {
            for (int k = 0; k < sizeN; ++k) // Producto
            {
                matriz[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }
    return matriz;
}

/***** Función Princial ******/

int main(int argc, char *argv[])
{
    /*** Sección de Declaración ***/
    int N = atoi(argv[1]); // Dimensión (Size) de las matrices
    double **matA = crearMatriz(N);
    double **matB = crearMatriz(N);
    double **matC = crearMatriz(N);
    inicializacionMatrices(N, matA, matB, matC);

    sampleStart();
    matC = productoMatrices(N, matA, matB);
    sampleEnd();

    // imprimirMatriz(matA, N);
    // imprimirMatriz(matB, N);
    // imprimirMatriz(matC, N);

    destruirMatriz(N, matA);
    destruirMatriz(N, matB);
    destruirMatriz(N, matC);

    return 0;
}