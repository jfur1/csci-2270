/*
Assignment 1
John Furlong
CSCI 2270
*/
#include <iostream>
#include <fstream>

using namespace std;

struct market{
	string type;
	string buyorsell;
	int price;
}available[100];

void parse(string line, string temp[3]){ // Separates each piece of info from about an item from a line into a temporary array
	string word;
	for(int i = 0; i <= line.length()-1; i++){ // Traverses through the line, looking for a comma
		if(line[i] == ','){ 
			if(word == "chicken" || word == "truck" || word == "dresser" || word == "microwave" || word == "bike"){
				temp[0] = word; // 1st spot in array stores the type of item trying to be listed
				word = "";
			}
			else if(word == " for sale" || word == " wanted"){
				temp[1] = word.substr(1, word.length()); // 2nd spot in temporary array stores the item's listing status (i.e "for sale")
				word = "";
			}
		}
		else // "word" continues adding characters to itself from the line until a comma is found
			word += line[i];
	}
	temp[2] = word.substr(1, word.length()); // After the line is traversed, the 3rd spot in the temp array hold the item's price
}

void deleter(market available[100], int index){ // Function deletes element in a given array starting at a given index, both given as parameters
	int numElements = 100;
	for(int i = index; i < numElements-2; i++){ 
		available[i].type = available[i+1].type;
		available[i].buyorsell = available[i+1].buyorsell;
		available[i].price = available[i+1].price;
	}
	numElements = numElements - 1;
}

bool sort(string temp[3], market available[100], int count){ // Determines if a new item has any matches that already exist in "available" array
	for(int i = 0; i < count; i++){ // Loops through "available" searching for matching item type
		if(temp[0] == available[i].type && temp[1] != available[i].buyorsell){ // If item types match AND the two items' listing statuses do not match
			if(temp[1] == "wanted" && stoi(temp[2]) >= available[i].price){ // If person who wants item will pay greater than or equal to "for sale" price...
				cout << temp[0] << " " << available[i].price << endl;
				deleter(available, i); // ... then the item is sold and the match is removed from the array.
				return true; // returns true if the match was deleted from the array
			}
			else if(temp[1] == "for sale" && available[i].price >= stoi(temp[2])){
				cout << temp[0] << " " << temp[2] << endl;
				deleter(available, i);
				return true;
			}
		}
	}
return false;
}


int main(int argc, char* argv[]){
	
	string temp[3]; // temporary string array to hold item's type, listing status and price.
	int count, count2 = 0; // "count" keeps track of total iterations, while "count2" keeps track of the size of the "available" array.
	string line;
	fstream myfile;
	myfile.open(argv[1]);

	if(myfile.is_open()){
		while(getline(myfile, line)){
			parse(line, temp); // After reading in a line from the .txt file, it is sorted into an array using the "parse" function.
			if(sort(temp, available, count) == false){ // If no preexisting matches were found for the new item, it gets added to the "available" array.
				available[count2].type = temp[0];
				available[count2].buyorsell = temp[1];
				available[count2].price = stoi(temp[2]);
				count2++; // Keeps track of how many items are in the "avaiable" array
			}
			else{
				count2 = count2 - 1; // Executes only if item match was found. Count2 decreases by 1 because preexisting match got deleted from the array.
			}

		count++;
		}
	cout << "#\n";
	for(int i = 0; i < count2; i++){ // Prints the remaining items from the "avaiable" array
		cout << available[i].type << ", " << available[i].buyorsell << ", " << available[i].price << endl; 
		}
	cout << "#\n";
	
	myfile.close();
	}
return 0;
}