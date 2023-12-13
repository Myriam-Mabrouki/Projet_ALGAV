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
#include <unordered_map>
#include <filesystem>
#include <random>
#include <set>


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

void generate_jeu(unsigned long long nb_cles) {
	random_device rd;
	uniform_int_distribution<unsigned long long> dist(0, numeric_limits<unsigned long long>::max());
	for (size_t i=1 ; i<=5; i++) {
		set<pair<unsigned long long, unsigned long long>> keys; // distinct keys
		string filename = "cles_alea/jeu_" + to_string(i) + "_nb_cles_" + to_string(nb_cles) + ".txt";
		cout << "Generating " << filename << "..." << endl;
		while (keys.size() < nb_cles) {
			keys.insert(make_pair(dist(rd), dist(rd)));
		}
		ofstream file(filename);
		for (const auto& key : keys) {
			file << "0x" << hex << key.first << key.second << "\n";
		}
		file.close();
	}
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


	cout << "========== TEST KEYS ==========" << endl;

	for (Key & k : keys1){
		cout << k << endl;
	}

	for (size_t i = 0; i < keys1.size()-1; ++i){
		if (keys1[i].eg(keys1[i+1])){
			cout << keys1[i] << " = " << keys1[i+1] << endl;
		}
		else if (keys1[i].inf(keys1[i+1])) {
			cout << keys1[i] << " < " << keys1[i+1] << endl;
		}
		else {
			cout << keys1[i] << " > " << keys1[i+1] << endl;
		}
	}


	
	cout << endl << "========== TEST HEAP_ARRAY ==========" << endl << endl;

	Heap_array ha1 = Heap_array();
	ha1.AjoutsIteratifs(keys1);
	cout << "ha1 with the size of " << ha1.getSize() << " : " << endl << ha1 << endl << endl;

	Heap_array ha2 = Heap_array();
	ha2.Construction(keys2);
	cout << "ha2 with the size of " << ha2.getSize() << " : " << endl << ha2 << endl << endl;

	ha1.Union(ha2);
	cout << "Union of ha1 and ha2 with the size of "<< ha1.getSize() << " : " << endl << ha1 << endl << endl;

	while (ha1.getSize() != 0) {
		cout << "DELETE MIN : " << ha1.SupprMin() << endl;
		cout << ha1 << endl << endl;
	}



	cout << endl << "========== TEST HEAP_TREE ==========" << endl << endl;

	Heap_tree ht1 = Heap_tree();
	ht1.Construction(keys1);
	cout << "ht1 with the size of " << ht1.getSize() << " : " << endl << ht1 << endl;

	Heap_tree ht2 = Heap_tree();
	ht2.Construction(keys2);
	cout << "ht2 with the size of " << ht2.getSize() << " : " << endl << ht2 << endl;

	ht1.Union(ht2);
	cout << "Union of ht1 and ht2 with the size of "<< ht1.getSize() << " : " << endl << ht1 << endl << endl;

	while (ht1.getSize() != 0) {
		cout << "DELETE MIN : " << *ht1.SupprMin() << endl;
		cout << ht1 << endl;
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
		bst1.Insert(k, "");
	}

	cout << "Size : " << bst1.getSize() << endl;
	cout << bst1 << endl << endl;



	cout << endl << "========== MEASURING COMPLEXITIES ==========" << endl << endl;

	// std::string path = "cles_alea/";
	// std::string filename;

	// int tab[] = {1000, 5000, 10000, 20000, 50000, 80000, 120000, 200000};//, 800000, 1600000};


	// /* --- Heap array --- */

	// cout << "Heap array..." << endl;
	// std::ofstream file_heap_array("complexity_heap_array.txt");
	// for (int i : tab) {

	// 	float moyenne_ajout = 0;
	// 	float moyenne_constr = 0;

	// 	for (int j = 1; j <= 5; j++) {
	// 		filename = path + "jeu_" + to_string(j) + "_nb_cles_" + to_string(i) + ".txt";
	// 		cout << filename << "..." << endl;
	// 		vector<Key> keys = readKeysFromFile(filename);

	// 		Heap_array h1 = Heap_array();
	// 		auto begin_ajout = chrono::high_resolution_clock::now();
	// 		h1.AjoutsIteratifs(keys);
	// 		auto end_ajout = chrono::high_resolution_clock::now();
	// 		auto duree_ajout = chrono::duration_cast<chrono::milliseconds>(end_ajout - begin_ajout);

	// 		Heap_array h2 = Heap_array();
	// 		auto begin_constr = chrono::high_resolution_clock::now();
	// 		h1.Construction(keys);
	// 		auto end_constr = chrono::high_resolution_clock::now();
	// 		auto duree_constr = chrono::duration_cast<chrono::milliseconds>(end_constr - begin_constr);

	// 		moyenne_ajout += duree_ajout.count();
	// 		moyenne_constr += duree_constr.count();
	// 	}

	// 	moyenne_ajout /= 5;
	// 	moyenne_constr /= 5;
    //     file_heap_array << i << " " << moyenne_ajout << " " << moyenne_constr << endl;

    // }

	// /* ---Heap Tree--- */

	// cout << "Heap tree..." << endl;
	// std::ofstream file_heap_tree("complexity_heap_tree.txt");
	// for (int i : tab) {

	// 	float moyenne_ajout = 0;
	// 	float moyenne_constr = 0;

	// 	for (int j = 1; j <= 5; j++) {
	// 		filename = path + "jeu_" + to_string(j) + "_nb_cles_" + to_string(i) + ".txt";
	// 		cout << filename << "..." << endl;
	// 		vector<Key> keys = readKeysFromFile(filename);

	// 		Heap_tree h1 = Heap_tree();
	// 		auto begin_ajout = chrono::high_resolution_clock::now();
	// 		h1.AjoutsIteratifs(keys);
	// 		auto end_ajout = chrono::high_resolution_clock::now();
	// 		auto duree_ajout = chrono::duration_cast<chrono::milliseconds>(end_ajout - begin_ajout);

	// 		Heap_tree h2 = Heap_tree();
	// 		auto begin_constr = chrono::high_resolution_clock::now();
	// 		h2.Construction(keys);
	// 		auto end_constr = chrono::high_resolution_clock::now();
	// 		auto duree_constr = chrono::duration_cast<chrono::milliseconds>(end_constr - begin_constr);

	// 		moyenne_ajout += duree_ajout.count();
	// 		moyenne_constr += duree_constr.count();
	// 	}

	// 	moyenne_ajout /= 5;
	// 	moyenne_constr /= 5;
    //     file_heap_tree << i << " " << moyenne_ajout << " " << moyenne_constr << endl;

    // }

	// /* ---File Binomiale--- */

	// cout << "File Binomiale..." << endl;
	// std::ofstream file_file_binomiale("complexity_file_binomiale.txt");
	// for (int i : tab) {

	// 	float moyenne = 0;

	// 	for (int j = 1; j <= 5; j++) {
	// 		filename = path + "jeu_" + to_string(j) + "_nb_cles_" + to_string(i) + ".txt";
	// 		cout << filename << "..." << endl;
	// 		vector<Key> keys = readKeysFromFile(filename);

	// 		FileBinomiale f = FileBinomiale();
	// 		auto begin = chrono::high_resolution_clock::now();
	// 		f.Construction(keys);
	// 		auto end = chrono::high_resolution_clock::now();
	// 		auto duree = chrono::duration_cast<chrono::milliseconds>(end - begin);

	// 		moyenne += duree.count();
	// 	}

	// 	moyenne /= 5;
    //     file_file_binomiale << i << " " << moyenne << endl;

    // }

	// //Union
	// cout << "Union Heap array..." << endl;
	// std::ofstream file_heap_array_union("complexity_heap_array_union.txt");
	// for (int i : tab) {

	// 	float moyenne_union = 0;

	// 	for (int j = 1; j <= 5; j++) {
	// 		std::string filename1 = path + "jeu_" + to_string(j) + "_nb_cles_" + to_string(i) + ".txt";
	// 		std::string filename2;
	// 		if (j == 5) {
	// 			filename2 = path + "jeu_1_nb_cles_" + to_string(i) + ".txt";
	// 		} else {
	// 			filename2 = path + "jeu_" + to_string(j+1) + "_nb_cles_" + to_string(i) + ".txt";
	// 		}
	// 		cout << "Union " << filename1 << " with " << filename2 << "..." << endl;
	// 		vector<Key> keys1 = readKeysFromFile(filename1);
	// 		vector<Key> keys2 = readKeysFromFile(filename2);

	// 		Heap_array h1 = Heap_array();
	// 		Heap_array h2 = Heap_array();
	// 		h1.Construction(keys1);
	// 		h2.Construction(keys2);
	// 		auto begin_union = chrono::high_resolution_clock::now();
	// 		h1.Union(h2);
	// 		auto end_union = chrono::high_resolution_clock::now();
	// 		auto duree_union = chrono::duration_cast<chrono::milliseconds>(end_union - begin_union);
	// 		moyenne_union += duree_union.count();
	// 	}

	// 	moyenne_union /= 5;
    //     file_heap_array_union << i+i << " " << moyenne_union << endl;

    // }

	// cout << "Union Heap tree..." << endl;
	// std::ofstream file_heap_tree_union("complexity_heap_tree_union.txt");
	// for (int i : tab) {

	// 	float moyenne_union = 0;

	// 	for (int j = 1; j <= 5; j++) {
	// 		std::string filename1 = path + "jeu_" + to_string(j) + "_nb_cles_" + to_string(i) + ".txt";
	// 		std::string filename2;
	// 		if (j == 5) {
	// 			filename2 = path + "jeu_1_nb_cles_" + to_string(i) + ".txt";
	// 		} else {
	// 			filename2 = path + "jeu_" + to_string(j+1) + "_nb_cles_" + to_string(i) + ".txt";
	// 		}
	// 		cout << "Union " << filename1 << " with " << filename2 << "..." << endl;
	// 		vector<Key> keys1 = readKeysFromFile(filename1);
	// 		vector<Key> keys2 = readKeysFromFile(filename2);

	// 		Heap_tree h1 = Heap_tree();
	// 		Heap_tree h2 = Heap_tree();
	// 		h1.Construction(keys1);
	// 		h2.Construction(keys2);
	// 		auto begin_union = chrono::high_resolution_clock::now();
	// 		h1.Union(h2);
	// 		auto end_union = chrono::high_resolution_clock::now();
	// 		auto duree_union = chrono::duration_cast<chrono::milliseconds>(end_union - begin_union);
	// 		moyenne_union += duree_union.count();
	// 	}

	// 	moyenne_union /= 5;
    //     file_heap_tree_union << i+i << " " << moyenne_union << endl;

    // }

	// cout << "Union File binomiale..." << endl;
	// std::ofstream file_file_union("complexity_file_binomiale_union.txt");
	// for (int i : tab) {

	// 	float moyenne_union = 0;

	// 	for (int j = 1; j <= 5; j++) {
	// 		std::string filename1 = path + "jeu_" + to_string(j) + "_nb_cles_" + to_string(i) + ".txt";
	// 		std::string filename2;
	// 		if (j == 5) {
	// 			filename2 = path + "jeu_1_nb_cles_" + to_string(i) + ".txt";
	// 		} else {
	// 			filename2 = path + "jeu_" + to_string(j+1) + "_nb_cles_" + to_string(i) + ".txt";
	// 		}
	// 		cout << "Union " << filename1 << " with " << filename2 << "..." << endl;
	// 		vector<Key> keys1 = readKeysFromFile(filename1);
	// 		vector<Key> keys2 = readKeysFromFile(filename2);

	// 		FileBinomiale f1 = FileBinomiale();
	// 		FileBinomiale f2 = FileBinomiale();
	// 		f1.Construction(keys1);
	// 		f2.Construction(keys2);
	// 		auto begin_union = chrono::high_resolution_clock::now();
	// 		f1.UnionFile(f2);
	// 		auto end_union = chrono::high_resolution_clock::now();
	// 		auto duree_union = chrono::duration_cast<chrono::milliseconds>(end_union - begin_union);
	// 		moyenne_union += duree_union.count();
	// 	}

	// 	moyenne_union /= 5;
    //     file_file_union << i+i << " " << moyenne_union << endl;

    // }



	cout << endl << "========== EXPERIMENTAL STUDY ==========" << endl << endl;

	string path = "Shakespeare/";

	vector<vector<string>> shakespeare_works;

	//Browse Shakespeare directory
	for (const auto& file : filesystem::directory_iterator(path)){
		
		//Add all the words encountered in one book
		shakespeare_works.push_back(readStringsFromFile(file.path()));
	}

	unordered_set<string> words_shakespeare;
	for (auto v : shakespeare_works){
		for (string s : v){
			words_shakespeare.insert(s);
		}
	}

	BinarySearchTree BST_MD5 = BinarySearchTree();
	unordered_set<string> collisions;
	vector<Key> hash_shakespeare;
	for (string v : words_shakespeare){
		hash_shakespeare.push_back(MD5Hash(v));
	}

	size_t i = 0;
	for (auto & v : words_shakespeare){
		if (!BST_MD5.Insert(hash_shakespeare[i], v)){ //Data already exists
			collisions.insert(v);
			collisions.insert(BST_MD5.Get(hash_shakespeare[i]));
		} 
		++i;
	};

	if (collisions.size() > 0) {
		cout << "L'ensemble des mots pour lesquels il existe des collisions sont les suivants : ";
		for (auto & e : collisions){
			cout << e << " ";
		}
		cout << "." << endl;
	}
	else {
		cout << "Il n'y a aucune collision." << endl;
	}
		


	//Question 6
	cout << "File Binomiale - Shakespeare" << endl;
	std::ofstream shakespeare_courbes("complexity_with_shakespeare.txt");
	FileBinomiale f = FileBinomiale();
	Heap_array ha = Heap_array();
	Heap_tree ht = Heap_tree();

	//Construction
	auto begin = chrono::high_resolution_clock::now();
	f.Construction(hash_shakespeare);
	auto end = chrono::high_resolution_clock::now();
	auto duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << "Construction: " << duree.count();
	begin = chrono::high_resolution_clock::now();
	ha.Construction(hash_shakespeare);
	end = chrono::high_resolution_clock::now();
	duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << " " << duree.count();
	begin = chrono::high_resolution_clock::now();
	ht.Construction(hash_shakespeare);
	end = chrono::high_resolution_clock::now();
	duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << " " << duree.count() << endl;

	//Union
	FileBinomiale f1 = FileBinomiale();
	Heap_array ha_1 = Heap_array();
	Heap_tree ht_1 = Heap_tree();

	FileBinomiale f2 = FileBinomiale();
	Heap_array ha_2 = Heap_array();
	Heap_tree ht_2 = Heap_tree();

	vector<Key> tmp1, tmp2;
	tmp1.reserve(hash_shakespeare.size());
	tmp2.reserve(hash_shakespeare.size());
	for(size_t j = 0; j < hash_shakespeare.size()/2; ++j){
		tmp1.emplace_back(hash_shakespeare[j]);
	}
	for(size_t j = hash_shakespeare.size()/2; j < hash_shakespeare.size(); ++j){
		tmp2.emplace_back(hash_shakespeare[j]);
	}
	f1.Construction(tmp1);
	f2.Construction(tmp2);
	ha_1.Construction(tmp1);
	ha_2.Construction(tmp2);
	ht_1.Construction(tmp1);
	ht_2.Construction(tmp2);

	begin = chrono::high_resolution_clock::now();
	f1.UnionFile(f2);
	end = chrono::high_resolution_clock::now();
	duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << "Union: " << duree.count();
	begin = chrono::high_resolution_clock::now();
	ha_1.Union(ha_2);
	end = chrono::high_resolution_clock::now();
	duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << " " << duree.count();
	begin = chrono::high_resolution_clock::now();
	ht_1.Union(ht_2);
	end = chrono::high_resolution_clock::now();
	duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << " " << duree.count() << endl;

	//Ajout
	begin = chrono::high_resolution_clock::now();
	f.Ajout(keys[0]);
	end = chrono::high_resolution_clock::now();
	duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << "Ajout: " << duree.count();
	begin = chrono::high_resolution_clock::now();
	ha.Ajout(keys[0]);
	end = chrono::high_resolution_clock::now();
	duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << " " << duree.count();
	begin = chrono::high_resolution_clock::now();
	ht.Ajout(keys[0]);
	end = chrono::high_resolution_clock::now();
	duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << " " << duree.count() << endl;

	//SupprMin
	begin = chrono::high_resolution_clock::now();
	f.SupprMin();
	end = chrono::high_resolution_clock::now();
	duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << "SupprMin: " << duree.count();
	begin = chrono::high_resolution_clock::now();
	ha.SupprMin();
	end = chrono::high_resolution_clock::now();
	duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << " " << duree.count();
	begin = chrono::high_resolution_clock::now();
	ht.SupprMin();
	end = chrono::high_resolution_clock::now();
	duree = chrono::duration_cast<chrono::milliseconds>(end - begin);
	shakespeare_courbes << " " << duree.count() << endl;

	return 0;

}
