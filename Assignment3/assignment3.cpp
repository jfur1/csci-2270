/*
John Furlong
CSCI 2270
Assignment 3
July 1, 2018
*/
#include <iostream>
#include "Communication.h"
using namespace std;

int main(int argc, char* argv[]){
	CommunicationNetwork network;
	int option;
	while(option != 7){ // loops until user enters a 7
		cout << "======Main Menu======" << endl;
		cout << "1. Build Network" << endl;
		cout << "2. Print Network Path" << endl;
		cout << "3. Transmit Message Coast-To-Coast-To-Coast" << endl;
		cout << "4. Add City" << endl;
		cout << "5. Delete City" << endl;
		cout << "6. Clear Network" << endl; 
		cout << "7. Quit" << endl;
		cin >> option;
		cin.clear(); // Fixes issues with getline used later
		cin.ignore();
		if(option == 1){
			network.buildNetwork();
		}
		else if(option == 2){
			network.printNetwork();
		}
		else if(option == 3){
			network.transmitMsg(argv[1]); // second command line argument given as file to read in from.
		}
		else if(option == 4){
			string nCity, prevCity;
			cout << "Enter new city name: " << endl;
			getline(cin, nCity); // use getline to account for cities that contain a space
			cout << "Enter a previous city name: " << endl;
			getline(cin, prevCity);
			if(prevCity.empty()){ // If the user enters nothing for previous city, the new city gets added to tail.
				prevCity = "Last";
			}
			network.addCity(nCity, prevCity);
		}
		
		else if(option == 5){
			string dCity;
			cout << "Enter a city name: " << endl;
			getline(cin, dCity);
			network.deleteCity(dCity);
		}
		else if(option == 6){
			network.deleteNetwork();
		}
		else if(option == 7){
			cout << "Goodbye!\n";
			break;
		}
		else{
			cout << "Enter a valid number." << endl; // If a user does not enter a number 1-7.
			continue;
		}
	}
return 0;
}