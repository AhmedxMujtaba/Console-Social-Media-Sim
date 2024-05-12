#pragma once
#include <iostream>
// Node structure for the linked list
template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
};

// Generic Double Linked List class
template<typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size; // Track the size of the linked list

public:
    // Constructor
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Destructor
    ~DoubleLinkedList() {
        // Delete all nodes
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Method to add a new node to the end of the list
    void append(const T& value) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = tail = newNode;
            newNode->prev = nullptr;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        size++; // Increment the size of the linked list
    }

    // Method to display the elements of the list
    void display() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Method to find a specific object by value
    Node<T>* find(const T& value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Object not found
    }

    // Method to search for an object by name (assuming T has a getName() method)
    Node<T>* searchByName(const std::string& name) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data.getName() == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Object not found
    }

    // Method to get the total number of nodes in the linked list
    int getSize() const {
        return size;
    }

    // Method to remove a node from the list
    void remove(Node<T>* node) {
        if (node == nullptr) {
            return;
        }

        if (node == head) {
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        } else if (node == tail) {
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        delete node;
        size--; // Decrement the size of the linked list
    }
};
