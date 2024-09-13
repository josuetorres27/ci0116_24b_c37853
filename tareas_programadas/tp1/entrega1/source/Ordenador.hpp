#pragma once

class Ordenador {
  private:
  // Defina aqui los metodos auxiliares de los algoritmos de ordenamiento solamente.
  // Puede definir cuantos metodos quiera.

  /** Función recursiva para el ordenamiento por mezcla. */
  void mezclaRec(int *A, int p, int r) const {
    if (p >= r) return;  /**< Caso de arreglo de un elemento o rango incorrecto. */

    int q = (p + r) / 2;  /**< Calcular el punto medio. */
    mezclaRec(A, p, q);  /**< Ordenar la primera mitad. */
    mezclaRec(A, q + 1, r);  /**< Ordenar la segunda mitad. */
    mezclar(A, p, q, r);  /**< Mezclar ambas partes. */
  }

  /** Función auxiliar para el ordenamiento por mezcla. */
  void mezclar(int* A, int p, int q, int r) const {
    int nL = q - p + 1;  /**< Tamaño del subarreglo izquierdo. */
    int nR = r - q;  /**< Longitud del subarreglo derecho. */

    /** Crear los subarreglos temporales L y R. */
    std::vector<int> L(nL);
    std::vector<int> R(nR);

    /** Copiar los elementos del subarreglo A[p:q] en L. */
    for (int i = 0; i < nL; ++i) {
      L[i] = A[p + i];
    }
    /** Copiar los elementos del subarreglo A[q+1:r] en R. */
    for (int j = 0; j < nR; ++j) {
      R[j] = A[q + 1 + j];
    }

    /** i: índice del subarreglo L. j: índice del subarreglo R. k: índice del arreglo original. */
    int i = 0, j = 0, k = p;

    /** Se mezclan los subarreglos L y R de regreso en A[p:r]. */
    while (i < nL && j < nR) {
      if (L[i] <= R[j]) {
        A[k] = L[i];
        i = i + 1;
      } else {
        A[k] = R[j];
        j = j + 1;
      }
      k = k + 1;
    }

    /** Si quedan elementos en L, se copian en A. */
    while (i < nL) {
      A[k] = L[i];
      i = i + 1;
      k = k + 1;
    }
    /** Si quedan elementos en R, se copian en A. */
    while (j < nR) {
      A[k] = R[j];
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

  void ordenamientoPorSeleccion(int *A, int n) const {
    if (A == nullptr || n <= 0) return;  /**< Verificación defensiva de entrada. */

    for (int i = 0; i < n - 1; ++i) {
      int m = i;  /**< m es el índice del elemento más pequeño. */
      for (int j = i + 1; j < n; ++j) {
        if (A[j] < A[m]) {
          m = j;  // Actualizar m si se encuentra un elemento más pequeño. */
        }
      }
      /** Se intercambia el elemento más pequeño encontrado con A[i]. */
      swap(A[i], A[m]);
    }
  }

  void ordenamientoPorInsercion(int *A, int n) const {
    if (A == nullptr || n <= 0) return;  /**< Verificación defensiva de entrada. */

    for (int i = 1; i < n; ++i) {
      int key = A[i];  /**< Se guarda el elemento actual. */
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

  void ordenamientoPorMezcla(int *A, int n) const {
    if (A == nullptr || n <= 0) return;  /**< Verificación defensiva de entrada. */

    /** Llamado a la función recursiva para ordenar el arreglo completo. */
    mezclarRec(A, 0, n - 1);
  }

  void ordenamientoPorMonticulos(int *A, int n) const;
  void ordenamientoRapido(int *A, int n) const;
  void ordenamientoPorRadix(int *A, int n) const;

  /**
   * @brief Retorna un std::string con los datos de la tarea.
   * 
   * @details Este método devuelve una cadena de texto que contiene el carné, nombre y tarea.
   * @return std::string Una cadena de texto con los datos de la tarea.
   */
  constexpr const char* datosDeTarea() const {
    return "Carné: C37853, Nombre: Josué Torres Sibaja, Tarea 1, Etapa 1"
  }
};
