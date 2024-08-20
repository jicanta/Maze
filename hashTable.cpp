// basic hash table in c++
// with separate chaining (using linked lists to deal with collisions)
// key-value pairs: 123, nacho

#include <iostream>
#include <list>
#include <cstring>
#include <cassert>

using namespace std;

class HashTable {
	private:
		static const int hashGroups = 10;
		list<pair<int, string>> table[hashGroups];
		
	public:
		bool isEmpty() const;
		int hashFunc(int key);
		void insert(int key, string value);
		void remove(int key);
		string search(int key);
		void printTable();
};

bool HashTable::isEmpty() const {
	bool isEmpty = true;
	for (int i = 0; i < hashGroups; i++) {
		isEmpty ^= (int(table[i].size()) != 0);
	}
	return isEmpty;
}

int HashTable::hashFunc(int key) {
	return key % hashGroups;
}

void HashTable::insert(int key, string value) {
	int hashKey = hashFunc(key);
	auto& cell = table[hashKey];
	auto beginIt = begin(cell);
	
	bool keyExists = false; // if the key exists, I replace it with this new val
	for (; beginIt != end(cell); beginIt++) {
		if (beginIt->first == key) {
			keyExists = true;
			beginIt->second = value;
			cout << "[WARNING] Key exists. Value has been replaced" << endl;
			break;
		}
	}
	
	if (!keyExists) {
		cell.emplace_back(key, value);
	}
	
	return;
}

void HashTable::remove(int key) {
	int hashKey = hashFunc(key);
	auto& cell = table[hashKey];
	auto beginIt = begin(cell);
	
	bool keyExists = false;
	for (; beginIt != end(cell); beginIt++) {
		if (beginIt->first == key) {
			keyExists = true;
			beginIt = cell.erase(beginIt);
			cout << "[INFO] Element removed." << endl;
			break;
		}
	}
	
	if (!keyExists) {
		cout << "[WARNING] Element not found. Pair not removed." << endl;
	}
	
	return;
}

void HashTable::printTable() {
	for (int i = 0; i < hashGroups; i++) {
		if (int(table[i].size()) == 0) continue;
		
		auto beginIt = begin(table[i]);
		for (; beginIt != end(table[i]); beginIt++) {
			cout << "[INFO] Key: " << beginIt->first << " Value: " << beginIt->second << endl;
		}
	}
	return;
}

int main() {
	HashTable HT;
	
	assert(HT.isEmpty());
	
	HT.insert(123456, "Nacho");
	HT.insert(123443, "Pedro");
	HT.insert(733452, "Crash");
	HT.insert(923451, "Spyro");
	HT.insert(123454, "Max");
	HT.insert(123455, "Drake");
	HT.insert(123455, "Ekard");
	
	HT.printTable();
	
	HT.remove(123454);
	HT.remove(100);
	
	assert(!HT.isEmpty());
	
	HT.printTable();
	
	return 0;
}
