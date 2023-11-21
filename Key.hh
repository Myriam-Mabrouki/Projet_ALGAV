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
			size_t i;
			for (i = 0; i < 4; ++i){
				if (hex.size() < 8) {
					break;
				}
				tmp = hex.substr(0, 8);
				hex = hex.substr(8, hex.size());
				unsigned long value;
				std::istringstream iss(tmp);
				iss >> std::hex >> value;
				key.emplace_back(value);
			}

			for (size_t j = i; j < 4; ++j){

				if (hex.size() > 0){
					tmp = hex;
					unsigned long value;
					std::istringstream iss(tmp);
					iss >> std::hex >> value;
					key.emplace_back(value);
					hex = hex.substr(0,0);
				}
				else {
					key.insert(key.begin(), 0);
				}
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

