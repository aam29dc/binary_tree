#include <iostream>
#include "binarytree.h"

int main() {
	BinaryTree<int> bt(10);

	bt.insert(8, bt._root);
	bt.insert(12, bt._root);
	bt.insert(6, bt._root);
	bt.insert(9, bt._root);
	bt.insert(11, bt._root);
	bt.insert(14, bt._root);

	bt.printPost(bt._root);

	std::cout << std::endl;

	bt.prependNode(12, 99, LEFT, bt._root);

	return 0;
}
