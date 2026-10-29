# Análisis Comparativo Empírico: Inserción Directa vs. Shellsort en C++

## 1. Descripción del proyecto

Este repositorio contiene el código fuente en C++, las pruebas experimentales y la documentación académica del proyecto, cuyo objetivo es comparar el rendimiento de dos algoritmos de ordenamiento: Inserción Directa (Insertion Sort) y Shellsort.

La comparación se realiza mediante el tiempo de ejecución, la cantidad de comparaciones y los movimientos efectuados durante el ordenamiento de arreglos de números enteros.

El programa permite seleccionar el tipo de entrada y la cantidad de elementos. Ambos algoritmos reciben los mismos datos, se ejecutan por separado y guardan sus resultados en archivos CSV para facilitar su análisis posterior.

## 2. Autor

- **Nombre completo:** Miriam Aydde Illacutipa Choque.
- **Universidad:** Universidad Nacional Jorge Basadre Grohmann.
- **Facultad:** Facultad de Ingeniería.
- **Escuela Profesional:** Ingeniería en Informática y Sistemas.
- **Asignatura:** Programación Avanzada.
- **Repositorio GitHub:** https://github.com/miriamillacutipa/ProyectoDeUnidad01

## 3. Algoritmos seleccionados

### Inserción Directa (Insertion Sort)

Algoritmo que ordena los elementos uno por uno, comparando cada elemento con los anteriores y desplazando los valores mayores hasta encontrar su posición correcta.

- Es un algoritmo estable.
- Su mejor caso es O(n).
- Su caso promedio y peor caso son O(n²).

### Shellsort

Algoritmo que mejora el método de Inserción Directa mediante comparaciones entre elementos separados por determinados saltos.

En esta implementación, los saltos comienzan aproximadamente en la mitad del tamaño del arreglo y se reducen sucesivamente hasta llegar a uno.

- No garantiza estabilidad.
- Su rendimiento depende del tamaño y del orden inicial de los datos.
- Ambos algoritmos son iterativos y no utilizan recursión.

## 4. Requisitos para la compilación y ejecución

Para ejecutar el proyecto se necesita:

- Sistema operativo Windows.
- Dev-C++ o Visual Studio Code para compilar y ejecutar el código fuente en C++.
- Compilador G++ compatible con C++11.
- Python 3.
- Matplotlib para la generación de gráficas.
- Excel para organizar los resultados experimentales.

## 5. Instrucciones para reproducir los experimentos

### 5.1. Descargar el repositorio

```bash
git clone https://github.com/miriamillacutipa/ProyectoDeUnidad01.git
````

Ingresar a la carpeta del proyecto:

```
cd ProyectoDeUnidad01
```

### 5.2. Compilar el programa

Desde la carpeta principal del proyecto, ejecutar:

```
g++ -std=c++11 -O2 -Wall -Wextra -Iinclude src/main.cpp -o main.exe
```

### 5.3. Ejecutar el programa

En Windows, desde PowerShell:

```
.\main.exe
```

El programa mostrará los menús para seleccionar el escenario y la cantidad de elementos.

### 5.4. Seleccionar el escenario

Se pueden elegir tres patrones de entrada:

- `1`: Aleatorio uniforme.
- `2`: Ascendente.
- `3`: Descendente.

### 5.5. Seleccionar el tamaño

Se pueden realizar pruebas con:

- `1000` elementos.
- `10000` elementos.
- `100000` elementos.

El programa ejecuta ambos algoritmos con los mismos datos iniciales y realiza 30 repeticiones por algoritmo.

Al finalizar, se genera un archivo CSV con los resultados de las pruebas.

## 6. Tamaños, patrones y semillas utilizados

### Tamaños de entrada

| Tamaño  | Cantidad de elementos |
| ------- | --------------------- |
| Pequeño | 1 000                 |
| Mediano | 10 000                |
| Grande  | 100 000               |

### Patrones de entrada

| Patrón             | Descripción                                     |
| ------------------ | ----------------------------------------------- |
| Aleatorio uniforme | Números enteros aleatorios entre 0 y 1 000 000. |
| Ascendente         | Números ordenados de menor a mayor.             |
| Descendente        | Números ordenados de mayor a menor.             |

### Semillas

Para las entradas aleatorias, se utiliza `mt19937` junto con `uniform_int_distribution<int>`.

La semilla se obtiene del reloj del sistema y se registra en el archivo CSV para identificar la entrada utilizada en cada prueba.

En los patrones ascendente y descendente, los datos se generan mediante secuencias ordenadas.

## 7. Descripción de los archivos de resultados

Los resultados experimentales se guardan en archivos CSV.

| Archivo o carpeta       | Descripción                                                     |
| ----------------------- | --------------------------------------------------------------- |
| `csvalgoritmos/`        | Carpeta donde se guardan los CSV generados por el programa C++. |
| `mediciones_1000.csv`   | Resultados consolidados para el tamaño de 1 000 elementos.      |
| `mediciones_10000.csv`  | Resultados consolidados para el tamaño de 10 000 elementos.     |
| `mediciones_100000.csv` | Resultados consolidados para el tamaño de 100 000 elementos.    |
| `results/`              | Tablas estadísticas y gráficas generadas durante el análisis.   |

Los archivos CSV contienen información sobre el algoritmo utilizado, el tamaño de entrada, el patrón, la repetición, el tiempo de ejecución, las comparaciones, los movimientos y la correctitud.

## 8. Análisis de resultados

Los resultados se organizan en tablas y gráficas para comparar el rendimiento de ambos algoritmos.

Mediante Python y Matplotlib se procesan los datos experimentales y se generan gráficas que permiten observar la variación del tiempo de ejecución según el tamaño y el patrón de entrada.

Los tiempos promedio obtenidos en el experimento fueron:

| Patrón      | n       | Inserción (ms) | Shellsort (ms) |
| ----------- | ------- | -------------- | -------------- |
| Aleatorio   | 1 000   | 1,067817       | 0,185617       |
| Aleatorio   | 10 000  | 98,263750      | 2,725607       |
| Aleatorio   | 100 000 | 5667,339010    | 32,591510      |
| Ascendente  | 1 000   | 0,005473       | 0,046683       |
| Ascendente  | 10 000  | 0,053690       | 2,102713       |
| Ascendente  | 100 000 | 0,383270       | 6,412127       |
| Descendente | 1 000   | 2,015637       | 0,067053       |
| Descendente | 10 000  | 198,767420     | 0,895327       |
| Descendente | 100 000 | 9141,407877    | 6,417387       |

## 9. Principales resultados y conclusiones

- Shellsort presentó menores tiempos promedio en las entradas aleatorias y descendentes.
- Inserción Directa fue más eficiente cuando los datos ya estaban ordenados de forma ascendente.
- El rendimiento de los algoritmos depende del tamaño y del patrón de entrada.
- Inserción Directa presenta un comportamiento cuadrático en el caso promedio y peor caso.
- Shellsort mostró mejores resultados en varios escenarios con mayor cantidad de elementos.

En conclusión, ambos algoritmos cumplen correctamente con la función de ordenar los datos, pero su rendimiento varía según las características de la entrada.

Shellsort resulta más conveniente en varios escenarios con grandes cantidades de datos, mientras que Inserción Directa destaca cuando los datos ya están ordenados.

## 10. Video de demostración

- Enlace de YouTube: https://youtu.be/LTH4TvSmp38?si=7P1dUX3O5V3LEfcl
- Visibilidad: No listado.

El video presenta el funcionamiento del programa, la implementación de los algoritmos, la ejecución de las pruebas, los archivos CSV y el análisis de los resultados obtenidos.

## 11. Identificador del commit final

\- Commit correspondiente a la versión final: subiendo ultima actualización

## 12. Estructura del repositorio

```
ProyectoDeUnidad01/
├── docs/
│   ├── articulo_Insercionyshellsort.docx
│   └── articulo_Insercionyhellsort.pdf
├── include/
│   └── cabecera.hpp
├── results/
├── src/
│   ├── main.cpp
│   └── graficos.py
└── README.md
```

```
