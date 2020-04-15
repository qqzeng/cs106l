//
// Created by GEORGE-pc on 2020/3/17.
//

#ifndef CHAPTER_09_REFINING_ABSTRACTIONS_MYVECTOR_H
#define CHAPTER_09_REFINING_ABSTRACTIONS_MYVECTOR_H

/* Exercise 20. */
template<typename ElemType>
class MyVector {
public:
    MyVector(int sizeHint = 0);

    int size() const;

    bool isEmpty() const;

    const ElemType& getAt(const int &index) const;

    void setAt(const int &index, const ElemType &value);

    ElemType &operator[](const int &index);

    void add(const ElemType &elem);

    void insertAt(const int &index, const ElemType &elem);

    void removeAt(const int &index);

    void clear();

    void mapAll(void fn(const ElemType &elem)) const ;

    template<typename ClientDataType>
    void mapAll(void fn(const ElemType &elem, ClientDataType &data),
                ClientDataType &data) const ;

//    Iterator iterator();
//    const_Iterator iterator() const ;
};

#endif //CHAPTER_09_REFINING_ABSTRACTIONS_MYVECTOR_H
