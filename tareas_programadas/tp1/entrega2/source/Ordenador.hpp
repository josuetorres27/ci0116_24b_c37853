// Copyright 2024 Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits.h>
#include <utility>
#include <vector>
using namespace std;

#pragma once

/**
 * @class Ordenador
 * @brief Clase que implementa varios algoritmos de ordenamiento.
 * 
 * @details Esta clase incluye los métodos para ordenar arreglos de valores
 * utilizando los algoritmos de selección, inserción, mezcla, por montículos,
 * ordenamiento rápido y ordenamiento por residuos. Los métodos hacen uso de
 * programación defensiva y están basados en el pseudocódigo provisto en el
 * libro de Cormen y colaboradores. La implementación de cada algoritmo se
 * realiza dentro del cuerpo de la clase para garantizar una correcta
 * compilación y ejecución.
 */
class Ordenador {
 private:
  /**
   * @brief Obtiene el valor de un dígito específico a partir de un conjunto de
   * bits.
   * 
   * @param num Número del que se extraerá el dígito.
   * @param bitPos Posición de inicio de los bits que se desean extraer.
   * @param mascara Máscara utilizada para extraer los bits correspondientes.
   * @return Valor del dígito extraído.
   */
  int obtenerValorDigito(int num, int bitPos, int mascara) const {
    return (num >> bitPos) & mascara;
  }

  /**
   * @brief Calcula el logaritmo en base 2 de un número entero.
   * 
   * @param n El número para el cual se desea calcular el logaritmo.
   * @return El logaritmo en base 2 de n, aproximado a un entero.
   */
  int calcularLog(int n) const {
    int log = 0;
    while (n >>= 1) ++log;
    return log;
  }

  /**
   * @brief Encuentra el valor máximo en un arreglo.
   * 
   * @param A El arreglo de enteros.
   * @param n La cantidad de elementos en el arreglo.
   * @return El valor máximo encontrado en el arreglo.
   */
  int encontrarValorMaximo(const int* A, int n) const {
    int max = A[0];
    for (int i = 1; i < n; ++i) {
      if (A[i] > max) {
        max = A[i];
      }
    }
    return max;
  }

  /**
   * @brief Realiza el ordenamiento rápido de forma recursiva.
   * 
   * @param A Arreglo a ordenar.
   * @param p Índice inicial del subarreglo.
   * @param r Índice final del subarreglo.
   */
  void rapidoRec(int *A, int p, int r) const {
    /** Caso de arreglo de un elemento o rango incorrecto. */
    if (p >= r) return;

    if (p < r) {
      int q = particionar(A, p, r);  /** Particionar el arreglo. */
      rapidoRec(A, p, q - 1);  /** Ordenar recursivamente el lado bajo. */
      rapidoRec(A, q + 1, r);  /** Ordenar recursivamente el lado alto. */
    }
  }

  /**
   * @brief Particiona el arreglo según el pivote para el ordenamiento rápido.
   * 
   * @param A Arreglo a particionar.
   * @param p Índice inicial del subarreglo.
   * @param r Índice final del subarreglo (donde está el pivote).
   * @return Índice del pivote después de la partición.
   */
  int particionar(int *A, int p, int r) const {
    int x = A[r];  /** El pivote es el último elemento. */
    int i = p - 1;  /** Índice más alto del lado bajo. */

    for (int j = p; j <= r - 1; j++) {
      if (A[j] <= x) {  /** Si el elemento pertenece al lado bajo. */
        i = i + 1;  /** Incrementar el índice del lado bajo. */
        swap(A[i], A[j]);  /** Intercambiar A[i] con A[j]. */
      }
    }
    /** Colocar el pivote en su lugar correcto. */
    swap(A[i + 1], A[r]);
    return i + 1;  /** Devolver la nueva posición del pivote. */
  }

  /** Devuelve el índice del padre de un nodo. */
  int padre(int i) const {
    return (i - 1) / 2;
  }

  /** Devuelve el índice del hijo izquierdo. */
  int izquierdo(int i) const {
    return 2 * i + 1;
  }

  /** Devuelve el índice del hijo derecho. */
  int derecho(int i) const {
    return 2 * i + 2;
  }

  /**
   * @brief Mantiene la propiedad de montículo máximo en un subárbol.
   * 
   * @param A Arreglo que representa el montículo.
   * @param tamMonticulo Tamaño del montículo.
   * @param i Índice de la raíz del subárbol que se va a "monticulizar".
   */
  void monticuloMax(int *A, int tamMonticulo, int i) const {
    int izq = izquierdo(i);
    int der = derecho(i);
    int nodo = i;

    /** Si el hijo izquierdo es mayor que el nodo actual. */
    if (izq < tamMonticulo && A[izq] > A[nodo])
      nodo = izq;

    /**
     * Si el hijo derecho es mayor que el nodo más grande encontrado hasta
     * ahora.
     */
    if (der < tamMonticulo && A[der] > A[nodo])
      nodo = der;

    /** Si el nodo más grande no es el nodo actual. */
    if (nodo != i) {
      swap(A[i], A[nodo]);
      /** Aplicar monticuloMax recursivamente. */
      monticuloMax(A, tamMonticulo, nodo);
    }
  }

  /** Función para construir un max-heap a partir del arreglo. */
  void monticulizar(int *A, int n) const {
    for (int i = (n / 2) - 1; i >= 0; --i) {
      monticuloMax(A, n, i);
    }
  }

  /**
   * @brief Función recursiva auxiliar para el algoritmo de ordenamiento por
   * mezcla.
   * 
   * @param A Arreglo a ordenar.
   * @param p Índice de inicio del subarreglo.
   * @param r Índice final del subarreglo.
   */
  void mezclaRec(int *A, int p, int r) const {
    /** Caso de arreglo de un elemento o rango incorrecto. */
    if (p >= r) return;

    int q = (p + r) / 2;  /** Calcular el punto medio. */
    mezclaRec(A, p, q);  /** Ordenar la primera mitad. */
    mezclaRec(A, q + 1, r);  /** Ordenar la segunda mitad. */
    mezclar(A, p, q, r);  /** Mezclar ambas partes. */
  }

  /**
   * @brief Función auxiliar que mezcla dos subarreglos.
   * 
   * @param A Arreglo a ordenar.
   * @param p Índice de inicio del subarreglo.
   * @param q Punto medio del subarreglo.
   * @param r Índice final del subarreglo.
   */
  void mezclar(int* A, int p, int q, int r) const {
    int nI = q - p + 1;  /** Tamaño del subarreglo izquierdo. */
    int nD = r - q;  /** Longitud del subarreglo derecho. */

    /** Crear los subarreglos temporales I y D. */
    vector<int> I(nI);
    vector<int> D(nD);
    /** Copiar los elementos del subarreglo A[p:q] en I. */
    for (int i = 0; i < nI; ++i) {
      I[i] = A[p + i];
    }
    /** Copiar los elementos del subarreglo A[q+1:r] en D. */
    for (int j = 0; j < nD; ++j) {
      D[j] = A[q + 1 + j];
    }
    /**
     * i: índice del subarreglo I. j: índice del subarreglo D. k: índice del
     * arreglo original.
     */
    int i = 0, j = 0, k = p;

    /** Se mezclan los subarreglos I y D de regreso en A[p:r]. */
    while (i < nI && j < nD) {
      if (I[i] <= D[j]) {
        A[k] = I[i];
        i = i + 1;
      } else {
        A[k] = D[j];
        j = j + 1;
      }
      k = k + 1;
    }
    /** Si quedan elementos en I, se copian en A. */
    while (i < nI) {
      A[k] = I[i];
      i = i + 1;
      k = k + 1;
    }
    /** Si quedan elementos en D, se copian en A. */
    while (j < nD) {
      A[k] = D[j];
      j = j + 1;
      k = k + 1;
    }
  }

 public:
  Ordenador() = default;
  ~Ordenador() = default;

  /**
   * @brief Algoritmo de ordenamiento por selección.
   * 
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorSeleccion(int *A, int n) const {
    /** Verificación defensiva de entrada. */
    if (A == nullptr || n <= 0) return;

    for (int i = 0; i < n - 1; ++i) {
      int m = i;  /** m es el índice del elemento más pequeño. */
      for (int j = i + 1; j < n; ++j) {
        if (A[j] < A[m]) {
          m = j;  // Actualizar m si se encuentra un elemento más pequeño. */
        }
      }
      /** Se intercambia el elemento más pequeño encontrado con A[i]. */
      swap(A[i], A[m]);
    }
  }

  /**
   * @brief Algoritmo de ordenamiento por inserción.
   * 
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorInsercion(int *A, int n) const {
    /** Verificación defensiva de entrada. */
    if (A == nullptr || n <= 0) return;

    for (int i = 1; i < n; ++i) {
      int valorClave = A[i];  /** Se guarda el elemento actual. */
      int j = i - 1;
      /**
       * Se mueven los elementos mayores que valorClave una posición adelante.
       */
      while (j >= 0 && A[j] > valorClave) {
        A[j + 1] = A[j];
        --j;
      }
      /** Insertar valorClave en la posición correcta. */
      A[j + 1] = valorClave;
    }
  }

  /**
   * @brief Algoritmo de ordenamiento por mezcla.
   * 
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorMezcla(int *A, int n) const {
    /** Verificación defensiva de entrada. */
    if (A == nullptr || n <= 0) return;

    /** Llamado a la función recursiva para ordenar el arreglo completo. */
    mezclaRec(A, 0, n - 1);
  }

  /**
   * @brief Algoritmo de ordenamiento por montículos.
   * 
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorMonticulos(int *A, int n) const {
    /** Verificación defensiva de entrada. */
    if (A == nullptr || n <= 0) return;

    monticulizar(A, n);  /** Construye el max-heap. */

    for (int i = n - 1; i >= 1; --i) {
      swap(A[0], A[i]);  /** Mueve el mayor elemento al final. */
      monticuloMax(A, i, 0);  /** Aplica monticuloMax al subárbol reducido. */
    }
  }

  /**
   * @brief Algoritmo de ordenamiento rápido.
   * 
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoRapido(int *A, int n) const {
    /** Verificación defensiva de entrada. */
    if (A == nullptr || n <= 0) return;

    /** Llama a la función recursiva sobre todo el arreglo. */
    rapidoRec(A, 0, n - 1);
  }

  /**
   * @brief Algoritmo de ordenamiento por residuos en base 2^lg(n).
   * 
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorRadix(int *A, int n) const {
    /** Verificación defensiva de entrada. */
    if (A == nullptr || n <= 0) return;

    /** Calcular el número de bits por cada dígito (lgn). */
    int bitsPorDigito = calcularLog(n);  /** Base 2^lg(n). */
    int totalBits = sizeof(int) * 8;  /** Número de bits en un entero. */

    /** Crear un buffer para el ordenamiento temporal. */
    int* memIntermedia = new int[n];

    /** Máscara para extraer los bits correspondientes a un dígito. */
    int mascara = (1 << bitsPorDigito) - 1;

    for (int bitPos = 0; bitPos < totalBits; bitPos += bitsPorDigito) {
      int count[1 << bitsPorDigito];
      for (int i = 0; i < (1 << bitsPorDigito); ++i) {
        count[i] = 0;
      }

      /** Contar las ocurrencias de cada dígito. */
      for (int i = 0; i < n; ++i) {
        int digito = obtenerValorDigito(A[i], bitPos, mascara);
        count[digito]++;
      }

      /** Calcular posiciones acumulativas. */
      for (int i = 1; i < (1 << bitsPorDigito); ++i) {
        count[i] += count[i - 1];
      }

      /** Construir el arreglo ordenado temporalmente usando el buffer. */
      for (int i = n - 1; i >= 0; --i) {
        int digito = obtenerValorDigito(A[i], bitPos, mascara);
        memIntermedia[--count[digito]] = A[i];
      }

      /** Copiar el contenido del buffer en el arreglo original. */
      for (int i = 0; i < n; ++i) {
        A[i] = memIntermedia[i];
      }
    }
    /** Liberar la memoria utilizada por el buffer. */
    delete[] memIntermedia;
  }

  /**
   * @brief Retorna un string con los datos de la tarea.
   * 
   * @details Este método devuelve una cadena de texto que contiene el carné,
   * nombre y entrega de la tarea.
   * @return string Una cadena de texto con los datos de la tarea.
   */
  constexpr const char* datosDeTarea() const {
    return "Carnet: C37853, Nombre: Josue Torres Sibaja, Tarea 1, Etapa 2";
  }
};
