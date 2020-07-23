/*
John Furlong
CSCI 2270
Assignment 4
July 8 2018
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.hpp"
using namespace std;

int main(int argc, char* argv[1]){
	ifstream myfile;
	myfile.open(argv[1]);

	MovieTree Movies;
	string title, word, line;
	char ch;
	int rank, year, quantity, option, count = 0;

	if(myfile.is_open()){
		while(getline(myfile, line)){
			stringstream ss(line);
			getline(ss, word, ',');
			istringstream(word) >> rank;
			getline(ss, word, ',');
			title = word;
			getline(ss, word, ',');
			istringstream(word) >> year;
			getline(ss, word, ',');
			istringstream(word) >> quantity;
			Movies.addMovieNode(rank, title, year, quantity);
			ss.clear();
		}

	}
	else{
		cout << "Could not open the file." << endl;
		return 0;
	}
		while(option != 6){
			string name = "";
			cout << "======Main Menu======" << endl; 
			cout << "1. Find a movie" << endl;
			cout << "2. Rent a movie" << endl;
			cout << "3. Print the inventory" << endl; 
			cout << "4. Delete a movie" << endl; 
			cout << "5. Count the movies" << endl; 
			cout << "6. Quit" << endl;
			cin >> option;
			cin.clear();
			cin.ignore();

			if(option == 1){
				cout << "Enter title: " << endl;
				getline(cin, name);
				Movies.findMovie(name);
			}
			else if(option == 2){
				cout << "Enter title: " << endl;
				getline(cin, name);
				Movies.rentMovie(name);
			}
			else if(option == 3){
				Movies.printMovieInventory();
			}
			else if(option == 4){
				cout << "Enter title: " << endl;
				getline(cin, title);
				Movies.deleteMovieNode(title);
			}
			else if(option == 5){
				cout << "Tree contains: " << Movies.countMovieNodes() << " movies." << endl;
			}
			else if(option == 6){
				cout << "Goodbye!" << endl;
				break;
			}
			else if(option > 6 || option < 1){
				cout << "Enter a valid number.\n";
			}
		}
		myfile.close();
	return 0;
}



