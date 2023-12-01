#include "Heap_array.hh"

#include <vector>
#include <iostream>
#include <algorithm>

namespace algav {

		Key Heap_array::SupprMin(){

			if (size == 0){
				exit(1);
			}

			//Deletion of the minimum
			Key to_delete = heap[0];
			heap[0] = heap[heap.size()-1];
			heap.pop_back();
			--size;

			size_t pos = 0;

			while (2 * pos + 1 < size){

				Key & current = heap[pos];
				Key & left = heap[2*pos+1];

				//No right child
				if (2 * pos + 2 > size){
					if (left.inf(current)){
						std::swap(left,current);
						break;
					}
				}

				//There are two children
				Key & right = heap[2*pos+2];

				if (left.inf(current) && left.inf(right)){
					std::swap(left,current);
					pos = 2*pos+1;
				}
				else if (right.inf(current) && right.inf(left)){
					std::swap(right,current);
					pos = 2*pos+2;
				}

				//Current is in the right position
				else {
					break;
				}
			}

			return to_delete;
		}

		void Heap_array::Ajout(Key & k){

			//Addition of a Key
			heap.push_back(k);
			size_t pos = size++;

			while (pos > 0){

				Key & current = heap[pos];
				Key & father = heap[(pos-1)/2];

				if (current.inf(father)){
					std::swap(current,father);
					pos = (pos-1)/2;
				}

				//Current is in the right position
				else {
					break;
				}
			}

		}

		void Heap_array::AjoutsIteratifs(std::vector<Key> keys){
			for (Key & k : keys){
				Ajout(k);
			}

		}

		size_t Heap_array::getSize(){
			return size;
		}

		void Heap_array::Construction(std::vector<Key> keys) {
			for (Key & k : keys){
				heap.push_back(k);
				++size;
			}
			for (size_t i=keys.size()/2; i>0; i--) {
				Construction_aux(i-1);
			}
		}

		void Heap_array::Construction_aux(size_t i) {
			size_t left = 2*i;
			size_t right = 2*i+1;
			size_t max = i;

			if (left < heap.size() && heap[left].inf(heap[max])) {
				max = left;
			}
			if (right < heap.size() && heap[right].inf(heap[max])) {
				max = right;
			}

			if (i != max) {
				std::swap(heap[i], heap[max]);
				Construction_aux(max);
			}
		}

		Heap_array & Heap_array::Union (Heap_array & h) {
			std::vector<Key> result;
			result.reserve(size + h.size);
			size_t tmp = size + h.size;

			while (!heap.empty() || !h.heap.empty()) {
				if (!heap.empty() && heap[0].inf(h.heap[0])) {
					result.push_back(SupprMin());
				} else {
					result.push_back(h.SupprMin());
				}
			}

			heap = result;
			size = tmp;

			return *this;
		}


		std::ostream & operator << (std::ostream & os, const Heap_array & h){
			os << "[";
			for (Key k : h.heap){
				os << std::hex << k << ", ";
			}
			os << "]";
			return os << std::dec;
		}

}
