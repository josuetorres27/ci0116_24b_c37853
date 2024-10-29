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

template <typename DataType>
class RBTreeNode {
 public:
  friend class RBTree<DataType>;

  /** Default constructor. */
  RBTreeNode() : key(DataType()), parent(nullptr), left(nullptr),
    right(nullptr), color(colors::BLACK) {}

  /** Constructor with values and pointers. */
  RBTreeNode(const DataType &key, RBTreeNode<DataType> *parent = nullptr,
    RBTreeNode<DataType> *left = nullptr, RBTreeNode<DataType>
      *right = nullptr, colors color = colors::RED)
        : key(key), parent(parent), left(left), right(right), color(color) {}

  /** Destructor. */
  ~RBTreeNode() {}

  /** Get the node's key. */
  DataType getKey() const { return key; }

  /** Get the node's parent. */
  RBTreeNode<DataType> *getParent() const { return parent; }

  /** Get the left child of the node. */
  RBTreeNode<DataType> *getLeft() const { return left; }

  /** Get the right child of the node. */
  RBTreeNode<DataType> *getRight() const { return right; }

  /** Set the node's key. */
  void setKey(DataType key) { this->key = key; }

  /** Set the parent of the node. */
  void setParent(RBTreeNode<DataType> *parent) { this->parent = parent; }

  /** Set the left child of the node. */
  void setLeft(RBTreeNode<DataType> *left) { this->left = left; }

  /** Set the right child of the node. */
  void setRight(RBTreeNode<DataType> *right) { this->right = right; }

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
  /** Constructor. */
  RBTree() {
    nil = new RBTreeNode<DataType>();
    nil->color = BLACK;
    nil->left = nil->right = nil->parent = nullptr;
    root = nil;
  }

  /** Destructor. */
  ~RBTree() {
    clearTree(root);
    delete nil;
  }

  /** Function to clear all nodes from the tree. */
  void clear() {
    clearTree(root);
    root = nil;
  }

  /** Insertion function. */
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

  /** Deletion function. */
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

  /** Search function. */
  RBTreeNode<DataType> *search(const RBTreeNode<DataType> *rootOfSubtree,
    const DataType &value) const {
    RBTreeNode<DataType> *node = const_cast<RBTreeNode<DataType> *>
      (rootOfSubtree);  // Eliminar const
    while (node != nil && node->key != value) {
      if (value < node->key)
        node = node->left;
      else
        node = node->right;
    }
    return node;
  }

  /** Function to get maximum. */
  RBTreeNode<DataType> *getMaximum(const RBTreeNode<DataType>
    *rootOfSubtree) const {
    RBTreeNode<DataType> *node = rootOfSubtree;
    while (node->right != nil) node = node->right;
    return node;
  }

  /** Function to get minimum. */
  RBTreeNode<DataType> *getMinimum(const RBTreeNode<DataType>
    *rootOfSubtree) const {
    RBTreeNode<DataType> *node = const_cast<RBTreeNode<DataType> *>
      (rootOfSubtree);
    while (node->left != nil) node = node->left;
    return node;
  }

  /** Function to get successor node. */
  RBTreeNode<DataType> *getSuccessor(const RBTreeNode<DataType> *node) const {
    if (node->right != nil) return getMinimum(node->right);
    RBTreeNode<DataType> *y = node->parent;
    while (y != nil && node == y->right) {
      node = y;
      y = y->parent;
    }
    return y;
  }

  /** Returns root node. */
  RBTreeNode<DataType> *getRoot() const { return root; }

  /** Returns sentinel node. */
  RBTreeNode<DataType> *getNil() const { return nil; }

 private:
  RBTreeNode<DataType> *root;

  RBTreeNode<DataType> *nil;

  /** Recursive function to clear all nodes from the tree. */
  void clearTree(RBTreeNode<DataType> *node) {
    if (node != nil) {
      clearTree(node->left);
      clearTree(node->right);
      delete node;
    }
  }

  /** Auxiliary function for deleting. */
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

  /** Auxiliary function to fix tree colors after insertion. */
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

  /** Left rotation. */
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

  /** Rigth rotation. */
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

  /** Auxiliary function to fix tree colors after deleting. */
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
