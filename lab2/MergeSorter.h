#ifndef MERGESORTER_H
#define MERGESORTER_H

#include "ISorter.h"
#include "../lab1/SmrtPtr.h"
#include "../lab1/Sequence.h"
#include "../lab1/LinkedList.h"
#include <stdexcept>


template<typename T>
class MergeSorter : public ISorter<T> {

private:
    void merge(SmrtPtr<Sequence<T>> seq, int left, int mid, int right, int (*cmp)(const T&, const T&), SmrtPtr<Sequence<T>> temp) {
        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) {
            if (cmp(seq->Get(i), seq->Get(j)) <= 0) {
                temp->Set(k, seq->Get(i));
                i++;
            } else {
                temp->Set(k, seq->Get(j));
                j++;
            }
            k++;
        }

        while (i <= mid) {
            temp->Set(k, seq->Get(i));
            i++;
            k++;
        }

        while (j <= right) {
            temp->Set(k, seq->Get(j));
            j++;
            k++;
        }

        // Copy back to the original sequence
        for (int l = left; l <= right; ++l) {
            seq->Set(l, temp->Get(l));
        }
    }

    void mergeSort(SmrtPtr<Sequence<T>> seq, int left, int right, int (*cmp)(const T&, const T&), SmrtPtr<Sequence<T>> temp) {

        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(seq, left, mid, cmp, temp);
            mergeSort(seq, mid + 1, right, cmp, temp);
            merge(seq, left, mid, right, cmp, temp);
        }
    }

public:
    SmrtPtr<Sequence<T>> Sort(SmrtPtr<Sequence<T>> seq, int (*cmp)(const T&, const T&)) override {
        SmrtPtr<Sequence<T>> temp(new LinkedList<T>());
        for (int i = 0; i < seq->GetLength(); ++i) {
            temp->Append(seq->Get(i));
        }
        mergeSort(seq, 0, seq->GetLength() - 1, cmp, temp);
        return seq;
    }
};

#endif // MERGESORTER_H
