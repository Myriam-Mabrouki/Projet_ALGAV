#pragma once

#include <array>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

namespace algav {

	class Key {

	private:
		std::array<unsigned long,4> key;

	public:

		Key() {
			key = {0, 0, 0, 0};
		}

		Key(std::string hex){
			hex = hex.substr(2, hex.size());

			//If the string is not 32 hex long (thus, not 128 bits long)
			while (hex.size() < 32) {
				hex.insert(0, "0");
			}


			std::string tmp;
			for (size_t i = 0; i < 4; ++i){
				tmp = hex.substr(0, 8);
				hex = hex.substr(8, hex.size());
				unsigned long value;
				std::istringstream iss(tmp);
				iss >> std::hex >> value;
				key[i]=value;
			}
		}

		Key(const Key& other) {
			key = other.key;
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
			return other.key[0] == key[0] &&  other.key[1] == key[1] && other.key[2] == key[2] && other.key[3] == key[3];
		}

		friend std::ostream & operator << (std::ostream & os, const Key & k){
			os << "0x";

			for (size_t i = 0; i < 4; ++i){
				std::ostringstream tmp;
				tmp << std::hex << k.key[i];
				std::string s = tmp.str();
				while (s.size() < 8) {
					s.insert(0, "0");
				}
				os << s;
			}
			return os << std::dec;
		}


	};

}

