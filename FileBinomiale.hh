#pragma once

#include "Key.hh"
#include <vector>
#include <list>
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

		void Union2Tid (TournoiBinomial & T);

		FileBinomiale Decapite ();

		FileBinomiale File ();

		size_t getSize();

		size_t getSize () const;

		Key * getValue (){
			return value;
		}

	};

	class FileBinomiale {
	private:
		std::vector<TournoiBinomial> tournois;
		size_t size;

	public:
		FileBinomiale():size(0){}

		bool EstVide();

		TournoiBinomial MinDeg();

		void Reste();

		void AjoutMin(TournoiBinomial & T);

		void SupprMin();

		FileBinomiale UFret(FileBinomiale & F, TournoiBinomial & T);

		void UnionFile(FileBinomiale & F);

		void Ajout(Key & k);

		void Construction(std::vector<Key> & keys);

		size_t getSize();

		friend std::ostream & operator << (std::ostream & os, const FileBinomiale & F){
			os << "<";
			for (size_t i = 0; i < F.tournois.size(); ++i){
				os << "TB" << std::log2(F.tournois[i].getSize());
				if (i != F.tournois.size()-1) os << ", ";
			}
			os << ">";
			return os;
		}

		void Reserve(size_t length);


	};

}
