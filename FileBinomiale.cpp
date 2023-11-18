#include "FileBinomiale.hh"
#include <vector>

namespace algav {

	bool TournoiBinomial::EstVide(){
		return size == 0;
	}

	size_t TournoiBinomial::Degre(){
		return children.size();
	}

	size_t TournoiBinomial::getSize(){
		return size;
	}

	TournoiBinomial & TournoiBinomial::Union2Tid (TournoiBinomial & T){
		if (value->inf(*(T.value))){
			children.push_back(T);
			size += T.size;
			return *this;
		}
		else {
			T.children.push_back(T);
			T.size += size;
			return T;
		}
	}

	FileBinomiale * TournoiBinomial::Decapite (){
		FileBinomiale * fb = new FileBinomiale();
		for (auto it = children.rbegin(); it != children.rend(); ++it){
			fb->AjoutMin(*it);
		}
		return fb;
	}

	bool FileBinomiale::EstVide(){
		return size == 0;
	}

	TournoiBinomial FileBinomiale::MinDeg(){
		if (size > 0) return tournois.back();
		return TournoiBinomial(); // @suppress("Ambiguous problem")
	}

	FileBinomiale FileBinomiale::Reste(){
		if (size > 0) {
			size -= tournois.back().getSize();
			tournois.pop_back();
			return *this;
		}
		else return FileBinomiale();
	}

	FileBinomiale FileBinomiale::AjoutMin(TournoiBinomial & T){
		tournois.push_back(T);
		size += T.getSize();
		return *this;
	}

	size_t FileBinomiale::getSize(){
		return size;
	}

}
