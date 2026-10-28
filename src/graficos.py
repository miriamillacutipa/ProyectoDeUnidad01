import argparse
import csv
import hashlib
import io
import math
import re
import statistics
import sys
from collections import defaultdict
from datetime import datetime
from pathlib import Path


def seleccionar_archivos():
    try:
        import tkinter as tk
        from tkinter import filedialog
        ventana = tk.Tk()
        ventana.withdraw()
        try:
            rutas = filedialog.askopenfilenames(
                title="Selecciona los CSV de tus pruebas (Ctrl para elegir varios)",
                filetypes=[("Archivos CSV", "*.csv")],
            )
        finally:
            ventana.destroy()
        return [Path(ruta) for ruta in rutas]
    except Exception as error:
        raise ValueError(
            "No se pudo abrir el selector. Usa: "
            "python analizar_ordenamientos.py --carpeta resultados"
        ) from error


def cargar_archivos(rutas):
    datos = []
    fuentes = []
    avisos = []
    huellas = set()
    for ruta in rutas:
        contenido = ruta.read_bytes()
        huella = hashlib.sha256(contenido).hexdigest()
        if huella in huellas:
            avisos.append("Copia identica omitida: " + str(ruta))
            continue
        try:
            texto = contenido.decode("utf-8-sig")
        except UnicodeDecodeError:
            texto = contenido.decode("cp1252")
        primera_linea = texto.splitlines()[0] if texto.splitlines() else ""
        delimitador = ";" if primera_linea.count(";") > primera_linea.count(",") else ","
        lector = csv.DictReader(io.StringIO(texto), delimiter=delimitador)
        if lector.fieldnames:
            lector.fieldnames = [nombre.strip().lower() for nombre in lector.fieldnames]
        requeridas = {"algoritmo", "n", "patron", "repeticion", "tiempo_ms"}
        if not requeridas.issubset(lector.fieldnames or []):
            avisos.append("CSV sin columnas de mediciones, omitido: " + str(ruta))
            continue
        filas = 0
        for fila_num, fila in enumerate(lector, start=2):
            try:
                algoritmo = fila["algoritmo"].strip().lower()
                patron = fila["patron"].strip().lower()
                if patron == "aleatorio":
                    patron = "aleatorio_uniforme"
                n = int(fila["n"])
                repeticion = int(fila["repeticion"])
                tiempo = float(fila["tiempo_ms"].strip().replace(",", "."))
                if not algoritmo or not patron or n <= 0 or repeticion <= 0:
                    raise ValueError("algoritmo/patron vacio o n/repeticion invalido")
                if not math.isfinite(tiempo) or tiempo < 0:
                    raise ValueError("tiempo_ms debe ser finito y no negativo")
                if "correcto" in fila and fila["correcto"].strip().lower() not in {"1", "true"}:
                    raise ValueError("el ordenamiento no tiene correcto=1")
            except (ValueError, TypeError, AttributeError) as error:
                raise ValueError(f"{ruta}, fila {fila_num}: {error}") from error
            datos.append({"algoritmo": algoritmo, "patron": patron, "n": n,
                          "repeticion": repeticion, "tiempo_ms": tiempo,
                          "archivo_origen": str(ruta)})
            filas += 1
        if filas:
            huellas.add(huella)
            fuentes.append((str(ruta), filas, huella))
    if not datos:
        raise ValueError("No se encontraron mediciones validas en los CSV seleccionados.")
    return datos, fuentes, avisos


def calcular_resumen(datos):
    grupos = defaultdict(list)
    for fila in datos:
        grupos[(fila["algoritmo"], fila["patron"], fila["n"])].append(fila["tiempo_ms"])
    resumen = []
    for (algoritmo, patron, n), tiempos in sorted(grupos.items(), key=lambda x: (x[0][1], x[0][0], x[0][2])):
        resumen.append({
            "algoritmo": algoritmo, "patron": patron, "n": n,
            "mediciones": len(tiempos),
            "media_ms": statistics.mean(tiempos),
            "mediana_ms": statistics.median(tiempos),
            "desviacion_estandar_ms": statistics.stdev(tiempos) if len(tiempos) > 1 else None,
            "minimo_ms": min(tiempos), "maximo_ms": max(tiempos),
        })
    return resumen


def nombre_seguro(texto):
    return re.sub(r"[^a-zA-Z0-9_-]", "_", texto)


def crear_visuales(resumen, salida):
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
    plt.rcParams.update({"font.size": 10, "axes.spines.top": False,
                         "axes.spines.right": False, "figure.facecolor": "white"})
    etiquetas = {"aleatorio_uniforme": "Aleatorio uniforme", "ascendente": "Ordenado ascendente",
                 "descendente": "Ordenado descendente"}
    nombres = {"insercion": "Inserción", "shellsort": "Shellsort"}
    colores = {"insercion": "#2455A4", "shellsort": "#D45A24"}
    avisos = []
    for patron in sorted({fila["patron"] for fila in resumen}):
        filas = [fila for fila in resumen if fila["patron"] == patron]
        titulo = etiquetas.get(patron, patron)
        sufijo = nombre_seguro(patron)
        fig, ax = plt.subplots(figsize=(8.8, 5.4), constrained_layout=True)
        for algoritmo in sorted({fila["algoritmo"] for fila in filas}):
            serie = sorted((f for f in filas if f["algoritmo"] == algoritmo), key=lambda f: f["n"])
            ax.plot([f["n"] for f in serie], [f["media_ms"] for f in serie],
                    marker="o", linewidth=2, label=nombres.get(algoritmo, algoritmo),
                    color=colores.get(algoritmo))
        tamanos = sorted({fila["n"] for fila in filas})
        ax.set_xscale("log")
        ax.set_xticks(tamanos, [f"{n:,}".replace(",", " ") for n in tamanos])
        ax.minorticks_off()
        ax.set_ylim(bottom=0)
        ax.set_xlabel("Tamaño de entrada n (eje logarítmico)")
        ax.set_ylabel("Tiempo medio (ms)")
        ax.set_title("n frente a tiempo medio — " + titulo, pad=12)
        ax.grid(axis="y", alpha=0.25)
        ax.legend()
        if len(tamanos) < 2:
            ax.text(0.02, 0.97, "Un solo tamaño: agrega otros CSV para observar la tendencia.",
                    transform=ax.transAxes, va="top", fontsize=9)
            avisos.append(f"{patron}: solo hay un tamaño; no permite evaluar crecimiento.")
        fig.savefig(salida / ("n_vs_tiempo_" + sufijo + ".png"), dpi=200)
        plt.close(fig)

        def numero(valor):
            return "N/D" if valor is None else f"{valor:.6f}"
        celdas = [[nombres.get(f["algoritmo"], f["algoritmo"]), str(f["n"]), str(f["mediciones"]),
                   numero(f["media_ms"]), numero(f["mediana_ms"]),
                   numero(f["desviacion_estandar_ms"]), numero(f["minimo_ms"]),
                   numero(f["maximo_ms"])] for f in filas]
        fig, ax = plt.subplots(figsize=(12, max(2.6, 1.4 + len(filas) * 0.4)))
        ax.axis("off")
        ax.set_title("Estadística del tiempo — " + titulo, fontsize=13, pad=16)
        tabla = ax.table(cellText=celdas, colLabels=["Algoritmo", "n", "Mediciones", "Media\n(ms)",
                          "Mediana\n(ms)", "Desv. estándar\n(ms)", "Mínimo\n(ms)", "Máximo\n(ms)"],
                         cellLoc="center", loc="center", colWidths=[.14, .09, .10, .13, .13, .15, .13, .13])
        tabla.auto_set_font_size(False)
        tabla.set_fontsize(9)
        tabla.scale(1, 1.9)
        for (r, c), celda in tabla.get_celld().items():
            celda.set_edgecolor("#DCE2EA")
            if r == 0:
                celda.set_facecolor("#1D3557")
                celda.set_text_props(color="white", weight="bold")
                celda.set_height(celda.get_height() * 1.45)
            else:
                celda.set_facecolor("#F0F4F8" if r % 2 else "white")
        fig.text(.5, .025, "Desviación estándar muestral (N−1). N/D: menos de dos mediciones.",
                 ha="center", fontsize=9)
        fig.tight_layout(rect=(0, .06, 1, 1))
        fig.savefig(salida / ("tabla_" + sufijo + ".png"), dpi=200, bbox_inches="tight")
        plt.close(fig)
    return avisos


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("archivos", nargs="*", type=Path, help="CSV que se van a analizar")
    parser.add_argument("--carpeta", type=Path, help="Buscar CSV dentro de esta carpeta y sus subcarpetas")
    parser.add_argument("--salida", type=Path, default=Path("analisis"), help="Carpeta base de salida")
    args = parser.parse_args()
    rutas = list(args.archivos)
    if args.carpeta:
        if not args.carpeta.is_dir():
            raise ValueError("La carpeta de entrada no existe: " + str(args.carpeta))
        rutas += sorted(args.carpeta.rglob("*.csv"))
    if not rutas and not args.carpeta:
        rutas = seleccionar_archivos()
    if not rutas:
        print("No se seleccionaron archivos.")
        return
    rutas = sorted({ruta.resolve() for ruta in rutas})
    datos, fuentes, avisos = cargar_archivos(rutas)
    resumen = calcular_resumen(datos)
    for fila in resumen:
        if fila["mediciones"] < 30:
            avisos.append(f"Menos de 30 mediciones: {fila['algoritmo']}, {fila['patron']}, n={fila['n']}.")
    salida = args.salida / datetime.now().strftime("analisis_%Y%m%d_%H%M%S_%f")
    salida.mkdir(parents=True, exist_ok=False)
    with (salida / "resumen_estadistico.csv").open("w", encoding="utf-8-sig", newline="") as archivo:
        escritor = csv.DictWriter(archivo, fieldnames=list(resumen[0]))
        escritor.writeheader()
        escritor.writerows(resumen)
    avisos += crear_visuales(resumen, salida)
    lineas = ["ANÁLISIS DE INSERCIÓN Y SHELLSORT", "",
              f"Archivos incluidos: {len(fuentes)}. Mediciones: {len(datos)}.",
              "Agrupación: algoritmo, patrón y n. Todos los tiempos están en ms.",
              "Desviación estándar muestral: divisor N-1. Con N=1 se deja vacía en CSV.",
              "Las gráficas representan la media. Eje n logarítmico y eje tiempo lineal.",
              "Varias ejecuciones del mismo grupo se combinan; no se eliminan repeticiones iguales.",
              "Se omiten copias de archivos con contenido idéntico (SHA-256).",
              "Combine únicamente pruebas del mismo equipo, compilador y opciones de compilación.",
              "Estos datos no permiten deducir por sí solos una complejidad asintótica.", "", "FUENTES:"]
    lineas += [f"{ruta}\n  Filas: {cantidad}; SHA-256: {huella}" for ruta, cantidad, huella in fuentes]
    lineas += ["", "AVISOS:"] + (avisos or ["Ninguno."])
    (salida / "detalles_analisis.txt").write_text("\n".join(lineas), encoding="utf-8")
    print("\n" + " ".join(["Algoritmo", "Patrón", "n", "Mediciones", "Media(ms)", "Mediana(ms)", "DE(ms)", "Mín(ms)", "Máx(ms)"]))
    for f in resumen:
        de = "N/D" if f["desviacion_estandar_ms"] is None else f"{f['desviacion_estandar_ms']:.6f}"
        print(f"{f['algoritmo']} {f['patron']} {f['n']} {f['mediciones']} "
              f"{f['media_ms']:.6f} {f['mediana_ms']:.6f} {de} {f['minimo_ms']:.6f} {f['maximo_ms']:.6f}")
    for aviso in avisos:
        print("AVISO:", aviso)
    print("\nResultados guardados en:", salida.resolve())


if __name__ == "__main__":
    try:
        main()
    except (ValueError, OSError, csv.Error) as error:
        print("ERROR:", error, file=sys.stderr)
        sys.exit(1)
    except ImportError:
        print("Instala matplotlib con: python -m pip install matplotlib", file=sys.stderr)
        sys.exit(1)
