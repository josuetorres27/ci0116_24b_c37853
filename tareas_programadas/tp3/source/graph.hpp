// Copyright 2024 Josue Torres Sibaja <josue.torressibaja@ucr.ac.cr>

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <queue>
#include <limits>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <unordered_map>

// Estructura para representar una arista.
struct Edge {
  std::string destination;  ///< Uses location name.
  int weight;
};

// Estructura para representar el grafo y sus operaciones.
class Graph {
 public:
  // Lista de adyacencia representando el grafo.
  std::unordered_map<std::string, std::vector<Edge>> adjList;

  // Matriz de distancias para el algoritmo de Floyd-Warshall.
  std::unordered_map<std::string, std::unordered_map<std::string, int>>
    floydWarshallDist;

  void printAdjList();
  void floydWarshall();
  void cityPlaceEquipment();
  void cityDispatchSupport();
  void citiesNearest();
  void citiesFarthest();
  void citiesAverageTime();
  bool isNumber(const std::string& str);
  void readCSV(const std::string& filepath);
  void exportGraphToCSV(const std::string& filepath);
  void exportGraphToDOT(const std::string& filepath);
};

#endif  // GRAPH_HPP
