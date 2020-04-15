//
// Created by GEORGE-pc on 2020/3/18.
//

#ifndef CHAPTER_10_OPERATOR_OVERLOADING_GRID_H
#define CHAPTER_10_OPERATOR_OVERLOADING_GRID_H

#include <vector>
using namespace std;

template<typename T> class Grid {
public:
    /* Constructors, destructors. */
    Grid();                               // Create empty grid
    Grid(size_t rows, size_t cols);       // Construct to specified size

    /* Resizing operations. */
    void clear();                          // Empty the grid
    void resize(size_t rows, size_t cols); // Resize the grid

    /* Query operations. */
    size_t numRows() const;              // Returns number of rows in the grid
    size_t numCols() const;              // Returns number of columns in the grid
    bool empty() const;                  // Returns whether the grid is empty
    size_t size() const;                 // Returns the number of elements

    /* Element access. */
    T &getAt(size_t row, int col);    // Access individual elements
    const T &getAt(int row, int col) const; // Same, but const

    void setAt(size_t row, int col, T val);    // Access individual elements


    /* iterators. */
    typedef typename vector<T>::iterator iterator;
    typedef typename vector<T>::const_iterator const_iterator;
    iterator begin();
    const_iterator begin() const ;
    iterator end();
    const_iterator end() const ;

    iterator row_begin(size_t row);
    const_iterator row_begin(size_t row) const ;
    iterator row_end(size_t row);
    const_iterator row_end(size_t row) const ;

    /*  Element Selection Operator Overloading. */
    class MutableReference {
    public:
        friend class Grid;
        T& operator[] (size_t col);

    private:
        MutableReference(Grid *owner, size_t row);

        Grid * const owner;
        const size_t row;
    };
    MutableReference operator [] (size_t row);

    class ImMutableReference {
    public:
        friend class Grid;
        T& operator[] (size_t col);

    private:
        ImMutableReference(const Grid *owner, size_t row);

        Grid * const owner;
        const size_t row;
    };
    const ImMutableReference& operator [] (size_t row) const ;

    /* Relational Operators Overloading. */
    bool operator< (const Grid<T>& other) const ;
    bool operator> (const Grid<T>& other) const ;
    bool operator<= (const Grid<T>& other) const ;
    bool operator>= (const Grid<T>& other) const ;
    bool operator== (const Grid<T>& other) const ;
    bool operator!= (const Grid<T>& other) const ;

    /* Element Range Selectoon Operators Overloading. */
//    class Span {
//    public:
//        Span();
//        Span(int start, int stop);
//        int getStart() const;
//        int getStop() const ;
//    private:
//        int start, stop;
//    };
//
//    class ImMutableRangeReference {
//    public:
//        friend class Grid;
//        Grid<T> operator [] (const Grid::Span& col);
//
//    private:
//        ImMutableRangeReference(const Grid *owner, const Grid::Span& row);
//
//        const Grid * const owner;
//        const Span row;
//    };
//    ImMutableRangeReference operator [] (const Grid::Span& row);

private:
    vector<T> elems;
    size_t rows;
    size_t cols;
};


/* elements range selection implementation. */

//template <typename T>
//Grid<T>::ImMutableRangeReference::ImMutableRangeReference(const Grid<T> *owner, const Grid<T>::Span& row)
//        : owner(owner), row(row) {
//}
//
//template <typename T>
//Grid<T> Grid<T>::ImMutableRangeReference::operator[] (const Grid::Span& col) {
//    size_t start1 = row.getStart();
//    size_t stop1 = row.getStop();
//    size_t start2 = col.getStart();
//    size_t stop2 = col.getStop();
//    Grid<T> result(stop1-start1, stop2-start2);
//    /* check argument valid. */
//    for (size_t i = start1; i < stop1; ++i) {
//        for (size_t j = start2; j < stop2; ++j) {
//            result.setAt(i-start1, j-start2, owner->getAt(i, j));
//        }
//    }
//    return result;
//}
//
//template <typename T>
//Grid<T>::Span::Span() : start(0), stop(0){
//}
//
//template <typename T>
//Grid<T>::Span::Span(int start, int stop) : start(start), stop(stop){
//}
//
//template <typename T>
//int Grid<T>::Span::getStart() const {
//    return start;
//}
//
//template <typename T>
//int Grid<T>::Span::getStop() const {
//    return stop;
//}

/* element selection implementation. */

template <typename T>
Grid<T>::ImMutableReference::ImMutableReference(const Grid *owner, size_t row)
        : owner(owner), row(row) {
}

template <typename T>
T & Grid<T>::ImMutableReference::operator[](size_t col) {
    return owner->getAt(row, col);;
}

template <typename T>
Grid<T>::MutableReference::MutableReference(Grid *owner, size_t row)
        : owner(owner), row(row) {
}

template <typename T>
T &Grid<T>::MutableReference::operator[](size_t col) {
    return owner->getAt(row, col);
}


/* basic member functions implementation. */

template <typename T>
Grid<T>::Grid() : rows(0), cols(0) {
}

template <typename T>
Grid<T>::Grid(size_t rows, size_t cols)
        : elems(rows * cols), rows(rows), cols(cols) {
}

template <typename T>
void Grid<T>::clear() {
    rows = 0;
    cols = 0;
    elems.clear();
}

template <typename T>
void Grid<T>::resize(size_t rows, size_t cols) {
    this->rows = rows;
    this->cols = cols;
    this->elems.assign(rows * cols, T());
}

template <typename T>
size_t Grid<T>::numRows() const {
    return rows;
}

template <typename T>
size_t Grid<T>::numCols() const {
    return cols;
}

template <typename T>
bool Grid<T>::empty() const {
    return size() == 0;
}

template <typename T>
size_t Grid<T>::size() const {
    return numRows() * numCols();
}

template <typename T>
T &Grid<T>::getAt(size_t row, int col) {
    return elems[row * numCols() + col];
}

template <typename T>
const T &Grid<T>::getAt(int row, int col) const {
    return elems[row * numCols() + col];
}

template <typename T>
void Grid<T>::setAt(size_t row, int col, T val) {
    elems[row * cols + col] = val;
}

/* iterator overloading implementation. */
template <typename T>
typename Grid<T>::iterator Grid<T>::begin() {
    return elems.begin();
}

template <typename T>
typename Grid<T>::const_iterator Grid<T>::begin() const {
    return elems.begin();
}

template <typename T>
typename Grid<T>::iterator Grid<T>::end() {
    return elems.end();
}

template <typename T>
typename Grid<T>::const_iterator Grid<T>::end() const {
    return elems.end();
}

template <typename T>
typename Grid<T>::iterator Grid<T>::row_begin(size_t row) {
    return elems.begin() + row * cols;
}

template <typename T>
typename Grid<T>::const_iterator Grid<T>::row_begin(size_t row) const {
    return elems.begin() + row * cols;
}

template <typename T>
typename Grid<T>::iterator Grid<T>::row_end(size_t row) {
    return row_begin(row) + cols;
}

template <typename T>
typename Grid<T>::const_iterator Grid<T>::row_end(size_t row) const {
    return row_begin(row) + cols;
}

/* element selection overloading implementation. */

template <typename T>
typename Grid<T>::MutableReference Grid<T>::operator[](size_t row) {
    Grid<T>::MutableReference mr(this, row);
    return mr;
}

template <typename T>
const typename Grid<T>::ImMutableReference &Grid<T>::operator[](size_t row) const {
    Grid<T>::ImMutableReference imr(this, row);
    return imr;
}

/* relation overloading implementation. */

template <typename T>
bool Grid<T>::operator<(const Grid<T> &other) const {
    if (this->numRows() != other.numRows())
        return this->numRows() < other.numRows();
    else if (this->numCols() != other.numCols()) {
        return this->numCols() < other.numCols();
    } else {
        return lexicographical_compare(begin(), end(), other.begin(), other.end());
    }
}

template <typename T>
bool Grid<T>::operator>(const Grid<T> &other) const {
    return (other<*this);
}

template <typename T>
bool Grid<T>::operator<=(const Grid<T> &other) const {
    return !(other<*this);
}

template <typename T>
bool Grid<T>::operator>=(const Grid<T> &other) const {
    return !(*this<other);
}

template <typename T>
bool Grid<T>::operator==(const Grid<T> &other) const {
    return !(*this<other) && !(other<*this);
}

template <typename T>
bool Grid<T>::operator!=(const Grid<T> &other) const {
    return (*this<other) || (*this>other);
}

/* elements range selection overloading implementation. */

//template <typename T>
//typename Grid<T>::ImMutableRangeReference Grid<T>::operator[](const Grid<T>::Span& row) {
//    return ImMutableRangeReference(this, row);
//}


/* another relation overloading implementation for == and != . */

//template <typename T>
//bool Grid<T>::operator==(const Grid<T> &other) const {
//    return (this == &other);
//}
//
//template <typename T>
//bool Grid<T>::operator!=(const Grid<T> &other) const {
//    return !(*this == other);
//}

#endif //CHAPTER_10_OPERATOR_OVERLOADING_GRID_H
