#include "BinarySearchTree.hh"

namespace algav {

	bool BinarySearchTree::Insert(Key & k, std::string v){

	    if (size == 0) {
	        key = &k;
			value = v;
			size = 1;
			return true;
	    }

		//Data already exists
		if (k.eg(*key)){
			return false;
		}

	    // Insert data.
	    if (k.inf(*key)) {
			if (left == nullptr) {
				left = new BinarySearchTree(&k, v);
			} else {
				left->Insert(k, v);
			}
	    }
	    else {
	        if (right == nullptr) {
				right = new BinarySearchTree(&k, v);
			} else {
				right->Insert(k, v);
			}
	    }


		size = 1;
		if (left != nullptr)
			size += left->size;
		if (right != nullptr)
			size += right->size;

		return true;
	}


	std::string BinarySearchTree::Get(Key & k){

	    if (size == 0) {
			return "";
	    }

		//Data found
		if (k.eg(*key)) {
			return value;
		}


	    // Search for data.
	    if (k.inf(*key)) {
			if (left == nullptr) {
				return "";
			} else {
				left->Get(k);
			}
	    }
	    else  {
	        if (right == nullptr) {
				return "";
			} else {
				right->Get(k);
			}
	    }

		return "";
	}
}