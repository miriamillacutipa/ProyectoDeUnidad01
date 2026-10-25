#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

//Método de insercion
void InsertionSort(vector<int>& A, int n, long long &inter, long long &comp, double &tiempo) {
	inter=0, comp=0;
	int aux, k;
	
	chrono::steady_clock::time_point inicio = chrono::steady_clock::now();
	
	for (int i=1; i<n; i++) {
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
	
	chrono::steady_clock::time_point fin = chrono::steady_clock::now();
    tiempo = chrono::duration<double, milli>(fin - inicio).count();
} 

//Metodo de Shell
void ShellSort(vector<int>& A, int n, long long &inter, long long &comp, double &tiempo) {
	inter=0, comp=0;
	
	chrono::steady_clock::time_point inicio = chrono::steady_clock::now();
	
	int k = n/2, aux, j;
    while (k > 0) {
        for (int i=k; i<n; i++) {
        	aux= A[i];
        	j=i;
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
    
    chrono::steady_clock::time_point fin = chrono::steady_clock::now();
    tiempo = chrono::duration<double, milli>(fin - inicio).count();
}

int main() {
	
	vector<int> entrada = {8, 2, 3, 9, 1, 3, 8, 5, 3, 8};
    int n = 10;
    
    vector<int> A = entrada;
	vector<int> B = entrada;


    long long  comp1 = 0, inter1 = 0;
    long long comp2 = 0, inter2 = 0;
    double tiempo1 = 0.0, tiempo2 = 0.0;

    InsertionSort(A, n, inter1, comp1, tiempo1);
    ShellSort(B, n, inter2, comp2, tiempo2);
    
    cout << "Arreglo Base: ";
    for (int i = 0; i < n; i++) {
        cout << entrada[i] << " ";
    }
    cout << endl;

    cout << "\nInsercion ordenada: ";
    for (int i=0; i<n; i++) {
    	cout << A[i]<< " ";
	}
    cout << "\nComparaciones: " << comp1 << endl;
	cout << "Intercambios: "<< inter1 << endl;
	cout << "Tiempo: "<< tiempo1 << "ms" << endl;

    cout << "\nShellsort ordenado: ";
    for (int i=0; i<n; i++) {
    	cout<< B[i] << " ";
	}
    cout << "\nComparaciones: " << comp2 << endl;
	cout << "Intercambios: "<< inter2 <<endl;
	cout << "Tiempo: " << tiempo2 << "ms" << endl;

    return 0;
}
