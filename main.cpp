#include "Key.hh"
#include "Heap_tree.hh"
#include "Heap_array.hh"
#include "FileBinomiale.hh"
#include "MD5.hh"
#include "BinarySearchTree.hh"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <unordered_set>
#include <filesystem>


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

vector<string> readStringsFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string line;
    std::vector<std::string> words;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return words;
    }

    // Read key from the file one by one
    while (file >> line) {
    	words.emplace_back(line);
    }

    file.close();

    return words;
}


int main(int argc, char ** argv) {

	if (argc != 2) {
		cerr << "Error wrong number of arguments: " << endl;
		return 1;
	}

	string file = argv[1];
	vector<Key> keys = readKeysFromFile(file);

	vector<Key> keys1;	
	for (size_t i=0; i<5; i++)  {
		keys1.push_back(keys[i]);
	}

	vector<Key> keys2;
	for (size_t i=5; i<20; i++)  {
		keys2.push_back(keys[i]);
	}


	/*cout << "========== TEST KEYS ==========" << endl;

	for (Key & k : keys){
		cout << k << endl;
	}

	for (size_t i = 0; i < keys.size()-1; ++i){
		if (keys[i].eg(keys[i+1])){
			cout << keys[i] << " = " << keys[i+1] << endl;
		}
		else if (keys[i].inf(keys[i+1])) {
			cout << keys[i] << " < " << keys[i+1] << endl;
		}
		else {
			cout << keys[i] << " > " << keys[i+1] << endl;
		}
	}*/


	
	/*cout << endl << "========== TEST HEAP_ARRAY ==========" << endl << endl;

	
	Heap_array h1 = Heap_array();
	h1.AjoutsIteratifs(keys1);
	cout << "h1 with the size of " << h1.getSize() << " : " << endl << h1 << endl << endl;

	Heap_array h2 = Heap_array();
	h2.Construction(keys2);
	cout << "h2 with the size of " << h2.getSize() << " : " << endl << h2 << endl << endl;

	h1.Union(h2);
	cout << "Union of h1 and h2 with the size of "<< h1.getSize() << " : " << endl << h1 << endl << endl;

	while (h1.getSize() != 0) {
		cout << "DELETE MIN : " << h1.SupprMin() << endl;
		cout << h1 << endl << endl;
	}*/



	cout << endl << "========== TEST HEAP_TREE ==========" << endl << endl;

	Heap_tree tt1 = Heap_tree();
	tt1.AjoutsIteratifs(keys1);
	cout << "tt1 with the size of " << tt1.getSize() << " : " << endl << tt1 << endl;

	/*Heap_tree tt2 = Heap_tree();
	tt2.Construction(keys2);
	cout << "tt2 with the size of " << tt2.getSize() << " : " << endl << tt2 << endl;*/

	while (tt1.getSize() != 0) {
		cout << "DELETE MIN : " << tt1.SupprMin() << endl;
		cout << tt1 << endl;
	}



	cout << endl << "========== TEST FILE_BINOMIALE ==========" << endl << endl;

	TournoiBinomial tb1 = TournoiBinomial(&keys[0]);
	TournoiBinomial tb2 = TournoiBinomial(&keys[1]);
	TournoiBinomial tb3 = TournoiBinomial(&keys[2]);
	TournoiBinomial tb4 = TournoiBinomial(&keys[3]);

	tb1.Union2Tid(tb1);
	tb1.Union2Tid(tb1);
	tb1.Union2Tid(tb1);
	tb2.Union2Tid(tb2);
	tb2.Union2Tid(tb2);
	tb3.Union2Tid(tb3);
	cout << "Size tb1 : " << tb1.getSize() << ", degré : " << tb1.Degre() << endl;
	cout << "Size tb2 : " << tb2.getSize() << ", degré : " << tb2.Degre() << endl;
	cout << "Size tb3 : " << tb3.getSize() << ", degré : " << tb3.Degre() << endl;
	cout << "Size tb4 : " << tb4.getSize() << ", degré : " << tb4.Degre() << endl << endl;

	FileBinomiale fb = tb1.Decapite();
	cout << "Decapitation de tb1 : " << fb << ", size : " << fb.getSize() << endl << endl;

	FileBinomiale fb1 = FileBinomiale();
	cout << "fb1 vide : " << fb1 << ", size : " << fb1.getSize()  << endl;
	fb1.AjoutMin(tb1);
	cout << "AjoutMin tb1 dans fb1 : " << fb1 << ", size : " << fb1.getSize() << endl;
	fb1.AjoutMin(tb2);
	cout << "AjoutMin tb2 dans fb1 : " << fb1 << ", size : " << fb1.getSize() << endl;
	fb1.AjoutMin(tb3);
	cout << "AjoutMin tb3 dans fb1 : " << fb1 << ", size : " << fb1.getSize() << endl;
	fb1.AjoutMin(tb4);
	cout << "AjoutMin tb4 dans fb1 : " << fb1 << ", size : " << fb1.getSize() << endl;
	TournoiBinomial tb_min = fb1.MinDeg();
	cout << "Tournoi de degre min de fb1, tb_min : Size : " << tb_min.getSize() << ", degré : " << tb_min.Degre() << endl;
	fb1.Reste();
	cout << "Supression of tb_min in fb1 : " << fb1 << ", size : " << fb1.getSize() << endl;
	fb1.Ajout(keys[0]);
	cout << "Add key in fb1 : " << fb1 << ", size : " << fb1.getSize() << endl << endl;

	TournoiBinomial tb5 = TournoiBinomial(&keys[4]);
	TournoiBinomial tb6 = TournoiBinomial(&keys[5]);
	TournoiBinomial tb7 = TournoiBinomial(&keys[6]);
	TournoiBinomial tb8 = TournoiBinomial(&keys[7]);
	tb5.Union2Tid(tb5);
	tb5.Union2Tid(tb5);
	tb5.Union2Tid(tb5);
	tb6.Union2Tid(tb6);
	tb6.Union2Tid(tb6);
	tb7.Union2Tid(tb7);
	FileBinomiale fb2 = FileBinomiale();
	fb2.AjoutMin(tb5);
	fb2.AjoutMin(tb6);
	fb2.AjoutMin(tb7);
	fb2.AjoutMin(tb8);
	cout << "fb2 : " << fb2 << ", size : " << fb2.getSize() << endl;
	fb1.UnionFile(fb2);
	cout << "Union of fb1 and fb2 : " << fb1 << ", size : " << fb1.getSize() << endl << endl;

	FileBinomiale fb3 = FileBinomiale();
	fb3.Construction(keys1);
	cout << "Construction : " << fb3 << ", size : " << fb3.getSize() << endl;
	while (!fb3.EstVide()) {
		cout << "Supression of min of fb3... " << endl;
		fb3.SupprMin();
		cout << "fb3 : " << fb3 << ", size : " << fb3.getSize() << endl;
	}


	cout << endl << "========== TEST MD5 ==========" << endl << endl;

	string md5_1 = MD5Hash("");
	string md5_2 = MD5Hash("The quick brown fox jumps over the lazy dog");
	string md5_3 = MD5Hash("The quick brown fox jumps over the lazy dog.");
	string md5_4 = MD5Hash("Et l’unique cordeau des trompettes marines");
	string md5_5 = MD5Hash("Et l’unique cordeau des trompettes marinEs");

	cout << md5_1 << endl << md5_2 << endl << md5_3 << endl << md5_4 << endl << md5_5 << endl;



	cout << endl << "========== TEST BINARY_SEARCH_TREE ==========" << endl << endl;

	BinarySearchTree bst1 = BinarySearchTree();

	for (Key & k : keys2) {
		bst1.Insert(k);
	}

	cout << "Size : " << bst1.getSize() << endl;
	cout << bst1 << endl << endl;



	cout << "Contruction of FileBinomiale of " << file << "..." << endl;
	FileBinomiale f = FileBinomiale();
	auto debut = chrono::high_resolution_clock::now();
	f.Construction(keys);
	auto fin = chrono::high_resolution_clock::now();
	auto duree = chrono::duration_cast<chrono::milliseconds>(fin - debut);
	cout << "Durée : " << duree.count() << " milliseconds" << endl;



	cout << endl << "========== MEASURING COMPLEXITIES ==========" << endl << endl;

	std::string path = "cles_alea/";
	std::string filename;

	int tab[] = {1000, 5000, 10000, 20000, 50000, 80000, 120000, 200000};

	/*cout << "Heap array..." << endl;
	std::ofstream file_heap_array("complexity_heap_array.txt");
	for (int i : tab) {

		float moyenne_ajout = 0;
		float moyenne_constr = 0;

		for (int j = 1; j <= 5; j++) {
			filename = chemin + "jeu_" + to_string(j) + "_nb_cles_" + to_string(i) + ".txt";
			cout << filename << "..." << endl;
			vector<Key> keys = readKeysFromFile(filename);

			Heap_array h1 = Heap_array();
			auto begin_ajout = chrono::high_resolution_clock::now();
			h1.AjoutsIteratifs(keys);
			auto end_ajout = chrono::high_resolution_clock::now();
			auto duree_ajout = chrono::duration_cast<chrono::milliseconds>(end_ajout - begin_ajout);

			Heap_array h2 = Heap_array();
			auto begin_constr = chrono::high_resolution_clock::now();
			h1.Construction(keys);
			auto end_constr = chrono::high_resolution_clock::now();
			auto duree_constr = chrono::duration_cast<chrono::milliseconds>(end_constr - begin_constr);

			moyenne_ajout += duree_ajout.count();
			moyenne_constr += duree_constr.count();
		}

		moyenne_ajout /= 5;
		moyenne_constr /= 5;
        file_heap_array << i << " " << moyenne_ajout << " " << moyenne_constr << endl;

    }*/


	/*cout << "Heap tree..." << endl;
	std::ofstream file_heap_tree("complexity_heap_tree.txt");
	for (int i : tab) {

		float moyenne_ajout = 0;
		float moyenne_constr = 0;

		for (int j = 1; j <= 5; j++) {
			filename = chemin + "jeu_" + to_string(j) + "_nb_cles_" + to_string(i) + ".txt";
			cout << filename << "..." << endl;
			vector<Key> keys = readKeysFromFile(filename);

			Heap_tree h1 = Heap_tree();
			auto begin_ajout = chrono::high_resolution_clock::now();
			h1.AjoutsIteratifs(keys);
			auto end_ajout = chrono::high_resolution_clock::now();
			auto duree_ajout = chrono::duration_cast<chrono::milliseconds>(end_ajout - begin_ajout);

			//Heap_tree h2 = Heap_tree();
			//auto begin_constr = chrono::high_resolution_clock::now();
			//h2.Construction(keys);
			//auto end_constr = chrono::high_resolution_clock::now();
			//auto duree_constr = chrono::duration_cast<chrono::milliseconds>(end_constr - begin_constr);

			moyenne_ajout += duree_ajout.count();
			//moyenne_constr += duree_constr.count();
		}

		moyenne_ajout /= 5;
		//moyenne_constr /= 5;
        file_heap_tree << i << " " << moyenne_ajout << " " << moyenne_constr << endl;

    }*/


	/*cout << "File Binomiale..." << endl;
	std::ofstream file_file_binomiale("complexity_file_binomiale.txt");
	for (int i : tab) {

		float moyenne = 0;

		for (int j = 1; j <= 5; j++) {
			filename = chemin + "jeu_" + to_string(j) + "_nb_cles_" + to_string(i) + ".txt";
			cout << filename << "..." << endl;
			vector<Key> keys = readKeysFromFile(filename);

			FileBinomiale f = FileBinomiale();
			auto begin = chrono::high_resolution_clock::now();
			f.Construction(keys);
			auto end = chrono::high_resolution_clock::now();
			auto duree = chrono::duration_cast<chrono::milliseconds>(end - begin);

			moyenne += duree.count();
		}

		moyenne /= 5;
        file_file_binomiale << i << " " << moyenne << endl;

    }*/

	cout << endl << "========== EXPERIMENTAL STUDY ==========" << endl << endl;

	path = "Shakespeare/";

	vector<vector<string>> shakespeare_works;

	//Browse Shakespeare directory
	for (const auto& file : filesystem::directory_iterator(path)){
		//Add all the words encountered in one book
		shakespeare_works.push_back(readStringsFromFile(file.path()));
	}

	vector<string> hash_shakespeare;
	unordered_set<string> words_shakespeare;
	for (auto v : shakespeare_works){
		for (string s : v){
			hash_shakespeare.push_back(MD5Hash(s));
			words_shakespeare.insert(s);
		}
	}


	vector<Key> hash_keys;
	for (string h : words_shakespeare){
		hash_keys.push_back(Key(h));
	}


//	BinarySearchTree BST_MD5 = BinarySearchTree();
//	for (Key k : hash_keys){
//		BST_MD5.Insert(k);
//	}

	return 0;

}
