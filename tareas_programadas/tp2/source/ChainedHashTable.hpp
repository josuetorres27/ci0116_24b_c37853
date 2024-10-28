/*
 * Credits
 * Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 * Template provided by: Prof. Allan Berrocal Rojas
 * Adapted by: Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>
 */

#pragma once
#include <vector>

#include "DoublyLinkedList.hpp"

template <typename DataType>
class ChainedHashTable {
 public:
  /** Constructor: creates the table with 'm' doubly linked lists. */
  ChainedHashTable(size_t size) : size(size), table(size) {}

  /** Destructor. */
  ~ChainedHashTable() { clear(); }

  /** Function to clear all lists in the hash table. */
  void clear() {
    for (auto &list : table) {
      list.clear();
    }
  }

  /** Function to insert a value into the table. */
  void insert(const DataType &value) {
    size_t index = hash(value);
    /** Inserts the value into the corresponding list. */
    table[index].insert(value);
  }

  /** Function to search for a value in the table. */
  DLListNode<DataType> *search(const DataType &value) const {
    size_t index = hash(value);
    /** Performs the search in the corresponding list. */
    return table[index].search(value);
  }

  /** Function to remove a value from the table. */
  void remove(const DataType &value) {
    size_t index = hash(value);
    /** Removes the value in the corresponding list if it exists. */
    table[index].remove(value);
  }

  /** Get the table size. */
  size_t getSize() const { return size; }

  /** Set a new table size. */
  void setSize(size_t newSize) {
    size = newSize;
    table.resize(newSize);
  }

  /** Get the current table for inspection or debugging. */
  std::vector<DLList<DataType>> getTable() const { return table; }

  /** Set a new table. */
  void setTable(std::vector<DLList<DataType>> newTable) { table = newTable; }

 private:
  size_t size;
  std::vector<DLList<DataType>> table;

  /** Hash function based on 'h(k) = k % m'. */
  size_t hash(const DataType &key) const { return key % size; }
};
