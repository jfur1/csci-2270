/*
John Furlong
CSCI 2270
Assignment 3
July 1, 2018
*/
#include "Communication.h"
#include <iostream>
#include <fstream>
using namespace std;

CommunicationNetwork::CommunicationNetwork(){

}

CommunicationNetwork::~CommunicationNetwork(){
	deleteNetwork(); // list is deleted within constructor to free memory.
	head = NULL;
	tail = NULL;
}

void CommunicationNetwork::addCity(string newCityName, string previousCityName){
	City *tmp = head;
	City *newCity = new City;
	newCity->cityName = newCityName; // Temporary City struct takes the name of user input


	if(previousCityName == "First"){ // User wants to set the new city as the head
		if(head == NULL){ // If the list is empty, the city is set as the head.
			City *newCity = new City(newCityName, NULL, NULL, "");
			head = newCity;
			return;
		}
		tmp->previous = newCity; // Setting the newCity node before the head
		newCity->next = tmp;
		head = newCity; // Assign newCity node to be the head.
	}
	else if(previousCityName == "Last"){ // User wants to add new city to the end of list
		if(head == NULL){ // If the list is empty, the city is set as the head.
			City *newCity = new City(newCityName, NULL, NULL, "");
			head = newCity;
			return;
		}
		else{
			while(tmp->next != NULL){
				tmp=tmp->next; // Iterate though the list to the tail
			}
			tmp->next = newCity; // Setting the newCity node after the tail.
			newCity->previous = tmp;
			tmp = newCity; // Setting the newCity node as the tail.
		}
	}
	else{
		bool found = false;
		if(tmp == NULL){
			cout << previousCityName << " not found." << endl;
			return;
		}
		while(tmp->next != NULL){
			if(tmp->cityName == previousCityName){ // If the previous city name entered by user is found in the list
				newCity->next = tmp->next; 
				newCity->previous = tmp;
				tmp->next->previous = newCity; // newCity node is placed between the previous city and the city following.
				tmp->next = newCity;
				found = true;
			}
			tmp = tmp->next;	
		}
		if(!found){ // If the previous city name entered by user is not found.
			cout << previousCityName << " not found." << endl;
		}

	}
}

void CommunicationNetwork::transmitMsg(char * filename){
	ifstream myfile;
	myfile.open(filename);
	string line;
	City *temp = head;
	if(temp == NULL){
		cout << "Empty List." << endl;
		return;
	}
	while(getline(myfile, line, ' ')){
		if(line.back() == '\n'){
			line.pop_back(); // Deletes last character in the string if it is a newline
		}
		City *tmp = head;
		tmp->message = line;
		if(tmp == NULL){
			cout << "Empty list" << endl; // If user tries transmitting a message through an empty list.
			break;
		}
		cout << tmp->cityName << " recieved " << tmp->message << endl;
		while(tmp->next != NULL){ 	// Traverses through the list to pass message along word by word.
			tmp->next->message = tmp->message;
			tmp->message = "";
			tmp = tmp->next;
			cout << tmp->cityName << " recieved " << tmp->message << endl;
		}
		cout << tmp->cityName << " recieved " << tmp->message << endl; // tail
		while(tmp->previous != NULL){ // Reverse traverses through list, tail to head.
			tmp->previous->message = tmp->message;
			tmp->message = "";
			tmp = tmp->previous;
			cout << tmp->cityName << " recieved " << tmp->message << endl;
		} 
	}
	myfile.close();
}


void CommunicationNetwork::printNetwork(){
	City* tmp = head;
	if(tmp == NULL){
		cout << "Empty list." << endl; // If user tries to print an empty list.
		return;
	}
	cout << "===CURRENT PATH===" << endl; 
	cout<< "NULL <- ";
	while(tmp->next != NULL){
		cout << tmp->cityName << " <-> ";
		tmp = tmp->next;
	}
	cout << tmp->cityName << " -> NULL" << endl;
	cout << "==================" << endl;
}

void CommunicationNetwork::buildNetwork(){
	string cities[10] = {"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis", "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};

	head = new City(cities[0], NULL, NULL, ""); // Initialize Los Angeles as head, so the rest can be initialized in a loop
	City *tmp = head;

	for(int i = 1; i < 10; i++){ // starts at 1 because Los Angeles is already initialized.
		City *newCity = new City(cities[i], NULL, tmp, ""); // create new City struct using constructor (name, *next, *previous, message)
		tmp->next = newCity;
		tmp = tmp->next;
	}
}

void CommunicationNetwork::deleteCity(string removeCity){
	City* tmp = head;

	if(tmp == NULL){
		cout << "Empty List" << endl;
		return;
	}

	while((tmp->cityName != removeCity) && (tmp->next != NULL)){ 
		tmp = tmp->next; // Iterates through list to find the city whose name matches the city the user wants to delete.
	}
	if(tmp->cityName == removeCity){ // City user wishes to delete matches the tmp city's name
		if(tmp->previous != NULL){ // If the match in the list follows an existing city
			tmp->previous->next = tmp->next; // city that will be deleted gets its previous pointers erased
		}
		else{
			head = tmp->next; // Otherwise, the match in the list must be the head.
		}
		if(tmp->next != NULL){ 
			tmp->next->previous = tmp->previous;  // city that will be deleted gets its next pointers erased
		}
		else{
			tail = tmp->previous; // Otherwise, the match in the list must be the tail.
		}
		delete tmp;
	}
	else{
		cout << removeCity << " was not found.\n"; // If city user entered to delete was not found
	}
}

void CommunicationNetwork::deleteNetwork(){
	City* tmp = head;
	if(tmp == NULL){
		cout << "List deleted." << endl; // If user attemps to delete an empty list.
		return;
	}
	while(tmp->next != NULL){
		tmp = tmp->next;
		cout << "Deleting " << tmp->previous->cityName << endl;
		delete tmp->previous;
	}
	cout << "Deleting " << tmp->cityName << endl; // tail
	delete tmp;
	head = NULL;
	tail = NULL;
}








