/*
John Furlong
CSCI 2270
July 27th 2018
*/
#include "graph6_2.hpp"
#include <queue>
#include <stack>
using namespace std;

Graph::Graph(){}

Graph::~Graph(){}

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
	v.districtID = -1;
	vertices.push_back(v); // New vertex added to vector if not already preexisting
}

void Graph::displayEdges(){
	for(int i = 0; i < vertices.size(); i++){
		
		cout<< vertices[i].districtID << ":" << vertices[i].name << "-->";
		
		for(int j = 0; j < vertices[i].adj.size(); j++){
			
			cout << vertices[i].adj[j].v->name;
			
			if (j != vertices[i].adj.size()-1){ // More adjacent cities
				
				cout<<"***";
			}
		}
		cout << "\n";
 	}
}

void Graph::assignDistricts(){
	int count = 1;

	for(int i = 0; i < vertices.size(); i++){

		if(vertices[i].districtID == -1){

			DFSLabel(vertices[i].name, count);
			count++;
		}
	}
}

// Breadth First Search
void Graph::shortestPath(string startingCity, string endingCity){
	// Reset
	for(int i = 0; i < vertices.size(); i++){
		vertices[i].parent = NULL;
		vertices[i].visited = false;
	}

	// Find the start and end node
	vertex* start = findVertex(startingCity);
	vertex* end = findVertex(endingCity);

	if(start == NULL || end == NULL){
		cout << "One or more cities doesn't exist" << endl;
		return;
	}

	if(start->districtID == -1){
		cout << "Please identify the districts before checking distances" << endl;
		return;
	}

	// Cities in different distritcs
	if(start->districtID != end->districtID){
		cout << "No safe path between cities" << endl;
		return;
	}

	// Traversal
	start->visited = true;
	start->parent = NULL;
	queue<vertex*> q;
	q.push(start);

	while(!q.empty()){
		vertex* curv = q.front();
		q.pop();
		for(int i = 0; i < curv->adj.size(); i++){
			if(curv->adj[i].v->visited == false){
				curv->adj[i].v->visited = true;
				curv->adj[i].v->parent = curv;
				q.push(curv->adj[i].v);
			}
		}
	}


	stack<string> reverse_path;
	vertex* curv = end;
	while(curv != NULL){
		reverse_path.push(curv->name);
		curv = curv->parent; // Iterates starting at Ending City up through the parent nodes
	}

	int edges = reverse_path.size()-1;
	cout << edges << ", ";
	while(!reverse_path.empty()){
		cout << reverse_path.top();
		reverse_path.pop();
		if(!reverse_path.empty()){
			cout << ", ";
		}
	}
	cout << endl;
}

vertex* Graph::findVertex(string name){
	for(int i = 0; i < vertices.size();i++){
		if(vertices[i].name == name){
			return &vertices[i];
		}
	}
return NULL;
}

//Depth First Search
void Graph::DFSLabel(string startingCity, int distID){
		//Reset
	for(int i = 0; i < vertices.size(); i++){
		vertices[i].parent = NULL;
		vertices[i].visited = false;
	}

	// Find the start node
	vertex* start = findVertex(startingCity);

	if(start == NULL){
		cout << "Not in graph\n";
		return;
	}

	// Traversal
	start->visited = true;
	start->districtID = distID;
	stack<vertex*> q;
	q.push(start);

	while(!q.empty()){

		vertex* curv = q.top();
		q.pop();

		for(int i = 0; i < curv->adj.size(); i++){

			if(curv->adj[i].v->visited == false){

				curv->adj[i].v->visited = true;
				curv->adj[i].v->districtID = distID;
				q.push(curv->adj[i].v);
			}
		}
	}
}

// Dijksrta's Algorithm
void Graph::shortestWeightedPath(string startingCity, string endingCity){
	// Reset
	for(int i = 0; i < vertices.size(); i++){
		vertices[i].parent = NULL;
		vertices[i].visited = false;
	}

	// Find the start and end node
	vertex* start = findVertex(startingCity);
	vertex* end = findVertex(endingCity);

	if(start == NULL || end == NULL){
		cout << "One or more cities doesn't exist" << endl;
		return;
	}

	if(start->districtID == -1){
		cout << "Please identify the districts before checking distances" << endl;
		return;
	}

	if(start->districtID != end->districtID){
		cout << "No safe path between cities" << endl;
		return;
	}

	// Mark the start as solved with distance 0 startV.solved = true	
	start->visited = true;
	start->weightedDistance = 0;
	// Store list of solved vertices solved = {startV}
	vector <vertex*> solved;
	//add start to vector
	solved.push_back(start);

	while(!end->visited){
		int minDistance = 100000;
		vertex * solvedV = NULL;
		vertex * parent = NULL;

		for(int i = 0; i < solved.size(); i++){
			vertex *s = solved[i];

			for(int j = 0; j < s->adj.size(); j++){

				if(!s->adj[j].v->visited){
					int dist = s->weightedDistance + s->adj[j].weight;
					if(dist < minDistance){
						solvedV = s->adj[j].v;
						minDistance = dist;
						parent = s;
					}
				}
			}
		}
		solvedV->weightedDistance = minDistance;
		solvedV->parent = parent;
		solvedV->visited = true;
		solved.push_back(solvedV);
	}



	stack<string> reverse_path;
	vertex* curv = end;
	while(curv != NULL){
		reverse_path.push(curv->name);
		curv = curv->parent;
	}

	cout << end->weightedDistance << ", ";
	while(!reverse_path.empty()){
		cout << reverse_path.top();
		reverse_path.pop();
		if(!reverse_path.empty()){
			cout << ", ";
		}
	}
	cout << endl;
}








