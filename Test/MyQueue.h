#pragma once
#include <iostream>

class MyQueue
{
private:
    int* elements;
    int frontIndex;
    int rearIndex;
    int capacity;
    int count;
public:
    MyQueue(int size = 10)
    {
        capacity = size;
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
        elements = new int[capacity];
    }

    void push(int val)
    {
        if (isFull()) {
            std::cout << "Queue is full" << std::endl;
            return;
        }
        rearIndex = (rearIndex + 1) % capacity;
        elements[rearIndex] = val;
        count++;
    }

    void pop()
    {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return;
        }
        frontIndex = (frontIndex + 1) % capacity;
        count--;
    }

    int front() const
    {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return -1;
        }
        return elements[frontIndex];
    }

    int rear() const
    {
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return -1;
        }
        return elements[rearIndex];
    }

    int size() const
    {
        return count;
    }

    bool isEmpty() const
    {
        return (size() == 0);
    }

    bool isFull() const
    {
        return (size() == capacity);
    }

    ~MyQueue()
    {
        delete[] elements;
    }
};