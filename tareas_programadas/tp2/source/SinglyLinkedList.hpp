/*
 * Credits
 * Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 * Template provided by: Prof. Allan Berrocal Rojas
 * Adapted by: Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>
 */

#pragma once
#include <iostream>

template <typename DataType>
class SLList;

/**
 * @class SLListNode
 * @brief Represents a node in a singly linked list with a sentinel.
 * @tparam DataType Type of the data stored in the node.
 */
template <typename DataType>
class SLListNode {
 public:
  friend class SLList<DataType>;

  /**
   * @brief Default constructor.
   * @details Initializes the node with a default value and null next pointer.
   */
  SLListNode() {
    key = DataType();
    next = nullptr;
  }

  /**
   * @brief Constructor with value and next pointer.
   * @param value The value to store in the node.
   * @param next Pointer to the next node in the list.
   */
  SLListNode(const DataType &value, SLListNode<DataType> *next = nullptr) {
    key = value;
    this->next = next;
  }

  /** Destructor. */
  ~SLListNode() {}

  /**
   * @brief Retrieves the value stored in the node.
   * @return The value stored in the node.
   */
  DataType getKey() const {
    return key;
  }

  /**
   * @brief Retrieves the next node pointer.
   * @return Pointer to the next node in the list.
   */
  SLListNode<DataType> *getNext() const {
    return next;
  }

  /**
   * @brief Sets the value stored in the node.
   * @param key The new value to store.
   */
  void setKey(DataType key) {
    this->key = key;
  }

  /**
   * @brief Sets the next node pointer.
   * @param next Pointer to the next node.
   */
  void setNext(SLListNode<DataType> *next) {
    this->next = next;
  }

 private:
  DataType key;                /** Value stored in the node. */
  SLListNode<DataType> *next;  /** Pointer to the next node. */
};

/**
 * @class SLList
 * @brief Implements all functions to create a singly linked list with a
 * sentinel node.
 * @tparam DataType Type of data stored in the list nodes.
 */
template <typename DataType>
class SLList {
 public:
  /**
   * @brief Constructor.
   * @details Initializes an empty list with a sentinel node.
   */
  SLList() {
    /** Sentinel node. */
    nil = new SLListNode<DataType>();
    /** Points sentinel to itself to denote an empty list. */
    nil->setNext(nil);
  }

  /**
   * @brief Destructor.
   * @details Clears the list and deletes the sentinel node.
   */
  ~SLList() {
    clear();
    delete nil;  /** Frees sentinel after clearing the list. */
  }

  /** Removes all nodes from the list. */
  void clear() {
    SLListNode<DataType> *current = nil->getNext();
    while (current != nil) {
      SLListNode<DataType> *toDelete = current;
      current = current->getNext();
      delete toDelete;
    }
    nil->setNext(nil);
  }

  /**
   * @brief Inserts a value at the beginning of the list.
   * @param value The value to insert.
   */
  void insert(const DataType &value) {
    SLListNode<DataType> *newNode =
      new SLListNode<DataType>(value, nil->getNext());
    nil->setNext(newNode);
  }

  /**
   * @brief Searches for the first occurrence of a value in the list.
   * @param value The value to search for.
   * @return Pointer to the node containing the value, or nullptr if not found.
   */
  SLListNode<DataType> *search(const DataType &value) const {
    SLListNode<DataType> *current = nil->getNext();
    while (current != nil) {
      if (current->getKey() == value) {
        return current;
      }
      current = current->getNext();
    }
    return nullptr;  /** Value not found. */
  }

  /**
   * @brief Removes all nodes with a specified value from the list.
   * @param value The value of the nodes to remove.
   */
  void remove(const DataType &value) {
    SLListNode<DataType> *current = nil;
    while (current->getNext() != nil) {
      if (current->getNext()->getKey() == value) {
        SLListNode<DataType> *temp = current->getNext();
        current->setNext(temp->getNext());
        delete temp;
      } else {
        current = current->getNext();
      }
    }
  }

  /**
   * @brief Retrieves the sentinel node.
   * @return Pointer to the sentinel node.
   */
  SLListNode<DataType> *getNil() const {
    return nil;
  }

 private:
  /** Sentinel node to ease list operations. */
  SLListNode<DataType> *nil;
};
