#ifndef SMRTPTR_H
#define SMRTPTR_H

#include <stdexcept>
#include <atomic>
#include <utility>
#include <type_traits>

// Контролируемый блок, содержащий указатель на объект и счетчик ссылок
template <typename T>
class ControlBlock {
    T* ptr;                              // Указатель на управляемый объект
    std::atomic<size_t> ref_count;

public:
    explicit ControlBlock(T* p) : ptr(p), ref_count(1) {}
    ~ControlBlock() {
        delete ptr;
    }

    void addRef() {
        ++ref_count;
    }

    void release() {
        if (--ref_count == 0) {
            delete this;
        }
    }

    T* get() const {
        return ptr;
    }

    size_t getRefCount() const {
        return ref_count;
    }
};


template <typename T>
class SmrtPtr {
private:
    ControlBlock<T>* control; // Указатель на контролируемый блок

    void release() {
        if (control) {
            control->release();
            control = nullptr;
        }
    }

    template <typename> friend class SmrtPtr;

public:
    SmrtPtr() : control(nullptr) {}

    explicit SmrtPtr(T* ptr) : control(nullptr) {
        if (ptr) {
            control = new ControlBlock<T>(ptr);
        }
    }

    SmrtPtr(const SmrtPtr& other) : control(other.control) {
        if (control) {
            control->addRef();
        }
    }

    SmrtPtr(SmrtPtr&& other) noexcept : control(other.control) {
        other.control = nullptr;
    }

    ~SmrtPtr() {
        release();
    }

    SmrtPtr& operator=(const SmrtPtr& other) {
        if (this != &other) {
            release();
            control = other.control;
            if (control) {
                control->addRef();
            }
        }
        return *this;
    }

    SmrtPtr& operator=(SmrtPtr&& other) noexcept {
        if (this != &other) {
            release();
            control = other.control;
            other.control = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        if (!control || !control->get()) {
            throw std::runtime_error("SmrtPtr: попытка разыменования нулевого указателя");
        }
        return *(control->get());
    }

    T* operator->() const {
        return control ? control->get() : nullptr;
    }

    T* get() const {
        return control ? control->get() : nullptr;
    }

    size_t use_count() const {
        return control ? control->getRefCount() : 0;
    }

    bool unique() const {
        return use_count() == 1;
    }

    void reset(T* ptr = nullptr) {
        release();
        if (ptr) {
            control = new ControlBlock<T>(ptr);
        }
    }

    void swap(SmrtPtr& other) {
        std::swap(control, other.control);
    }

    explicit operator bool() const {
        return get() != nullptr;
    }

    // Шаблонный конструктор для подтипизации
    template <typename U, typename = typename std::enable_if<std::is_convertible<U*, T*>::value>::type>
    SmrtPtr(const SmrtPtr<U>& other) : control(reinterpret_cast<ControlBlock<T>*>(other.control)) {
        if (control) {
            control->addRef();
        }
    }

    // Шаблонный оператор присваивания для подтипизации
    template <typename U, typename = typename std::enable_if<std::is_convertible<U*, T*>::value>::type>
    SmrtPtr& operator=(const SmrtPtr<U>& other) {
        if (reinterpret_cast<void*>(this) != reinterpret_cast<const void*>(&other)) {
            release();
            control = reinterpret_cast<ControlBlock<T>*>(other.control);
            if (control) {
                control->addRef();
            }
        }
        return *this;
    }
};

template <typename T>
void swap(SmrtPtr<T>& lhs, SmrtPtr<T>& rhs) {
    lhs.swap(rhs);
}

#endif // SMRTPTR_H
