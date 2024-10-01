// Copyright 2024 Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>

#include "Ordenador.hpp"

/** Función para generar un arreglo de enteros positivos. */
vector<int> arregloAleatorio(int tam) {
  srand(time(0));  /** Semilla para los números aleatorios. */
  vector<int> arreglo(tam);
  for (int i = 0; i < tam; ++i) {
    /** Generar números positivos hasta el número máximo posible. */
    mt19937 generador(random_device{}());  /** Crear el generador. */
    /** Definir el rango. */
    uniform_int_distribution<uint32_t> distribucion(0, UINT32_MAX);
    /** Asignar un valor aleatorio dentro del rango. */
    arreglo[i] = distribucion(generador);
  }
  return arreglo;
}

/** Función para medir el tiempo y ejecutar el algoritmo. */
double medirTiempo(Ordenador& ordenador, void (Ordenador::*metodo)(int*, int)
  const, vector<int>& arregloOriginal) {
  /** Hacer una copia del arreglo original. */
  vector<int> arreglo(arregloOriginal);
  /** Capturar el tiempo de inicio. */
  auto inicio = chrono::high_resolution_clock::now();
  /** Ejecutar el algoritmo. */
  (ordenador.*metodo)(arreglo.data(), arreglo.size());
  /** Capturar el tiempo de fin. */
  auto fin = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> duracion = fin - inicio;
  return duracion.count();  /** Retornar el tiempo en milisegundos. */
}

int main() {
  Ordenador ordenador;
  vector<int> tams = {50000, 100000, 150000, 200000};
  vector<string> algoritmos = {"Seleccion", "Insercion", "Mezcla",
    "Monticulos", "Rapido", "Residuos"};
  cout << "Tiempos de ejecucion\n";
  cout << "\n";

  for (int i = 0; i < (end(algoritmos)-begin(algoritmos)); i++) {
    if (i == 1) {
      cout << "----- Ordenamiento " << algoritmos[i] << " -----\n";
    } else {
      cout << "----- Ordenamiento por " << algoritmos[i] << " -----\n";
    }
    cout << "\n";
    /** Probar con cada tamaño de arreglo. */
    for (int tam : tams) {
      vector<double> tiempos;
      /** Generar un solo arreglo aleatorio para todas las ejecuciones. */
      vector<int> arreglo = arregloAleatorio(tam);

      /** Ejecutar el algoritmo 3 veces con el mismo arreglo. */
      for (int j = 0; j < 3; j++) {
        double tiempo;
        if (algoritmos[i] == "Seleccion") {
          /** Medir el tiempo de ejecución. */
          tiempo = medirTiempo(ordenador, &Ordenador::
            ordenamientoPorSeleccion, arreglo);
        }
        if (algoritmos[i] == "Insercion") {
          /** Medir el tiempo de ejecución. */
          tiempo = medirTiempo(ordenador, &Ordenador::
            ordenamientoPorInsercion, arreglo);
        }
        if (algoritmos[i] == "Mezcla") {
          /** Medir el tiempo de ejecución. */
          tiempo = medirTiempo(ordenador, &Ordenador::
            ordenamientoPorMezcla, arreglo);
        }
        if (algoritmos[i] == "Monticulos") {
          /** Medir el tiempo de ejecución. */
          tiempo = medirTiempo(ordenador, &Ordenador::
            ordenamientoPorMonticulos, arreglo);
        }
        if (algoritmos[i] == "Rapido") {
          /** Medir el tiempo de ejecución. */
          tiempo = medirTiempo(ordenador, &Ordenador::
            ordenamientoRapido, arreglo);
        }
        if (algoritmos[i] == "Residuos") {
          /** Medir el tiempo de ejecución. */
          tiempo = medirTiempo(ordenador, &Ordenador::
            ordenamientoPorRadix, arreglo);
        }
        tiempos.push_back(tiempo);
        cout << "Tamano: " << tam << " | Tiempo de ejecucion: " << tiempo <<
          " ms\n";
      }
      /** Calcular el promedio de los 3 tiempos. */
      double promedio = (tiempos[0] + tiempos[1] + tiempos[2]) / 3.0;
      cout << "Promedio: " << promedio << " ms\n";
      cout << "\n";
    }
  }
  return 0;
}
