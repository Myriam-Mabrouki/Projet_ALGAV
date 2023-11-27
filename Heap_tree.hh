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
		Heap_tree * SupprMin_aux();
		void SupprMin_aux2();

	public:
		Heap_tree():value(nullptr),left(nullptr),right(nullptr),size(0){}

		Heap_tree(Key * value):value(value),left(nullptr),right(nullptr),size(1){}

		Heap_tree(Key * value, Heap_tree * left, Heap_tree * right):value(value),left(left),right(right),size(1){}

		~Heap_tree(){
		}

		Key & SupprMin();

		void Ajout(Key & k);

		void AjoutsIteratifs(std::vector<Key> keys);

		size_t getSize();

		Heap_tree * getLeft(){
			return left;
		}

		Heap_tree * getRight(){
			return right;
		}

		friend std::ostream & operator << (std::ostream & os, const Heap_tree & h);

	};


}
