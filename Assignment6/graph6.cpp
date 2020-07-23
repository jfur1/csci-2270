/*
John Furlong
CSCI 2270
Assignment 6 Part 1
July 20, 2018
*/

#include "graph6.h"
using namespace std;

void Graph::addEdge(string v1, string v2, int weight){ 
	
	for(int i = 0; i < vertices.size(); i++){

		if(vertices[i].name == v1){ // found v1

			for(int y = 0; y < vertices.size(); y++){

				if(vertices[y].name == v2 && i != y){ // found v2
					adjVertex av; // New adjVertex struct created 
					av.v = &vertices[y];
					av.weight = weight;
					vertices[i].adj.push_back(av);
				} 
			}
		}
	}
}

void Graph::addVertex(string name){
	
	for(int i = 0; i < vertices.size(); i++){
		if(name == vertices[i].name){
			cout << "Already there." << endl;
			return;
		}
	}
	vertex v;
	v.name = name;
	vertices.push_back(v); // New vertex added to vector if not already preexisting
}

int Graph::isAdjacent(string v1, string v2){
	for(int i = 0; i < vertices.size(); i++){

		if(vertices[i].name == v1){

			for(int j = 0; j < vertices[i].adj.size(); j++){

				if(vertices[i].adj[j].v->name == v2){
					
					return 1;
				}
			}
		}
	}
	return 0;
}

void Graph::displayEdges(){
	for(int i = 0; i < vertices.size(); i++){
		
		cout << vertices[i].name << "-->";
		
		for(int j = 0; j < vertices[i].adj.size(); j++){
			
			cout << vertices[i].adj[j].v->name;
			
			if (j != vertices[i].adj.size()-1){ // More adjacent cities
				
				cout<<"***";
			}
		}
		cout << "\n";
 	}
}


