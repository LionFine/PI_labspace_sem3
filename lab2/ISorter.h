#ifndef ISORTER_H
#define ISORTER_H

#include "../lab1/SmrtPtr.h"
#include "../lab1/Sequence.h"

template<typename T>
class ISorter {
public:
    virtual SmrtPtr<Sequence<T>> Sort(SmrtPtr<Sequence<T>> seq, int (*cmp)(const T&, const T&)) = 0;
    virtual ~ISorter() {}
};

#endif // ISORTER_H
