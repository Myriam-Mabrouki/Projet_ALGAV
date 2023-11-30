#pragma once

#include <array>
#include <vector>
#include <cmath>
#include <iostream>
#include <string.h>

//Note : Toutes les variables sont sur 32 bits
#define INT_BITS 32

namespace algav {

	int leftRotate(unsigned n, unsigned d){ //rotate n by d bits
		return (n << d)|(n >> (INT_BITS - d));
	}

	void hash (std::string msg){

		//Définir r comme suit :
		constexpr std::array<int, 64> r = {{
			7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,5,9,14,20,5,9,14,20,
			5,9,14,20,5,9,14,20,4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
			6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
		}};

		std::array<int, 64> k;

		//MD5 utilise des sinus d'entiers pour ses constantes :
		for (size_t i = 0; i < 64; ++i){
			k[i] = std::floor(std::abs(std::sin(i+1)) * 4294967296 ); // 2^32 = 4294967296
		}


		//Préparation des variables :
		int h0 = std::stoi("67452301", 0, 16);
		int h1 = std::stoi("EFCDAB89", 0, 16);
		int h2 = std::stoi("98BADCFE", 0, 16);
		int h3 = std::stoi("10325476", 0, 16);
//
//		//Préparation du message (padding) :
		//int msg_int = std::stoi(msg, 0, 16) + 0b1;
//		ajouter le bit "1" au message
//		ajouter le bit "0" jusqu'à ce que la taille du message en bits soit égale à 448 (mod 512)
//		ajouter la taille du message initial(avant le padding) codée en 64-bit little-endian au message
//
//		//Découpage en blocs de 512 bits :
//		pour chaque bloc de 512 bits du message
//			subdiviser en 16 mots de 32 bits en little-endian w[i], 0 ≤ i ≤ 15
//
			//initialiser les valeurs de hachage :
			int a = h0;
			int b = h1;
			int c = h2;
			int d = h3;

			int f;
			int g;

			//Boucle principale :
			for (size_t i = 0; i < 64; ++i){
				if (0 <= i && i <= 15){
					  f = (b & c) | ((~ b) & d);
					  g = i;
				}
				else if (16 <= i && i <= 31){
					  f = (d & b) | ((~ d) & c);
					  g = (5*i + 1) % 16;
				}
				else if (32 <= i && i <= 47){
					  f = b ^ c ^ d;
					  g = (3*i + 5) % 16;
				}
				else if (48 <= i && i <= 63){
					f = c ^ (b | (~ d));
					g = (7*i) % 16;
				}
				int temp = d;
				d = c;
				c = b;
				b = leftRotate((a + f + k[i] + w[g]), r[i]) + b;
				a = temp;
			}

			//ajouter le résultat au bloc précédent :
			h0 = h0 + a;
			h1 = h1 + b;
			h2 = h2 + c;
			h3 = h3 + d;
//		}
//
//		int empreinte = h0 concaténer h1 concaténer h2 concaténer h3

	}

}
