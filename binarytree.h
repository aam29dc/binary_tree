#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <assert.h>

const bool LEFT = 0;
const bool RIGHT = 1;

template <typename T>
class Node {
private:
	unsigned int static _count;
public:
	T _data;
	Node<T>* _left;
	Node<T>* _right;
	
	Node(const T data) : _data(data) {
		_left = nullptr;
		_right = nullptr;
		_count++;
	}

	~Node() {
		_count--;
	}

	unsigned int getCount() const {
		return Node<T>::_count;
	}
};

template <typename T>
unsigned int Node<T>::_count = 0;

template <typename T>
class BinaryTree {
private:
	unsigned int static _count;

	void convertIndexArray(const unsigned int index, T arr[], const Node<T>* const root) const {
		if (root == nullptr) return;
		if (root->_left != nullptr) arr[index + 1] = root->_left->_data;
		if (root->_right != nullptr) arr[index + 2] = root->_right->_data;

		convertIndexArray(index + 2, arr, root->_left);
		convertIndexArray(index + 4, arr, root->_right);
	}
	/*
	bool sideHelper(const T key, const Node<T>* const root) {
		if (root == nullptr) return false;
		if (root->_data == key) return true;

		bool left = false;
		bool right = false;

		if (root->_left != nullptr) left = sideHelper(key, root->_left);
		if (root->_right != nullptr) right = sideHelper(key, root->_right);

		if (left == true || right == true) return true;
		else return false;
	}*/

public:
	Node<T>* _root;

	BinaryTree(const T data) {
		_root = new Node<T>(data);
		_count++;
	}

	~BinaryTree() {
		_count--;
	}

	T* convertToArray(const Node<T>* const root) const {
		const unsigned int length = size(root);
		T *arr = new T[length];

		arr[0] = root->_data;
		convertIndexArray(0, arr, root);
		return arr;
	}

	unsigned int maxDepth(const Node<T>* const root) const {
		if (root == nullptr) return 0;

		unsigned int left = maxDepth(root->_left);
		unsigned int right = maxDepth(root->_right);
		
		if (left >= right) return 1 + maxDepth(root->_left);
		else return 1 + maxDepth(root->_right);
	}

	Node<T>* findNode(const T key, Node<T>* root) const {
		if (root == nullptr) return nullptr;

		Node<T>* left = nullptr;
		Node<T>* right = nullptr;

		if (root->_data == key) return root;
		else {
			left = findNode(key, root->_left);
			right = findNode(key, root->_right);
		}

		if (left != nullptr) return left;
		else if (right != nullptr) return right;

		return nullptr;
	}

	Node<T>* findParent(const T key, Node<T>* root) const {
		if (root == nullptr) return nullptr;

		Node<T>* left = nullptr;
		Node<T>* right = nullptr;

		if (root->_left != nullptr) {
			if (root->_left->_data == key) return root;
		}

		if (root->_right != nullptr) {
			if (root->_right->_data == key) return root;
		}

		left = findNode(key, root->_left);
		right = findNode(key, root->_right);

		if (left != nullptr) return left;
		else if (right != nullptr) return right;

		return nullptr;
	}

	T minValue(const Node<T>* const root, T min = root->_data) const {
		assert(root != nullptr);

		if (root->_left != nullptr) {
			if (root->_left->_data < min) min = root->_left->_data;
		}

		if (root->_right != nullptr) {
			if (root->_right->_data < min) min = root->_right->_data;
		}

		T left = min;
		T right = min;

		if (root->_left != nullptr) {
			left = minValue(root->_left, min);
		}
		if (root->_right != nullptr) {
			right = minValue(root->_right, min);
		}

		return left < right ? left : right;
	}

	T maxValue(const Node<T>* const root, T max = root->_data) const {
		assert(root != nullptr);

		if (root->_left != nullptr) {
			if (root->_left->_data > max) max = root->_left->_data;
		}

		if (root->_right != nullptr) {
			if (root->_right->_data > max) max = root->_right->_data;
		}

		T left = max;
		T right = max;

		if (root->_left != nullptr) {
			left = maxValue(root->_left, max);
		}
		if (root->_right != nullptr) {
			right = maxValue(root->_right, max);
		}

		return left > right ? left : right;
	}

	T BSTminValue(const Node<T>* const root) const {
		while (root->_left != nullptr) {
			root = root->_left;
		}
		return root->_data;
	}

	T BSTmaxValue(const Node<T>* const root) const {
		while (root->_right != nullptr) {
			root = root->_right;
		}
		return root->_data;
	}
	/*
	char side(const T key, const Node<T>* const root) {
		assert(root != nullptr);

		bool left = false;
		bool right = false;

		if (root->_left != nullptr) left = sideHelper(key, root->_left);
		if (root->_right != nullptr) right = sideHelper(key, root->_right);

		if (left) return 'L';
		else if (right) return 'R';
		else return 0;
	}

	unsigned int distance(const T key1, const T key2, const Node<T>* const root, const unsigned int dist = 0) {
		assert(root != nullptr);

		if (key1 == root->_data) return distance(key2, root);
		else if (key2 == root->_data) return distance(key1, root);

		char side1 = side(key1, root);
		char side2 = side(key2, root);
		unsigned int dist1 = distance(key1, root);
		unsigned int dist2 = distance(key2, root);

		if (side1 == side2) {
			return dist1 > dist2 ? dist1 - dist2 : dist2 - dist1;
		}
		else return dist1 + dist2 + 1;
	}

	unsigned int distance(const T key, const Node<T>* const root, const unsigned int dist = 0) const {
		assert(root != nullptr);

		if (root->_data == key) return dist - 1;

		unsigned int left = 0;
		unsigned int right = 0;
		
		if(root->_left != nullptr) left = distance(key, root->_left, dist + 1);
		if(root->_right != nullptr) right = distance(key, root->_right, dist + 1);

		if (left != 0) return left;
		if (right != 0) return right;

		return 0;
	}
	*/

	void mirror(Node<T>* root) {
		if (root == nullptr) return;

		Node<T>* temp = root->_right;
		root->_right = root->_left;
		root->_left = temp;
		if (root->_left != nullptr) mirror(root->_left);
		if (root->_right != nullptr) mirror(root->_right);
	}

	bool identical(const Node<T>* const x, const Node<T>* const y) const {
		if (x == nullptr && y == nullptr) return true;

		else if (x != nullptr && y != nullptr) {
			if (x->_data == y->_data) {
				return identical(x->_left, y->_left) && identical(x->_right, y->_right);
			}
			else return false;
		}
		else return false;
	}

	bool isBST(const Node<T>* const root) const {
		if (root->_left != nullptr && root->_data < root->_left->_data) return false;
		if (root->_right != nullptr && root->_data > root->_right->_data) return false;
		if (root->_left == nullptr || root->_right == nullptr) return true;

		return isBST(root->_left) && isBST(root->_right) && true;
	}

	unsigned int size(const Node<T>* const root) const {
		if (root == nullptr) return 0;
		else return 1 + size(root->_left) + size(root->_right);
	}

	void insert(const T data, Node<T>* root) {
		if (root == nullptr) {
			root = new Node<T>(data);
			return;
		}

		if (data > root->_data) {
			if(root->_right != nullptr)	insert(data, root->_right);
			else root->_right = new Node<T>(data);
		}
		else {
			if(root->_left != nullptr) insert(data, root->_left);
			else root->_left = new Node<T>(data);
		}
	}

	void prependNode(const T key, const T data, const bool side, Node<T>* root) {
		assert(root != nullptr);

		Node<T>* newNode = new Node<T>(data);
		Node<T>* current = findParent(key, root);
		Node<T>* save = nullptr;
		
		if (current == nullptr) {
			if (side == LEFT) {
				newNode->_left = root;
				_root = newNode;
			}
			else {
				newNode->_right = root;
				_root = newNode;
			}
		}
		else {
			if (side == LEFT) {
				save = current->_left;
				current->_left = newNode;
				newNode->_left = save;
			}
			else {
				save = current->_right;
				current->_right = newNode;
				newNode->_right = save;
			}
		}
	}

	void deleteNode(const T key, Node<T>* root) {
		assert(root != nullptr);

		Node<T>* current = findNode(key, root);
		Node<T>* prev = nullptr;

		if (current != nullptr) {
			while (current->_right != nullptr) {
				current->_data = current->_right->_data;
				prev = current;
				current = current->_right;
			}

			if (current->_left != nullptr) {
				current->_data = current->_left->_data;
				delete current->_left;
				current->_left = nullptr;
			}
			else {
				delete current;
				current = nullptr;
				prev->_right = nullptr;
			}
		}
	}

	void destroy(Node<T>* root) {
		if (root->_left != nullptr) { destroy(root->_left); }
		if (root->_right != nullptr) { destroy(root->_right); }
		if (root != nullptr) {
			delete root;
			root = nullptr;
		}
	}

	void printPre(const Node<T>* const root) const {
		if (root != nullptr) {
			std::cout << root->_data << ", ";
			printPost(root->_left);
			printPost(root->_right);
		}
	}

	void printPost(const Node<T>* const root) const {
		if (root != nullptr) {
			printPost(root->_left);
			printPost(root->_right);
			std::cout << root->_data << ", ";
		}
	}

	void printInorder(const Node<T>* const root) const {
		if (root != nullptr) {
			printPost(root->_left);
			std::cout << root->_data << ", ";
			printPost(root->_right);
		}
	}

	unsigned int getCount() const {
		return BinaryTree<T>::_count;
	}
};

template <typename T>
unsigned int BinaryTree<T>::_count = 0;

#endif