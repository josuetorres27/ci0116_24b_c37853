/*
 * Credits
 * Based on: Prof. Arturo Camacho, Universidad de Costa Rica
 * Template provided by: Prof. Allan Berrocal Rojas
 * Adapted by: Josué Torres Sibaja <josue.torressibaja@ucr.ac.cr>
 */

#pragma once

enum colors { RED, BLACK };

template <typename DataType>
class RBTree;

/**
 * @class RBTreeNode
 * @brief A node class for a Red-Black Tree (RBT) containing a key of generic
 * data type, color, and pointers to its parent, left, and right children.
 *
 * @tparam DataType The data type of the node's key.
 */
template <typename DataType>
class RBTreeNode {
 public:
  friend class RBTree<DataType>;

  /** 
   * @brief Default constructor that initializes a black node with a default 
   * key value and all pointers set to nullptr.
   */
  RBTreeNode() {
    key = DataType();
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = colors::BLACK;
  }

  /**
   * @brief Constructs a node with a specified key, parent, left child, 
   * right child, and color.
   *
   * @param key The key value to store in the node.
   * @param parent Pointer to the parent node (default is nullptr).
   * @param left Pointer to the left child node (default is nullptr).
   * @param right Pointer to the right child node (default is nullptr).
   * @param color The color of the node, either RED or BLACK (default is RED).
   */
  RBTreeNode(const DataType &key, RBTreeNode<DataType>* parent = nullptr,
    RBTreeNode<DataType>* left = nullptr,
      RBTreeNode<DataType>* right = nullptr, colors color = colors::RED) {
    this->key = key;
    this->parent = parent;
    this->left = left;
    this->right = right;
    this->color = color;
  }

  /** Destructor. */
  ~RBTreeNode() {}

  /**
   * @brief Retrieves the key stored in the node.
   *
   * @return The key value.
   */
  DataType getKey() const {
    return key;
  }

  /**
   * @brief Retrieves the parent node.
   *
   * @return Pointer to the parent node.
   */
  RBTreeNode<DataType> *getParent() const {
    return parent;
  }

  /**
   * @brief Retrieves the left child node.
   *
   * @return Pointer to the left child node.
   */
  RBTreeNode<DataType> *getLeft() const {
    return left;
  }

  /**
   * @brief Retrieves the right child node.
   *
   * @return Pointer to the right child node.
   */
  RBTreeNode<DataType> *getRight() const {
    return right;
  }

  /**
   * @brief Sets the key of the node.
   *
   * @param key The new key value.
   */
  void setKey(DataType key) {
    this->key = key;
  }

  /**
   * @brief Sets the parent node pointer.
   *
   * @param parent Pointer to the new parent node.
   */
  void setParent(RBTreeNode<DataType> *parent) {
    this->parent = parent;
  }

  /**
   * @brief Sets the left child node pointer.
   *
   * @param left Pointer to the new left child node.
   */
  void setLeft(RBTreeNode<DataType> *left) {
    this->left = left;
  }

  /**
   * @brief Sets the right child node pointer.
   *
   * @param right Pointer to the new right child node.
   */
  void setRight(RBTreeNode<DataType> *right) {
    this->right = right;
  }

 private:
  DataType key;  /** The key value stored in the node. */
  RBTreeNode<DataType> *parent;  /** Pointer to the parent node. */
  RBTreeNode<DataType> *left;  /** Pointer to the left child node. */
  RBTreeNode<DataType> *right;  /** Pointer to the right child node. */
  enum colors color;  /** Color of the node, either red or black. */
};

/**
 * @class RBTree
 * @brief Implementation of a Red-Black Tree (RBTree), a self-balancing binary
 * search tree.
 *
 * @details The RBTree class maintains balanced tree properties, ensuring
 * efficient insertions, deletions, and lookups.
 * @tparam DataType Type of data stored in each tree node.
 */
template <typename DataType>
class RBTree {
 public:
  /**
   * @brief Constructor.
   *
   * @details Initializes the red-black tree by creating a sentinel (nil) node
   * with color black. The root of the tree is set to the nil node, indicating
   * an initially empty tree.
   */
  RBTree() {
    nil = new RBTreeNode<DataType>();
    nil->color = BLACK;
    nil->left = nil->right = nil->parent = nullptr;
    root = nil;
  }

  /**
   * @brief Destructor.
   *
   * @details Calls clearTree to recursively delete all nodes in the tree. The
   * sentinel node (nil) is then deleted, freeing all allocated memory.
   */
  ~RBTree() {
    clearTree(root);
    delete nil;
  }

  /**
   * @brief Clears all nodes from the tree.
   *
   * @details Calls 'clearTree()' to recursively free memory starting from the
   * root, then points the root to 'nil'.
   */
  void clear() {
    clearTree(root);
    root = nil;
  }

  /**
   * @brief Insertion function.
   *
   * @details Inserts a new node with the given value into the tree, ensuring
   * it remains balanced.
   * @param value The value to insert.
   * @note Duplicates are not allowed; if the value already exists, the
   * function exits early.
   */
  void insert(const DataType &value) {
    /** Check if the value already exists to prevent duplicates. */
    if (search(root, value) != nil) return;
    RBTreeNode<DataType> *node = new RBTreeNode<DataType>
      (value, nil, nil, nil, RED);
    RBTreeNode<DataType> *y = nil;
    RBTreeNode<DataType> *x = root;
    while (x != nil) {
      y = x;
      if (node->key < x->key)
        x = x->left;
      else
        x = x->right;
    }
    node->parent = y;
    if (y == nil)
      root = node;
    else if (node->key < y->key)
      y->left = node;
    else
      y->right = node;
    node->left = nil;
    node->right = nil;
    node->color = RED;
    insertFixup(node);
  }

  /**
   * @brief Deletion function.
   *
   * @details Removes a node with the specified value from the tree, if it
   * exists, maintaining balance.
   * @param value The value to remove.
   * After removal, a fixup function is called if necessary to restore
   * red-black properties.
   */
  void remove(const DataType &value) {
    RBTreeNode<DataType> *nodeToDelete = search(root, value);
    if (nodeToDelete == nil) return;
    RBTreeNode<DataType> *y = nodeToDelete;
    RBTreeNode<DataType> *x;
    enum colors originalColor = y->color;
    if (nodeToDelete->left == nil) {
      x = nodeToDelete->right;
      transplant(nodeToDelete, nodeToDelete->right);
    } else if (nodeToDelete->right == nil) {
      x = nodeToDelete->left;
      transplant(nodeToDelete, nodeToDelete->left);
    } else {
      y = getMinimum(nodeToDelete->right);
      originalColor = y->color;
      x = y->right;
      if (y->parent == nodeToDelete) {
        x->parent = y;
      } else {
        transplant(y, y->right);
        y->right = nodeToDelete->right;
        y->right->parent = y;
      }
      transplant(nodeToDelete, y);
      y->left = nodeToDelete->left;
      y->left->parent = y;
      y->color = nodeToDelete->color;
    }
    delete nodeToDelete;
    if (originalColor == BLACK) removeFixup(x);
  }

  /**
   * @brief Search function.
   *
   * @details Searches for a node with a specified value in a subtree rooted at
   * a given node.
   * @param rootOfSubtree The root of the subtree to search.
   * @param value The value to search for.
   * @return A pointer to the found node or the sentinel (nil) if not found.
   */
  RBTreeNode<DataType> *search(const RBTreeNode<DataType> *rootOfSubtree,
    const DataType &value) const {
    RBTreeNode<DataType> *node = const_cast<RBTreeNode<DataType> *>
      (rootOfSubtree);
    while (node != nil && node->key != value) {
      if (value < node->key)
        node = node->left;
      else
        node = node->right;
    }
    return node;
  }

  /**
   * @brief Function to get maximum.
   *
   * @details Finds the maximum (rightmost) node in a subtree rooted at a
   * specified node.
   * @param rootOfSubtree The root of the subtree.
   * @return A pointer to the node with the maximum value in the subtree.
   */
  RBTreeNode<DataType> *getMaximum(const RBTreeNode<DataType>
    *rootOfSubtree) const {
    RBTreeNode<DataType> *node = rootOfSubtree;
    while (node->right != nil) node = node->right;
    return node;
  }

  /**
   * @brief Function to get minimum.
   *
   * @details Finds the minimum (leftmost) node in a subtree rooted at a
   * specified node.
   * @param rootOfSubtree The root of the subtree.
   * @return A pointer to the node with the minimum value in the subtree.
   */
  RBTreeNode<DataType> *getMinimum(const RBTreeNode<DataType>
    *rootOfSubtree) const {
    RBTreeNode<DataType> *node = const_cast<RBTreeNode<DataType> *>
      (rootOfSubtree);
    while (node->left != nil) node = node->left;
    return node;
  }

  /**
   * @brief Function to get successor node.
   *
   * @details Finds the successor of a given node, which is the node with the
   * smallest value greater than the given node's value.
   * @param node The node for which the successor is to be found.
   * @return A pointer to the successor node, or nil if no successor exists.
   */
  RBTreeNode<DataType> *getSuccessor(const RBTreeNode<DataType> *node) const {
    if (node->right != nil) return getMinimum(node->right);
    RBTreeNode<DataType> *y = node->parent;
    while (y != nil && node == y->right) {
      node = y;
      y = y->parent;
    }
    return y;
  }

  /**
   * @brief Returns root node.
   *
   * @details Provides access to the root node of the red-black tree.
   * @return A pointer to the root node.
   */
  RBTreeNode<DataType> *getRoot() const {
    return root;
  }

  /**
   * @brief Returns sentinel node.
   *
   * @details Provides access to the sentinel (nil) node, representing null
   * leaves and boundaries.
   * @return A pointer to the sentinel node.
   */
  RBTreeNode<DataType> *getNil() const {
    return nil;
  }

 private:
  /** Pointer to the tree's root node. */
  RBTreeNode<DataType> *root;

  /** Sentinel node (NIL) used to represent empty nodes. */
  RBTreeNode<DataType> *nil;

  /**
   * @brief Recursive function to clear all nodes from the tree, releasing node
   * memory.
   *
   * @param node Node from which to start clearing.
   */
  void clearTree(RBTreeNode<DataType> *node) {
    if (node != nil) {
      clearTree(node->left);
      clearTree(node->right);
      delete node;
    }
  }

  /**
   * @brief Auxiliary function to replace one subtree with another.
   *
   * @details Used during deletion to update node links.
   * @param u Node to be replaced.
   * @param v Node that will replace 'u'.
   */
  void transplant(RBTreeNode<DataType> *u, RBTreeNode<DataType> *v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    if (v != nullptr) {
      v->parent = u->parent;
    }
  }

  /**
   * @brief Function to fix colors after insertion, ensuring that the red-black
   * tree properties are maintained.
   *
   * @param node Recently inserted node that may cause imbalance.
   */
  void insertFixup(RBTreeNode<DataType> *node) {
    while (node->parent->color == RED) {
      if (node->parent == node->parent->parent->left) {
        RBTreeNode<DataType> *uncle = node->parent->parent->right;
        if (uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {
          if (node == node->parent->right) {
            node = node->parent;
            rotateLeft(node);
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          rotateRight(node->parent->parent);
        }
      } else {
        RBTreeNode<DataType> *uncle = node->parent->parent->left;
        if (uncle->color == RED) {
          node->parent->color = BLACK;
          uncle->color = BLACK;
          node->parent->parent->color = RED;
          node = node->parent->parent;
        } else {
          if (node == node->parent->left) {
            node = node->parent;
            rotateRight(node);
          }
          node->parent->color = BLACK;
          node->parent->parent->color = RED;
          rotateLeft(node->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

  /**
   * @brief Left rotation in the tree.
   *
   * @details Changes structure between node 'x' and its right child to
   * rebalance the tree.
   * @param x Node on which the rotation is performed.
   */
  void rotateLeft(RBTreeNode<DataType> *x) {
    RBTreeNode<DataType> *y = x->right;
    x->right = y->left;
    if (y->left != nil) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
    y->left = x;
    x->parent = y;
  }

  /**
   * @brief Right rotation in the tree.
   *
   * @details Changes structure between node 'y' and its left child to
   * rebalance the tree.
   * @param y Node on which the rotation is performed.
   */
  void rotateRight(RBTreeNode<DataType> *y) {
    RBTreeNode<DataType> *x = y->left;
    y->left = x->right;
    if (x->right != nil) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == nil)
      root = x;
    else if (y == y->parent->right)
      y->parent->right = x;
    else
      y->parent->left = x;
    x->right = y;
    y->parent = x;
  }

  /**
   * @brief Function to fix colors after deletion, ensuring that the tree
   * maintains color properties.
   *
   * @param x Node at which to start color correction.
   */
  void removeFixup(RBTreeNode<DataType> *x) {
    while (x != root && x->color == BLACK) {
      if (x == x->parent->left) {
        RBTreeNode<DataType> *w = x->parent->right;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          rotateLeft(x->parent);
          w = x->parent->right;
        }
        if (w->left->color == BLACK && w->right->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else {
          if (w->right->color == BLACK) {
            w->left->color = BLACK;
            w->color = RED;
            rotateRight(w);
            w = x->parent->right;
          }
          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->right->color = BLACK;
          rotateLeft(x->parent);
          x = root;
        }
      } else {
        RBTreeNode<DataType> *w = x->parent->left;
        if (w->color == RED) {
          w->color = BLACK;
          x->parent->color = RED;
          rotateRight(x->parent);
          w = x->parent->left;
        }
        if (w->right->color == BLACK && w->left->color == BLACK) {
          w->color = RED;
          x = x->parent;
        } else {
          if (w->left->color == BLACK) {
            w->right->color = BLACK;
            w->color = RED;
            rotateLeft(w);
            w = x->parent->left;
          }
          w->color = x->parent->color;
          x->parent->color = BLACK;
          w->left->color = BLACK;
          rotateRight(x->parent);
          x = root;
        }
      }
    }
    x->color = BLACK;
  }
};
