#include<iostream>
#include<math.h>
#include <iomanip>
using namespace std;


float** transpusa(float** matrix, int n)
{
	int i, j;
	float** transpusa_matrice;
	transpusa_matrice = new float* [n];
	for (i = 0; i < n; i++) transpusa_matrice[i] = new float[n];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			transpusa_matrice[j][i] = matrix[i][j];


		}
	}

	return transpusa_matrice;

	for (int i = 0; i < n; i++) // dealocarea memoriei
		delete[] transpusa_matrice[i];
	delete[] transpusa_matrice;
}


float determinant(float** matrix, int n)
{
	int i, j, x;
	int subi, subj;
	float det = 0;
	float** submatrix;
	submatrix = new float* [n - 1];
	for (i = 0; i < n; i++) submatrix[i] = new float[n - 1];

	if (n == 2)
		return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
	else {
		for (x = 0; x < n; x++) {
			subi = 0;
			for (i = 1; i < n; i++) {
				subj = 0;
				for (j = 0; j < n; j++) {
					if (j == x)
						continue;
					submatrix[subi][subj] = matrix[i][j];
					subj++;
				}
				subi++;
			}
			det = det + (pow(-1.0, x) * matrix[0][x] * determinant(submatrix, n - 1));
		}
	}

	return det;
	for (i = 0; i < n; i++) // dealocarea memoriei
		delete[] submatrix[i];
	delete[] submatrix;
}

float cofactor(float** matrix, int q, int p, int n)
{
	float** cofactor_matrice;
	int i, j, lin = 0, col = 0;
	cofactor_matrice = new float* [n - 1];
	for (i = 0; i < n - 1; i++) cofactor_matrice[i] = new float[n - 1];//alocare memorie

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			if (i != p && j != q)
			{
				cofactor_matrice[lin][col++] = matrix[i][j];
				if (col == n - 1)
				{
					col = 0;
					lin++;
				}
			}
	}


	return determinant(cofactor_matrice, n - 1);

	for (i = 0; i < n - 1; i++) // dealocarea memoriei
		delete[] cofactor_matrice[i];
	delete[] cofactor_matrice;
}


float** adjuncta(float** matrix, int n)
{
	int i, j;
	float** adjuncta_matrice;
	adjuncta_matrice = new float* [n];
	for (i = 0; i < n; i++) adjuncta_matrice[i] = new float[n];
	float** temporar;
	temporar = new float* [n];
	for (i = 0; i < n; i++) temporar[i] = new float[n];

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			adjuncta_matrice[i][j] = pow(-1, i + j) * cofactor(matrix, i, j, n);

	}
	return adjuncta_matrice;

	for (int i = 0; i < n; i++) // dealocarea memoriei
		delete[] adjuncta_matrice[i];
	delete[] adjuncta_matrice;
}


float** invers(float** matrix, int n)
{
	int i, j;
	float** inversa_matrice;
	inversa_matrice = new float* [n];
	for (i = 0; i < n; i++) inversa_matrice[i] = new float[n];

	float det = determinant(matrix, n);
	inversa_matrice = adjuncta(matrix, n);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			inversa_matrice[i][j] = inversa_matrice[i][j] / ((float)det);
	}
	return inversa_matrice;
	for (i = 0; i < n; i++) // dealocarea memoriei
		delete[] inversa_matrice[i];
	delete[] inversa_matrice;
}



int main() {
	int n, i, j;
	float** matriceA;
	float** matriceB;

	cout << "Introduceti Rangul matricilor patratice:";
	cin >> n;

	matriceA = new float* [n];
	for (i = 0; i < n; i++) matriceA[i] = new float[n];

	matriceB = new float* [n];
	for (i = 0; i < n; i++) matriceB[i] = new float[n];


	cout << "Introduceti elementele matricii A:\n";
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			cin >> matriceA[i][j];
		}
	cout << "Introduceti elementele matricii B:\n";
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			cin >> matriceB[i][j];
		}
	cout << "-------------------------------------------" << endl;
	cout << "Matricea A este:" << endl;// afisarea
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout << matriceA[i][j] << " ";
		cout << endl;
	}

	cout << "-------------------------------------------" << endl;
	cout << "Matricea B este:" << endl;// afisarea
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout << matriceA[i][j] << " ";
		cout << endl;
	}

	matriceA = invers(matriceA, n);
	matriceB = transpusa(matriceB, n);


	cout << "-------------------------------------------" << endl;
	cout << "Matricea C=A^(-1) - B(T) este:" << endl;// afisarea
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			cout << setw(6) << matriceA[i][j] - matriceB[i][j] << " ";
		cout << endl;
	}

	for (i = 0; i < n; i++) // dealocarea memoriei
		delete[] matriceA[i];
	delete[] matriceA;
	for (i = 0; i < n; i++) // dealocarea memoriei
		delete[] matriceB[i];
	delete[] matriceB;

	return 0;
}