/*
John Furlong
CSCI 2270
Assignment 4
July 8 2018
*/
#include "MovieTree.hpp"
#include <iostream>
using namespace std;

MovieTree::MovieTree(){
	root = NULL;
}

MovieTree::~MovieTree(){
	DeleteAll(root); // BST gets deleted along w linked list after program exits
	root = NULL;
}

void MovieTree::printMovieInventory(){
	if(root == NULL){
		cout << "Movie inventory is empty." << endl;
		return;
	}
	else{
		printMovieInventory(root);
	}
}

int MovieTree::countMovieNodes(){
	int count = 0;
	countMovieNodes(root, &count);
	return count;
}

void MovieTree::deleteMovieNode(string title){
	MovieNodeBST *target = searchBST(root, title);
	MovieNodeLL *tmp2 = searchLL(target->head, title);
	if(tmp2 == NULL){
		cout << "Movie was not found" << endl;
		return;
	}
	if(target->head->title == title){ // deleting head
		MovieNodeLL *tmp = target->head;
		if(tmp->next != NULL){
			target->head = tmp->next;
		}
		else{
			target->head = tmp->next;
		}
		tmp->next = NULL;
		delete tmp;
	}
	else{ // deleting from middle or tail
		MovieNodeLL *tmp = target->head->next;
		MovieNodeLL *tmp_prev = target->head; // Variable iterating 1 index behind "tmp"
		while(tmp != NULL && tmp->title != title){ // Loops until title either found/not
			tmp_prev = tmp;
			tmp = tmp->next;
		}
		if(tmp == NULL){
			cout << "Movie not found." << endl;
		}
		else{ // title added after the previous node 
			tmp_prev->next = tmp->next;
			delete tmp;
		}
	}
	if (target->head == NULL) //No linked list
	{
		MovieNodeBST* tmp = target;
		if ((tmp->leftChild != NULL) != (tmp->rightChild != NULL)) // when we only have one child.
		{
			if (tmp->parent == NULL) //Case if we delete the root
			{
				MovieNodeBST* tmp_root = root;
				if (tmp->leftChild != NULL)
				{
					root = tmp->leftChild;
					delete tmp_root;
				}
				else
				{
					root = tmp->rightChild;
					delete tmp_root;
				}
				return;
			}
			if (tmp->leftChild != NULL) //going left
			{
				if (tmp->letter < tmp->parent->letter) // left of the parent
				{
					tmp->parent->leftChild = tmp->leftChild;
				}
				else // Right of the parent
				{
					 tmp->parent->rightChild = tmp->leftChild;
				}
				tmp->leftChild->parent = tmp->parent;
			}
			else //going right
			{
				if (tmp->letter < tmp->parent->letter)//left of the parent
				{
					tmp->parent->leftChild = tmp->rightChild;
				}
				else //right of the parent
				{
					 tmp->parent->rightChild = tmp->rightChild;
				}
				tmp->rightChild->parent = tmp->parent;

			}
		delete tmp;
		return;
		}
		else if ((tmp->leftChild == NULL) && (tmp->rightChild == NULL)) // We have no children
		{
			if (tmp->parent == NULL) // if we delete the root
			{
				delete root;
				root = NULL;
				return;
			}
			if (tmp->letter < tmp->parent->letter)
			{
				tmp->parent->leftChild = NULL;
			}
			else
			{
				tmp->parent->rightChild = NULL;
			}
		delete tmp;
		return;
		}
		else //Two children
		{ 
			MovieNodeBST* rightMin = treeMinimum(tmp->rightChild); 
			if (tmp->parent == NULL) //if we delete the root
			{
				MovieNodeBST* temp_root = root;
				root = root->rightChild;
				rightMin->leftChild = temp_root->leftChild;
				temp_root->parent = rightMin;
				root->parent = NULL;
				delete temp_root;
				return;
			}
			if (tmp->parent != NULL) //Not the root
			{  
				if (rightMin->letter != tmp->rightChild->letter) //Update rightChild pointer 
				{
					rightMin->rightChild = tmp->rightChild;
					tmp->rightChild->parent = rightMin;
					rightMin->parent->leftChild = NULL;
				}
				rightMin->parent = tmp->parent; //Update parent's pointers
				if (target->letter < tmp->parent->letter) //left child
				{ 
					tmp->parent->leftChild = rightMin;
				} 
				else //Right child
				{ 
					tmp->parent->rightChild = rightMin;
				}
				if (tmp->leftChild != NULL) //Update left pointer 
				{
					rightMin->leftChild = tmp->leftChild;
					tmp->leftChild->parent = rightMin;
				}
			}
		delete tmp;
		return;
		}
	}

}



void MovieTree::findMovie(string title){
	MovieNodeBST *letterNode = searchBST(root, title);
	if(letterNode == NULL){
		cout << "Movie not found." << endl;
	}
	else{
		MovieNodeLL *foundMovie = searchLL(letterNode->head, title);
		if(foundMovie == NULL){
			cout << "Movie was not found." << endl;
			return;
		}
		cout << "Movie Info:" << endl;
		cout << "===========" << endl;
		cout << "Ranking:" << foundMovie->ranking << endl; cout << "Title:" << foundMovie->title << endl;
		cout << "Year:" << foundMovie->year << endl;
		cout << "Quantity:" << foundMovie->quantity << endl;
	}
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity){
	char ch = title[0];
	MovieNodeBST *bstNode = new MovieNodeBST(ch);
	MovieNodeLL *addN = new MovieNodeLL(ranking, title, releaseYear, quantity);

	if(root == NULL){
		root = bstNode;
		bstNode->parent = NULL;
		bstNode->head = addN;
	}
	else{ 
		MovieNodeBST *letterNode = root;
		MovieNodeBST *parent = NULL; 
		while(letterNode != NULL){

			if(letterNode->letter == ch){ // We are at the correct BST node letter
				MovieNodeLL *head= letterNode->head;
				MovieNodeLL *prev = head;  
				if(letterNode->head == NULL){
					letterNode->head = addN;
					return; 
				}
				while(head != NULL){

					if(head->title >= addN->title)
					{
						if (letterNode->head == head){
							letterNode->head = addN;
							addN->next = head; 
							return;
						}
						break;
					}
					prev = head; 
					head = head->next;
				}
				addN->next = prev->next;
				prev->next = addN; // "prev" variable iterating 1 index behind "addN"
				return;
			}
			parent = letterNode; 
			if(letterNode->letter > ch){ // "ch" comes earlier in the alphabet
				letterNode = letterNode->leftChild;
			}
			else{	// ch should be later in the alphabet
				letterNode = letterNode->rightChild;
			}
			if (letterNode== NULL){
				letterNode = new MovieNodeBST(ch);
				letterNode->parent = parent;
				if(ch > parent->letter){
					parent->rightChild = letterNode; 
				}
				else{
					parent->leftChild = letterNode;
				}
			}
		}
	}
}


void MovieTree::rentMovie(string title){
	MovieNodeBST *letterNode = searchBST(root, title);
	MovieNodeLL *foundMovie = searchLL(letterNode->head, title);
	if(foundMovie->title != title){
		cout << "Movie was not found" << endl;
	}
	else{
		foundMovie->quantity--;
		if(foundMovie->quantity == 0){
			deleteMovieNode(title); // Movie deleted from inventory if stock quantity = 0.
		}
		//If movie is in stock
		cout << "Movie has been rented." << endl;
		cout << "Movie Info:" << endl;
		cout << "===========" << endl;
		cout << "Ranking:" << foundMovie->ranking << endl; cout << "Title:" << foundMovie->title << endl;
		cout << "Year:" << foundMovie->year << endl;
		cout << "Quantity:" << foundMovie->quantity << endl;
	}
}

// Private methods

void MovieTree::DeleteAll(MovieNodeBST *node){
	if(node == NULL){
		return;
	}
	else{
		MovieNodeLL *temp = node->head;
		MovieNodeLL *temp_next = temp->next;
		while(temp != NULL){
			temp_next = temp->next;
			cout << "Deleting: " << temp->title << endl; // Deletes each movie in LL as well as BST node
			delete temp;
			temp = temp_next;
		}
		delete node;
		DeleteAll(node->leftChild);
		DeleteAll(node->rightChild);
	}
} 

void MovieTree::printMovieInventory(MovieNodeBST *node){
	if(node == NULL){
		return;
	}
	else{
		printMovieInventory(node->leftChild);
		MovieNodeLL *tmp = node->head; // Start indexing thru LL starting at head
		while(tmp != NULL){
			cout << "Movie: " << tmp->title << " " << tmp->quantity << endl;
			tmp = tmp->next;
		}
		printMovieInventory(node->rightChild);
	}
}

void MovieTree::countMovieNodes(MovieNodeBST *node, int *c){
	if(node->leftChild != NULL){
		countMovieNodes(node->leftChild, c); // Use of recursion to iterate node
	}
	if(node->rightChild != NULL){
		countMovieNodes(node->rightChild, c);
	}
	MovieNodeLL *tmp = node->head;
	while(tmp != NULL){
		(*c)++;
		tmp = tmp->next;
	}
}

MovieNodeBST* MovieTree::searchBST(MovieNodeBST *node, string title){
	if (node == NULL) { 
		return NULL;
	}
	if (title[0] == node->letter) {
		return node;
	} else if (title[0] < node->letter){ // going left
		return searchBST(node->leftChild, title); // Uses itself recursively to iterate node
	} 
	else if (title[0] > node->letter){ // going right
		return searchBST(node->rightChild, title);
	}
	return NULL;
}

MovieNodeLL* MovieTree::searchLL(MovieNodeLL *head, string title){
	MovieNodeLL *tmp = head;
	if(tmp == NULL){
		return NULL;
	}
	while(tmp != NULL){
		if(tmp->title == title){
			return tmp;	// node that gets returned will either match title or return NULL
		}
		tmp = tmp->next;
	}
	return NULL;
}

MovieNodeBST* MovieTree::treeMinimum(MovieNodeBST *node){
	while (node->leftChild != NULL) { // there is a smaller value
		node = node->leftChild;
	}
	return node;
}














