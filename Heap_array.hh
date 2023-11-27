#pragma once

#include "Key.hh"
#include <vector>
#include <iostream>

namespace algav {

	class Heap_array{

	private:
		std::vector<Key> heap;
		size_t size;

	public:
		Heap_array():size(0){}

		Key & SupprMin();

		void Ajout(Key & k);

		void AjoutsIteratifs(std::vector<Key> keys);

		size_t getSize();

		friend std::ostream & operator << (std::ostream & os, const Heap_array & h);

	};

}
