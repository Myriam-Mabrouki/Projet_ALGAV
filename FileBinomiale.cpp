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
			fb->AjoutMin(*it, *fb);
		}
		return fb;
	}

	FileBinomiale * TournoiBinomial::File (){
		FileBinomiale * fb = new FileBinomiale();
		fb->AjoutMin(*this, *fb);
		return fb;
	}

	bool FileBinomiale::EstVide(){
		return size == 0;
	}

	TournoiBinomial FileBinomiale::MinDeg(){
		if (size > 0) return tournois.back();
		return TournoiBinomial(); // @suppress("Ambiguous problem")
	}

	FileBinomiale FileBinomiale::Reste(FileBinomiale & F){
		if (F.size > 0) {
			F.size -= F.tournois.back().getSize();
			F.tournois.pop_back();
		}
		return F;
	}

	FileBinomiale FileBinomiale::AjoutMin(TournoiBinomial & T, FileBinomiale & F){
		F.tournois.push_back(T);
		F.size += T.getSize();
		return F;
	}

	FileBinomiale FileBinomiale::UFret(FileBinomiale & F1, FileBinomiale & F2, TournoiBinomial & T){
		if (T.EstVide()){
			if (F1.EstVide()){
				return F2;
			}
			if (F2.EstVide()){
				return F1;
			}

			TournoiBinomial T1 = F1.MinDeg();
			TournoiBinomial T2 = F2.MinDeg();

			if (T1.Degre() < T2.Degre()){
				FileBinomiale fb = Reste(F1);
				fb = UnionFile(fb, F2);
				return AjoutMin(T1, fb);
			}
			if (T1.Degre() > T2.Degre()){
				FileBinomiale fb = Reste(F2);
				fb = UnionFile(fb, F1);
				return AjoutMin(T2, fb);
			}
			if (T1.Degre() == T2.Degre()){
				FileBinomiale fb1 = Reste(F1);
				FileBinomiale fb2 = Reste(F2);
				TournoiBinomial tb_union = T1.Union2Tid(T2);
				return UFret(fb1, fb2, tb_union);
			}
		}

		else {
			if (F1.EstVide()){
				FileBinomiale * fb = T.File();
				return UnionFile(*fb, F2);
			}
			if (F2.EstVide()){
				FileBinomiale * fb = T.File();
				return UnionFile(*fb, F1);
			}

			TournoiBinomial T1 = F1.MinDeg();
			TournoiBinomial T2 = F2.MinDeg();

			if (T.Degre() < T1.Degre() && T.Degre() < T2.Degre()){
				FileBinomiale fb = UnionFile(F1, F2);
				return AjoutMin(T, fb);
			}

			if (T.Degre() == T1.Degre() && T.Degre() == T2.Degre()){
				FileBinomiale fb1 = Reste(F1);
				FileBinomiale fb2 = Reste(F2);
				TournoiBinomial tb_union = T1.Union2Tid(T2);
				FileBinomiale fb = UFret(fb1, fb2, tb_union);
				return AjoutMin(T, fb);
			}

			if (T.Degre() == T1.Degre() && T.Degre() < T2.Degre()){
				FileBinomiale fb1 = Reste(F1);
				TournoiBinomial tb_union = T1.Union2Tid(T2);
				return UFret(fb1, F2, tb_union);
			}

			if (T.Degre() < T1.Degre() && T.Degre() == T2.Degre()){
				FileBinomiale fb2 = Reste(F2);
				TournoiBinomial tb_union = T1.Union2Tid(T2);
				return UFret(fb2, F1, tb_union);
			}
		}

		return *this;
	}

	FileBinomiale FileBinomiale::UnionFile(FileBinomiale & F1, FileBinomiale & F2){
		TournoiBinomial vide = TournoiBinomial(); // @suppress("Ambiguous problem")
		return UFret(F1, F2, vide);
	}

	size_t FileBinomiale::getSize(){
		return size;
	}

}
