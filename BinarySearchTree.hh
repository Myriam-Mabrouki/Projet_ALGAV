#pragma once

#include "Key.hh"
#include <vector>
#include <iostream>
#include <algorithm>

namespace algav {

	class BinarySearchTree{

	private:
		Key * key;
		std::string value;
		BinarySearchTree * left;
		BinarySearchTree * right;
		size_t size;
		size_t height;

		void print_tree(std::ostream & os, const BinarySearchTree & bst, size_t indent) const {
			for (size_t i = 0; i < indent; ++i) {
				os << "  ";
			}
			os << "| " << std::hex << *bst.key << "\n";
			if (bst.left != nullptr) {
				print_tree(os, *bst.left, indent+1);
			} else {
				for (size_t i = 0; i < indent + 1; ++i) {
					os << "  ";
				}
				os << "| _" << "\n";
			} 
			if (bst.right != nullptr) {
				print_tree(os, *bst.right, indent+1);
			} else {
				for (size_t i = 0; i < indent + 1; ++i) {
					os << "  ";
				}
				os << "| _" << "\n";
			} 
		}

	public:
		BinarySearchTree():key(nullptr),value(""),left(nullptr),right(nullptr),size(0){}

		BinarySearchTree(Key * key, std::string value):key(key),value(value),left(nullptr),right(nullptr),size(1){}

		~BinarySearchTree(){
			delete left;
			delete right;
		}

		size_t getSize(){
			return size;
		}

		bool Insert(Key & k, std::string v);
		std::string Get(Key & k);

		friend std::ostream & operator << (std::ostream & os, const BinarySearchTree & bst) {
			if (bst.size == 0) {
				return os;
			}
			bst.print_tree(os, bst, 0);
			return os;
		}

	};

}