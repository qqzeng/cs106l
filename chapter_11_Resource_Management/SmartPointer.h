//
// Created by GEORGE-pc on 2020/3/19.
//

#ifndef CHAPTER_11_RESOURCE_MANAGEMENT_SMARTPOINTER_H
#define CHAPTER_11_RESOURCE_MANAGEMENT_SMARTPOINTER_H

#include <cstdio>
#include <iostream>

template <typename T>
class SmartPointer {
public:
    explicit SmartPointer(T* memory);
    SmartPointer(const SmartPointer& sp);
    SmartPointer&operator = (const SmartPointer& sp);
    ~SmartPointer();

    T& operator * () const;
    T* operator -> () const;

    T* get() const;
    size_t getShareCount() const;
private:
    struct Intermediary {
        T* memory;
        size_t reference_count;
    };
    Intermediary* data;

    void detach();
    void attach(Intermediary* other);
};

template <typename T>
SmartPointer<T>::SmartPointer(T *memory) {
    data = new Intermediary;
    data->memory = memory;
    data->reference_count = 1;
    std::cout << "SmartPointer() is called." << std::endl;
}

template <typename T>
SmartPointer<T>::~SmartPointer() {
   detach();
   std::cout << "~SmartPointer() is called." << std::endl;
}

template <typename T>
T &SmartPointer<T>::operator*() const {
    return *data->memory;
}

template <typename T>
T *SmartPointer<T>::operator->() const {
    return data->memory;
}

template <typename T>
SmartPointer<T>::SmartPointer(const SmartPointer &sp) {
    attach(sp.data);
    std::cout << "Copy SmartPointer is called." << std::endl;
}

template <typename T>
void SmartPointer<T>::detach() {
    data->reference_count--;
    if (data->reference_count == 0) {
        delete data->memory;
        delete data;
        std::cout << "memory is released."<< std::endl;
    }
}

template <typename T>
void SmartPointer<T>::attach(SmartPointer<T>::Intermediary *other) {
    data = other;
    ++data->reference_count;
}

template <typename T>
SmartPointer<T> & SmartPointer<T>::operator=(const SmartPointer &sp) {
    if (this != &sp) {
        detach();
        attach(sp.data);
    }
    std::cout << "Assignment Operator is called." << std::endl;
    return *this;
}

template <typename T>
T *SmartPointer<T>::get() const {
    return data->memory;
}

template <typename T>
size_t SmartPointer<T>::getShareCount() const {
    return data->reference_count;
}


#endif //CHAPTER_11_RESOURCE_MANAGEMENT_SMARTPOINTER_H
