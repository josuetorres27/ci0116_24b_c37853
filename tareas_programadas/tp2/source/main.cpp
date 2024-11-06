// Copyright 2024 Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>

#include <chrono>
#include <random>
#include <string>

#include "SinglyLinkedList.hpp"
#include "BinarySearchTree.hpp"
#include "RedBlackTree.hpp"
#include "ChainedHashTable.hpp"

/** Function to handle insertion in any structure. */
template <typename Structure>
void measureInsertion(Structure& structure, int n, std::mt19937& rng,
  std::uniform_int_distribution<int>& dist, bool ordered) {
  auto start = std::chrono::high_resolution_clock::now();
  if (ordered) {
    /** Ordered insertion. */
    if constexpr (std::is_same_v<Structure, BSTree<int>>) {
      structure.fastInsert(n);
      std::cout << "Insertion time (ordered) in Binary Search Tree "
        "(fastInsert): ";
    } else if constexpr (std::is_same_v<Structure, RBTree<int>>) {
      for (int i = 0; i < n; ++i) {
        structure.insert(i);
      }
      std::cout << "Insertion time (ordered) in Red-Black Tree: ";
    } else if constexpr (std::is_same_v<Structure, ChainedHashTable<int>>) {
      for (int i = 0; i < n; ++i) {
        structure.insert(i);
      }
      std::cout << "Insertion time (ordered) in Hash Table: ";
    } else {
      for (int i = 0; i < n; ++i) {
        structure.insert(i);
      }
      std::cout << "Insertion time (ordered) in Singly Linked List: ";
    }
  } else {
    /** Random insertion. */
    for (int i = 0; i < n; ++i) {
      int value = dist(rng);
      structure.insert(value);
    }
    if constexpr (std::is_same_v<Structure, BSTree<int>>) {
      std::cout << "Insertion time (random) in Binary Search Tree: ";
    } else if constexpr (std::is_same_v<Structure, RBTree<int>>) {
      std::cout << "Insertion time (random) in Red-Black Tree: ";
    } else if constexpr (std::is_same_v<Structure, ChainedHashTable<int>>) {
      std::cout << "Insertion time (random) in Hash Table: ";
    } else {
      std::cout << "Insertion time (random) in Singly Linked List: ";
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << elapsed.count() << " ms\n";
}

/** Function to handle search in any structure. */
template <typename Structure>
void measureSearch(Structure& structure, int e, std::mt19937& rng,
  std::uniform_int_distribution<int>& dist, bool ordered) {
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < e; ++i) {
    int value = dist(rng);
    if constexpr (std::is_same_v<Structure, BSTree<int>> ||
      std::is_same_v<Structure, RBTree<int>>) {
      structure.search(structure.getRoot(), value);
    } else if constexpr (std::is_same_v<Structure, ChainedHashTable<int>>) {
      structure.search(value);
    } else {
      structure.search(value);
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  if constexpr (std::is_same_v<Structure, BSTree<int>>) {
    std::cout << "Search time " << (ordered ? "(ordered)" : "(random)")
      << " in Binary Search Tree: ";
  } else if constexpr (std::is_same_v<Structure, RBTree<int>>) {
    std::cout << "Search time " << (ordered ? "(ordered)" : "(random)")
      << " in Red-Black Tree: ";
  } else if constexpr (std::is_same_v<Structure, ChainedHashTable<int>>) {
    std::cout << "Search time " << (ordered ? "(ordered)" : "(random)")
      << " in Hash Table: ";
  } else {
    std::cout << "Search time " << (ordered ? "(ordered)" : "(random)")
      << " in Singly Linked List: ";
  }
  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << elapsed.count() << " ms\n";
}

/** Function to handle deletion in any structure. */
template <typename Structure>
void measureDeletion(Structure& structure, int e, std::mt19937& rng,
  std::uniform_int_distribution<int>& dist, bool ordered) {
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < e; ++i) {
    int value = dist(rng);
    structure.remove(value);
  }
  auto end = std::chrono::high_resolution_clock::now();
  if constexpr (std::is_same_v<Structure, BSTree<int>>) {
    std::cout << "Deletion time " << (ordered ? "(ordered)" : "(random)")
      << " in Binary Search Tree: ";
  } else if constexpr (std::is_same_v<Structure, RBTree<int>>) {
    std::cout << "Deletion time " << (ordered ? "(ordered)" : "(random)")
      << " in Red-Black Tree: ";
  } else if constexpr (std::is_same_v<Structure, ChainedHashTable<int>>) {
    std::cout << "Deletion time " << (ordered ? "(ordered)" : "(random)")
      << " in Hash Table: ";
  } else {
    std::cout << "Deletion time " << (ordered ? "(ordered)" : "(random)")
      << " in Singly Linked List: ";
  }
  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << elapsed.count() << " ms\n";
  std::cout << "\n";
}

int main() {
  /** Nodes to insert. */
  constexpr int n = 1'000'000;

  /** Nodes to search and delete. */
  constexpr int e = 10'000;

  /** Size of the Hash Table (m), with a load factor of α = 1 (m = n). */
  size_t m = n;

  /** Random numbers generator. */
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> dist(0, 3 * n - 1);

  /** ----- Singly Linked List ----- */

  /** Create a Singly Linked List. */
  SLList<int> sllR;  /** Random list. */

  /** 5.1.1. Random insertion. */
  measureInsertion(sllR, n, rng, dist, false);

  /** 5.1.1. Random search. */
  measureSearch(sllR, e, rng, dist, false);

  /** 5.1.1. Random deletion. */
  measureDeletion(sllR, e, rng, dist, false);

  /** Create a Singly Linked List. */
  SLList<int> sllO;  /** Ordered list. */

  /** 5.1.2. Ordered insertion. */
  measureInsertion(sllO, n, rng, dist, true);

  /** 5.1.2. Ordered search. */
  measureSearch(sllO, e, rng, dist, true);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(sllO, e, rng, dist, true);

  /** ----- Binary Search Tree ----- */

  /** Create a Binary Search Tree. */
  BSTree<int> bstR;  /** Random tree. */

  /** 5.1.1. Random insertion. */
  measureInsertion(bstR, n, rng, dist, false);

  /** 5.1.1. Random search. */
  measureSearch(bstR, e, rng, dist, false);

  /** 5.1.1. Random deletion. */
  measureDeletion(bstR, e, rng, dist, false);

  /** Create a Binary Search Tree. */
  BSTree<int> bstO;  /** Ordered tree. */

  /** 5.1.2. Ordered insertion. */
  measureInsertion(bstO, n, rng, dist, true);

  /** 5.1.2. Ordered search. */
  measureSearch(bstO, e, rng, dist, true);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(bstO, e, rng, dist, true);

  /** ----- Red-Black Tree ----- */

  /** Create a Red-Black Tree. */
  RBTree<int> rbtR;  /** Random tree. */

  /** 5.1.2. Ordered insertion. */
  measureInsertion(rbtR, n, rng, dist, false);

  /** 5.1.2. Ordered search. */
  measureSearch(rbtR, e, rng, dist, false);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(rbtR, e, rng, dist, false);

  /** Create a Red-Black Tree. */
  RBTree<int> rbtO;  /** Ordered tree. */

  /** 5.1.2. Ordered insertion. */
  measureInsertion(rbtO, n, rng, dist, true);

  /** 5.1.2. Ordered search. */
  measureSearch(rbtO, e, rng, dist, true);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(rbtO, e, rng, dist, true);

  /** ----- Hash Table ----- */

  /** Create a Hash Table. */
  ChainedHashTable<int> htR(m);  /** Random table. */

  /** 5.1.2. Ordered insertion. */
  measureInsertion(htR, n, rng, dist, false);

  /** 5.1.2. Ordered search. */
  measureSearch(htR, e, rng, dist, false);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(htR, e, rng, dist, false);

  /** Create a Hash Table. */
  ChainedHashTable<int> htO(m);  /** Ordered table. */

  /** 5.1.2. Ordered insertion. */
  measureInsertion(htO, n, rng, dist, true);

  /** 5.1.2. Ordered search. */
  measureSearch(htO, e, rng, dist, true);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(htO, e, rng, dist, true);

  return 0;
}
