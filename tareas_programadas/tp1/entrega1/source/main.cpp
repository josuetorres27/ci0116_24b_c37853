#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <limits.h>
#include "Ordenador.hpp"

/** Función para generar un arreglo de enteros positivos. */
vector<int> arregloAleatorio(int tam) {
  srand(time(0));  /** Semilla para los números aleatorios. */
  vector<int> arreglo(tam);
  for (int i = 0; i < tam; ++i) {
    arreglo[i] = rand() % INT_MAX + 1;  /** Generar números positivos hasta el número máximo posible. */
  }
  return arreglo;
}

/** Función para medir el tiempo y ejecutar el algoritmo. */
double medirTiempo(Ordenador& ordenador, void (Ordenador::*metodo)(int*, int)
  const, vector<int>& arregloOriginal) {
  vector<int> arreglo(arregloOriginal);  /** Hacer una copia del arreglo original. */
  auto inicio = chrono::high_resolution_clock::now();  /** Capturar el tiempo de inicio. */
  (ordenador.*metodo)(arreglo.data(), arreglo.size());  /** Ejecutar el algoritmo. */
  auto fin = chrono::high_resolution_clock::now();  /** Capturar el tiempo de fin. */
  chrono::duration<double, milli> duracion = fin - inicio;
  return duracion.count();  /** Retornar el tiempo en milisegundos. */
}

int main() {
  Ordenador ordenador;

  vector<int> tams = {50000, 100000, 150000, 200000};
  vector<string> algoritmos = {"Seleccion", "Insercion", "Mezcla"};
  cout<<"Tiempos de ejecucion\n";
  cout<<"\n";

  for (int i = 0; i < (end(algoritmos)-begin(algoritmos)); i++) {
    cout<<"----- Algoritmo por "<<algoritmos[i]<<" -----\n";
    cout<<"\n";
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
        tiempos.push_back(tiempo);
        cout<<"Tamano: "<<tam<<" | Tiempo de ejecucion: "<<tiempo<<" ms\n";
      }
      /** Calcular el promedio de los 3 tiempos. */
      double promedio = (tiempos[0] + tiempos[1] + tiempos[2]) / 3.0;
      cout<<"Promedio: "<<promedio<<" ms\n";
      cout<<"\n";
    }
  }
  return 0;
}
