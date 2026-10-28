#ifndef ORDENAMIENTOS_HPP
#define ORDENAMIENTOS_HPP

#include <string>

void InsertionSort(int A[], int n, long long& mov, long long& comp, double& tiempo);
void ShellSort(int A[], int n, long long& mov, long long& comp, double& tiempo);
std::string saltosShell(int n);

#endif
