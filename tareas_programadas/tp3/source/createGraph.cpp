// Copyright 2024 Josue Torres Sibaja <josue.torressibaja@ucr.ac.cr>

#include "graph.hpp"

bool Graph::isNumber(const std::string& str) {
  for (char c : str) {
    if (!isdigit(c)) return false;
  }
  return !str.empty();
}

void Graph::printAdjList() {
  if (adjList.empty()) {
    std::cout << "El grafo esta vacio. Asegurese de que el archivo fue leido "
      "correctamente." << std::endl;
    return;
  }

  std::cout << "Lista de adyacencia del grafo:" << std::endl;
  for (const auto& pair : adjList) {
    std::cout << pair.first << " -> ";
    for (const auto& edge : pair.second) {
      std::cout << "(" << edge.destination << ", " << edge.weight << ") ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl << "Grafo procesado correctamente." << std::endl;
}

void Graph::createOutputDirectory(const std::string& path) {
  struct stat info;
  if (stat(path.c_str(), &info) != 0) {
    // The directory does not exist, tries to create it.
    if (mkdir(path.c_str(), 0755) != 0) {
      std::cerr << "Error: No se pudo crear el directorio de salida: " << path
        << std::endl;
    }
  } else if (!(info.st_mode & S_IFDIR)) {
    // The name exists, but it is not a directory.
    std::cerr << "Error: Existe un archivo con el mismo nombre que el "
      "directorio: " << path << std::endl;
  }
}

void Graph::readCSV(const std::string& filepath) {
  std::ifstream file(filepath);

  if (!file.is_open()) {
    std::cerr << "Error: No se pudo abrir el archivo en la ruta especificada: "
      << filepath << std::endl;
    return;
  }

  std::string line;
  // Read and discard the header.
  getline(file, line);

  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string sourceId, sourceName, targetId, targetName, weightStr;

    getline(ss, sourceId, ',');
    getline(ss, sourceName, ',');
    getline(ss, targetId, ',');
    getline(ss, targetName, ',');
    getline(ss, weightStr, ',');

    // Validate that the columns are not empty.
    if (sourceId.empty() || sourceName.empty() || targetId.empty() ||
      targetName.empty() || weightStr.empty()) {
      std::cerr << "Error: Linea mal formateada en el archivo: " << line
        << std::endl;
      continue;
    }

    // Validate that the weight is a valid number.
    if (!isNumber(weightStr)) {
      std::cerr << "Error: Peso no valido en la linea: " << line << std::endl;
      continue;
    }

    int weight = stoi(weightStr);

    // Add connections to the graph using only names.
    adjList[sourceName].push_back({targetName, weight});
    adjList[targetName].push_back({sourceName, weight});
  }
  file.close();
}

void Graph::exportGraphToCSV(const std::string& filepath) {
  // Ensure the output directory exists.
  std::string outputDir = "../output/";
  createOutputDirectory(outputDir);

  std::string fullPath = outputDir + filepath;
  std::ofstream file(fullPath);

  if (!file.is_open()) {
    std::cerr << "Error: No se pudo crear el archivo CSV: " << fullPath
      << std::endl;
    return;
  }

  file << "SourceName,TargetName,Weight\n";
  for (const auto& pair : adjList) {
    for (const auto& edge : pair.second) {
      if (pair.first < edge.destination) {
        file << pair.first << "," << edge.destination << "," << edge.weight
          << "\n";
      }
    }
  }

  file.close();
  std::cout << "El grafo fue exportado al archivo CSV: " << fullPath
    << std::endl;
}

void Graph::exportGraphToDOT(const std::string& filepath) {
  // Ensure the output directory exists.
  std::string outputDir = "../output/";
  createOutputDirectory(outputDir);

  std::string fullPath = outputDir + filepath;
  std::ofstream dotFile(fullPath);

  if (!dotFile.is_open()) {
    std::cerr << "Error: No se pudo crear el archivo DOT: " << fullPath
      << std::endl;
    return;
  }

  dotFile << "graph Grafo {" << std::endl;

  for (const auto& pair : adjList) {
    for (const auto& edge : pair.second) {
      if (pair.first < edge.destination) {
        dotFile << "    \"" << pair.first << "\" -- \"" << edge.destination
          << "\" [label=\"" << edge.weight << "\"];" << std::endl;
      }
    }
  }

  dotFile << "}" << std::endl;
  dotFile.close();

  std::cout << "El grafo fue exportado al archivo DOT: " << fullPath
    << std::endl;

  // Generate PNG image.
  std::cout << "Generar una imagen PNG del grafo (s/n): ";
  char option;
  std::cin >> option;

  if (tolower(option) == 's') {
    std::string pngPath = outputDir + "grafo_generado.png";
    std::string command = "dot -Tpng " + fullPath + " -o " + pngPath;
    int result = system(command.c_str());
    if (result == 0) {
      std::cout << "Imagen PNG generada exitosamente en: " << pngPath
        << std::endl;
    } else {
      std::cerr << "Error: No se pudo generar la imagen PNG." << std::endl;
    }
  }
}
