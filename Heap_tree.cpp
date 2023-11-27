#include "Heap_tree.hh"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

namespace algav {

	Heap_tree * Heap_tree::SupprMin_aux(Heap_tree * parent){
		if (left == nullptr || right == nullptr){
            if (left != nullptr){
				--size;
                Heap_tree * tmp = left;
                left = nullptr;
                return tmp;
            }
            else {
				Heap_tree * tmp = this;
                parent->right = nullptr;
				return tmp;
            }
        }
        else {
            int h = std::log2(size); //height of the current tree
            size_t max_size = std::pow(2,h+1);

            if (size < max_size/2 + (max_size/2)/2){
				--size;
                return left->SupprMin_aux(this);
            }
            else {
				--size;
                return right->SupprMin_aux(this);
            }
        }
    }

	void Heap_tree::SupprMin_aux2(){
		if (left == nullptr || right == nullptr){
			if (left != nullptr && !value->inf(*left->value)){
				std::swap(value,left->value);
			}
			return;
		}
		else {
			if (!value->inf(*left->value) && left->value->inf(*right->value)){
				std::swap(value, left->value);
				left->SupprMin_aux2();
			}
			else if (!value->inf(*right->value) && right->value->inf(*left->value)){
				std::swap(value, right->value);
				right->SupprMin_aux2();
			}
			else {
				//No more swapping has to be done
				return;
			}
		}
	}

	Key & Heap_tree::SupprMin(){

		Key & res = *value;

		if (size == 1) {
			value = nullptr;
			--size;
			return res;
		}

		//Deletion of a Key
		Heap_tree * to_delete = SupprMin_aux(this);
		value = to_delete->value;
		
		//Finding the right position
		SupprMin_aux2();
		return res;
	}

	void Heap_tree::Ajout(Key & k){

		++size;

		//Addition of a Key
		if (value == nullptr){
			value = &k;
			return;
		}

		int left_right = 0;
		if (left == nullptr || right == nullptr){
			Heap_tree * h = new Heap_tree(&k);
			if (left != nullptr){
				left_right = 1;
				right = h;
			}
			else left = h;
		}

		else {
			int h = std::log2(size); //height of the current tree
			size_t max_size = std::pow(2,h+1);

			if (size < max_size/2 + (max_size/2)/2){
				left->Ajout(k);
			}

			else {
				left_right = 1;
				right->Ajout(k);
			}
		}

		//Finding the right position
		if (left_right == 0 && !value->inf(*left->value)){
			std::swap(value, left->value);
		}
		else if (left_right == 1 && !value->inf(*right->value)){
			std::swap(value, right->value);
		}

	}

	void Heap_tree::AjoutsIteratifs(std::vector<Key> keys){
		for (Key & k : keys){
			Ajout(k);
		}
	}

	size_t Heap_tree::getSize(){
		return size;
	}

}
