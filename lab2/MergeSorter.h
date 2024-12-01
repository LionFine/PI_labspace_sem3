#ifndef MERGESORTER_H
#define MERGESORTER_H

#include "ISorter.h"
#include "../lab1/SmrtPtr.h"
#include "../lab1/Sequence.h"
#include "../lab1/LinkedList.h"
#include <stdexcept>



template<typename T>
class MergeSorter : public ISorter<T> {
    //glob
    int a;
    //glob
private:
    void merge(SmrtPtr<Sequence<T>> seq, int left, int mid, int right, int (*cmp)(const T&, const T&)) {
        SmrtPtr<Sequence<T>> leftSeq = seq->GetSubsequence(left, mid);
        SmrtPtr<Sequence<T>> rightSeq = seq->GetSubsequence(mid + 1, right);

        int i = 0, j = 0, k = left;
        while (i < leftSeq->GetLength() && j < rightSeq->GetLength()) {
            if (cmp(leftSeq->Get(i), rightSeq->Get(j)) <= 0) {
                seq->Set(k, leftSeq->Get(i));
                i++;
            } else {
                seq->Set(k, rightSeq->Get(j));
                j++;
            }
            k++;
        }

        while (i < leftSeq->GetLength()) {
            seq->Set(k, leftSeq->Get(i));
            i++;
            k++;
        }

        while (j < rightSeq->GetLength()) {
            seq->Set(k, rightSeq->Get(j));
            j++;
            k++;
        }
    }

    void mergeSort(SmrtPtr<Sequence<T>> seq, int left, int right, int (*cmp)(const T&, const T&)) {

        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(seq, left, mid, cmp);
            mergeSort(seq, mid + 1, right, cmp);
            merge(seq, left, mid, right, cmp);
        }

        if(left==0){
            std::cout<<"merg sort: "<<right<<" / "<<a<<"\n";
        }
    }

public:
    SmrtPtr<Sequence<T>> Sort(SmrtPtr<Sequence<T>> seq, int (*cmp)(const T&, const T&)) override {
        a=seq->GetLength() - 1;
        mergeSort(seq, 0, seq->GetLength() - 1, cmp);
        return seq;
    }
};

#endif // MERGESORTER_H
