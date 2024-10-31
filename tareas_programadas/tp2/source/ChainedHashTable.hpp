/*
 * Credits
 * Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 * Template provided by: Prof. Allan Berrocal Rojas
 * Adapted by: Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>
 */

#pragma once
#include <vector>

#include "DoublyLinkedList.hpp"

/**
 * @class ChainedHashTable
 * @brief Implements a hash table with chaining for collision resolution.
 * @tparam DataType Type of data stored in the hash table.
 */
template <typename DataType>
class ChainedHashTable {
 public:
  /**
   * @brief Constructor that initializes the hash table with a specified number
   * of buckets.
   * @param size The number of buckets in the hash table.
   */
  ChainedHashTable(size_t size) {
    this->size = size;
    table.resize(size);
  }

  /** Destructor. */
  ~ChainedHashTable() {
    clear();
  }

  /**
   * @brief Clears all buckets in the hash table.
   * @details Deletes all elements in each linked list of the table.
   */
  void clear() {
    for (auto &list : table) {
      list.clear();
    }
  }

  /**
   * @brief Inserts a value into the hash table, avoiding duplicates.
   * @param value The value to insert.
   * @details Checks if the value already exists in the appropriate bucket
   * before insertion.
   */
  void insert(const DataType &value) {
    size_t index = hash(value);
    if (table[index].search(value) == nullptr) {  /** Avoid duplicates. */
      table[index].insert(value);
    }
  }

  /**
   * @brief Searches for a value in the hash table.
   * @param value The value to search for.
   * @return Pointer to the node containing the value, or nullptr if not found.
   */
  DLListNode<DataType> *search(const DataType &value) const {
    size_t index = hash(value);
    return table[index].search(value);
  }

  /**
   * @brief Removes a value from the hash table.
   * @param value The value to remove.
   * @details Removes the value if it exists in the corresponding bucket.
   */
  void remove(const DataType &value) {
    size_t index = hash(value);
    table[index].remove(value);
  }

  /**
   * @brief Retrieves the current size (number of buckets) of the hash table.
   * @return The number of buckets in the hash table.
   */
  size_t getSize() const {
    return size;
  }

  /**
   * @brief Sets a new size for the hash table and resizes the table.
   * @param newSize The new number of buckets for the hash table.
   */
  void setSize(size_t newSize) {
    size = newSize;
    table.resize(newSize);
  }

  /**
   * @brief Retrieves the current hash table.
   * @return A vector of doubly linked lists representing the table buckets.
   */
  std::vector<DLList<DataType>> getTable() const {
    return table;
  }

  /**
   * @brief Sets a new hash table.
   * @param newTable A vector of doubly linked lists to replace the current
   * table.
   */
  void setTable(std::vector<DLList<DataType>> newTable) {
    table = newTable;
  }

 private:
  size_t size;  /** Number of buckets in the hash table. */
  /** Hash table represented by a vector of doubly linked lists. */
  std::vector<DLList<DataType>> table;

  /**
   * @brief Hash function that computes the bucket index for a given key.
   * @param key The key to hash.
   * @return The index of the bucket for the key.
   * @details Uses a simple mod hash function: h(k) = k % m.
   */
  size_t hash(const DataType &key) const {
    return key % size;
  }
};
