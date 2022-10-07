# ifndef TREE_H
# define TREE_H

template<class T>
class Node {
    T data;
    Node<T> *left;
    Node<T> *right;

public:
    Node(const T &);
    ~Node();
    void insert(const T &);
    bool member(const T &) const;
};

template<class T>
class Tree {
    Node<T> *root;

public:
    Tree();
    ~Tree();
    void insert(const T &);
    bool member(const T &) const;
};


template<class T>
Node<T>::Node(const T &x)
    : data(x), left(NULL), right(NULL)
{
}


template<class T>
Node<T>::~Node()
{
    delete left;
    delete right;
}


template<class T>
void Node<T>::insert(const T &x)
{
    if (x < data)
	if (left == NULL)
	    left = new Node<T>(x);
	else
	    left->insert(x);

    else if (x > data)
	if (right == NULL)
	    right = new Node(x);
	else
	    right->insert(x);
}


template<class T>
bool Node<T>::member(const T &x) const
{
    if (x < data)
	if (left == NULL)
	    return false;
	else
	    return left->member(x);

    if (x > data)
	if (right == NULL)
	    return false;
	else
	    return right->member(x);

    return true;
}


template<class T>
Tree<T>::Tree()
    : root(NULL)
{
}


template<class T>
Tree<T>::~Tree()
{
    delete root;
}


template<class T>
void Tree<T>::insert(const T &x)
{
    if (root == NULL)
	root = new Node<T>(x);
    else
	root->insert(x);
}


template<class T>
bool Tree<T>::member(const T &x) const
{
    if (root == NULL)
	return false;

    return root->member(x);
}

# endif /* TREE_H */
