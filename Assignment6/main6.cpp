/*
John Furlong
CSCI 2270
Assignment 6 Part 1
July 20, 2018
*/

#include "graph6.h"
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]){

	ifstream myfile(argv[1]);
	string line, cityname, weight, city, word;
	int w;
	string tmp[16];

	Graph g;

	getline(myfile, line);
	stringstream ss(line);


	for(int i = 0; i < 16; i++){
		getline(ss, cityname, ',');
		if(i == 0){
			continue;
		}
		tmp[i] = cityname;	// stores city names in tmp array since vertices vector is private
		g.addVertex(cityname); // Each city name gets added as a vertex
	}

	while(getline(myfile, line)){
		stringstream s(line);
		for(int i = 0; i < 17; i++){
			getline(s, weight, ',');
			if(i == 0){ // city name
				city = weight;
				// cout << "City: " << city<< endl;
			}
			if(weight == "-1" || weight == "0"){  // Blocked by "zombies" or path to itself
				continue;
			}
			else{
				istringstream(weight) >> w;	// string -> int
				g.addEdge(city, tmp[i], w);	// Edge created between current city and adjacent city
			}
		}
	}

	int option;
	while(option != 3){
		cout << "======Main Menu======" << endl; 
		cout << "1. Print vertices" << endl;
		cout << "2. Vertex adjacent" << endl;
		cout << "3. Quit" << endl;
		cin >> option;
		cin.clear();
		cin.ignore();	// Resolved errors with "getline(cin, tmp)"

		if(option == 1){
			g.displayEdges();
		}
		else if(option == 2){
			string city1, city2;
			cout << "Enter first city:" << endl; 
			getline(cin, city1);
			cout << "Enter second city:" << endl;
			getline(cin, city2);
			int z = g.isAdjacent(city1, city2);
			if(z == 1){
				cout << "True" << endl;
			}
			else{
				cout << "False" << endl;
			}
		}
		else if(option == 3){
			cout << "Goodbye!" << endl;
			break;
		}
		else if(option < 1 || option > 3){
			cout << "Enter a valid number." << endl;
		}

	}

	return 0;
}