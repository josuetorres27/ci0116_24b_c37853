/*
 * Credits
 * Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 * Template provided by: Prof. Allan Berrocal Rojas
 * Adapted by: Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>
 */

#pragma once

template <typename DataType>
class DLList;

template <typename DataType>
class DLListNode {
 public:
  friend class DLList<DataType>;

  /** Default constructor. */
  DLListNode() : key(DataType()), next(nullptr), prev(nullptr) {}

  /** Constructor with values and pointers. */
  DLListNode(const DataType &value, DLListNode<DataType> *next = nullptr,
    DLListNode<DataType> *prev = nullptr)
      : key(value), next(next), prev(prev) {}

  /** Destructor. */
  ~DLListNode() {}

  /** Getter for the node's key value. */
  DataType getKey() const { return key; }

  /** Getter for the previous node pointer. */
  DLListNode<DataType> *getPrev() const { return prev; }

  /** Getter for the next node pointer. */
  DLListNode<DataType> *getNext() const { return next; }

  /** Setter for the node's key value. */
  void setKey(DataType key) { this->key = key; }

  /** Setter for the previous node pointer. */
  void setPrev(DLListNode<DataType> *prev) { this->prev = prev; }

  /** Setter for the next node pointer. */
  void setNext(DLListNode<DataType> *next) { this->next = next; }

 private:
  DataType key;
  DLListNode<DataType> *next;
  DLListNode<DataType> *prev;
};

template <typename DataType>
class DLList {
 public:
  /** Constructor. */
  DLList() {
    nil = new DLListNode<DataType>();
    nil->next = nil;
    nil->prev = nil;
  }

  /** Destructor. */
  ~DLList() {
    clear();
    delete nil;
  }

  /** Function to clear all nodes in the list. */
  void clear() {
    DLListNode<DataType> *current = nil->next;
    while (current != nil) {
      DLListNode<DataType> *toDelete = current;
      current = current->next;
      delete toDelete;
    }
    nil->next = nil;
    nil->prev = nil;
  }

  /** Insert a value at the beginning of the list. */
  void insert(const DataType &value) {
    DLListNode<DataType> *newNode = new DLListNode<DataType>(value, nil->next,
      nil);
    nil->next->prev = newNode;
    nil->next = newNode;
  }

  /** Search for a value and return a pointer to the node if found. */
  DLListNode<DataType> *search(const DataType &value) const {
    DLListNode<DataType> *current = nil->next;
    while (current != nil && current->key != value) {
      current = current->next;
    }
    return (current == nil) ? nullptr : current;
  }

  /** Remove a value from the list. */
  void remove(const DataType &value) {
    DLListNode<DataType> *node = search(value);
    if (node != nullptr) {
      remove(node);
    }
  }

  /** Remove a specific node from the list. */
  void remove(DLListNode<DataType> *node) {
    if (node != nil) {
      node->prev->next = node->next;
      node->next->prev = node->prev;
      delete node;
    }
  }

  /** Get the sentinel node. */
  DLListNode<DataType> *getNil() const { return nil; }

 private:
  DLListNode<DataType> *nil;  /** Sentinel node to ease operations. */
};
