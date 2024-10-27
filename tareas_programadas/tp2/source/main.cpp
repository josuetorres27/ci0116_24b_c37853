// Copyright 2024 Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>

#include <chrono>
#include <iostream>
#include <random>

#include "BinarySearchTree.hpp"
#include "ChainedHashTable.hpp"
#include "RedBlackTree.hpp"
#include "SinglyLinkedList.hpp"

template <typename Structure>
void measureInsertion(Structure& structure, int n, std::mt19937& rng, std::uniform_int_distribution<int>& dist, bool ordered) {
    auto start = std::chrono::high_resolution_clock::now();

    if (ordered) {
        // Inserción ordenada
        if constexpr (std::is_same_v<Structure, BSTree<int>>) {
            structure.fastInsert(0, n - 1);
            std::cout << "Tiempo de inserción ordenada en árbol binario (con fastInsert): ";
        } else {
            for (int i = 0; i < n; ++i) {
                structure.insert(i);
            }
            std::cout << "Tiempo de inserción ordenada en lista enlazada: ";
        }
    } else {
        // Inserción aleatoria
        for (int i = 0; i < n; ++i) {
            int value = dist(rng);
            structure.insert(value);
        }
        if constexpr (std::is_same_v<Structure, BSTree<int>>) {
            std::cout << "Tiempo de inserción aleatoria en árbol binario: ";
        } else {
            std::cout << "Tiempo de inserción aleatoria en lista enlazada: ";
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

template <typename Structure>
void measureSearch(Structure& structure, int e, std::mt19937& rng, std::uniform_int_distribution<int>& dist, bool ordered) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < e; ++i) {
        int value = dist(rng);
        
        if constexpr (std::is_same_v<Structure, BSTree<int>>) {
            structure.search(structure.getRoot(), value);
        } else {
            structure.search(value);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    if constexpr (std::is_same_v<Structure, BSTree<int>>) {
        std::cout << "Tiempo de búsqueda " << (ordered ? "ordenada" : "aleatoria") << " en árbol binario: ";
    } else {
        std::cout << "Tiempo de búsqueda " << (ordered ? "ordenada" : "aleatoria") << " en lista enlazada: ";
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

template <typename Structure>
void measureDeletion(Structure& structure, int e, std::mt19937& rng, std::uniform_int_distribution<int>& dist, bool ordered) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < e; ++i) {
        int value = dist(rng);
        structure.remove(value);
    }

    auto end = std::chrono::high_resolution_clock::now();
    if constexpr (std::is_same_v<Structure, BSTree<int>>) {
        std::cout << "Tiempo de eliminación " << (ordered ? "ordenada" : "aleatoria") << " en árbol binario: ";
    } else {
        std::cout << "Tiempo de eliminación " << (ordered ? "ordenada" : "aleatoria") << " en lista enlazada: ";
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

int main() {
  /** Nodes to insert. */
  constexpr int n = 1'000'000;

  /** Nodes to search and delete. */
  constexpr int e = 10'000;

  /** Size of the hash table (m), with a load factor of α = 1 (m = n). */
  size_t m = n;

  /** Random numbers generator. */
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> dist(0, 3 * n - 1);

  /** --- Singly linked list --- */

  /** Create a singly linked list. */
  SLList<int> list;

  /** 5.1.1. Random insertion. */
  measureInsertion(list, n, rng, dist, false);

  /** 5.1.1. Random search. */
  measureSearch(list, e, rng, dist, false);

  /** 5.1.1. Random deletion. */
  measureDeletion(list, e, rng, dist, false);

  /** Clear list. */
  list = SLList<int>();

  /** 5.1.2. Ordered insertion. */
  measureInsertion(list, n, rng, dist, true);

  /** 5.1.2. Ordered search. */
  measureSearch(list, e, rng, dist, true);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(list, e, rng, dist, true);

  /** --- Binary search tree --- */

  /** Create a binary search tree. */
  BSTree<int> bst;

  /** 5.1.1. Random insertion. */
  measureInsertion(bst, n, rng, dist, false);

  /** 5.1.1. Random search. */
  measureSearch(bst, e, rng, dist, false);

  /** 5.1.1. Random deletion. */
  measureDeletion(bst, e, rng, dist, false);

  /** Clear tree. */
  bst = BSTree<int>();

  /** 5.1.2. Ordered insertion. */
  measureInsertion(bst, n, rng, dist, true);

  /** 5.1.2. Ordered search. */
  measureSearch(bst, e, rng, dist, true);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(bst, e, rng, dist, true);

  return 0;
}
