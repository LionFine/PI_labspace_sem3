#ifndef SHELLSORTER_H
#define SHELLSORTER_H

#include "ISorter.h"
#include "../lab1/SmrtPtr.h"
#include "../lab1/Sequence.h"

template<typename T>
class ShellSorter : public ISorter<T> {
private:
    void shellSort(SmrtPtr<Sequence<T>> seq, int (*cmp)(const T&, const T&)) {
        int n = seq->GetLength();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                T temp = seq->Get(i);
                int j;
                for (j = i; j >= gap && cmp(seq->Get(j - gap), temp) > 0; j -= gap) {
                    seq->Set(j, seq->Get(j - gap));
                }
                seq->Set(j, temp);
            }
        }
    }

public:
    SmrtPtr<Sequence<T>> Sort(SmrtPtr<Sequence<T>> seq, int (*cmp)(const T&, const T&)) override {
        if (!seq) {
            throw std::invalid_argument("Sort: seq is nullptr");
        }
        shellSort(seq, cmp);
        return seq;
    }
};

#endif // SHELLSORTER_H
