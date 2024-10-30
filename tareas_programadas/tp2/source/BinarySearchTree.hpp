/*
 * Credits
 * Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 * Template provided by: Prof. Allan Berrocal Rojas
 * Adapted by: Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>
 */

#pragma once
#include <cstddef>
#include <iostream>
#include <stack>

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

  /** Constructor with value and pointers. */
  BSTreeNode(const DataType &value, BSTreeNode<DataType> *parent = nullptr,
    BSTreeNode<DataType> *left = nullptr, BSTreeNode<DataType>
      *right = nullptr) {
    key = value;
    this->parent = parent;
    this->left = left;
    this->right = right;
  }

  /** Destructor. */
  ~BSTreeNode() {}

  /** Get nodes's key. */
  DataType getKey() const {
    return key;
  }

  /** Get parent node. */
  BSTreeNode<DataType> *getParent() const {
    return parent;
  }

  /** Get node on the left. */
  BSTreeNode<DataType> *getLeft() const {
    return left;
  }

  /** Get node on the rigth. */
  BSTreeNode<DataType> *getRight() const {
    return right;
  }

  /** Set parent node. */
  void setParent(BSTreeNode<DataType> *parent) {
    this->parent = parent;
  }

  /** Set node on the left. */
  void setLeft(BSTreeNode<DataType> *left) {
    this->left = left;
  }

  /** Set node on the rigth. */
  void setRight(BSTreeNode<DataType> *right) {
    this->right = right;
  }

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
  BSTree() {
    root = nullptr;
  }

  /** Destructor. */
  ~BSTree() {
    clear();
  }

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
      } else if (value > x->getKey()) {
        x = x->getRight();
      } else {
        /** Duplicated value. */
        delete newNode;
        return;
      }
    }
    newNode->setParent(y);
    if (y == nullptr) {
      root = newNode;  /** The tree was empty. */
    } else if (value < y->getKey()) {
      y->setLeft(newNode);
    } else {
      y->setRight(newNode);
    }
  }

  /** Search function. */
  BSTreeNode<DataType> *search(const BSTreeNode<DataType> *rootOfSubtree,
    const DataType &value) const {
    while (rootOfSubtree != nullptr && value != rootOfSubtree->getKey()) {
      if (value < rootOfSubtree->getKey()) {
        rootOfSubtree = rootOfSubtree->getLeft();
      } else {
        rootOfSubtree = rootOfSubtree->getRight();
      }
    }
    return const_cast<BSTreeNode<DataType> *>(rootOfSubtree);
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

  /** Inorder traversal (iterative). */
  void inorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {
    std::stack<BSTreeNode<DataType> *> stack;
    BSTreeNode<DataType> *current = rootOfSubtree;
    while (current != nullptr || !stack.empty()) {
      while (current != nullptr) {
        stack.push(current);
        current = current->getLeft();
      }
      current = stack.top();
      stack.pop();
      std::cout << current->getKey() << " ";
      current = current->getRight();
    }
  }

  void preorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {}

  void postorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {}

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

  /** Returns root node. */
  BSTreeNode<DataType> *getRoot() const {
    return root;
  }

  /**
   * @note Why can inserting 𝑛 ordered keys into a binary search tree take too
   * much time if 𝑛 is large?
   * This is because inserting a sequence in sorted order (e.g., 0, 1, 2, ...,
   * 𝑛 − 1) can result in an unbalanced tree, resembling a linked list. This
   * configuration causes each insertion to require traversing most of the
   * existing nodes, resulting in a time complexity of 𝑂(𝑛²) for all insertions
   * combined. This inefficiency is due to the tree's height approaching 𝑛,
   * which slows down operations as the tree becomes "skewed" rather than
   * balanced.
   *
   * @note How can we avoid the long wait?
   * To avoid the long wait, we can implement a fastInsert method that
   * constructs a balanced BST directly. By recursively selecting the middle
   * element of a given range (e.g., the middle of 0 to 𝑛 − 1) as the root, and
   * then dividing the range to assign the left and right subtrees, we can
   * efficiently create a balanced tree. This approach ensures that the tree's
   * height remains 𝑂(log𝑛), resulting in an overall time complexity of 𝑂(𝑛)
   * for the insertions, as each node is created and linked only once without
   * additional traversal or rebalancing.
   */

  /** Function for fast insertion of an ordered sequence of keys. */
  void fastInsert(size_t n) {
    root = buildBalancedTree(0, n - 1);
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

  BSTreeNode<DataType>* buildBalancedTree(int start, int end) {
    if (start > end) {
      return nullptr;
    }
    /** Finds the mid value and creates a node for it. */
    int mid = start + (end - start) / 2;
    BSTreeNode<DataType>* node = new BSTreeNode<DataType>(mid);
    /** Recursively builds the right and left subtrees. */
    node->setLeft(buildBalancedTree(start, mid - 1));
    if (node->getLeft()) {
      node->getLeft()->setParent(node);
    }
    node->setRight(buildBalancedTree(mid + 1, end));
    if (node->getRight()) {
      node->getRight()->setParent(node);
    }
    return node;
  }

  /** Auxiliary function for deleting. */
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
