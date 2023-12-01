#pragma once

#include "Key.hh"
#include <vector>
#include <iostream>

namespace algav {

	class Heap_tree{

	private:
		Key * value;
		Heap_tree * left;
		Heap_tree * right;
		size_t size;
		Heap_tree * SupprMin_aux(Heap_tree * parent);
		void SupprMin_aux2();
		void Construction_aux(size_t i);

		void print_tree(std::ostream & os, const Heap_tree & h, size_t indent) const {
			for (size_t i = 0; i < indent; ++i) {
				os << "  ";
			}
			os << "| " << std::hex << *h.value << "\n";
			if (h.left != nullptr) {
				print_tree(os, *h.left, indent+1);
			}
			if (h.right != nullptr) {
				print_tree(os, *h.right, indent+1);
			}
		}

	public:
		Heap_tree():value(nullptr),left(nullptr),right(nullptr),size(0){}

		Heap_tree(Key * value):value(value),left(nullptr),right(nullptr),size(1){}

		Heap_tree(Key * value, Heap_tree * left, Heap_tree * right):value(value),left(left),right(right),size(1){}

		~Heap_tree(){
		}

		Key & SupprMin();

		void Ajout(Key & k);

		void AjoutsIteratifs(std::vector<Key> & keys);

		size_t getSize();

		void Construction(std::vector<Key> & keys);

		friend std::ostream & operator << (std::ostream & os, const Heap_tree & h) {
			if (h.size == 0) {
				return os;
			}
			h.print_tree(os, h, 0);
			return os << std::dec;
		}
		
		/*friend std::ostream & operator << (std::ostream & os, const Heap_tree & h){
			os << std::hex << *h.value << " ";
			if (h.left != nullptr){
				os << *h.left; 
			}
			if (h.right != nullptr){
				os << *h.right;
			}
			return os << std::dec;
		}*/

	};


}
