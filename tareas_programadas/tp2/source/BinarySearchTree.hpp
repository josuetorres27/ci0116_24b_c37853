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

  /** 
   * @brief Default constructor that initializes an empty node with all 
   * pointers set to nullptr.
   */
  BSTreeNode() = default;

  /**
   * @brief Constructs a node with a specified key, parent, left child, and
   * right child.
   * @param value The key value to store in the node.
   * @param parent Pointer to the parent node (default is nullptr).
   * @param left Pointer to the left child node (default is nullptr).
   * @param right Pointer to the right child node (default is nullptr).
   */
  BSTreeNode(const DataType &value, BSTreeNode<DataType> *parent = nullptr,
    BSTreeNode<DataType> *left = nullptr,
      BSTreeNode<DataType> *right = nullptr) {
    key = value;
    this->parent = parent;
    this->left = left;
    this->right = right;
  }

  /** Destructor. */
  ~BSTreeNode() {}

  /**
   * @brief Retrieves the key stored in the node.
   * @return The key value.
   */
  DataType getKey() const {
    return key;
  }

  /**
   * @brief Retrieves the parent node.
   * @return Pointer to the parent node.
   */
  BSTreeNode<DataType> *getParent() const {
    return parent;
  }

  /**
   * @brief Retrieves the left child node.
   * @return Pointer to the left child node.
   */
  BSTreeNode<DataType> *getLeft() const {
    return left;
  }

  /**
   * @brief Retrieves the right child node.
   * @return Pointer to the right child node.
   */
  BSTreeNode<DataType> *getRight() const {
    return right;
  }

  /**
   * @brief Sets the parent node pointer.
   * @param parent Pointer to the new parent node.
   */
  void setParent(BSTreeNode<DataType> *parent) {
    this->parent = parent;
  }

  /**
   * @brief Sets the left child node pointer.
   * @param left Pointer to the new left child node.
   */
  void setLeft(BSTreeNode<DataType> *left) {
    this->left = left;
  }

  /**
   * @brief Sets the right child node pointer.
   * @param right Pointer to the new right child node.
   */
  void setRight(BSTreeNode<DataType> *right) {
    this->right = right;
  }

 private:
  DataType key;  /** The key value stored in the node. */
  BSTreeNode<DataType> *parent = nullptr;  /** Pointer to the parent. */
  BSTreeNode<DataType> *left = nullptr;  /** Pointer to the left child. */
  BSTreeNode<DataType> *right = nullptr;  /** Pointer to the right child. */
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

  /**
   * @brief Removes all nodes from the tree.
   *
   * @details Frees memory occupied by each node, recursively traversing 
   * from the root to all child nodes.
   */
  void clear() {
    clear(root);
    root = nullptr;
  }

  /**
   * @brief Inserts a new value into the tree.
   * 
   * @param value The value to be inserted into the tree.
   * @note Duplicated values are ignored.
   */
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

  /**
   * @brief Searches for a value within the subtree rooted at the given node.
   *
   * @param rootOfSubtree The subtree root node where the search starts.
   * @param value The value to search for.
   * @return Pointer to the node containing the value, or nullptr if not found.
   */
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

  /**
   * @brief Finds the maximum value in the subtree rooted at the given node.
   *
   * @param node The root of the subtree.
   * @return Pointer to the node with the maximum value, or nullptr if the
   * subtree is empty.
   */
  BSTreeNode<DataType> *getMaximum(const BSTreeNode<DataType> *node) const {
    while (node && node->getRight() != nullptr) {
      node = node->getRight();
    }
    return const_cast<BSTreeNode<DataType> *>(node);
  }

  /**
   * @brief Finds the minimum value in the subtree rooted at the given node.
   * 
   * @param node The root of the subtree.
   * @return Pointer to the node with the minimum value, or nullptr if the
   * subtree is empty.
   */
  BSTreeNode<DataType> *getMinimum(const BSTreeNode<DataType> *node) const {
    while (node && node->getLeft() != nullptr) {
      node = node->getLeft();
    }
    return const_cast<BSTreeNode<DataType> *>(node);
  }

  /**
   * @brief Finds the successor of the given node.
   *
   * @param node The node whose successor is to be found.
   * @return Pointer to the successor node, or nullptr if no successor exists.
   */
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

  /**
   * @brief Performs an inorder traversal of the tree, printing node values.
   *
   * @param rootOfSubtree The subtree root to start the inorder traversal from.
   */
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

  /** Could be implemented in the future. */
  void preorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {}

  /** Could be implemented in the future. */
  void postorderWalk(BSTreeNode<DataType> *rootOfSubtree) const {}

  /**
   * @brief Deletes a node containing the specified value from the tree.
   *
   * @param value The value of the node to be deleted.
   */
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

  /**
   * @brief Retrieves the root of the tree.
   * 
   * @return Pointer to the root node, or nullptr if the tree is empty.
   */
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

  /**
   * @brief Efficiently inserts an ordered sequence of keys by constructing a
   * balanced tree.
   * 
   * @param n The number of keys in the ordered sequence.
   */
  void fastInsert(size_t n) {
    root = buildBalancedTree(0, n - 1);
  }

 private:
  BSTreeNode<DataType> *root;  /** The root node of the tree. */

  /**
   * @brief Recursively clears all nodes from the subtree rooted at the
   * specified node.
   *
   * @param node The root node of the subtree to clear.
   */
  void clear(BSTreeNode<DataType> *node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  /**
   * @brief Recursively builds a balanced binary search tree.
   *
   * @param start The start index for the range of keys.
   * @param end The end index for the range of keys.
   * @return Pointer to the root of the balanced subtree.
   */
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

  /**
   * @brief Transplants one subtree in place of another.
   *
   * @param u The subtree to be replaced.
   * @param v The subtree to be placed in the position of 'u'.
   */
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
