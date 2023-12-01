#include "BinarySearchTree.hh"

namespace algav {

	BinarySearchTree * BinarySearchTree::Insert(BinarySearchTree * root, Key & value){

	    if (!root) {
	        // Insert the first node, if root is NULL.
	        return new BinarySearchTree(&value);
	    }

	    ++size;

	    // Insert data.
	    if (root->value->inf(value)) {
	        root->right = Insert(root->right, value);
	    }
	    else if (value.inf(*root->value)) {
	        root->left = Insert(root->left, value);
	    }

	    // Return 'root' node, after insertion.
	    return root;
	}

}
