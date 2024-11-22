// Copyright 2024 Josue Torres Sibaja <josue.torressibaja@ucr.ac.cr>

#include "graph.hpp"

void Graph::floydWarshall() {
  for (const auto& [node, edges] : adjList) {
    for (const auto& edge : edges) {
      floydWarshallDist[node][edge.destination] = edge.weight;
    }
  }

  for (const auto& [node, _] : adjList) {
    floydWarshallDist[node][node] = 0;
    for (const auto& [otherNode, _] : adjList) {
      if (floydWarshallDist[node].find(otherNode) ==
        floydWarshallDist[node].end()) {
        floydWarshallDist[node][otherNode] = std::numeric_limits<int>::max();
      }
    }
  }

  // Apply the Floyd-Warshall algorithm.
  for (const auto& [k, _] : adjList) {
    for (const auto& [i, _] : adjList) {
      for (const auto& [j, _] : adjList) {
        if (floydWarshallDist[i][k] != std::numeric_limits<int>::max() &&
          floydWarshallDist[k][j] != std::numeric_limits<int>::max()) {
          int newDistance = floydWarshallDist[i][k] + floydWarshallDist[k][j];
          if (newDistance < floydWarshallDist[i][j]) {
            floydWarshallDist[i][j] = newDistance;
          }
        }
      }
    }
  }
}

void Graph::cityPlaceEquipment() {
  int minTotalTime = std::numeric_limits<int>::max();
  std::vector<std::string> bestCities;

  for (const auto& i : floydWarshallDist) {
    int timeSum = 0;
    bool valid = true;

    for (const auto& j : floydWarshallDist[i.first]) {
      if (j.second == std::numeric_limits<int>::max()) {
        valid = false;
        break;  // The city cannot reach all the other cities.
      }
      timeSum += j.second;
    }

    if (valid) {
      if (timeSum < minTotalTime) {
        minTotalTime = timeSum;
        bestCities.clear();
        bestCities.push_back(i.first);
      } else if (timeSum == minTotalTime) {
        bestCities.push_back(i.first);
      }
    }
  }

  std::cout << "Mejor(es) ciudad(es) para colocar mayor capacidad de equipo:"
    << std::endl;
  for (const auto& city : bestCities) {
    std::cout << "- " << city << std::endl;
  }
}

void Graph::cityDispatchSupport() {
  std::string destination;
  std::cout << "Ingrese el nombre de la ciudad destino: ";
  std::cin.ignore();
  std::getline(std::cin, destination);

  if (floydWarshallDist.find(destination) == floydWarshallDist.end()) {
    std::cout << "La ciudad ingresada no existe en el grafo." << std::endl;
    return;
  }

  int minDistance = std::numeric_limits<int>::max();
  std::vector<std::string> bestCities;

  for (const auto& i : floydWarshallDist) {
    if (i.first != destination &&
      floydWarshallDist[i.first][destination] < minDistance) {
      minDistance = floydWarshallDist[i.first][destination];
      bestCities.clear();
      bestCities.push_back(i.first);
    } else if (floydWarshallDist[i.first][destination] == minDistance) {
      bestCities.push_back(i.first);
    }
  }

  if (minDistance == std::numeric_limits<int>::max()) {
    std::cout << "No hay ciudades desde las cuales se pueda apoyar a "
      << destination << "." << std::endl;
    return;
  }

  std::cout << "Ciudad(es) desde donde es mejor apoyar a " << destination
    << ":" << std::endl;
  for (const auto& city : bestCities) {
    std::cout << "- " << city << " (Distancia: " << minDistance << ")"
      << std::endl;
  }
}

void Graph::citiesFarthest() {
  int maxDistance = 0;
  std::vector<std::pair<std::string, std::string>> pairs;

  // Iterate over the city combinations.
  for (const auto& origin : floydWarshallDist) {
    for (const auto& destination : floydWarshallDist[origin.first]) {
      if (origin.first < destination.first &&
        destination.second != std::numeric_limits<int>::max()) {
        // If a new maximum distance is found, update.
        if (destination.second > maxDistance) {
          maxDistance = destination.second;
          pairs.clear();
          pairs.emplace_back(origin.first, destination.first);
        } else if (destination.second == maxDistance) {
          pairs.emplace_back(origin.first, destination.first);
        }
      }
    }
  }

  // Check for valid pairs.
  if (pairs.empty()) {
    std::cout << "No se encontraron pares de ciudades distantes (grafo vacío o"
      " sin conexiones)." << std::endl;
  } else {
    std::cout << "El/Los par(es) de ciudades más distantes son:" << std::endl;
    for (const auto& par : pairs) {
      std::cout << par.first << " - " << par.second
        << " (Distancia: " << maxDistance << ")" << std::endl;
    }
  }
}

void Graph::citiesNearest() {
  int minDistance = std::numeric_limits<int>::max();
  std::vector<std::pair<std::string, std::string>> pairs;

  for (const auto& origin : floydWarshallDist) {
    for (const auto& destination : floydWarshallDist[origin.first]) {
      if (origin.first < destination.first &&
        destination.second != std::numeric_limits<int>::max()) {
        // If a new minimum distance is found, update.
        if (destination.second < minDistance) {
          minDistance = destination.second;
          pairs.clear();
          pairs.emplace_back(origin.first, destination.first);
        } else if (destination.second == minDistance) {
          pairs.emplace_back(origin.first, destination.first);
        }
      }
    }
  }

  std::cout << "El/Los par(es) de ciudades más cercanas son:" << std::endl;
  for (const auto& par : pairs) {
    std::cout << par.first << " - " << par.second << " (Distancia: "
      << minDistance << ")" << std::endl;
  }
}

void Graph::citiesAverageTime() {
  std::vector<std::pair<std::string, double>> averages;

  for (const auto& i : floydWarshallDist) {
    double sum = 0;
    int counter = 0;
    for (const auto& j : floydWarshallDist[i.first]) {
      if (i.first != j.first && j.second != std::numeric_limits<int>::max()) {
        sum += j.second;
        counter++;
      }
    }
    if (counter > 0) {
      averages.push_back({i.first, sum / counter});
    }
  }

  sort(averages.begin(), averages.end(), [](const auto& a, const auto& b) {
    return a.second < b.second;
  });

  std::cout << "Ciudades ordenadas por tiempo promedio de viaje:" << std::endl;
  for (const auto& city : averages) {
    std::cout << city.first << " (Promedio: " << city.second << ")"
      << std::endl;
  }
}
