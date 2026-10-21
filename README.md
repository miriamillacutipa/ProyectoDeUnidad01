# Análisis Comparativo Empírico: Inserción vs. Shellsort en C++

## Descripción
Este repositorio contiene el código en C++, el experimento y la documentación académica para comparar ambos dos algoritmos de ordenacion:

* **Inserción Directa (Insertion Sort):** Algoritmo sencillo de complejidad cuadrática O(n²) que ordena elemento por elemento. Su ventaja es que es estable, es decir, conserva el orden original de los datos iguales.

* **Shellsort:** Variante más rápida de complejidad promedio O(n^1.3) que compara elementos alejados entre sí (usando la secuencia k = n/2). Al mover datos a mayor distancia, pierde la estabilidad.
  

## Objetivos
1. Implementar los algoritmos de Inserción y Shellsort en C++.
2. Evaluar el desempeño temporal (benchmark) de ambos algoritmos variando el tamaño de las entradas.
3. Analizar empíricamente el impacto de la complejidad teórica O(n²) frente a O(n^1.3) en tiempo real de ejecución.


## Métricas Evaluadas
* **Tiempo de ejecución (ms):** Duración del proceso de ordenamiento.
* **Número de comparaciones:** Cantidad de veces que se comparan dos elementos del arreglo.
* **Número de intercambios:** Cantidad de desplazamientos/asignaciones realizadas en memoria.
* **Profundidad de recursión:** No aplica (ambos algoritmos son iterativos).


## Estructura del Repositorio
* `src/`: Código fuente en C++ de los algoritmos y el benchmark.
* `include/`: Interfaces y cabeceras comunes.
* `results/`: Archivos CSV con los datos crudos obtenidos del experimento.
* `docs/`: Documentación académica del proyecto (`manuscrito.pdf` y `diapositiva.pdf`).


## Entorno de Pruebas
* **CPU:** Intel Core 5 120U (10 núcleos, 12 hilos, 1.40 GHz)
* **Sistema Operativo:** Windows 11 Home Single Language (compilación 26200)
* **Modelo del equipo:** ASUS Vivobook 15 X1504VA
* **Compilador:** GCC g++ (versión 11.0 o superior)
* **Estándar C++:** C++17
