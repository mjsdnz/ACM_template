#ifndef __NODE__
#define __NODE__

template <typename T> class basicNode {
protected:
    T value;

public:
    basicNode<T>(T _value = T()) : value(_value) {}
};

template <typename T> class treeNode : protected basicNode<T> {
    treeNode<T> *leftSon;
    treeNode<T> *rightSon;
    treeNode<T> fatherNode;

public:
    treeNode<T>(T _value = T())
        : leftSon(nullptr), rightSon(nullptr), fatherNode(nullptr),
          basicNode<T>(_value) {}
};

#endif
