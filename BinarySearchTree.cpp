#include "BinarySearchTree.hh"

namespace algav {

	void BinarySearchTree::Insert(Key & v){

	    if (size == 0) {
	        value = &v;
			size = 1;
			return;
	    }

	    // Insert data.
	    if (v.inf(*value)) {
			if (left == nullptr) {
				left = new BinarySearchTree(&v);
			} else {
				left->Insert(v);
			}
	    }
	    else {
	        if (right == nullptr) {
				right = new BinarySearchTree(&v);
			} else {
				right->Insert(v);
			}
	    }

		size = 1;
		if (left != nullptr)
			size += left->size;
		if (right != nullptr)
			size += right->size;
	}

}