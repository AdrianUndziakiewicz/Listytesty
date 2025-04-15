#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdexcept>

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            addLast(current->data);
            current = current->next;
        }
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this != &other) {
            Node* current = head;
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
            tail = nullptr;
            size = 0;

            current = other.head;
            while (current != nullptr) {
                addLast(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    ~SinglyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void addFirst(T value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void addLast(T value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void addAt(int index, T value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            addFirst(value);
            return;
        }
        if (index == size) {
            addLast(value);
            return;
        }

        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }

    T removeFirst() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }

        Node* temp = head;
        T value = temp->data;

        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
        }

        delete temp;
        size--;
        return value;
    }

    T removeLast() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }

        T value = tail->data;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }

        size--;
        return value;
    }

    T removeAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            return removeFirst();
        }
        if (index == size - 1) {
            return removeLast();
        }

        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* temp = current->next;
        T value = temp->data;
        current->next = temp->next;
        delete temp;
        size--;
        return value;
    }

    bool search(T value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int getSize() const {
        return size;
    }

    T get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

#endif