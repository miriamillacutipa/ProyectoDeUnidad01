#ifndef SORTING_HPP
#define SORTING_HPP

#include <vector>

using namespace std;

void InsertionSort(vector<int>& A, int n, long long &inter, long long &comp, double &tiempo);
void ShellSort(vector<int>& A, int n, long long &inter, long long &comp, double &tiempo);
vector<int> generarPatron(const string& patron, int n, int semilla);
#endif

