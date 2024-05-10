#include <iostream>

// Define the struct for the node
template<typename T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(const T& newData, Node<T>* newPrev = nullptr, Node<T>* newNext = nullptr)
        : data(newData), prev(newPrev), next(newNext) {}
};

// Define the class for the doubly linked list
template<typename T>
class DoublLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoublLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Function to insert a new node at a specific index
    void insertAtIndex(const T& newData, int index) {
        if (index < 0 || index > size) {
            std::cerr << "Index out of bounds\n";
            return;
        }

        Node<T>* newNode = new Node<T>(newData);

        if (index == 0) {
            newNode->next = head;
            if (head != nullptr) {
                head->prev = newNode;
            }
            head = newNode;
            if (tail == nullptr) {
                tail = newNode;
            }
        } else if (index == size) {
            newNode->prev = tail;
            if (tail != nullptr) {
                tail->next = newNode;
            }
            tail = newNode;
            if (head == nullptr) {
                head = newNode;
            }
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }

        size++;
    }

    // Function to delete the node at a specific index
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Index out of bounds\n";
            return;
        }

        Node<T>* temp;

        if (index == 0) {
            temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete temp;
            if (head == nullptr) {
                tail = nullptr;
            }
        } else if (index == size - 1) {
            temp = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            delete temp;
            if (tail == nullptr) {
                head = nullptr;
            }
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            temp = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete temp;
        }

        size--;
    }

    // Function to display the doubly linked list
    void display() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    DoublLinkedList<int> myList;

    myList.insertAtIndex(10, 0);
    myList.insertAtIndex(20, 1);
    myList.insertAtIndex(30, 2);
    myList.display(); // Output: 10 20 30

    myList.deleteAtIndex(1);
    myList.display(); // Output: 10 30

    return 0;
}
