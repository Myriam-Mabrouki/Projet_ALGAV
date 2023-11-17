#include "Key.hh"
#include "Heap.hh"
//#include "TournoiBinomial.hh"
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
	}

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
	cout << h.getSize() << endl;
	return 0;

}
