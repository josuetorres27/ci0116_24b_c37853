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
 * @brief Node class for singly linked list with sentinel.
 *
 * @tparam DataType Type of data stored in the node.
 */
template <typename DataType>
class SLListNode {
 public:
  friend class SLList<DataType>;

  /** Default constructor. */
  SLListNode() {
    key = DataType();
    next = nullptr;
  }

  /** Constructor with value and pointer. */
  SLListNode(const DataType &value, SLListNode<DataType> *next = nullptr) {
    key = value;
    this->next = next;
  }

  /** Destructor. */
  ~SLListNode() {}

  /** Access and modification functions. */
  DataType getKey() const {
    return key;
  }

  SLListNode<DataType> *getNext() const {
    return next;
  }

  void setKey(DataType key) {
    this->key = key;
  }

  void setNext(SLListNode<DataType> *next) {
    this->next = next;
  }

 private:
  DataType key;
  SLListNode<DataType> *next;
};

/**
 * @brief Singly linked list with a sentinel node.
 *
 * @tparam DataType Type of data stored in the list.
 */
template <typename DataType>
class SLList {
 public:
  /** Constructor. */
  SLList() {
    nil = new SLListNode<DataType>();  /** Sentinel node. */
    nil->setNext(nil);  /** Initialize itself. */
  }

  /** Destructor. */
  ~SLList() {
    clear();
    delete nil;  /** Frees sentinel after clearing the list. */
  }

  /** Function to clear all nodes from the list. */
  void clear() {
    SLListNode<DataType> *current = nil->getNext();
    while (current != nil) {
      SLListNode<DataType> *toDelete = current;
      current = current->getNext();
      delete toDelete;
    }
    nil->setNext(nil);
  }

  /** Insertion function. */
  void insert(const DataType &value) {
    SLListNode<DataType> *newNode =
      new SLListNode<DataType>(value, nil->getNext());
    nil->setNext(newNode);
  }

  /** Search function (returns first occurrence). */
  SLListNode<DataType> *search(const DataType &value) const {
    SLListNode<DataType> *current = nil->getNext();
    while (current != nil) {
      if (current->getKey() == value) {
        return current;
      }
      current = current->getNext();
    }
    return nullptr;  /** Not found. */
  }

  /** Deletion function (deletes all occurrences). */
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

  /** Returns sentinel node. */
  SLListNode<DataType> *getNil() const {
    return nil;
  }

 private:
  SLListNode<DataType> *nil;
};
