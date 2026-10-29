#ifndef CABECERA_HPP
#define CABECERA_HPP

void InsertionSort(int A[], int n, long long& mov, long long& comp, double& tiempo);
void ShellSort(int A[], int n, long long& mov, long long& comp, double& tiempo);

#include <random>
#include <string>

inline void aleatorioUniforme(int entrada[], int n, unsigned int semilla) {
    std::mt19937 generador(semilla);
    std::uniform_int_distribution<int> aleatorio(0, 1000000);
    for (int i = 0; i < n; i++) entrada[i] = aleatorio(generador);
}

inline void ordenadoAscendente(int entrada[], int n) {
    for (int i = 0; i < n; i++) entrada[i] = i;
}

inline void ordenadoDescendente(int entrada[], int n) {
    for (int i = 0; i < n; i++) entrada[i] = n - i;
}

inline void generarEntrada(int entrada[], int n, int escenario, unsigned int semilla) {
    if (escenario == 1) aleatorioUniforme(entrada, n, semilla);
    else if (escenario == 2) ordenadoAscendente(entrada, n);
    else ordenadoDescendente(entrada, n);
}

inline void copiarEntradas(const int entrada[], int A[], int B[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = entrada[i];
        B[i] = entrada[i];
    }
}

inline bool estaOrdenado(const int A[], int n) {
    for (int i = 1; i < n; i++) {
        if (A[i - 1] > A[i]) return false;
    }
    return true;
}

inline const char* nombrePatron(int escenario) {
    if (escenario == 1) return "aleatorio_uniforme";
    if (escenario == 2) return "ascendente";
    return "descendente";
}

inline std::string saltosShell(int n) {
    std::string texto;
    int k = n + 1;
    while (k > 1) {
        k = k / 2;
        if (!texto.empty()) texto += ";";
        texto += std::to_string(k);
    }
    return texto;
}

#endif
