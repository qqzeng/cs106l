//
// Created by GEORGE-pc on 2020/3/18.
//

#ifndef CHAPTER_11_RESOURCE_MANAGEMENT_VECTOR_H
#define CHAPTER_11_RESOURCE_MANAGEMENT_VECTOR_H

#include <cstdio>
#include <algorithm>
#include <iostream>

#define DISALLOW_COPYING(str) (str(const& (str));)


namespace tz {
    template<typename T>
    class Vector {
    public:
        Vector();
        Vector(size_t initialSize);

        Vector(const Vector& other);             // Copy constructor
        Vector &operator=(const Vector &other); // Assignment operator
        ~Vector();

        typedef T *iterator;
        typedef const T *const_iterator;
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        /* ... other member functions ... */
    private:
        T *array;
        size_t allocatedLength;
        size_t logicalLength;
        static const size_t kStartSize = 16;
        void copyInstance(const Vector &other);
        void clear();
        void swapWith(Vector& other);
    };

    template<typename T>
    void Vector<T>::copyInstance(const Vector &other) {
        allocatedLength = other.allocatedLength;
        logicalLength = other.logicalLength;
        array = new T[allocatedLength];
        for (int i = 0; i < allocatedLength; ++i) array[i] = other.array[i];
//        std::copy(other.begin(), other.end(), array); // no implementation for member function begin() and end().
    }

    template<typename T>
    void Vector<T>::clear() {
        delete []array;
    }

    template<typename T>
    Vector<T>::Vector()
            : allocatedLength(kStartSize), logicalLength(0), array(new T[allocatedLength]) {
        std::cout << "Default Constructor is called." << std::endl;
    }

    template <typename T>
    Vector<T>::Vector(size_t initialSize) :
            allocatedLength(initialSize), logicalLength(0), array(new T[initialSize]) {
        std::cout << "Default Constructor is called." << std::endl;
    }

    // NOTE: can NOT call assignment operator directly !! (Exercise 11.)
    template<typename T>
    Vector<T>::Vector(const Vector &other) {
        copyInstance(other);
        std::cout << "Copy Constructor is called." << std::endl;
    }

    /**
     * Exercise 12.
     * 关于复制构造函数：
     * 若直接使用值传递，那么编译器在处理此赋值语句时，需要创建该实参对象的副本。
     * 但由于是按值传递，在创建此实参的副本时，还要再调用实参的复制构造函数，因此陷入了一个无穷调用的死循环。
     * 另外，理论上不用 const 修饰也是可以运行的，编译器不会报错。但为避免引用形参被无意修改，加上 const 修饰符更合理。
     */
//    template<typename T>
//    Vector<T>::Vector(Vector other) {
//        copyInstance(other);
//        std::cout << "Copy Constructor is called." << std::endl;
//    }

    template<typename T>
    Vector<T>::~Vector() {
        clear();
        std::cout << "Destructor is called." << std::endl;
    }

    /***
     * Exercise 12&20.
     * 关于赋值操作符：
     * 0. 需要检测是否为当前对象的原因是：避免在 clear 的时候，释放了当前对象，
     * 而又在 copyInstance中，将当前已经释放的对象（自己）深度拷贝给自己。
     * 1. const和引用都不是必须的，但加上const可以避免无意修改，并且可以让形参为const或非const的变量。
     * 而引用的目的是避免拷贝，提升调用效率。
     * 2. 其返回值为当前对象的引用，一是可以实现连续赋值操作符可以一起运算，而返回引用则是为了效率。
     * 但需要返回当前对象的引用并不是强制的。
     * 3. 当程序没有显式提供一个以本类或本类引用为参数的赋值运算符重载函数时，编译器会自动生成这样一个赋值运算符重载函数。
     * 4. 当用一个非本类的值为本类的对象赋值时，会优先调用赋值操作符，然后再考虑复制构造函数。
     * 5. 赋值运算符重载函数只能是类的非静态的成员（非友元）函数。
     *      5.1 非静态是为了能够在赋值运算符重载函数中能够操作类的实例成员。
     *      5.2 而非友元是考虑到友元函数不隶属于类本身，因此，当定义一个友元的赋值运算符重载函数时，
     *          编译器同样会为类生成一个以本类或本类引用为参数的赋值运算符重载函数。这样在调用时，产生了二义性。
     * 6. 赋值运算符重载函数不能被继承。因为基类的赋值运算符重载函数只能操作基类数据成员，因此若子类继承了基类赋值运算符重载函数，
     * 则子类不能操作自己定义的的数据成员，这是不合理的。
     */
    template<typename T>
    Vector<T> &Vector<T>::operator=(const Vector &other) {
        if (this != &other) {
            //clear();
            //copyInstance(other); // 直接拷贝效率较低，因此需要释放之前占用的空间，然后又重新分配空间
            if (this->allocatedLength < other.allocatedLength) {
                clear();
                copyInstance(other);
            } else {
                for (size_t i = 0; i < other.allocatedLength; ++i) {
                    this->array[i] = other.array[i];
                }
                this->logicalLength = other.logicalLength;
            }
            std::cout << "Assignment Operator is called." << std::endl;
        }
        return *this;
    }

    /**
     * Exercise 13&14.
     * 如此设计赋值运算重载函数也是可以的。
     * 赋值运算重载函数的设计在于：1. 如何释放被赋值对象原有空间。2. 如何将赋值对象内容深度拷贝给被赋值对象。
     * 首先使用const引用形参构造一个临时对象，然后，将当前对象和临时对象的成员交换，因此在内容上来看，二者进行了交换。
     * 最后，当出了此函数后，临时对象会自动被释放，即相当于释放了原有对象所占用的空间。
     * 在此版本的赋值运算符重载函数中，理论上不需要显式地加上是否执行了自我赋值的判断，
     * 原因在于，即使是自我赋值，将临时对象和当前对象进行内容深度交换，也不会有任何副作用。
     * 但最好的设计还是检测一下是否是当前对象，因为，这样避免了构造临时对象，提升了效率。
     */
    template <typename T>
    void Vector<T>::swapWith(Vector& other)
    {
        std::swap(array, other.array);
        std::swap(logicalLength, other.logicalLength);
        std::swap(allocatedLength, other.allocatedLength);
    }


//    template <typename T>
//    Vector<T>& Vector<T>::operator= (const Vector& other)
//    {
//        if (this != &other) {
//            Vector<T> temp(other);
//            swapWith(temp);
//            std::cout << "Assignment#2 Operator is called." << std::endl;
//        }
//        return *this;
//    }
}

#endif //CHAPTER_11_RESOURCE_MANAGEMENT_VECTOR_H
