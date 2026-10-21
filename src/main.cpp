#include <iostream>
using namespace std;

//Método de insercion
void InsertionSort(int A[], int n, long &inter, long &comp) {
	inter=0, comp=0;
	int aux, k;
	for (int i=0; i<n; i++) {
		aux= A[i];
		k= i-1;
		while(k>=0) {
			comp++;
			if(A[k] > aux) {
				A[k+1] = A[k];
				inter++;
				k--;
			} else {
				break;
			}
		}
		A[k+1] =aux;
	}
} 

//Metodo de Shell
void ShellSort(int A[], int n, long &inter, long &comp) {
	inter=0, comp=0;
	int k = n/2, aux;
    while (k > 0) {
        for (int i=k; i<n; i++) {
        	int aux= A[i];
        	int j=i;
            while (j>=k) {
                comp++;
                if (A[j-k] > aux) {
                    A[j] = A[j-k];
                    inter++;
                    j = j - k;
                } else {
                    break;
                }
            }
            A[j] = aux;
        }
        k = k/2;
    }
}

int main() {
	int A[10] = {8, 2, 3, 9, 1, 3, 8, 5, 3, 8};
    int B[10] = {8, 2, 3, 9, 1, 3, 8, 5, 3, 8};
    int n = 10;

    long comp1 = 0, inter1 = 0;
    long comp2 = 0, inter2 = 0;

    InsertionSort(A, n, comp1, inter1);
    ShellSort(B, n, comp2, inter2);

    cout << "Insercion ordenada: ";
    for (int i=0; i<n; i++) cout << A[i]<< " ";
    cout << "\nComparaciones: " << comp1 << endl;
	cout << "Intercambios: "<< inter1 << endl;

    cout << "\nShellsort ordenado: ";
    for (int i=0; i<n; i++) cout<< B[i] << " ";
    cout << "\nComparaciones: " << comp2 << endl;
	cout << "Intercambios: "<< inter2 <<endl;

    return 0;
}
