/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once

enum colors { RED, BLACK };

template <typename DataType>
class RBTree;

template <typename DataType>
class RBTreeNode {
 public:
  friend class RBTree<DataType>;

  RBTreeNode() = default;

  RBTreeNode(const DataType &value, RBTreeNode<DataType> *parent = nullptr,
             RBTreeNode<DataType> *left = nullptr,
             RBTreeNode<DataType> *right = nullptr, enum colors c = RED);

  ~RBTreeNode();

  DataType getKey() const;

  RBTreeNode<DataType> *getParent() const;

  RBTreeNode<DataType> *getLeft() const;

  RBTreeNode<DataType> *getRight() const;

  void setKey(DataType key);

  void setParent(RBTreeNode<DataType> *parent);

  void setLeft(RBTreeNode<DataType> *left);

  void setRight(RBTreeNode<DataType> *right);

 private:
  DataType key;

  RBTreeNode<DataType> *parent;

  RBTreeNode<DataType> *left;

  RBTreeNode<DataType> *right;

  enum colors color;
};

template <typename DataType>
class RBTree {
 public:
  RBTree() = default;

  ~RBTree() {}

  void insert(const DataType &value);

  void remove(const DataType &value);

  RBTreeNode<DataType> *search(const RBTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const;

  RBTreeNode<DataType> *getMinimum(
      const RBTreeNode<DataType> *rootOfSubtree) const;

  RBTreeNode<DataType> *getMaximum(
      const RBTreeNode<DataType> *rootOfSubtree) const;

  RBTreeNode<DataType> *getSuccessor(const RBTreeNode<DataType> *node) const;

  RBTreeNode<DataType> *getRoot() const;


  RBTreeNode<DataType> *getNil() const;


 private:
  RBTreeNode<DataType> *root;

  RBTreeNode<DataType> *nil;
};
