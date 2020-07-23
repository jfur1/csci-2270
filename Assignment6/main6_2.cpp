/*
John Furlong
CSCI 2270
July 27th 2018
*/
#include "graph6_2.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]){
	
	ifstream myfile(argv[1]);
	string line, cityname, weight, city;
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
	while(option != 5){
		cout << "======Main Menu======" << endl; 
		cout << "1. Print vertices" << endl;
		cout << "2. Find districts" << endl;
		cout << "3. Find shortest path" << endl;
		cout << "4. Find shortest weighted path" << endl; 
		cout << "5. Quit" << endl;
		cin >> option;
		cin.clear();
		cin.ignore();

		if(option == 1){
			g.displayEdges();
		}
		else if(option == 2){
			g.assignDistricts();
		}
		else if(option == 3){
			string start, end;
			cout << "Enter a starting city:" << endl; 
			getline(cin, start);
			cout << "Enter an ending city:" << endl;
			getline(cin, end);
			g.shortestPath(start, end);
		}
		else if(option == 4){
			string start, end;
			cout << "Enter a starting city:" << endl; 
			getline(cin, start);
			cout << "Enter an ending city:" << endl;
			getline(cin, end);
			g.shortestWeightedPath(start, end);
		}
		else {
			cout << "Goodbye!" << endl;
			break;
		}
	}

	return 0;
}