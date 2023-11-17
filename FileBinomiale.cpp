#include "FileBinomiale.hh"
#include <vector>

namespace algav {

	bool TournoiBinomial::EstVide(){
		return size == 0;
	}

	bool TournoiBinomial::Degre(){
		return children.size();
	}

	TournoiBinomial & TournoiBinomial::Union2Tid (TournoiBinomial & T1, const TournoiBinomial & T2){
		T1.children.push_back(T2);
		return T1;
	}

	FileBinomiale * TournoiBinomial::Decapite (){
		FileBinomiale * fb = new FileBinomiale();
//			for (TournoiBinomial & t : children){
//				//fb->AjoutMin(t);
//			}
		return fb;
	}

	bool FileBinomiale::EstVide(){
		return size == 0;
	}

	TournoiBinomial FileBinomiale::MinDeg(){
		return tournois[size-1];
	}

	FileBinomiale FileBinomiale::Reste(){
		tournois.pop_back();
		return *this;
	}

	void FileBinomiale::AjoutMin(TournoiBinomial & T){

	}

}
