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
  SLList<int> sll;

  /** 5.1.1. Random insertion. */
  measureInsertion(sll, n, rng, dist, false);

  /** 5.1.1. Random search. */
  measureSearch(sll, e, rng, dist, false);

  /** 5.1.1. Random deletion. */
  measureDeletion(sll, e, rng, dist, false);

  /** Clear Singly Linked List. */
  sll.clear();

  /** 5.1.2. Ordered insertion. */
  measureInsertion(sll, n, rng, dist, true);

  /** 5.1.2. Ordered search. */
  measureSearch(sll, e, rng, dist, true);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(sll, e, rng, dist, true);

  /** ----- Binary Search Tree ----- */

  /** Create Binary Search Tree. */
  BSTree<int> bst;

  /** 5.1.1. Random insertion. */
  measureInsertion(bst, n, rng, dist, false);

  /** 5.1.1. Random search. */
  measureSearch(bst, e, rng, dist, false);

  /** 5.1.1. Random deletion. */
  measureDeletion(bst, e, rng, dist, false);

  /** Clear Binary Search Tree. */
  bst.clear();

  /** 5.1.2. Ordered insertion. */
  measureInsertion(bst, n, rng, dist, true);

  /** 5.1.2. Ordered search. */
  measureSearch(bst, e, rng, dist, true);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(bst, e, rng, dist, true);

  /** ----- Red-Black Tree ----- */

  /** Create Red-Black Tree. */
  RBTree<int> rbt;

  /** 5.1.2. Ordered insertion. */
  measureInsertion(rbt, n, rng, dist, false);

  /** 5.1.2. Ordered search. */
  measureSearch(rbt, e, rng, dist, false);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(rbt, e, rng, dist, false);

  /** Clear Red-Black Tree. */
  rbt.clear();

  /** 5.1.2. Ordered insertion. */
  measureInsertion(rbt, n, rng, dist, true);

  /** 5.1.2. Ordered search. */
  measureSearch(rbt, e, rng, dist, true);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(rbt, e, rng, dist, true);

  /** ----- Hash Table ----- */

  /** Create Hash Table. */
  ChainedHashTable<int> ht(m);

  /** 5.1.2. Ordered insertion. */
  measureInsertion(ht, n, rng, dist, false);

  /** 5.1.2. Ordered search. */
  measureSearch(ht, e, rng, dist, false);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(ht, e, rng, dist, false);

  /** Clear Hash Table. */
  ht.clear();

  /** 5.1.2. Ordered insertion. */
  measureInsertion(ht, n, rng, dist, true);

  /** 5.1.2. Ordered search. */
  measureSearch(ht, e, rng, dist, true);

  /** 5.1.2. Ordered deletion. */
  measureDeletion(ht, e, rng, dist, true);

  return 0;
}
