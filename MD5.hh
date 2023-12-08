#pragma once

#include <array>
#include <vector>
#include <cmath>
#include <iostream>
#include <string.h>
#include <iomanip>
#include "Key.hh"

namespace algav {

	typedef union uwb {
		unsigned w;
		unsigned char b[4];
	} MD5union;

	static unsigned leftRotate(unsigned r, short N)
	{
		unsigned  mask1 = (1 << N) - 1;
		return ((r >> (32 - N)) & mask1) | ((r << N) & ~mask1);
	}

	Key MD5Hash(std::string msg)
	{
		int mlen = msg.length();

		// Initialize variables:
		unsigned h0 = 0x67452301;
		unsigned h1 = 0xEFCDAB89; 
		unsigned h2 = 0x98BADCFE;
		unsigned h3 = 0x10325476;

		// r specifies the per-round shift amounts
		static short r [] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
							  5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
							  4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
							  6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };


		static unsigned k[64];
		for (size_t i = 0; i<64; ++i) {
			k[i] = (unsigned)(fabs(sin(1.0 + i)) * 4294967296); //2^32 = 4294967296
		}

		union {
			unsigned w[16];
			char     b[64];
		}mm;

		
		int blocks;
		unsigned char *msg2;

		// Pre-processing: adding a single 1 bit
		blocks = 1 + (mlen + 8) / 64;
		msg2 = (unsigned char*)malloc(64 * blocks);
		memcpy(msg2, msg.c_str(), mlen);
		msg2[mlen] = (unsigned char)0x80;

		// Pre-processing: padding with zeros
		 for (size_t i = mlen + 1; i < 64 * blocks; ++i){
			msg2[i] = 0;
		 }


		MD5union u;
		u.w = 8 * mlen;
		memcpy(msg2 + 64 * blocks - 8, &u.w, 4);


		// Process the message in successive 512-bit chunks:
		int offset = 0;
		for (size_t block = 0; block < blocks; ++block){

			memcpy(mm.b, msg2 + offset, 64);

			unsigned a = h0;
			unsigned b = h1;
			unsigned c = h2;
			unsigned d = h3;
			unsigned temp, f;
			short g;

			//Main loop
			for (size_t i = 0; i<64; ++i) {

				if (i >= 0 && i < 16) {
					f = (b & c) | (~b & d);
					g = i;
				}
				if (i >= 16 && i < 32) {
					f = (d & b) | (~d & c);
					g = (5*i + 1) % 16;
				}
				if (i >= 32 && i < 48) {
					f = b ^ c ^ d;
					g = (3*i + 5) % 16;
				}
				if (i >= 48 && i < 64) {
					f = c ^ (b | ~d);
					g = (7*i) % 16;
				}

				temp = d;
				d = c;
				c = b;
				b = leftRotate(a + f + k[i] + mm.w[g], r[i]) + b;
				a = temp;


			}

			h0 += a;
			h1 += b;
			h2 += c;
			h3 += d;

			offset += 64;
		}

		//Concatenate h0, h1, h2 and h3
		std::string str = "0x";
		MD5union uu;
		for (int j = 0; j<4; ++j){
			if (j == 0) uu.w = h0;
			if (j == 1) uu.w = h1;
			if (j == 2) uu.w = h2;
			if (j == 3) uu.w = h3;
			char s[9];
			sprintf(s, "%02x%02x%02x%02x", uu.b[0], uu.b[1], uu.b[2], uu.b[3]);
			str += s;
		}
		
		return Key(str);
	}

}


