#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include "node.hpp"
#include <vector>

template <class T>
class BST
{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T); //done
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T); //done
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void); //done
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void); //done
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void); //done
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T); //done
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void); //done

private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;
    Node<T> *insert_helper(Node<T> *, T);
    Node<T> *remove_helper(Node<T> *, T);
    Node<T> *search_helper(Node<T> *, T);
    Node<T> *smallestNode(Node<T> *);
    void *inorder_helper(Node<T> *, std::vector<T> *);
    void *preorder_helper(Node<T> *, std::vector<T> *);
    void *postorder_helper(Node<T> *, std::vector<T> *);
};

template <class T>
BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template <class T>
BST<T>::~BST()
{
    root = NULL;
    while (root != NULL)
    {
        remove(root->get_data());
    }
}

template <class T>
std::vector<T> *BST<T>::inorder()
{
    std::vector<T> *vec = new std::vector<T>;
    Node<T> *tmpo = new Node<T>;
    tmpo->set_left(root->get_left());
    tmpo->set_right(root->get_right());
    int a = root->get_data();
    tmpo->set_data(a);
    inorder_helper(tmpo, vec);
    delete (tmpo);
    return vec;
}

template <class T>
std::vector<T> *BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    Node<T> *tmpo = new Node<T>;
    tmpo->set_left(root->get_left());
    tmpo->set_right(root->get_right());
    int a = root->get_data();
    tmpo->set_data(a);
    preorder_helper(tmpo, vec);
    delete (tmpo);
    return vec;
}

template <class T>
std::vector<T> *BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;
    Node<T> *tmpo = new Node<T>;
    tmpo->set_left(root->get_left());
    tmpo->set_right(root->get_right());
    int a = root->get_data();
    tmpo->set_data(a);
    postorder_helper(tmpo, vec);
    delete (tmpo);
    return vec;
}

template <class T>
void BST<T>::insert(T new_data)
{
    root = insert_helper(root, new_data);
}

template <class T>
Node<T> *BST<T>::search(T val)
{
    root = search_helper(root, val);
    return root;
}

template <class T>
void BST<T>::remove(T val)
{
    root = remove_helper(root, val);
}

template <class T>
int BST<T>::get_size()
{
    return node_count;
}

template <class T>
Node<T> *BST<T>::insert_helper(Node<T> *node, T val)
{
    if (node == NULL)
    {
        Node<T> *tmp = new Node<T>;
        tmp->set_data(val);
        tmp->set_left(NULL);
        tmp->set_right(NULL);
        node_count++;
        return tmp;
    }
    else if (node->get_data() > val)
    {
        node->set_left(insert_helper(node->get_left(), val));
    }
    else if (node->get_data() < val)
    {
        node->set_right(insert_helper(node->get_right(), val));
    }
    else if (node->get_data() == val)
    {
        return NULL;
    }
    return node;
}
template <class T>
Node<T> *BST<T>::remove_helper(Node<T> *node, T remove_data)
{
    if (node == NULL)
    {
        return node;
    }
    if (node->get_data() == remove_data)
    {
        node_count--;
        if (node->get_left() == NULL)
        {
            Node<T> *tmp = new Node<T>;
            tmp = node->get_right();
            delete (node);
            return tmp;
        }
        else if (node->get_right() == NULL)
        {
            Node<T> *tmp = new Node<T>;
            tmp = node->get_left();
            delete (node);
            return tmp;
        } 
        else 
        {
            Node<T> *tmp = new Node<T>;
            tmp = smallestNode(node->get_right());
            int a = tmp->get_data();
            node->set_data(a);
            node->set_right(remove_helper(node->get_right(), tmp->get_data()));
        }
        return node;
    }
    else if (node->get_data() < remove_data)
    {
        node->set_right(remove_helper(node->get_right(), remove_data));
    }
    else if (node->get_data() > remove_data)
    {
        node->set_left(remove_helper(node->get_left(), remove_data));
    }
    return node;
}
template <class T>
Node<T> *BST<T>::smallestNode(Node<T> *node)
{
    Node<T> *current = new Node<T>;
    current = node;
    //loop to find the leftmost leaf
    while (current != NULL && current->get_left() != NULL)
    {
        current = current->get_left();
    }
    return current;
}
template <class T>
Node<T> *BST<T>::search_helper(Node<T> *node, T val)
{
    if (node == NULL || node->get_data() == val)
    {
        return node;
    }
    else if (node->get_data() < val)
    {
      node = search_helper(node->get_right(), val);
    }
    else if (node->get_data() > val)
    {
       node = search_helper(node->get_left(), val);
    }
    return node;
}
template <class T>
void *BST<T>::inorder_helper(Node<T> *node, std::vector<T> *vector)
{
    if (node == NULL)
    {
        return 0;
    }
    inorder_helper(node->get_left(), vector);
    vector->push_back(node->get_data());
    inorder_helper(node->get_right(), vector);
    return 0;
}
template <class T>
void *BST<T>::preorder_helper(Node<T> *node, std::vector<T> *vector)
{
    if (node == NULL)
    {
        return 0;
    }
    vector->push_back(node->get_data());
    preorder_helper(node->get_left(), vector);
    preorder_helper(node->get_right(), vector);
    return 0;
}
template <class T>
void *BST<T>::postorder_helper(Node<T> *node, std::vector<T> *vector)
{
    if (node == NULL)
    {
        return 0;
    }
    postorder_helper(node->get_left(), vector);
    postorder_helper(node->get_right(), vector);
    vector->push_back(node->get_data());
    return 0;
}