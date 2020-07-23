/*
John Furlong
CSCI 2270
Assignment 2
June 22, 2018
*/

#include <iostream>
#include <fstream>
using namespace std;

struct wordItem{
	string word;
 	int count;
};

void getStopWords(string filename, string ignoreWords[]){ // Function retrieves the list of words to ignore
	string line;
	int i = 0;
	ifstream ignore;
	ignore.open(filename);
	if(ignore.is_open()){
		while(getline(ignore, line)){
			if(line.substr(line.length()-1, line.length()) == "\n" || line.substr(line.length()-1, line.length()) == "\r")
				line = line.substr(0, line.length()-1); //Cuts the "\n" or "\r" off the end of the ignore word
			ignoreWords[i] = line;
			i++;
		}
	}
	else{
		cout << "file did not open correctly.\n";
	}
ignore.close();
}

bool isStopWord(string word, string ignoreWords[]){ // Checks to see if a given word is in the list of words to ignore.
	for(int i = 0; i < 50; i++){
		if(ignoreWords[i] == word){
			return true;	// returns true if the given word can be ignored
		}
	}
return false;	// returns false if given word is a non-common word.
}

int getTotalNumberNonStopWords(wordItem list[], int length){ // Function returns the total number of non-ignore words
	int num = 0;
	for(int i = 0; i < length; i++){
		num = num + list[i].count;
	}
	return num;
}

void arraySort(wordItem list[], int length){	// sorts list of words in descending order based on their counts
	wordItem temp;
	for(int i = 0; i < length; i++){
		for(int j = i+1; j < length; j++){
			if(list[i].count < list[j].count){
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
}

void printTopN(wordItem wordItemList[], int topN){ // Returns the top number of words and their counts 
	for(int i = 0; i < topN; i++){
		cout << wordItemList[i].count << " - " << wordItemList[i].word << endl;
	}
}

int main(int argc, char* argv[]){
	string word, ignoreWords[50];
	int uniqueCount = 0;
	int doubleCount = 0;
	int listSize = 100;
	wordItem * list = new wordItem[100]; // Dynamically allocated array for non common words
	
	ifstream myfile;
	myfile.open(argv[2]); // third command line argument opens "HungerGames_edit.txt"
	string ignoreTxt = argv[3]; // fourth command line argument opens "ignoreWords.txt"
	getStopWords(ignoreTxt, ignoreWords); 
	
	while(getline(myfile, word, ' ')){ // gets line wherever there is a space
		if(word.substr(0,1) == "\n") // if word begins with a "\n" newline 
    	{
      		word  = word.substr(1, word.length()); // delete the newline ("\n") from the word
   		}
   		if(word != ""){ // Cannot be an empty string
			if(!isStopWord(word, ignoreWords)){ // given word is not in list of words to ignore
				for(int i = 0; i < listSize; i++){
					if(list[i].word == word){ // If word being evaluated already exists in the list of non common words
              			list[i].count++; // word does not get added, but count for that word increases.
              			break;
           			}
					if(list[i].word == ""){ // index reaches the first empty spot in the list of non common words
						list[i].word = word; // word gets added to the list at the first empty index
						list[i].count = 1; // count = 1 because this is the first time this word has been encountered
						uniqueCount++; // new unqiue word, so count is incremented
						break;
					}
					if(i == listSize-1){ // index has reached the end of the list (array is full)
						wordItem *ptr = new wordItem[listSize*2]; //pointer pointing to new array of "wordItem" structs with double the current list size.
						for(int i = 0; i < listSize; i++){
							ptr[i] = list[i]; // copying data from old array to new array
						}
						doubleCount = doubleCount + 1; // array doubling count increments
						delete[] list; // old array gets deleted
						list = ptr; // new array of structs pointed to by "ptr" copied to "list" so program can continue using "list" variable
						ptr = NULL; //ptr set to point to null
						listSize = listSize * 2; // array size doubled.
					}
				}
			}
		}

	}
	arraySort(list, listSize);
	int topN = stoi(argv[1]); // 2nd command line argument tells function how many top words to print
	printTopN(list, topN);
cout << "#" <<endl;
cout << "Array doubled: " << doubleCount <<endl;
cout << "#" <<endl;
cout << "Unique non-common words: " << uniqueCount << endl;
cout << "#" <<endl;
cout << "Total non-common words: " << getTotalNumberNonStopWords(list, listSize) << endl;
myfile.close();

return 0;
}