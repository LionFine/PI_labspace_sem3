// QuickSorter.h
#ifndef QUICKSORTER_H
#define QUICKSORTER_H

#include "ISorter.h"
#include "../lab1/SmrtPtr.h"
#include "../lab1/Sequence.h"
#include "../lab1/LinkedList.h"
#include <vector>

template<typename T>
class QuickSorter : public ISorter<T> {
    //glob
    int a;
    int all=0;
    //glob

private:
    int partition(SmrtPtr<Sequence<T>> seq, int low, int high, int (*cmp)(const T &, const T &)) {
        int i = low + (rand() % (high - low));
        T pivot = seq->Get(i);

        std::vector<T> under;
        std::vector<T> upper;

        for (int j = low; j < high + 1; j++) {
            if (cmp(seq->Get(j), pivot) < 0) {
                under.push_back(seq->Get(j));
            } else {
                upper.push_back(seq->Get(j));
            }
        }

        for (int j = low; j < high + 1; j++) {
            if (j - low < under.size()) {
                seq->Set(j, under[j-low]);
            } else {
                seq->Set(j, upper[j -low-under.size()]);
            }
        }
        return low + under.size();
    }


    void quickSort(SmrtPtr<Sequence<T>> seq, int low, int high, int (*cmp)(const T &, const T &)) {
        std::cout<<"quick: "<<low<<" "<<high<<"\n";

        if (low < high) {
            int pi = partition(seq, low, high, cmp);
            if (((pi - 1) - low) >= 1) {
                all+=((pi - 1) - low)==1;
                quickSort(seq, low, pi - 1, cmp);
            }
            if ((high - (pi + 1)) >= 1) {
                all+=((pi - 1) - low)==1;
                quickSort(seq, pi + 1, high, cmp);
            }
        }

    }

public:
    SmrtPtr<Sequence<T>> Sort(SmrtPtr<Sequence<T>> seq, int (*cmp)(const T &, const T &)) override {

        a = seq->GetLength() - 1;
        std::cout << "quick of " << a << '\n';

        if (!seq) {
            throw std::invalid_argument("Sort: seq is nullptr");
        }
        if (seq->GetLength() <= 1) {
            return seq; // Уже отсортировано
        }
        quickSort(seq, 0, seq->GetLength() - 1, cmp);
        return seq;
    }
};

#endif // QUICKSORTER_H
