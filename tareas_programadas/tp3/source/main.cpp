// Copyright 2024 Josue Torres Sibaja <josue.torressibaja@ucr.ac.cr>

#include "graph.hpp"

int main() {
  Graph graph;
  std::string filepath;

  std::cout << "Ingrese la ruta y el nombre del archivo CSV (por ejemplo: "
    "../tests/input_small.csv): ";
  std::cin >> filepath;

  // Read the file and build the graph.
  graph.readCSV(filepath);

  // Check that the graph is not empty before continuing.
  if (graph.adjList.empty()) {
    std::cout << "Error: No se pudo cargar el archivo de entrada. Por favor "
      "verifique el nombre y la ruta del archivo." << std::endl;
    return 1;
  }

  // Display the adjacency list generated from the file.
  graph.printAdjList();

  // Initialize the minimum distance matrix.
  graph.floydWarshall();

  // Options menu.
  while (true) {
    std::cout << "\nSeleccione una opcion:\n";
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
        graph.cityPlaceEquipment();
        break;
      case 2:
        graph.cityDispatchSupport();
        break;
      case 3:
        graph.citiesFarthest();
        break;
      case 4:
        graph.citiesNearest();
        break;
      case 5:
        graph.citiesAverageTime();
        break;
      case 6:
        std::cout << "Seleccione el formato de exportacion:\n";
        std::cout << "1. Exportar como CSV.\n";
        std::cout << "2. Exportar como DOT (opcion de generar imagen PNG).\n";
        int sub_option;
        std::cin >> sub_option;
        switch (sub_option) {
          case 1:
            graph.exportGraphToCSV("grafo_generado.csv");
            break;
          case 2:
            graph.exportGraphToDOT("grafo_generado.dot");
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
