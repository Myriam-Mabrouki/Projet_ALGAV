#pragma once

#include "Key.hh"
#include <vector>
#include <cmath>

namespace algav {

	class FileBinomiale;


	class TournoiBinomial {
	private:
		Key * value;
		std::vector<TournoiBinomial> children;
		size_t size;

	public:
		TournoiBinomial():value(nullptr),size(0){}

		TournoiBinomial(Key * value):value(value),size(1){}

		bool EstVide();

		size_t Degre();

		TournoiBinomial & Union2Tid (TournoiBinomial & T);

		FileBinomiale * Decapite ();

		FileBinomiale * File ();

		size_t getSize();

		size_t getSize2 () const;

	};

	class FileBinomiale {
	private:
		std::vector<TournoiBinomial> tournois;
		size_t size;

	public:
		FileBinomiale():size(0){}

		bool EstVide();

		TournoiBinomial MinDeg();

		FileBinomiale Reste(FileBinomiale & F);

		FileBinomiale AjoutMin(TournoiBinomial & T);

		FileBinomiale UFret(FileBinomiale & F1, FileBinomiale & F2, TournoiBinomial & T);

		FileBinomiale UnionFile(FileBinomiale & F1, FileBinomiale & F2);

		FileBinomiale Ajout(Key & k);

		FileBinomiale Construction(std::vector<Key> keys);

		size_t getSize();

		friend std::ostream & operator << (std::ostream & os, const FileBinomiale & F){
			os << "<";
			for (auto & t : F.tournois){
				os << std::log2(t.getSize2()) << ", ";
			}
			os << ">";
			return os;
		}

	};

}
