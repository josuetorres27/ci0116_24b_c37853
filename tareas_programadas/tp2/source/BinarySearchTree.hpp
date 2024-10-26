/*
 Credits
 Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 */

#pragma once
#include <cstddef>

template <typename DataType>
class BSTree;

template <typename DataType>
class BSTreeNode {
 public:
  friend class BSTree<DataType>;

  BSTreeNode() = default;

  BSTreeNode(const DataType &value, BSTreeNode<DataType> *parent = nullptr,
             BSTreeNode<DataType> *left = nullptr,
             BSTreeNode<DataType> *right = nullptr);

  ~BSTreeNode();

  DataType getKey() const;

  BSTreeNode<DataType> *getParent() const;

  BSTreeNode<DataType> *getLeft() const;

  BSTreeNode<DataType> *getRight() const;

  void setParent(BSTreeNode<DataType> *parent);

  void setLeft(BSTreeNode<DataType> *left);

  void setRight(BSTreeNode<DataType> *right);

 private:
  DataType key;

  BSTreeNode<DataType> *parent = nullptr;

  BSTreeNode<DataType> *left = nullptr;

  BSTreeNode<DataType> *right = nullptr;
};

template <typename DataType>
class BSTree {
 public:
  BSTree() = default;

  ~BSTree() {};

  void insert(const DataType &value);

  void remove(const DataType &value);

  void inorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  void preorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  void postorderWalk(BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *search(const BSTreeNode<DataType> *rootOfSubtree,
                               const DataType &value) const;

  BSTreeNode<DataType> *getMinimum(
      const BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *getMaximum(
      const BSTreeNode<DataType> *rootOfSubtree) const;

  BSTreeNode<DataType> *getSuccessor(const BSTreeNode<DataType> *node) const;

  BSTreeNode<DataType> *getRoot() const;

  void fastInsert(size_t n);
  
 private:
  BSTreeNode<DataType> *root;
};
