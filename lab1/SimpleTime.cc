//This is just a very simple way (GEMM) to get the time result of matix a and b
//In this method the result C = AB, Cij = Ai1*B1j+Ai2*B2j+......
//Author: William Liang lbb@hnu.edu.cn
//Input form: Three integers M,N,K (M,N,K <= 2048)
//			  This program will get two random matrixes, A's size is M*N
//			  and B's size is N*K
//We assume that every number in the matrix values from 0 to 255.
//Output form: matrix A,B,C and used time.

#include <iostream>
#include <time.h>
#include <stdlib.h>
clock_t start, endtime;

using namespace std;

#define MAX 2048
int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];
/*The function that calculate the matrix time
  M,N is the matrix A's size
  N,K is the matrix B's size
  the result will be stored in C
  C = AB, Cij = Ai1*B1j+Ai2*B2j+......
  C's size if M,K
*/

void MatirxTime(int* A, int* B, int* C, int M, int N, int K){
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < K; ++j)
		{
			//C[i][j] = 0
			*( C + (i * MAX) + j ) = 0;
			for (int k = 0; k < N; ++k)
			{
				//C[i][j] += A[i][k] * B[k][j];
				*( C + (i * MAX) + j ) += (*( A + (i * MAX) + k )) * (*(B + (k * MAX) + j));
			}
		}
	}
}

void displayMatrix(int* A, int M, int N){
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			//cout << a[i][j];
			cout << *(A + i * MAX + j) << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

int main(int argc, char const *argv[]){
	//srand the time seed
	//cout << RAND_MAX << endl;
	srand(time(0));
	//Input the data
	int M,N,K;
	cout << "Please enter M,N and K, use space to split.\n";
	cin >> M >> N >> K;
	if(M > MAX || N > MAX || K > MAX){
		cout << "The number is too much!\n";
		exit(0);
	}

	//Input the data

	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			A[i][j] = rand() % 256;
		}
	}

	cout << "Matrix A is: \n";
	displayMatrix(&A[0][0],M,N);

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < K; ++j)
		{
			B[i][j] = rand() % 256;
		}
	}
	cout << "Matrix B is: \n";
	displayMatrix(&B[0][0],N,K);
	start = clock();
	MatirxTime(&A[0][0], &B[0][0], &C[0][0], M, N, K);
	endtime = clock();
	cout << "Matrix C is: \n";
	displayMatrix(&C[0][0],M,K);
	double times = double(endtime-start)/CLOCKS_PER_SEC;
	cout << "Used time: " << times*1000 << " ms\n"; 
	return 0;
}