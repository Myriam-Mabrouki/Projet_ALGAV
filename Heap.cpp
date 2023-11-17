#include "Heap.hh"
#include <vector>
#include <iostream>
#include <algorithm>

namespace algav {

		Key & Heap::SupprMin(){

			if (size == 0){
				exit(1);
			}

			//Deletion of the minimum
			Key & to_delete = heap[0];
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

		void Heap::Ajout(Key & k){

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

		void Heap::AjoutsIteratifs(std::vector<Key> keys){
			for (Key & k : keys){
				Ajout(k);
			}

		}

		size_t Heap::getSize(){
			return size;
		}

		std::ostream & operator << (std::ostream & os, const Heap & h){
			os << "[";
			for (Key k : h.heap){
				os << std::hex << k << ", ";
			}
			os << "]";
			return os;
		}

}
