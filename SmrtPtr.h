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

    // Освобождение ресурсов
    void release() {
        if (control) {
            control->release();
            control = nullptr;
        }
    }
    template <typename> friend class SmrtPtr;

public:

    SmrtPtr() : control(nullptr) {}

    // Конструктор от сырого указателя
    explicit SmrtPtr(T* ptr) : control(nullptr) {
        if (ptr) {
            control = new ControlBlock<T>(ptr);
        }
    }

    // Конструктор копирования
    SmrtPtr(const SmrtPtr& other) : control(other.control) {
        if (control) {
            control->addRef();
        }
    }

    // Конструктор перемещения
    SmrtPtr(SmrtPtr&& other) : control(other.control) {
        other.control = nullptr;
    }

    // Деструктор
    ~SmrtPtr() {
        release();
    }

    // Оператор присваивания копированием
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

    // Оператор присваивания перемещением
    SmrtPtr& operator=(SmrtPtr&& other) {
        if (this != &other) {
            release();
            control = other.control;
            other.control = nullptr;
        }
        return *this;
    }

    // Оператор разыменования
    T& operator*() const {
        if (!control || !control->get()) {
            throw std::runtime_error("SmrtPtr: попытка разыменования нулевого указателя");
        }
        return *(control->get());
    }

    // Оператор доступа к члену
    T* operator->() const {
        return control ? control->get() : nullptr;
    }

    // Получение сырого указателя
    T* get() const {
        return control ? control->get() : nullptr;
    }

    // Получение количества ссылок
    size_t use_count() const {
        return control ? control->getRefCount() : 0;
    }

    // Проверка уникальности владения
    bool unique() const {
        return use_count() == 1;
    }

    // Сброс указателя (освобождение ресурсов)
    void reset(T* ptr = nullptr) {
        release();
        if (ptr) {
            control = new ControlBlock<T>(ptr);
        }
    }

    // Обмен содержимым с другим SmrtPtr
    void swap(SmrtPtr& other) {
        std::swap(control, other.control);
    }

    // Явное приведение к bool для проверки валидности
    explicit operator bool() const {
        return get() != nullptr;
    }

    // Шаблонный конструктор для подтипизации

};

// Функция обмена двумя SmrtPtr
template <typename T>
void swap(SmrtPtr<T>& lhs, SmrtPtr<T>& rhs) {
    lhs.swap(rhs);
}

#endif // SMRTPTR_H
