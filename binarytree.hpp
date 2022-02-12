
#ifndef binarytree_H_
#define binarytree_H_


#include <iostream>
#include <cstdlib>
#include <vector>

template<typename Tree>
class IterratorTree {

public:
    using TypeIterator  = typename Tree::TypeTree;
    using PointerType   = TypeIterator*;
    using ReferenceType = TypeIterator&;
    using ValueType     = typename Tree::ValueType;

private:
    PointerType m_ptr;
    std::vector<PointerType> stack;
    

public:

    IterratorTree() : m_ptr(nullptr) {};

    IterratorTree(PointerType ptr) {
        if (ptr == nullptr) {
            m_ptr = nullptr;
        } else {
            PointerType aux = ptr;
            while (aux != nullptr) {
                stack.push_back(aux);
                aux = aux->left;
            }
            m_ptr = *(stack.end() - 1);
            stack.pop_back();
           
            if (m_ptr->right != nullptr) {
                PointerType aux = m_ptr->right;

                while (aux != nullptr) {
                    stack.push_back(aux);
                    aux = aux->left;
                }
            }
        }
    }

    ~IterratorTree() {
        m_ptr = nullptr;
    }

    // Operators
    bool operator != (const IterratorTree ptr) {
        return m_ptr != ptr.m_ptr;
    }
   
    bool operator == (const IterratorTree ptr) {
        return m_ptr == ptr.m_ptr;
    }

    bool operator < (const IterratorTree ptr) {
        return m_ptr < ptr.m_ptr;
    }
    
    bool operator > (const IterratorTree ptr) {
        return m_ptr > ptr.m_ptr;
    }

    PointerType operator ->() {
        return m_ptr;
    }

    const ValueType &operator *() {
        return m_ptr->m_value;
    }

    IterratorTree &operator ++() {
        if (stack.empty() || m_ptr == nullptr) {
            m_ptr = nullptr;
        } else {
            m_ptr = *(stack.end() - 1);
            stack.pop_back();

            if (m_ptr->right != nullptr) {
                PointerType aux = m_ptr->right;

                while (aux != nullptr) {
                    stack.push_back(aux);
                    aux = aux->left;
                }
            }
        }
  
        return * this;
    }
};




template<typename T>
class Tree {
    struct Node {
        T m_value;
        Node *left;
        Node *right;

        Node() : m_value(0), left(nullptr), right(nullptr) {}

        Node(T value) : m_value(value), left(nullptr), right(nullptr) {}
    };

    Node *m_root;


public:
    using TypeTree  = Node;
    using Iterator  = IterratorTree<Tree<T>>;
    using ValueType = T;


private:
    // Private methods
    void m_free_tree(Node *node) {

        if (node != nullptr) {
            m_free_tree(node->left);
            m_free_tree(node->right);
            delete node;
        }
    }

    Node* m_insert(Node *node, const T &value) {

        if (node == nullptr) {
            node = new Node(value);
        } else if (value < node->m_value) {
            node->left = m_insert(node->left, value);
        } else {
           node->right = m_insert(node-> right, value);
        }
        return node;
    }

    void m_print(Node *node) {

        if (node != nullptr) {
            m_print(node->left);
            std::cout << node->m_value << " ";
            m_print(node->right);
        }
    }

    Node* m_search (Node *node, const T value) {

        if (node != nullptr) {
            if (node->m_value == value) {
                return node;
            } else if (value < node->m_value) {
                return m_search(node->left, value);
            } else {
                return m_search(node->right, value);
            }
        } else {
            return nullptr;
        }
    }

    Node* m_last_node(Node *node) {

        if (node != nullptr) {
            if(node->left == nullptr) {
                return node;
            } else {
                return m_last_node(node->left);
            }
        } else {
            return nullptr;
        }
    }

    Node* m_get_father(Node *parent, const T value) {

        if (parent != nullptr) {
            if ((parent->left != nullptr && parent->left->m_value == value ) || (parent->right != nullptr && parent->right->m_value == value )) {
                return parent;
            } else if (value < parent->m_value) {
                return m_get_father(parent->left, value);
            } else {
                return m_get_father(parent->right, value);
            }
        } else {
            return nullptr;
        }
    }

    void m_remove(const T value) {

        // Number not in list
        if (!search(value)) 
            return;

        // Delete root
        if (m_root->m_value == value) {

            Node *ptr = m_last_node(m_root->right);
            Node *aux = m_root->right;
            ptr->left = m_root->left;
            delete m_root;
            m_root = aux;

        } else {

            Node *ptr = m_search(m_root, value);
            // Delete a leaf
            if (ptr->right == nullptr && ptr->left == nullptr) {
                Node *father = m_get_father(m_root, value);
                if(/*father->left != nullptr &&*/ father->left->m_value == value) {
                    delete ptr;
                    father->left = nullptr;
                } else if (/*father->right != nullptr &&*/ father->right->m_value == value) {
                    delete ptr;
                    father->right = nullptr;
                }

            // Delete a intermediate node
            } else {

                Node *parent = m_get_father(m_root, value);
                Node *last   = m_last_node(ptr->right);
                if (parent->right->m_value == value) {
                    parent->right = ptr->right;
                    last->left = ptr->left;
                    delete ptr;
                } else if (parent->left->m_value == value) {
                    parent->left = ptr->right;
                    last->left = ptr->left;
                    delete ptr;
                }

            }
        }
    }

    void m_size(Node *node, int &len) {
        if (node->left != nullptr) {
            len++;
            m_size(node->left, len);
        } 
        if (node->right != nullptr) {
            len++;
            m_size(node->right, len);
        }
    }
    
    void m_output (std::ostream &os, Node *node) {
        if (node != nullptr) {
            m_output(os, node->left);
            os << node->m_value << " ";
            m_output(os, node->right);
        }
    }

    T m_input() {
        T input;
        std::cin >> input;

        return input;
    }


public:
    // Constructor
    Tree() : m_root(nullptr) {} 
    
    Tree(const T value) : m_root(new Node(value)) {}

    Tree(std::initializer_list<T> list) : m_root(nullptr){
        for (auto value : list) {
            insert(value);
        }
    }

    // Destructor
    ~Tree() {
        m_free_tree(m_root);

        m_root = nullptr;
    }

    // Public Methods
    void insert(T const &element) {
        m_root = m_insert(m_root, element);
    }

    void print() {
        m_print(m_root);
        std::cout << std::endl;
    }

    bool search (const T value) {
        if (m_search(m_root, value) != nullptr)
            return true;
        else 
            return false;
    }
    
    void remove(const T value) {
        m_remove(value);
    }

    // returns the number of nodes
    int size() {
        if (m_root == nullptr) {
            return 0;
        }

        int i = 1;
        m_size(m_root, i);

        return i;
    }

    bool empty() {
        return m_root == nullptr;
    }

    // Operators 
    bool operator [](T value) { return search(value); }
    
    void operator = (std::vector<T> v) {
        for (auto value : v) {
            insert(value);
        }
    }

    friend std::ostream &operator <<(std::ostream& os, Tree<T> *tree) {

        tree->m_output(os, tree->m_root);
        return os;
    }

    friend std::istream &operator >>(std::istream &in, Tree<T> *tree) {
        
        tree->insert(tree->m_input());
        return in;
    }


    // Iterator
    Iterator begin() {
        return Iterator(m_root);
    }

    Iterator end() {
        return Iterator();
    }

};

#endif 