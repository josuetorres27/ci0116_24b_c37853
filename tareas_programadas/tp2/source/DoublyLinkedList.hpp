/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once
template <typename DataType>
class DLList;

template <typename DataType>
class DLListNode {
 public:
  friend class DLList<DataType>;

  DLListNode() = default;

  DLListNode(const DataType& value, DLListNode<DataType>* next = nullptr,
             DLListNode<DataType>* prev = nullptr);

  ~DLListNode() {};

  DataType getKey() const;

  DLListNode<DataType>* getPrev() const;

  DLListNode<DataType>* getNext() const;

  void setKey(DataType key);

  void setPrev(DLListNode<DataType>* prev);

  void setNext(DLListNode<DataType>* next);

 private:
  DataType key;

  DLListNode<DataType>* next;

  DLListNode<DataType>* prev;
};

template <typename DataType>
class DLList {
 public:
  DLList() = default;

  ~DLList() {};

  void insert(const DataType& value);

  DLListNode<DataType>* search(const DataType& value) const;

  void remove(const DataType& value);

  void remove(DLListNode<DataType>* node);

  DLListNode<DataType>* getNil() const;

 private:
  DLListNode<DataType>* nil;
};
