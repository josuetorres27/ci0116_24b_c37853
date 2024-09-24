#include <iostream>
#include <vector>
using namespace std;

#pragma once

/**
 * @class Ordenador
 * @brief Clase que implementa varios algoritmos de ordenamiento.
 * 
 * @details Esta clase incluye los métodos para realizar ordenamiento
 * utilizando los algoritmos de selección, inserción y mezcla, así como
 * encabezados para otros algoritmos que serán implementados en el futuro. Los
 * métodos hacen uso de programación defensiva y están basados en el
 * pseudocódigo provisto en el libro de Cormen y colaboradores. La
 * implementación de cada algoritmo se realiza dentro del cuerpo de la clase
 * para garantizar una correcta compilación y ejecución.
 */
class Ordenador {
  private:
  // Defina aqui los metodos auxiliares de los algoritmos de ordenamiento solamente.
  // Puede definir cuantos metodos quiera.

  /** Función recursiva para aplicar el ordenamiento rápido. */
  void quickRec(int *A, int p, int r) const {
    if (p < r) {
      int q = partition(A, p, r);  /** Particionar el arreglo. */
      quickRec(A, p, q - 1);  /** Ordenamos recursivamente el lado bajo. */
      quickRec(A, q + 1, r);  /** Ordenamos recursivamente el lado alto. */
    }
  }

  int partition(int *A, int p, int r) const {
    int x = A[r];  /** El pivote es el último elemento. */
    int i = p - 1;  /** Índice más alto del lado bajo. */

    for (int j = p; j <= r - 1; j++) {
      if (A[j] <= x) {  /** Si el elemento pertenece al lado bajo. */
        i = i + 1;  /** Incrementamos el índice del lado bajo. */
        swap(A[i], A[j]);  /** Intercambiamos A[i] con A[j]. */
      }
    }
    /** Colocamos el pivote en su lugar correcto. */
    swap(A[i + 1], A[r]);
    return i + 1;  /** Devolvemos la nueva posición del pivote. */
  }

  /** Devuelve el índice del padre de un nodo. */
  int parent(int i) const {
    return (i - 1) / 2;
  }

  /** Devuelve el índice del hijo izquierdo. */
  int left(int i) const {
    return 2 * i + 1;
  }

  /** Devuelve el índice del hijo derecho. */
  int right(int i) const {
    return 2 * i + 2;
  }

  void maxHeapify(int *A, int heapSize, int i) const {
    int l = left(i);
    int r = right(i);
    int largest = i;

    /** Si el hijo izquierdo es mayor que el nodo actual. */
    if (l < heapSize && A[l] > A[largest])
      largest = l;

    /** Si el hijo derecho es mayor que el nodo más grande encontrado hasta ahora. */
    if (r < heapSize && A[r] > A[largest])
      largest = r;

    /** Si el nodo más grande no es el nodo actual. */
    if (largest != i) {
      swap(A[i], A[largest]);
      maxHeapify(A, heapSize, largest);  /** Aplica maxHeapify recursivamente. */
    }
  }

  /** Función para construir un max-heap a partir del arreglo. */
  void buildMaxHeap(int *A, int n) const {
    for (int i = (n / 2) - 1; i >= 0; --i) {
      maxHeapify(A, n, i);
    }
  }

  /**
   * @brief Función recursiva auxiliar para el algoritmo de ordenamiento por mezcla.
   * 
   * @param A Arreglo a ordenar.
   * @param p Índice de inicio del subarreglo.
   * @param r Índice final del subarreglo.
   */
  void mezclaRec(int *A, int p, int r) const {
    if (p >= r) return;  /** Caso de arreglo de un elemento o rango incorrecto. */

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

    /** Crear los subarreglos temporales L y R. */
    vector<int> I(nI);
    vector<int> D(nD);
    /** Copiar los elementos del subarreglo A[p:q] en L. */
    for (int i = 0; i < nI; ++i) {
      I[i] = A[p + i];
    }
    /** Copiar los elementos del subarreglo A[q+1:r] en R. */
    for (int j = 0; j < nD; ++j) {
      D[j] = A[q + 1 + j];
    }
    /** i: índice del subarreglo L. j: índice del subarreglo R. k: índice del arreglo original. */
    int i = 0, j = 0, k = p;

    /** Se mezclan los subarreglos L y R de regreso en A[p:r]. */
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
    /** Si quedan elementos en L, se copian en A. */
    while (i < nI) {
      A[k] = I[i];
      i = i + 1;
      k = k + 1;
    }
    /** Si quedan elementos en R, se copian en A. */
    while (j < nD) {
      A[k] = D[j];
      j = j + 1;
      k = k + 1;
    }
  }

  public:
  Ordenador() = default;
  ~Ordenador() = default;

  /* Nota:
   - Si no planea implementar algunos de los métodos de ordenamiento, no los borre.
   - Simplemente déjelos con el cuerpo vacío para evitar errores de compilación, ya
     que se ejecutará el mismo main para todas las tareas.
   - Recuerde hacer uso de programación defensiva y documentar los métodos con formato Doxygen, por ejemplo.
   - No cambié la firma de los métodos de la clase Ordenador.
   - No lance excepciones para el manejo de errores.
     Ante un error, basta con que el método no modifique el arreglo original y que no cause la caída del programa.
  */

  /**
   * @brief Algoritmo de ordenamiento por selección.
   * 
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorSeleccion(int *A, int n) const {
    if (A == nullptr || n <= 0) return;  /** Verificación defensiva de entrada. */

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
    if (A == nullptr || n <= 0) return;  /** Verificación defensiva de entrada. */

    for (int i = 1; i < n; ++i) {
      int key = A[i];  /** Se guarda el elemento actual. */
      int j = i - 1;
      /** Se mueven los elementos mayores que key una posición adelante. */
      while (j >= 0 && A[j] > key) {
        A[j + 1] = A[j];
        --j;
      }
      /** Insertar key en la posición correcta. */
      A[j + 1] = key;
    }
  }

  /**
   * @brief Algoritmo de ordenamiento por mezcla.
   * 
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorMezcla(int *A, int n) const {
    if (A == nullptr || n <= 0) return;  /** Verificación defensiva de entrada. */

    /** Llamado a la función recursiva para ordenar el arreglo completo. */
    mezclaRec(A, 0, n - 1);
  }

  void ordenamientoPorMonticulos(int *A, int n) const {
    buildMaxHeap(A, n);  /** Construye el max-heap. */

    for (int i = n - 1; i >= 1; --i) {
      swap(A[0], A[i]);  /** Mueve el mayor elemento al final. */
      maxHeapify(A, i, 0);  /** Aplica maxHeapify al subárbol reducido. */
    }
  }

  void ordenamientoRapido(int *A, int n) const {
    quickRec(A, 0, n - 1);  /** Llama a la función quickRec sobre todo el arreglo. */
  }

  void ordenamientoPorRadix(int *A, int n) const;

  /**
   * @brief Retorna un string con los datos de la tarea.
   * 
   * @details Este método devuelve una cadena de texto que contiene el carné, nombre y tarea.
   * @return string Una cadena de texto con los datos de la tarea.
   */
  constexpr const char* datosDeTarea() const {
    return "Carnet: C37853, Nombre: Josue Torres Sibaja, Tarea 1, Etapa 2";
  }
};
