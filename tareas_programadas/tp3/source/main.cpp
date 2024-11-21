// Copyright 2024 Josue Torres Sibaja <josue.torressibaja@ucr.ac.cr>

#include "graph.hpp"

int main() {
  Graph graph;
  std::string filepath;

  std::cout << "Ingrese la ruta y el nombre del archivo CSV (por ejemplo: "
    "../tests/input_small.csv): ";
  std::cin >> filepath;

  // Leer el archivo y construir el grafo.
  graph.readCSV(filepath);

  // Verificar que el grafo no este vacio antes de continuar.
  if (graph.adjList.empty()) {
    std::cout << "Error: No se pudo cargar el archivo de entrada. Por favor "
      "verifique el nombre y la ruta del archivo." << std::endl;
    return 1;
  }

  // Mostrar la lista de adyacencia generada a partir del archivo.
  graph.printAdjList();

  // Inicializar la matriz de distancias minimas.
  //graph.floydWarshall();

  // Menu de selected_optiones.
  while (true) {
    std::cout << "\nSeleccione una selected_option:\n";
    std::cout << "1. Ciudad donde es mas efectivo colocar mayor capacidad de "
      "equipo.\n";
    std::cout << "2. Mejor ciudad para apoyar a una ciudad dada.\n";
    std::cout << "3. Ciudades mas distantes.\n";
    std::cout << "4. Ciudades mas cercanas.\n";
    std::cout << "5. Orden de ciudades por tiempo promedio.\n";
    std::cout << "6. Exportar grafo (CSV, DOT, PNG).\n";
    std::cout << "7. Salir.\n";
    int selected_option;
    std::cin >> selected_option;

    switch (selected_option) {
      case 1:
        graph.ciudadColocarEquipo();
        break;
      case 2:
        graph.ciudadDespacharApoyo();
        break;
      case 3:
        graph.ciudadesMasDistantes();
        break;
      case 4:
        graph.ciudadesMasCercanas();
        break;
      case 5:
        graph.ciudadesPorTiempoPromedio();
        break;
      case 6:
        std::cout << "Seleccione el formato de exportacion:\n";
        std::cout << "1. Exportar como CSV.\n";
        std::cout << "2. Exportar como DOT (opcion de generar imagen PNG).\n";
        int sub_option;
        std::cin >> sub_option;
        switch (sub_option) {
          case 1:
            graph.exportGraphToCSV("grafo_exportado.csv");
            break;
          case 2:
            graph.exportGraphToDOT("grafo_exportado.dot");
            break;
          default:
            std::cout << "Opcion no valida. Regresando al menu principal." <<
              std::endl;
            break;
        }
        break;
      case 7:
        std::cout << "Saliendo del programa..." << std::endl;
        return 0;
      default:
        std::cout << "Opcion no valida. Intente nuevamente." << std::endl;
        break;
    }
  }
  return 0;
}
