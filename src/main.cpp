#include "./cabecera.hpp"
#include <iostream>
#include <fstream>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif
#include <chrono>
using namespace std;

void InsertionSort(int A[], int n, long long& mov, long long& comp, double& tiempo) {
    mov = 0;
    comp = 0;
    int aux, k;

    chrono::steady_clock::time_point inicio = chrono::steady_clock::now();

    for (int i = 1; i < n; i++) {
        aux = A[i];
        k = i - 1;
        while (k >= 0) {
            comp++;
            if (A[k] > aux) {
                A[k + 1] = A[k];
                mov++;
                k--;
            } else {
                break;
            }
        }
        A[k + 1] = aux;
        mov++;
    }

    chrono::steady_clock::time_point fin = chrono::steady_clock::now();

    tiempo = chrono::duration<double, milli>(fin - inicio).count();
}

void ShellSort(int A[], int n, long long& mov, long long& comp, double& tiempo) {
    mov = 0;
    comp = 0;
    int k, aux, j;

    chrono::steady_clock::time_point inicio = chrono::steady_clock::now();

    k = n + 1;
    while (k > 1) {
        k = k / 2;
        for (int i = k; i < n; i++) {
            aux = A[i];
            j = i;
            while (j >= k) {
                comp++;
                if (A[j - k] > aux) {
                    A[j] = A[j - k];
                    mov++;
                    j = j - k;
                } else {
                    break;
                }
            }
            A[j] = aux;
            mov++;
        }
    }

    chrono::steady_clock::time_point fin = chrono::steady_clock::now();
    tiempo = chrono::duration<double, milli>(fin - inicio).count();
}

int main() {
    const int REPETICIONES = 30;
    const int TAMANOS[] = {1000, 10000, 100000};
    int escenario, opcionCantidad;

    cout << "ESCENARIO\n1. Aleatorio uniforme\n2. Ascendente\n3. Descendente\nElige: ";
    if (!(cin >> escenario) || escenario < 1 || escenario > 3) {
        cout << "Opcion invalida.\n";
        return 1;
    }
    cout << "\nCANTIDAD\n1. 1000\n2. 10000\n3. 100000\nElige: ";
    if (!(cin >> opcionCantidad) || opcionCantidad < 1 || opcionCantidad > 3) {
        cout << "Opcion invalida.\n";
        return 1;
    }
    int n = TAMANOS[opcionCantidad - 1];

#ifdef _WIN32
    _mkdir("csvalgoritmos");
#else
    mkdir("csvalgoritmos", 0755);
#endif
    int numero = 1;
    string ruta;
    do {
        ruta = "csvalgoritmos/csvalgoritmos_" + to_string(numero++) + ".csv";
    } while (ifstream(ruta.c_str()).good());
    ofstream csv(ruta.c_str());
    if (!csv) {
        cout << "No se pudo crear el archivo CSV.\n";
        return 1;
    }
    csv << "algoritmo,n,patron,repeticion,tiempo_ms,comparaciones,"
           "intercambios,movimientos,profundidad_recursion,semilla,"
           "commit_hash,correcto,saltos\n";
    csv.setf(ios::fixed);
    csv.precision(9);

    int* entrada = new int[n];
    int* A = new int[n];
    int* B = new int[n];
    unsigned int semillaBase = static_cast<unsigned int>(
        chrono::system_clock::now().time_since_epoch().count());
    bool todoCorrecto = true;

    for (int repeticion = 1; repeticion <= REPETICIONES; repeticion++) {

        unsigned int semilla = semillaBase + repeticion;
        generarEntrada(entrada, n, escenario, semilla);
        copiarEntradas(entrada, A, B, n);

        long long comp1 = 0, mov1 = 0, comp2 = 0, mov2 = 0;
        double tiempo1 = 0.0, tiempo2 = 0.0;
        InsertionSort(A, n, mov1, comp1, tiempo1);
        ShellSort(B, n, mov2, comp2, tiempo2);

        bool correctoInsercion = estaOrdenado(A, n);
        bool correctoShell = estaOrdenado(B, n);
        if (!correctoInsercion || !correctoShell) todoCorrecto = false;

        csv << "insercion," << n << ',' << nombrePatron(escenario)
            << ',' << repeticion << ',' << tiempo1 << ',' << comp1
            << ",0," << mov1 << ",0," << semilla
            << ",NA," << (correctoInsercion ? 1 : 0) << ",NA\n";
        csv << "shellsort," << n << ',' << nombrePatron(escenario)
            << ',' << repeticion << ',' << tiempo2 << ',' << comp2
            << ",0," << mov2 << ",0," << semilla
            << ",NA," << (correctoShell ? 1 : 0) << ',' << saltosShell(n) << '\n';
        csv.flush();
    }

    delete[] entrada;
    delete[] A;
    delete[] B;
    csv.close();
    if (!csv) {
        cout << "Error al guardar el CSV.\n";
        return 1;
    }
    cout << "\n30 pruebas por algoritmo finalizadas.\nCSV guardado en: " << ruta << '\n';
    if (!todoCorrecto) cout << "Se detectaron resultados incorrectos. Revisa el CSV.\n";
    return todoCorrecto ? 0 : 1;
}
