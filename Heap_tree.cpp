#include "Heap_tree.hh"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

namespace algav {

//	void Heap_tree::SupprMin_aux(){
//	    std::queue<Heap_tree*> q;
//	    q.push(root);
//
//	    // Do level order traversal until last node
//	    struct Node* temp;
//	    while (!q.empty()) {
//	        temp = q.front();
//	        q.pop();
//	        if (temp == d_node) {
//	            temp = NULL;
//	            delete (d_node);
//	            return;
//	        }
//	        if (temp->right) {
//	            if (temp->right == d_node) {
//	                temp->right = NULL;
//	                delete (d_node);
//	                return;
//	            }
//	            else
//	                q.push(temp->right);
//	        }
//
//	        if (temp->left) {
//	            if (temp->left == d_node) {
//	                temp->left = NULL;
//	                delete (d_node);
//	                return;
//	            }
//	            else
//	                q.push(temp->left);
//	        }
//	    }
//	}

	Heap_tree * Heap_tree::SupprMin_aux(){
		--size;
		if (left == nullptr || right == nullptr){
			if (left != nullptr){
				return left;
			}
			else {
				return this;
			}
		}
		else {
			int h = std::log2(size); //height of the current tree
			size_t max_size = std::pow(2,h+1);

			if (size + 1 < max_size/2 + (max_size/2)/2){
				return left->SupprMin_aux();
			}

			else {
				return right->SupprMin_aux();
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

		//Deletion of a Key
		Heap_tree * to_delete = SupprMin_aux();
		this->value = to_delete->value;
//		std::cout << "to_del " << std::hex << *to_delete << std::endl;
		//delete to_delete;
		to_delete = nullptr;

		//Finding the right position
		//SupprMin_aux2();
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

	std::ostream & operator << (std::ostream & os, const Heap_tree & h){
		os << "[";
		os << std::hex << *h.value << ", ";
//		if (h.left != nullptr){
//			os <<(h.left); //????? jpp jsp cmt faire oskours
//		}
//		if (h.right != nullptr){
//			os <<(h.right);
//		}
		os << "]";
		return os;
	}

}
