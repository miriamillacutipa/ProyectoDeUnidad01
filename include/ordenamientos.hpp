#ifndef ORDENAMIENTOS_HPP
#define ORDENAMIENTOS_HPP
#include <string> 

extern long long comparacionesInsercion;
extern long long movimientosInsercion;
extern long long comparacionesShell;
extern long long movimientosShell;

void insercionDir(int A[], int n);
void ShellSort(int A[], int n);
std::string saltosShell(int n);

#endif
