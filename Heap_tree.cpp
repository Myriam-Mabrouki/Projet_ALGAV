#include "Heap_tree.hh"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

namespace algav {

	Heap_tree * Heap_tree::last_element(Heap_tree * parent){
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
                return left->last_element(this);
            }
            else {
				--size;
                return right->last_element(this);
            }
        }
    }

	void Heap_tree::SupprMin_aux(){
		if (left == nullptr || right == nullptr){
			if (left != nullptr && !value->inf(*left->value)){
				std::swap(value,left->value);
			}
			return;
		}
		else {
			if (!value->inf(*left->value) && left->value->inf(*right->value)){
				std::swap(value, left->value);
				left->SupprMin_aux();
			}
			else if (!value->inf(*right->value) && right->value->inf(*left->value)){
				std::swap(value, right->value);
				right->SupprMin_aux();
			}
			else {
				//No more swapping has to be done
				return;
			}
		}
	}

	Key * Heap_tree::SupprMin(){

		Key * res = value;

		if (size == 1) {
			value = nullptr;
			--size;
			return res;
		}

		//Deletion of a Key
		Heap_tree * to_delete = last_element(this);
		value = to_delete->value;
		delete to_delete;
		
		//Finding the right position
		SupprMin_aux();
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

	void Heap_tree::AjoutsIteratifs(std::vector<Key> & keys){
		for (Key & k : keys){
			Ajout(k);
		}
	}

	size_t Heap_tree::getSize(){
		return size;
	}

	void Heap_tree::Construction(std::vector<Key> & keys) {
		if (keys.empty()) {
            return;
        }

		value = &keys[0];
		size=1;

		std::vector<Heap_tree*> tab;
		tab.reserve(keys.size());
		tab.push_back(this);

		size_t indice = 0;
		//Insertion of all keys
		for (size_t i = 1; i < keys.size(); ++i) {
            Heap_tree* current = tab[indice++];

            current->left = new Heap_tree(&keys[i]);
            tab.push_back(current->left);

            ++i;
            if (i < keys.size()) {
                current->right = new Heap_tree(&keys[i]);
                tab.push_back(current->right);
            }
        }

		//Remontées and update of size
		for (size_t i=keys.size()/2; i>0; --i) {
			Heap_tree* current = tab[i-1];
			current->size += current->left->size;
			if (current->right != nullptr) 
				current->size += current->right->size;
			current->Construction_aux();
		}
	}

	void Heap_tree::Construction_aux() {
		//It is a leaf
		if (size == 1) {
			return;
		}
		if (right != nullptr && left->value->inf(*right->value)) {
			if (!value->inf(*left->value)) {
				std::swap(value, left->value);
				left->Construction_aux();
			}
		} else if (right != nullptr && !value->inf(*right->value)) {
			std::swap(value, right->value);
			right->Construction_aux();
		}
	}

	void Heap_tree::Union (Heap_tree & h) {

		Heap_tree * result;

		if (h.size == 0 || (size != 0 && value->inf(*h.value))) {
			result = new Heap_tree(SupprMin());
		} else if (h.size != 0) {
			result = new Heap_tree(h.SupprMin());
		} else {
			return;
		}

		std::vector<Heap_tree*> tab;
		tab.reserve(size + h.size);
		tab.push_back(result);

		size_t indice = 0;

		while (size != 0 || h.size != 0) {
			Heap_tree* current = tab[indice++];

			if (h.size == 0 || (size != 0 && value->inf(*h.value))) {
				current->left = new Heap_tree(SupprMin());
			} else {
				current->left = new Heap_tree(h.SupprMin());
			}
			tab.push_back(current->left);

            if (size != 0 || h.size != 0) {
                if (h.size == 0 || (size != 0 && value->inf(*h.value))) {
					current->right = new Heap_tree(SupprMin());
				} else {
					current->right = new Heap_tree(h.SupprMin());
				}
				tab.push_back(current->right);
            }
		}

		//Update of size of all non-leaf nodes
		for (size_t i=tab.size()/2; i>0; --i) {
			Heap_tree* current = tab[i-1];
			current->size += current->left->size;
			if (current->right != nullptr) 
				current->size += current->right->size;
		}

		std::swap(*this, *result);
		delete result;

	}


}
