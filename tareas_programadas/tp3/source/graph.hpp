// Copyright 2024 Josue Torres Sibaja <josue.torressibaja@ucr.ac.cr>

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>

/**
 * @brief Structure to represent an edge in a graph.
 *
 * @details Each edge connects the source node (not explicitly stored here) to
 * a destination node, with an associated weight representing the cost or
 * distance.
 */
struct Edge {
  std::string destination;  ///< The name of the destination node.
  int weight;               ///< The weight or cost of the edge.
};

/**
 * @brief Class to represent a graph and provide operations on it.
 *
 * @details The graph supports directed or undirected edges with weights and
 * various algorithms, including Floyd-Warshall for shortest paths.
 */
class Graph {
 public:
  /**
   * @brief Adjacency list representing the graph.
   *
   * @details Stores each node (key) and a vector of edges originating from it.
   * Each edge connects to a destination node with a specified weight.
   * This structure is used for efficient traversal and manipulation.
   */
  std::unordered_map<std::string, std::vector<Edge>> adjList;

  /**
   * @brief Distance matrix for the Floyd-Warshall algorithm.
   *
   * @details Represents the shortest path distances between all pairs of
   * nodes.
   * The outer key is the source node, and the inner key is the destination
   * node.
   * If two nodes are not connected, their distance is set to INF.
   */
  std::unordered_map<std::string, std::unordered_map<std::string, int>>
    floydWarshallDist;

  /**
   * @brief Prints the adjacency list representation of the graph.
   *
   * @details Displays each vertex and its connected edges with their
   * respective weights.
   * If the graph is empty, a warning message is shown.
   */
  void printAdjList();

  /**
   * @brief Implements the Floyd-Warshall algorithm to compute shortest paths
   * between all pairs of nodes.
   *
   * @details Populates the 'floydWarshallDist' matrix with the shortest
   * distances.
   * Uses adjacency list data to initialize distances and handles nodes that
   * are not directly connected.
  */
  void floydWarshall();

  /**
   * @brief Determines the best city (or cities) to place high-capacity
   * equipment.
   *
   * @details This is based on minimizing the total travel time to all other
   * cities.
   * Only considers cities that can reach all other cities.
   * Prints the result to the console.
   */
  void cityPlaceEquipment();

  /**
   * @brief Determines the best city (or cities) to dispatch support to a
   * specified destination.
   *
   * @details Prompts the user to input a destination city, and calculates the
   * closest city (or cities) to the destination based on the shortest paths.
   * Prints the result or an error if the destination is unreachable.
   */
  void cityDispatchSupport();

  /**
   * @brief Identifies the pair(s) of cities that are the farthest apart based
   * on the shortest path.
   *
   * @details Uses the Floyd-Warshall distance matrix to determine the maximum
   * distance between any two cities.
   * If multiple pairs share the maximum distance, all are listed.
   */
  void citiesFarthest();

  /**
   * @brief Identifies the pair(s) of cities that are the closest based on the
   * shortest path.
   *
   * @details Uses the Floyd-Warshall distance matrix to determine the minimum
   * distance between any two cities.
   * If multiple pairs share the minimum distance, all are listed.
   */
  void citiesNearest();

  /**
   * @brief Calculates and lists all cities in ascending order of their average
   * travel time to all other cities.
   *
   * @details For each city, computes the average travel time to all reachable
   * cities.
   * Only considers finite distances and skips unreachable nodes.
   */
  void citiesAverageTime();

  /**
   * @brief Checks if a given string is a valid numeric value.
   *
   * @param str The string to validate.
   * @return true If the string represents a valid number.
   * @return false Otherwise.
   */
  bool isNumber(const std::string& str);

  /**
   * @brief Reads a CSV file and builds the graph.
   *
   * @details Each row in the CSV should define an edge with source,
   * destination, and weight.
   * Invalid or poorly formatted rows are ignored with an error message.
   *
   * @param filepath Path to the CSV file.
   */
  void readCSV(const std::string& filepath);

  /**
   * @brief Creates the specified output directory if it does not exist.
   *
   * @details If the directory exists, it ensures it is a valid directory.
   * Otherwise, it attempts to create it.
   *
   * @param path The path of the directory to create.
   */
  void createOutputDirectory(const std::string& path);

  /**
   * @brief Exports the graph to a CSV file.
   *
   * @details Each row in the exported CSV represents an edge in the graph,
   * showing its source, destination, and weight.
   * Ensures the output directory exists before exporting.
   *
   * @param filepath The name of the output CSV file.
   */
  void exportGraphToCSV(const std::string& filepath);

  /**
   * @brief Exports the graph to a DOT file.
   *
   * @details The DOT file can be used for visualizing the graph using Graphviz
   * tools. Optionally, it also generates a PNG image of the graph if the user
   * chooses to do so.
   *
   * @param filepath The name of the output DOT file.
   */
  void exportGraphToDOT(const std::string& filepath);
};

#endif  // GRAPH_HPP
