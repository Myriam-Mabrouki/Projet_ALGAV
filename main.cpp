#include "Key.hh"
#include "Heap.hh"
#include "FileBinomiale.hh"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace algav;
using namespace std;


vector<Key> readKeysFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string line;
    std::vector<Key> keys;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return keys;
    }

    // Read key from the file one by one
    while (file >> line) {
    	keys.emplace_back(line);
    }

    file.close();

    return keys;
}

int main(int argc, char ** argv) {

	if (argc != 2) {
		cerr << "Error wrong number of arguments: " << endl;
		return 1;
	}

	string filename = argv[1];
	vector<Key> keys = readKeysFromFile(filename);

//	for (Key & k : keys){
//		cout << k << endl;
//	}
//
//	for (size_t i = 0; i < keys.size()-1; ++i){
//		if (keys[i].eg(keys[i+1])){
//			cout << keys[i] << " = " << keys[i+1] << endl;
//		}
//		else if (keys[i].inf(keys[i+1])) {
//			cout << keys[i] << " < " << keys[i+1] << endl;
//		}
//		else {
//			cout << keys[i] << " > " << keys[i+1] << endl;
//		}
//	}

	Heap h = Heap();
//	h.Ajout(keys[0]);
//	h.Ajout(keys[1]);
//	h.Ajout(keys[2]);
//	h.Ajout(keys[3]);
//	h.Ajout(keys[4]);
//	h.Ajout(keys[5]);
//	cout << h << endl;
//	h.SupprMin();
//	cout << h << endl;
//	h.SupprMin();
//	cout << h << endl;
//	h.SupprMin();
//	cout << h << endl;
//	h.SupprMin();
//	cout << h << endl;
//	h.SupprMin();
//	cout << h << endl;
//	h.SupprMin();

	h.AjoutsIteratifs(keys);
	//cout << h.getSize() << endl;

	TournoiBinomial tb0 = TournoiBinomial(); // @suppress("Ambiguous problem")

	if (tb0.EstVide()){
		cout << "le tournoi tb0 est vide" << endl;
	}
	else {
		cout << "ERR  : le tournoi tb0 n'est pas vide" << endl;
	}

	Key k1 = Key("0xdf6943ba6d51464f6b02157933bdd9ad");

	TournoiBinomial tb1 = TournoiBinomial(&keys[0]);
	TournoiBinomial tb2 = TournoiBinomial(&keys[1]);

	cout << "size tb1 : " << tb1.getSize() << endl;
	cout << "size tb2 : " << tb2.getSize() << endl;

	tb2 = tb2.Union2Tid(tb1);

	cout << "size tb2 : " << tb2.getSize() << ", degré : " << tb2.Degre() << endl;

	FileBinomiale fb = FileBinomiale();

	if (fb.EstVide()){
		cout << "la file fb est vide" << endl;
	}
	else {
		cout << "ERR  : la file fb n'est pas vide" << endl;
	}

	fb.AjoutMin(tb2);
	cout << "size fb : " << fb.getSize() << endl;
	fb.AjoutMin(tb1);
	cout << "size fb : " << fb.getSize() << endl;

	TournoiBinomial tb3 = TournoiBinomial(&keys[2]);
	TournoiBinomial tb4 = TournoiBinomial(&keys[3]);
	tb3 = tb3.Union2Tid(tb4);
	tb3 = tb3.Union2Tid(tb2);

	cout << "test" << endl;
	FileBinomiale * fb2 = tb3.Decapite();
	cout << "size fb2 : " << fb2->getSize() << endl;

	TournoiBinomial tb_min = fb2->MinDeg();
	cout << "size tb_min : " << tb_min.getSize() << endl;


	FileBinomiale tb_reste = fb2->Reste();
	cout << "size tb_reste : " << tb_reste.getSize() << endl;

//	FileBinomiale fb1 = FileBinomiale();
//	fb1.AjoutMin(tb3);
//	cout << "size fb : " << fb1.getSize() << endl;
//	fb1.AjoutMin(tb2);
//	cout << "size fb : " << fb1.getSize() << endl;
//	fb1.AjoutMin(tb1);
//	cout << "size fb : " << fb1.getSize() << endl;

	return 0;

}
