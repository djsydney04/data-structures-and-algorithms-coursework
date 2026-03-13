#ifndef MONOSTACK_H
#define MONOSTACK_H

#include <stdexcept>

template <typename T>
class MonoStack {
    public:
        MonoStack(int capacity, char order) {
            if (capacity <= 0) {
                throw std::invalid_argument("Size must be greater than 0");
            }
            if (order != 'a' && order != 'd') {
                throw std::invalid_argument("Order must be 'a' or 'd'");
            }
            this->capacity_ = capacity;
            this->stack = new T[capacity];
            this->top = -1;
            this->order = order;
        }

        ~MonoStack() {
            delete[] stack;
        }

        bool isEmpty() const {
            return top == -1;
        }

        bool isFull() const {
            return top == capacity_ - 1;
        }

        size_t size() const {
            return top + 1;
        }

        size_t capacity() const {
            return capacity_;
        }

        T peek() const {
            if (isEmpty()) {
                throw std::underflow_error("Stack is empty");
            }
            return stack[top];
        }

        T pop() {
            if (isEmpty()) {
                throw std::underflow_error("Stack is empty");
            }
            return stack[top--];
        }

        void push(T value) {
            if (order == 'a') {
                while (!isEmpty() && peek() < value) {
                    pop();
                }
            } else if (order == 'd') {
                while (!isEmpty() && peek() > value) {
                    pop();
                }
            }
            stack[++top] = value;
        }
    private:
        T* stack;
        int top;
        int capacity_;
        char order;
};

#endif