#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdexcept>
//klasa obiektu tablica dynamiczna
template <typename T>
class ArrayList {
private:
    T* array;
    int capacity;
    int size;
    //funkcja do zmiany rozmiaru tablicy
    void resize() {
        capacity *= 2;
        T* newArray = new T[capacity];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }

public:
    //konstruktor domyœlny
    ArrayList(int initialCapacity = 10) {       
        capacity = initialCapacity;
        size = 0;
        array = new T[capacity];
    }
    //konstruktor parametryczny
    ArrayList(const ArrayList& other) {      
        capacity = other.capacity;
        size = other.size;
        array = new T[capacity];
        for (int i = 0; i < size; i++) {
            array[i] = other.array[i];
        }
    }
    //przeci¹¿enie operatora =
    ArrayList& operator=(const ArrayList& other) {      
        if (this != &other) {
            delete[] array;
            capacity = other.capacity;
            size = other.size;
            array = new T[capacity];
            for (int i = 0; i < size; i++) {
                array[i] = other.array[i];
            }
        }
        return *this;
    }
    //destruktor
    ~ArrayList() {
        delete[] array;
    }
    //testowane funkcje 
    void addFirst(T value) {
        if (size == capacity) {
            resize();
        }
        for (int i = size; i > 0; i--) {
            array[i] = array[i - 1];
        }
        array[0] = value;
        size++;
    }

    void addLast(T value) {
        if (size == capacity) {
            resize();
        }
        array[size++] = value;
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
        if (size == capacity) {
            resize();
        }
        for (int i = size; i > index; i--) {
            array[i] = array[i - 1];
        }
        array[index] = value;
        size++;
    }

    T removeFirst() {
        if (size == 0) {
            throw std::out_of_range("List is empty");
        }
        T value = array[0];
        for (int i = 0; i < size - 1; i++) {
            array[i] = array[i + 1];
        }
        size--;
        return value;
    }

    T removeLast() {
        if (size == 0) {
            throw std::out_of_range("List is empty");
        }
        return array[--size];
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
        T value = array[index];
        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }
        size--;
        return value;
    }

    bool search(T value) const {
        for (int i = 0; i < size; i++) {
            if (array[i] == value) {
                return true;
            }
        }
        return false;
    }
    //funkcja do pobrania rozmiaru
    int getSize() const {
        return size;
    }
    T get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

    void clear() {
        size = 0;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

#endif