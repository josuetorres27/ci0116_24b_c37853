/*
 * Credits
 * Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 * Template provided by: Prof. Allan Berrocal Rojas
 * Adapted by: Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>
 */

#pragma once
#include <iostream>

template <typename DataType>
class BSTree;

/**
 * @brief Node class for a Binary Search Tree, supporting basic node
 * properties and links to parent and child nodes.
 *
 * @tparam DataType Type of data stored in the node.
 */
template <typename DataType>
class BSTreeNode {
 public:
  friend class BSTree<DataType>;
  /** Default constructor. */
  BSTreeNode() = default;

  /** Constructor with values and pointers. */
  BSTreeNode(const DataType &value, BSTreeNode<DataType> *parent = nullptr,
    BSTreeNode<DataType> *left = nullptr,
      BSTreeNode<DataType> *right = nullptr)
        : key(value), parent(parent), left(left), right(right) {}

  /** Destructor. */
  ~BSTreeNode() {}

  /** Get nodes's key. */
  DataType getKey() const { return key; }

  /** Get parent node. */
  BSTreeNode<DataType> *getParent() const { return parent; }

  /** Get node on the left. */
  BSTreeNode<DataType> *getLeft() const { return left; }

  /** Get node on the rigth. */
  BSTreeNode<DataType> *getRight() const { return right; }

  /** Set parent node. */
  void setParent(BSTreeNode<DataType> *parent) { this->parent = parent; }

  /** Set node on the left. */
  void setLeft(BSTreeNode<DataType> *left) { this->left = left; }

  /** Set node on the rigth. */
  void setRight(BSTreeNode<DataType> *right) { this->right = right; }

 private:
  DataType key;
  BSTreeNode<DataType> *parent = nullptr;
  BSTreeNode<DataType> *left = nullptr;
  BSTreeNode<DataType> *right = nullptr;
};

/**
 * @brief Binary Search Tree class supporting basic operations such as
 * insertion, searching, deletion and traversal.
 *
 * @tparam DataType Type of data stored in the tree.
 */
template <typename DataType>
class BSTree {
 public:
  /** Constructor. */
  BSTree() : root(nullptr) {}

  /** Destructor. */
  ~BSTree() { clear(); }

  /** Function to clear all nodes from the tree. */
  void clear() {
    clear(root);
    root = nullptr;
  }

  /** Insertion function. */
  void insert(const DataType &value) {
    BSTreeNode<DataType> *newNode = new BSTreeNode<DataType>(value);
    BSTreeNode<DataType> *y = nullptr;
    BSTreeNode<DataType> *x = root;

    while (x != nullptr) {
      y = x;
      if (value < x->getKey()) {
        x = x->getLeft();
      } else {
        x = x->getRight();
      }
    }

    newNode->setParent(y);

    if (y == nullptr) {
      root = newNode;
    } else if (value < y->getKey()) {
      y->setLeft(newNode);
    } else {
      y->setRight(newNode);
    }
  }

  /** Search function. */
  BSTreeNode<DataType> *search(const BSTreeNode<DataType> *node,
    const DataType &value) const {
    while (node != nullptr && value != node->getKey()) {
      if (value < node->getKey()) {
        node = node->getLeft();
      } else {
        node = node->getRight();
      }
    }
    return const_cast<BSTreeNode<DataType> *>(node);
  }

  /** Function to get maximum (iterative). */
  BSTreeNode<DataType> *getMaximum(const BSTreeNode<DataType> *node) const {
    while (node && node->getRight() != nullptr) {
      node = node->getRight();
    }
    return const_cast<BSTreeNode<DataType> *>(node);
  }

  /** Function to get minimum (iterative). */
  BSTreeNode<DataType> *getMinimum(const BSTreeNode<DataType> *node) const {
    while (node && node->getLeft() != nullptr) {
      node = node->getLeft();
    }
    return const_cast<BSTreeNode<DataType> *>(node);
  }

  /** Function to get successor node (iterative). */
  BSTreeNode<DataType> *getSuccessor(const BSTreeNode<DataType> *node) const {
    if (node->getRight() != nullptr) {
      return getMinimum(node->getRight());
    }
    BSTreeNode<DataType> *parent = node->getParent();
    while (parent != nullptr && node == parent->getRight()) {
      node = parent;
      parent = parent->getParent();
    }
    return parent;
  }

  /** Inorder traversal. */
  void inorderWalk(BSTreeNode<DataType> *node) const {
    if (node != nullptr) {
      inorderWalk(node->getLeft());
      std::cout << node->getKey() << " ";
      inorderWalk(node->getRight());
    }
  }

  /** Deletion function. */
  void remove(const DataType &value) {
    BSTreeNode<DataType> *node = search(root, value);
    if (node == nullptr) return;

    if (node->getLeft() == nullptr) {
      transplant(node, node->getRight());
    } else if (node->getRight() == nullptr) {
      transplant(node, node->getLeft());
    } else {
      BSTreeNode<DataType> *y = getMinimum(node->getRight());
      if (y->getParent() != node) {
        transplant(y, y->getRight());
        y->setRight(node->getRight());
        y->getRight()->setParent(y);
      }
      transplant(node, y);
      y->setLeft(node->getLeft());
      y->getLeft()->setParent(y);
    }
    delete node;
  }

  /** Obtain tree's root. */
  BSTreeNode<DataType> *getRoot() const { return root; }

  /** Function for fast insertion of an ordered sequence of keys. */
  void fastInsert(int start, int end) {
    if (start > end) return;
    int mid = start + (end - start) / 2;
    insert(mid);  /** Insert element in the middle of the tree. */
    fastInsert(start, mid - 1);  /** Insert left elements. */
    fastInsert(mid + 1, end);  /** Insert rigth elements. */
  }

 private:
  BSTreeNode<DataType> *root;

  /** Recursive function to clear all nodes from the tree. */
  void clear(BSTreeNode<DataType> *node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  /** Auxiliar function for deleting. */
  void transplant(BSTreeNode<DataType> *u, BSTreeNode<DataType> *v) {
    if (u->getParent() == nullptr) {
      root = v;
    } else if (u == u->getParent()->getLeft()) {
      u->getParent()->setLeft(v);
    } else {
      u->getParent()->setRight(v);
    }
    if (v != nullptr) {
      v->setParent(u->getParent());
    }
  }
};
