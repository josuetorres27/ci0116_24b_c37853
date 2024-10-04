// Copyright 2024 Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>

#include "Ordenador.hpp"

/** Función para generar un arreglo dinámico de enteros positivos uint32_t. */
uint32_t* arregloAleatorio(int tam, uint32_t semilla) {
  /** Semilla fija para los números aleatorios. */
  mt19937 generador(semilla);
  /** Crear el arreglo dinámico. */
  uint32_t* arreglo = new uint32_t[tam];
  /** Definir el rango de números aleatorios. */
  uniform_int_distribution<uint32_t> distribucion(0, UINT32_MAX);
  /** Llenar el arreglo con números aleatorios de tipo uint32_t. */
  for (int i = 0; i < tam; ++i) {
    arreglo[i] = distribucion(generador);
  }
  return arreglo;
}

/**
 * Función para medir el tiempo y ejecutar el algoritmo con conversión de
 * uint32_t* a int*.
 */
double medirTiempo(Ordenador& ordenador, void (Ordenador::*metodo)(int*, int)
  const, uint32_t* arregloOriginal, int tam) {
  /** Crear un arreglo de tipo int* y copiar los elementos de uint32_t*. */
  int* arreglo = new int[tam];
  for (int i = 0; i < tam; ++i) {
    /** Conversión de uint32_t a int. */
    arreglo[i] = static_cast<int>(arregloOriginal[i]);
  }
  /** Capturar el tiempo de inicio. */
  auto inicio = chrono::high_resolution_clock::now();
  /** Ejecutar el algoritmo. */
  (ordenador.*metodo)(arreglo, tam);
  /** Capturar el tiempo de fin. */
  auto fin = chrono::high_resolution_clock::now();
  chrono::duration<double, milli> duracion = fin - inicio;
  /** Liberar la memoria del arreglo. */
  delete[] arreglo;
  return duracion.count();  /** Retornar el tiempo en milisegundos. */
}

int main() {
  Ordenador ordenador;
  vector<int> tams = {50000, 100000, 150000, 200000};
  vector<string> algoritmos = {"Seleccion", "Insercion", "Mezcla",
    "Monticulos", "Rapido", "Residuos"};
  cout << "Tiempos de ejecucion\n";
  /** Usar una semilla fija para generar los números aleatorios. */
  const uint32_t semilla = 123456;
  for (vector<string>::size_type i = 0; i < algoritmos.size(); i++) {
    if (i == 1) {
      cout << "----- Ordenamiento " << algoritmos[i] << " -----\n";
    } else {
      cout << "----- Ordenamiento por " << algoritmos[i] << " -----\n";
    }
    cout << "\n";
    /** Probar con cada tamaño de arreglo. */
    for (int tam : tams) {
      vector<double> tiempos;
      /**
       * Generar el arreglo dinámico con la semilla y el tamaño especificado.
       */
      uint32_t* arreglo = arregloAleatorio(tam, semilla);

      /** Ejecutar el algoritmo 3 veces con el mismo arreglo. */
      for (int j = 0; j < 3; j++) {
        double tiempo;
        if (algoritmos[i] == "Seleccion") {
          tiempo = medirTiempo(ordenador, &Ordenador::ordenamientoPorSeleccion,
            arreglo, tam);
        }
        if (algoritmos[i] == "Insercion") {
          tiempo = medirTiempo(ordenador, &Ordenador::ordenamientoPorInsercion,
            arreglo, tam);
        }
        if (algoritmos[i] == "Mezcla") {
          tiempo = medirTiempo(ordenador, &Ordenador::ordenamientoPorMezcla,
            arreglo, tam);
        }
        if (algoritmos[i] == "Monticulos") {
          tiempo = medirTiempo(ordenador,
            &Ordenador::ordenamientoPorMonticulos, arreglo, tam);
        }
        if (algoritmos[i] == "Rapido") {
          tiempo = medirTiempo(ordenador, &Ordenador::ordenamientoRapido,
            arreglo, tam);
        }
        if (algoritmos[i] == "Residuos") {
          tiempo = medirTiempo(ordenador, &Ordenador::ordenamientoPorRadix,
            arreglo, tam);
        }
        tiempos.push_back(tiempo);
        cout << "Tamano: " << tam << " | Tiempo de ejecucion: " << tiempo <<
          " ms\n";
      }
      /** Calcular el promedio de los 3 tiempos. */
      double promedio = (tiempos[0] + tiempos[1] + tiempos[2]) / 3.0;
      cout << "Promedio: " << promedio << " ms\n\n";

      /** Liberar la memoria del arreglo original. */
      delete[] arreglo;
    }
  }
  return 0;
}
