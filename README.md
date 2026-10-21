# Análisis Comparativo Empírico: Inserción vs. Shellsort en C++

## Descripción
Este repositorio contiene el código en C++, el experimento y la documentación académica para comparar ambos dos algoritmos de ordenacion:

* **Inserción Directa (Insertion Sort):** Algoritmo sencillo de complejidad cuadrática O(n²) que ordena elemento por elemento. Su ventaja es que es estable, es decir, conserva el orden original de los datos iguales.

* **Shellsort:** Variante más rápida de complejidad promedio O(n^1.3) que compara elementos alejados entre sí (usando la secuencia k = n/2). Al mover datos a mayor distancia, pierde la estabilidad.
  
---

## Objetivos
1. Implementar los algoritmos de Inserción y Shellsort en C++.
2. Evaluar el desempeño temporal (benchmark) de ambos algoritmos variando el tamaño de las entradas.
3. Analizar empíricamente el impacto de la complejidad teórica O(n²) frente a O(n^1.3) en tiempo real de ejecución.
