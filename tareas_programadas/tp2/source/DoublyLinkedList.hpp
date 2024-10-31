/*
 * Credits
 * Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 * Template provided by: Prof. Allan Berrocal Rojas
 * Adapted by: Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>
 */

#pragma once

template <typename DataType>
class DLList;

/**
 * @class DLListNode
 * @brief Represents a node in a doubly linked list.
 * @tparam DataType Type of the data stored in the node.
 */
template <typename DataType>
class DLListNode {
 public:
  friend class DLList<DataType>;

  /**
   * @brief Default constructor.
   * Initializes the node with default values.
   */
  DLListNode() {
    key = DataType();
    next = nullptr;
    prev = nullptr;
  }

  /**
   * @brief Constructor with values and pointers.
   * @param value The value to store in the node.
   * @param next Pointer to the next node in the list.
   * @param prev Pointer to the previous node in the list.
   */
  DLListNode(const DataType &value, DLListNode<DataType> *next = nullptr,
    DLListNode<DataType> *prev = nullptr) {
    this->key = value;
    this->next = next;
    this->prev = prev;
  }

  /** Destructor. */
  ~DLListNode() {}

  /**
   * @brief Retrieves the value stored in the node.
   * @return The value stored in the node.
   */
  DataType getKey() const {
    return key;
  }

  /**
   * @brief Retrieves a pointer to the previous node.
   * @return Pointer to the previous node.
   */
  DLListNode<DataType> *getPrev() const {
    return prev;
  }

  /**
   * @brief Retrieves a pointer to the next node.
   * @return Pointer to the next node.
   */
  DLListNode<DataType> *getNext() const {
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
   * @brief Sets the pointer to the previous node.
   * @param prev Pointer to the previous node.
   */
  void setPrev(DLListNode<DataType> *prev) {
    this->prev = prev;
  }

  /**
   * @brief Sets the pointer to the next node.
   * @param next Pointer to the next node.
   */
  void setNext(DLListNode<DataType> *next) {
    this->next = next;
  }

 private:
  DataType key;                /** Value stored in the node. */
  DLListNode<DataType> *next;  /** Pointer to the next node. */
  DLListNode<DataType> *prev;  /** Pointer to the previous node. */
};

/**
 * @class DLList
 * @brief Implements all functions to create a doubly linked list. It is used
 * to correct collisions in the Hash Table.
 * @tparam DataType Type of data stored in the list nodes.
 */
template <typename DataType>
class DLList {
 public:
  /**
   * @brief Constructor.
   * @details Initializes an empty list with a sentinel node.
   */
  DLList() {
    nil = new DLListNode<DataType>();
    nil->next = nil;
    nil->prev = nil;
  }

  /**
   * @brief Destructor.
   * @details Clears the list and deletes the sentinel node.
   */
  ~DLList() {
    clear();
    delete nil;
  }

  /** Removes all nodes from the list. */
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

  /**
   * @brief Inserts a value at the beginning of the list.
   * @param value The value to insert.
   */
  void insert(const DataType &value) {
    DLListNode<DataType> *newNode = new DLListNode<DataType>(value, nil->next,
      nil);
    nil->next->prev = newNode;
    nil->next = newNode;
  }

  /**
   * @brief Searches for a value in the list.
   * @param value The value to search for.
   * @return Pointer to the node containing the value, or nullptr if not found.
   */
  DLListNode<DataType> *search(const DataType &value) const {
    DLListNode<DataType> *current = nil->next;
    while (current != nil && current->key != value) {
      current = current->next;
    }
    return (current == nil) ? nullptr : current;
  }

  /**
   * @brief Removes a node with a specified value from the list.
   * @param value The value of the node to remove.
   */
  void remove(const DataType &value) {
    DLListNode<DataType> *node = search(value);
    if (node != nullptr) {
      remove(node);
    }
  }

  /**
   * @brief Removes a specified node from the list.
   * @param node Pointer to the node to remove.
   */
  void remove(DLListNode<DataType> *node) {
    if (node != nil) {
      node->prev->next = node->next;
      node->next->prev = node->prev;
      delete node;
    }
  }

  /**
   * @brief Retrieves the sentinel node.
   * @return Pointer to the sentinel node.
   */
  DLListNode<DataType> *getNil() const {
    return nil;
  }

 private:
  /** Sentinel node to ease list operations. */
  DLListNode<DataType> *nil;
};
