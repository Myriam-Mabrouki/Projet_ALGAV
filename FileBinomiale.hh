#pragma once

#include "Key.hh"
//#include "TournoiBinomial.hh"
#include <vector>

namespace algav {

	class FileBinomiale;

	class TournoiBinomial {
	private:
		//Key root; //TODO init ???
		std::vector<TournoiBinomial> children;
		size_t size;

	public:
		TournoiBinomial():size(0){}

		bool EstVide();

		bool Degre();

		TournoiBinomial & Union2Tid (TournoiBinomial & T1, const TournoiBinomial & T2);

		FileBinomiale * Decapite ();

	};

	class FileBinomiale {
	private:
		std::vector<TournoiBinomial> tournois;
		size_t size;

	public:
		FileBinomiale():size(0){}

		bool EstVide();

		TournoiBinomial MinDeg();

		FileBinomiale Reste();

		void AjoutMin(TournoiBinomial & T);


	};

}
