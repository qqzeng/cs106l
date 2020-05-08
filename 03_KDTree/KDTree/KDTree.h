/**
 * File: KDTree.h
 * Author: (your name here)
 * ------------------------
 * An interface representing a kd-tree in some number of dimensions. The tree
 * can be constructed from a set of data and then queried for membership and
 * nearest neighbors.
 */

#ifndef KDTREE_INCLUDED
#define KDTREE_INCLUDED

#include <stdexcept>
#include <iostream>
#include <cmath>
#include <memory> // import unique_ptr
#include "Point.h"
#include "BoundedPQueue.h"


// "using namespace" in a header file is conventionally frowned upon, but I'm
// including it here so that you may use things like size_t without having to
// type std::size_t every time.
using namespace std;

//refer: https://github.com/yangyueren/CS106L/blob/master/03_KDTree/src/KDTree.h

/* The defintion of node of KDTree. */
template <size_t N, typename ElemType>
struct Node{
    /* the key typed Point of node. */
    Point<N> pt;
    /* the value typed ElemType of node. */
    ElemType val;
    /* the left child of node. */
    unique_ptr<Node<N, ElemType> > left;
    /* the right child of node. */
    unique_ptr<Node<N, ElemType> > right;
    /* the leve of node. */
    int level;

    /* overide default consturct. */
    Node():left(nullptr), right(nullptr),level(0){}
    /* common consturct. */
    Node(Point<N> pt, ElemType val, int level) :
        pt(pt), val(val), left(nullptr), right(nullptr), level(level) {}

    /*insert a new node, return whether insert operation is successful. */
    bool insert(const Point<N>& pt, const ElemType& val) {
        if (pt == this->pt) {
            this->val = val;
            return false;
        }
        if (pt[level % N] < this->pt[level % N]) {
            if (this->left != nullptr) {
                return left->insert(pt, val);
            } else {
                this->left.reset(new Node<N, ElemType>(pt, val, level+1));
                return true;
            }
        } else {
            if (this->right != nullptr) {
                return right->insert(pt, val);
            } else {
                this->right.reset(new Node<N, ElemType>(pt, val, level+1));
                return true;
            }
        }
    }
};


template <size_t N, typename ElemType>
class KDTree {
public:
    // Constructor: KDTree();
    // Usage: KDTree<3, int> myTree;
    // ----------------------------------------------------
    // Constructs an empty KDTree.
    KDTree();

    // Destructor: ~KDTree()
    // Usage: (implicit)
    // ----------------------------------------------------
    // Cleans up all resources used by the KDTree.
    ~KDTree();

    // KDTree(const KDTree& rhs);
    // KDTree& operator=(const KDTree& rhs);
    // Usage: KDTree<3, int> one = two;
    // Usage: one = two;
    // -----------------------------------------------------
    // Deep-copies the contents of another KDTree into this one.
    KDTree(const KDTree& rhs);
    KDTree& operator=(const KDTree& rhs);

    // size_t dimension() const;
    // Usage: size_t dim = kd.dimension();
    // ----------------------------------------------------
    // Returns the dimension of the points stored in this KDTree.
    size_t dimension() const;

    // size_t size() const;
    // bool empty() const;
    // Usage: if (kd.empty())
    // ----------------------------------------------------
    // Returns the number of elements in the kd-tree and whether the tree is
    // empty.
    size_t size() const;
    bool empty() const;

    // bool contains(const Point<N>& pt) const;
    // Usage: if (kd.contains(pt))
    // ----------------------------------------------------
    // Returns whether the specified point is contained in the KDTree.
    bool contains(const Point<N>& pt) const;

    // void insert(const Point<N>& pt, const ElemType& value);
    // Usage: kd.insert(v, "This value is associated with v.");
    // ----------------------------------------------------
    // Inserts the point pt into the KDTree, associating it with the specified
    // value. If the element already existed in the tree, the new value will
    // overwrite the existing one.
    void insert(const Point<N>& pt, const ElemType& value);

    // ElemType& operator[](const Point<N>& pt);
    // Usage: kd[v] = "Some Value";
    // ----------------------------------------------------
    // Returns a reference to the value associated with point pt in the KDTree.
    // If the point does not exist, then it is added to the KDTree using the
    // default value of ElemType as its key.
    ElemType& operator[](const Point<N>& pt);

    // ElemType& at(const Point<N>& pt);
    // const ElemType& at(const Point<N>& pt) const;
    // Usage: cout << kd.at(v) << endl;
    // ----------------------------------------------------
    // Returns a reference to the key associated with the point pt. If the point
    // is not in the tree, this function throws an out_of_range exception.
    ElemType& at(const Point<N>& pt);
    const ElemType& at(const Point<N>& pt) const;

    // ElemType kNNValue(const Point<N>& key, size_t k) const
    // Usage: cout << kd.kNNValue(v, 3) << endl;
    // ----------------------------------------------------
    // Given a point v and an integer k, finds the k points in the KDTree
    // nearest to v and returns the most common value associated with those
    // points. In the event of a tie, one of the most frequent value will be
    // chosen.
    ElemType kNNValue(const Point<N>& key, size_t k) const;

private:
    // TODO: Add implementation details here.
    /* the root node of KDTree. */
    unique_ptr<Node<N, ElemType> > root;
    /* the number of node of KDTree. */
    size_t num;
    /* the dimenstion of node/KDTree. */
    size_t dim;

    const unique_ptr<Node<N, ElemType> >& findNode(const unique_ptr<Node<N, ElemType> >& node, const Point<N>& pt) const;
    unique_ptr<Node<N, ElemType> > copyOther(const unique_ptr<Node<N, ElemType> >& rhs);
    void kNNSearch(BoundedPQueue<Point<N> > &q, const unique_ptr<Node<N, ElemType> >& root, const Point<N>& key) const;
    ElemType findRequentItem(BoundedPQueue<Point<N> > &bpq) const;
};

/** KDTree class implementation details */

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree() : root(nullptr), num(0), dim(N) {}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree(){}


template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
    return dim;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const{
    return num;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const{
    return num == 0;
}


template <size_t N, typename ElemType>
const unique_ptr<Node<N, ElemType> >& KDTree<N, ElemType>::findNode(const unique_ptr<Node<N, ElemType> >& node, const Point<N>& pt) const {
    if (node == nullptr) return node;
    if (node->pt == pt) return node;
    if (pt[node->level % N] < node->pt[node->level % N]) {
        return findNode(node->left, pt);
    }
    return findNode(node->right, pt);
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N>& pt) const{
    return findNode(root, pt) != nullptr;
}


template <size_t N, typename ElemType>
unique_ptr<Node<N, ElemType> > KDTree<N, ElemType>::copyOther(const unique_ptr<Node<N, ElemType> >& node) {
    if (node == nullptr) return nullptr;
    unique_ptr<Node<N, ElemType> > dup(new Node<N, ElemType>(node->pt, node->val, node->level));
    dup->left = copyOther(node->left);
    dup->right = copyOther(node->right);
    return dup;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree<N, ElemType>& rhs) {
    root = copyOther(rhs.root);
    num = rhs.num;
    dim = rhs.dim;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>& KDTree<N, ElemType>::operator=(const KDTree<N, ElemType>& rhs) {
    if (this != &rhs) {
        // unnecessary to release original data by hand.
        root = copyOther(rhs.root);
        num = rhs.num;
        dim = rhs.dim;
    }
    return *this;
}


template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N>& pt, const ElemType& value){
    if(root == nullptr){
        root.reset(new Node<N, ElemType>(pt, value, 0));
        ++num;
    }else{
        bool ok = root->insert(pt, value);
        if(ok) ++num;
    }
}


template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt){
    const unique_ptr<Node<N, ElemType> >& e = findNode(root, pt);
    if (e == nullptr) {
        insert(pt, ElemType());
        const unique_ptr<Node<N, ElemType> >& e = findNode(root, pt);
        return e->val;
    } else {
        return e->val;
    }
}


template <size_t N, typename ElemType>
const ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) const {
    const unique_ptr<Node<N, ElemType> >& e = findNode(root, pt);
    if(e == nullptr){
        throw out_of_range("fail executing at(): out of range");
    }else{
        return e->val;
    }
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::at(const Point<N>& pt){
    /* to enable non-const object call const member funciton,
     * we need convert the object to const object. */
    const KDTree<N, ElemType>* tmp = this;
    return const_cast<ElemType&>(tmp->at(pt));
}


template <size_t N, typename ElemType>
void KDTree<N, ElemType>::kNNSearch(BoundedPQueue<Point<N> > &bpq, const unique_ptr<Node<N, ElemType> >& root, const Point<N>& key) const{
    if(root == nullptr) return;
    double dist = Distance(root->pt, key);
    bpq.enqueue(root->pt, dist);
    int branch=0;
    if (key[root->level % N] < root->pt[root->level % N]){
        kNNSearch(bpq, root->left, key);
        branch = 0;
    } else{
        kNNSearch(bpq, root->right, key);
        branch = 1;
    }
    /* Attention! */
    if (bpq.size() <= bpq.maxSize() || dist <= bpq.worst()){
        if (branch == 0){
            kNNSearch(bpq, root->right, key);
        } else{
            kNNSearch(bpq, root->left, key);
        }
    }

}

template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::findRequentItem(BoundedPQueue<Point<N> > &bpq) const {
    std::map<ElemType, int> mp;
    while (!bpq.empty()){
        Point<N> tmp = bpq.dequeueMin();
        ElemType t = at(tmp);
        if(mp.find(t) != mp.end()){
            ++mp[t];
        } else {
            mp[t] = 1;
        }
    }
    ElemType mostFreqentElem;
    int max = 0;
    for (auto pair: mp){
        if(pair.second > max){
            max = pair.second;
            mostFreqentElem = pair.first;
        }
    }
//    cout << "most frequent entry index is " << mostFreqentElem << ", and its freqent is " << max << " ";
    return mostFreqentElem;
}

template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::kNNValue(const Point<N>& key, size_t k) const {
    if(root == nullptr) return ElemType();
    BoundedPQueue<Point<N> > bpq(k);
    kNNSearch(bpq, root, key);
    return findRequentItem(bpq);
}

#endif // KDTREE_INCLUDED
