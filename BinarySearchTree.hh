#pragma once

#include "Key.hh"
#include <vector>
#include <iostream>

namespace algav {

	class BinarySearchTree{

	private:
		Key * value;
		BinarySearchTree * left;
		BinarySearchTree * right;
		size_t size;
		void print_tree(std::ostream & os, const BinarySearchTree & bst, size_t indent) const {
			for (size_t i = 0; i < indent; ++i) {
				os << "  ";
			}
			os << "| " << std::hex << *bst.value << "\n";
			if (bst.left != nullptr) {
				print_tree(os, *bst.left, indent+1);
			}
			if (bst.right != nullptr) {
				print_tree(os, *bst.right, indent+1);
			}
		}

	public:
		BinarySearchTree():value(nullptr),left(nullptr),right(nullptr),size(0){}

		BinarySearchTree(Key * value):value(value),left(nullptr),right(nullptr),size(1){}

		BinarySearchTree * Insert(BinarySearchTree * root, Key & value);

		friend std::ostream & operator << (std::ostream & os, const BinarySearchTree & bst) {
			if (bst.size == 0) {
				return os;
			}
			bst.print_tree(os, bst, 0);
			return os;
		}

	};

}
