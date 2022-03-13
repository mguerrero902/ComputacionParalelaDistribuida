/* 	Universidad Sergio Arboleda
	Fecha: 08/02/2022
	Autor: Miguel �ngel Guerrero Medina
	Materia: Parallel Computing
	Tema: Implementaci�n Benchmark en C
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <errno.h>

/* 	Se crea una variable con un valor alto
	para reservar memoria	*/

#define DATA_SZ (1024 * 1024 * 64 * 3)

// 	Se reserva el espacio de memoria seg�n el valor

static double MEM_CHUNK[DATA_SZ];

/* Definición de constantes */

struct timespec inicio, fin;

/********************************* Funciones ************************************/

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
	printf("%f \n", tiempoTotal);
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

// 	Se crea la funci�n para inicializar las matrices

void initMatrix(int SZ, double *Ma, double *Mb, double *Mr)
{
	int i, j;
	for (i = 0; i < SZ; i++)
	{
		for (j = 0; j < SZ; ++j)
		{
			Ma[j + i * SZ] = randMM();
			Mb[j + i * SZ] = randMM();
			Mr[j + i * SZ] = 0.0;
		}
	}
}

void productMatrix(int SZ, double *Ma, double *Mb, double *Mr)
{
	int i, j, k;

	for (i = 0; i < SZ; i++)
	{
		for (j = 0; j < SZ; j++)
		{
			double *pA, *pB;
			double auxiliarSum = 0;
			pA = Ma + (i * SZ);
			pB = Mb + j;
			for (k = 0; k < SZ; k++, pA++, pB += SZ)
			{
				auxiliarSum += (*pA * *pB);
			}
			Mr[i * SZ + j] = auxiliarSum;
		}
	}
}

// Impresi�n para efectos de validaci�n

void printMatrix(int SZ, double *M)
{
	int i, j;
	printf("\n");
	for (i = 0; i < SZ; ++i)
	{
		for (j = 0; j < SZ; ++j)
		{
			printf("	%f	", M[j + i * SZ]);
		}
		printf("\n");
	}
	printf("\n");
}

/* 	Se implementa paso a paso benchmark Multiplicaci�n de Matrices
	algoritmo cl�sico (filas x columnas) de matrices de igual dimensi�n */

int main(int argc, char *argv[])
{
	//	Se captura la dimensi�n de la matriz
	int N = (int)atof(argv[1]);
	// printf("Valor ingresado: %d", N);
	/*	Apuntamos los vectores (creaci�n) al espacio de memoria reservado, con dimensiones NxN*/
	double *Ma, *Mb, *Mr;
	Ma = MEM_CHUNK;
	Mb = Ma + N * N;
	Mr = Mb + N * N;

	initMatrix(N, Ma, Mb, Mr);
	// printf("\nMatrix A: ");
	// printMatrix(N, Ma);
	// printf("\nMatrix B: ");
	// printMatrix(N, Mb);
	sampleStart();

	// printf("\nMatrix Result: ");

	productMatrix(N, Ma, Mb, Mr);
	sampleEnd();
	// printMatrix(N, Mr);

	return 0;
}
