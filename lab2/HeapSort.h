#ifndef HEAPSORTER_H
#define HEAPSORTER_H

#include "ISorter.h"
#include "../lab1/SmrtPtr.h"
#include "../lab1/Sequence.h"

template<typename T>
class HeapSorter : public ISorter<T> {
private:
    void heapSort(SmrtPtr<Sequence<T>> seq, int (*cmp)(const T&, const T&)) {
        int n = seq->GetLength();

        // Построение кучи
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(seq, n, i, cmp);
        }

        // Извлечение элементов из кучи
        for (int i = n - 1; i > 0; --i) {
            // Меняем местами через Get и Set
            T temp = seq->Get(0);
            seq->Set(0, seq->Get(i));
            seq->Set(i, temp);

            heapify(seq, i, 0, cmp);
        }
    }

    void heapify(SmrtPtr<Sequence<T>> seq, int n, int i, int (*cmp)(const T&, const T&)) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && cmp(seq->Get(left), seq->Get(largest)) > 0) {
            largest = left;
        }

        if (right < n && cmp(seq->Get(right), seq->Get(largest)) > 0) {
            largest = right;
        }

        if (largest != i) {
            // Меняем местами через Get и Set
            T temp = seq->Get(i);
            seq->Set(i, seq->Get(largest));
            seq->Set(largest, temp);

            heapify(seq, n, largest, cmp);
        }
    }


public:
    SmrtPtr<Sequence<T>> Sort(SmrtPtr<Sequence<T>> seq, int (*cmp)(const T&, const T&)) override {
        if (!seq) {
            throw std::invalid_argument("Sort: seq is nullptr");
        }
        heapSort(seq, cmp);
        return seq;
    }
};

#endif // HEAPSORTER_H
