#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace algav {

	class Key {

	private:
		std::vector<unsigned long> key;

	public:
		Key(std::string hex){
			//TODO clé < 128 bits
			hex = hex.substr(2, hex.size());
			std::string tmp;
			for (size_t i = 0; i < 4; ++i){
				tmp = hex.substr(i*8, 8);
				unsigned long value;
				std::istringstream iss(tmp);
				iss >> std::hex >> value;
				key.emplace_back(value);
			}
		}

		~Key(){}

		bool inf (Key & other) {
			for (size_t i = 0; i < 4; ++i){
				if (key[i] < other.key[i]) return true;
				if (key[i] > other.key[i]) return false;
			}
			return false;
		}

		bool eg (Key & other) {
			return other.key == key;
		}

		friend std::ostream & operator << (std::ostream & os, const Key & k){
			os << "0x";
			for (size_t i = 0; i < 4; ++i){
				os << std::hex << k.key[i];
			}
			return os;
		}


	};

}

