#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Sequence.h"
#include "SmrtPtr.h"
#include <stdexcept>

template <typename T>
class LinkedList : public Sequence<T> {
private:
    struct Node {
        T value;
        SmrtPtr<Node> next;
        explicit Node(const T& val) : value(val), next(nullptr) {}
    };

    SmrtPtr<Node> head;
    SmrtPtr<Node> tail;
    int length;

public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), length(0) {
        if (!other.head) {
            return;
        }
        SmrtPtr<Node> current = other.head;
        while (current) {
            this->Append(current->value);
            current = current->next;
        }
    }

    LinkedList(LinkedList&& other) noexcept : head(std::move(other.head)), tail(std::move(other.tail)), length(other.length) {
        other.length = 0;
    }


    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            if (!other.head) {
                return *this;
            }
            SmrtPtr<Node> current = other.head;
            while (current) {
                this->Append(current->value);
                current = current->next;
            }
        }
        return *this;
    }


    LinkedList& operator=(LinkedList&& other)  {
        if (this != &other) {
            head = std::move(other.head);
            tail = std::move(other.tail);
            length = other.length;
            other.length = 0;
        }
        return *this;
    }

    ~LinkedList() = default;


    T GetFirst() const override {
        if (!head) {
            throw std::out_of_range("LinkedList is empty");
        }
        return head->value;
    }

    T GetLast() const override {
        if (!tail) {
            throw std::out_of_range("LinkedList is empty");
        }
        return tail->value;
    }

    T Get(int index) const override {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range in Get");
        }
        SmrtPtr<Node> current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    SmrtPtr<Sequence<T>> GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex >= length || startIndex > endIndex) {
            throw std::out_of_range("Invalid indices in GetSubsequence");
        }
        SmrtPtr<LinkedList<T>> sub(new LinkedList<T>());
        SmrtPtr<Node> current = head;
        for (int i = 0; i <= endIndex; ++i) {
            if (i >= startIndex) {
                sub->Append(current->value);
            }
            current = current->next;
        }
        return sub;
    }

    int GetLength() const override {
        return length;
    }

    void Append(const T &item) override {
        SmrtPtr<Node> new_node(new Node(item));
        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        ++length;
    }

    void Prepend(const T &item) override {
        SmrtPtr<Node> new_node(new Node(item));
        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
            new_node->next = head;
            head = new_node;
        }
        ++length;
    }

    void InsertAt(const T &item, int index) override {
        if (index < 0 || index > length) {
            throw std::out_of_range("Index out of range in InsertAt");
        }
        if (index == 0) {
            Prepend(item);
            return;
        }
        if (index == length) {
            Append(item);
            return;
        }
        SmrtPtr<Node> new_node(new Node(item));
        SmrtPtr<Node> current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        ++length;
    }

    void Set(int index, const T &item) override {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range in Set");
        }
        SmrtPtr<Node> current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->value = item;
    }

    SmrtPtr<Sequence<T>> Concat(SmrtPtr<Sequence<T>>& list) const override {
        if (!list) {
            throw std::invalid_argument("Concat: list is nullptr");
        }
        SmrtPtr<LinkedList<T>> result(new LinkedList<T>());
        SmrtPtr<Node> current = head;
        while (current) {
            result->Append(current->value);
            current = current->next;
        }
        for (int i = 0; i < list->GetLength(); ++i) {
            result->Append(list->Get(i));
        }
        return result;
    }

};


#endif // LINKEDLIST_H
