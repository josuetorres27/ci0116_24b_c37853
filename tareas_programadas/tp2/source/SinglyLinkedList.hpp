/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once
template <typename DataType>
class SLList;

template <typename DataType>
class SLListNode {
 public:
  friend class SLList<DataType>;

  SLListNode();

  SLListNode(const DataType& value, SLListNode<DataType>* next = nullptr);

  ~SLListNode();

  DataType getKey() const;

  SLListNode<DataType>* getNext() const;

  void setKey(DataType key);

  void setNext(SLListNode<DataType>*);

 private:
  DataType key;

  SLListNode<DataType>* next;
};

template <typename DataType>
class SLList {
 public:
  SLList() = default;

  ~SLList() {};

  void insert(const DataType& value);

  SLListNode<DataType>* search(const DataType& value) const;

  void remove(const DataType& value);

  void remove(SLListNode<DataType>* node);

  SLListNode<DataType>* getNil() const;
  
 private:
  SLListNode<DataType>* nil;
};
