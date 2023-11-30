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

	size_t TournoiBinomial::getSize2() const{
		return size;
	}

	void TournoiBinomial::Union2Tid (TournoiBinomial & T){
		if (value->inf(*(T.value))){
			children.push_back(T);
			size += T.size;
		}
		else {
			T.children.push_back(*this);
			T.size += size;
			*this = T;
		}
	}

	FileBinomiale * TournoiBinomial::Decapite (){
		FileBinomiale * fb = new FileBinomiale();
		for (auto it = children.rbegin(); it != children.rend(); ++it){
			fb->AjoutMin(*it);
		}
		return fb;
	}

	FileBinomiale * TournoiBinomial::File (){
		FileBinomiale * fb = new FileBinomiale();
		fb->AjoutMin(*this);
		return fb;
	}

	bool FileBinomiale::EstVide(){
		return size == 0;
	}

	TournoiBinomial FileBinomiale::MinDeg(){
		if (size > 0) return tournois.back();
		return TournoiBinomial(); // @suppress("Ambiguous problem")
	}

	void FileBinomiale::Reste(){
		if (size > 0) {
			size -= tournois.back().getSize();
			tournois.pop_back();
		}
	}

	void FileBinomiale::AjoutMin(TournoiBinomial & T){
		tournois.push_back(T);
		size += T.getSize();
	}

	void FileBinomiale::SupprMin(){

		//Search of the minimum key value
		size_t pos = 0;
		for (size_t i = 1; i < tournois.size(); ++i){
			if ((tournois[i].getValue())->inf(*tournois[pos].getValue())){
				pos = i;
			}
		}

		FileBinomiale * F = tournois[pos].Decapite();
		std::cout << *F << std::endl;

		//Rebuilt the FileBinomiale without the TournoiBinomial at position pos
		std::vector<TournoiBinomial> new_tournois;
		for (size_t i = 1; i < tournois.size(); ++i){
			if (i != pos) new_tournois.push_back(tournois[i]);
		}

		tournois = new_tournois;

		//UnionFile(*F); 	//TODO ça marche pas pcq qd on appelle la fonction y a plus rien dans l'arg
		TournoiBinomial vide = TournoiBinomial(); // @suppress("Ambiguous problem")
		*this = UFret(*F, vide);
	}

	FileBinomiale & FileBinomiale::UFret(FileBinomiale & F, TournoiBinomial & T){
		if (T.EstVide()){
			if (EstVide()){
				return F;
			}
			if (F.EstVide()){
				return *this;
			}

			TournoiBinomial T1 = MinDeg();
			TournoiBinomial T2 = F.MinDeg();

			if (T1.Degre() < T2.Degre()){
				Reste();
				UnionFile(F);
				AjoutMin(T1);
				return *this;
			}
			else if (T1.Degre() > T2.Degre()){
				F.Reste();
				F.UnionFile(*this);
				F.AjoutMin(T2);
				return F;
			}
			else if (T1.Degre() == T2.Degre()){
				Reste();
				F.Reste();
				T1.Union2Tid(T2);
				return UFret(F, T1);
			}
		}

		else {
			if (EstVide()){
				FileBinomiale * fb = T.File();
				fb->UnionFile(F);
				return *fb;
			}
			if (F.EstVide()){
				FileBinomiale * fb = T.File();
				fb->UnionFile(*this);
				return *fb;
			}

			TournoiBinomial T1 = MinDeg();
			TournoiBinomial T2 = F.MinDeg();

			if (T.Degre() < T1.Degre() && T.Degre() < T2.Degre()){
				UnionFile(F);
				AjoutMin(T);
				return *this;
			}

			else if (T.Degre() == T1.Degre() && T.Degre() == T2.Degre()){
				Reste();
				F.Reste();
				T1.Union2Tid(T2);
				FileBinomiale & fb = UFret(F, T1);
				fb.AjoutMin(T);
				return fb;
			}

			else if (T.Degre() == T1.Degre() && T.Degre() < T2.Degre()){
				Reste();
				T1.Union2Tid(T2);
				return UFret(F, T1);
			}

			else if (T.Degre() < T1.Degre() && T.Degre() == T2.Degre()){
				F.Reste();
				T1.Union2Tid(T2);
				return F.UFret(*this, T1);
			}
		}
		return *this;
	}

	void FileBinomiale::UnionFile(FileBinomiale & F){
		TournoiBinomial vide = TournoiBinomial(); // @suppress("Ambiguous problem")
		*this = UFret(F, vide);
	}

	void FileBinomiale::Ajout(Key & k){
		TournoiBinomial t = TournoiBinomial(&k);
		FileBinomiale * fb = t.File();
		UnionFile(*fb);
	}

	void FileBinomiale::Construction(std::vector<Key> & keys){
		for (Key & k : keys){
			Ajout(k);
		}
	}

	size_t FileBinomiale::getSize(){
		return size;
	}


}
