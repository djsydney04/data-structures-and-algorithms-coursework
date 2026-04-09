/*
Dylan Mitic
Mitic@chapman.edu
CPSC 350-01
PA-3
*/

#ifndef MONOSTACK_H
#define MONOSTACK_H

#include <stdexcept>

template <typename T>
class MonoStack {
    public:
        // Constructor
        MonoStack(int capacity, char order) {
            // If the capacity is less than or equal to 0, throw an invalid argument error
            if (capacity <= 0) {
                throw std::invalid_argument("Size must be greater than 0");
            }
            // If the order is not 'i' or 'd', throw an invalid argument error
            if (order != 'i' && order != 'd') {
                throw std::invalid_argument("Order must be 'i' or 'd'");
            }
            // Set the capacity, stack, top, and order
            this->capacity_ = capacity;
            this->stack = new T[capacity];
            this->top = -1;
            this->order = order;
        }
        // Destructor
        ~MonoStack() {
            delete[] stack;
        }
        // Check if the stack is empty
        bool isEmpty() const {
            return top == -1;
        }
        // Check if the stack is full
        bool isFull() const {
            return top == capacity_ - 1;
        }
        // Get the size of the stack
        size_t size() const {
            return top + 1;
        }
        // Get the capacity of the stack
        size_t capacity() const {
            return capacity_;
        }
        // Get the top element of the stack
        T peek() const {
            if (isEmpty()) {
                throw std::underflow_error("Stack is empty");
            }
            return stack[top];
        }
        // Pop the top element of the stack
        T pop() {
            if (isEmpty()) {
                throw std::underflow_error("Stack is empty");
            }
            return stack[top--];
        }
        // Push a value onto the stack
        void push(T value) {
            if (order == 'i') {
                // If the order is 'i', push the value onto the stack
                while (!isEmpty() && peek() >= value) {
                    pop();
                }
            } else if (order == 'd') {
                // If the order is 'd', push the value onto the stack
                while (!isEmpty() && peek() <= value) {
                    pop();
                }
            }
            if (isFull()) {
                // If the stack is full, throw an overflow error
                throw std::overflow_error("Stack is full");
            }
            // Push the value onto the stack
            stack[++top] = value;
        }
    private:
        // Private members
        T* stack;
        // Top of the stack
        int top;
        // Capacity of the stack
        int capacity_;
        // Order of the stack
        char order;
};

#endif
